#include "user.h"
#include <stdlib.h>

#define ROUNDUP(a, sz)      ((((uintptr_t)a) + (sz) - 1) & ~((sz) - 1))
#define ROUNDDOWN(a, sz)    ((((uintptr_t)a)) & ~((sz) - 1))

typedef struct vma_t {
  void *addr;
  size_t length;
  int prot;
  int flags;
  int fd;
  off_t offset;
  struct vma_t *next;
  struct vma_t *prev;
} vma_t;

static vma_t vma_list = { };
static vma_t *dyn_start;

#define vma_foreach(p) for (p = vma_list.next; !vma_list_is_end(p); p = p->next)

static inline void vma_list_add_after(vma_t *left, vma_t *new) {
  vma_t *right = left->next;
  new->next = right;
  new->prev = left;
  left->next = new;
  right->prev = new;
}

static inline bool vma_list_is_end(vma_t *p) {
  return (p == &vma_list);
}

static inline bool vma_list_is_empty() {
  return vma_list_is_end(vma_list.next);
}

static inline vma_t* vma_list_find_fix_area(void *addr, size_t length) {
  vma_t *p;
  vma_foreach(p) {
    if (p->addr == addr && p->length == length) return p;
  }
  return NULL;
}

static inline vma_t* vma_list_new_fix_area(void *addr, size_t length) {
  vma_t *candidate = NULL;
  vma_t *p;
  vma_foreach(p) {
    void *l = p->addr;
    void *r = p->addr + p->length;
    if (!((addr + length <= l) || (addr >= r))) {
      // overlap
      return NULL;
    }
    vma_t *right = p->next;
    if (p->addr < addr && addr < right->addr) { candidate = p; }
  }
  assert(candidate != NULL);
  return candidate;
}

// return the vma_t whose right is suitable
static inline vma_t* vma_list_new_dyn_area(size_t length) {
  vma_t *p = dyn_start;
  for (; !vma_list_is_end(p); p = p->next) {
    vma_t *right = p->next;
    size_t free = right->addr - p->addr + p->length;
    if (free >= length) return p;
  }
  assert(0);
  return NULL;
}

static inline vma_t* vma_new(void *addr, size_t length, int prot,
    int flags, int fd, off_t offset) {
  vma_t *vma = malloc(sizeof(vma_t));
  assert(vma);
  *vma = (vma_t) { .addr = addr, .length = length, .prot = prot,
    .flags = flags, .fd = fd, .offset = offset };
  return vma;
}

void init_mmap() {
  vma_t *p = &vma_list;
  p->next = p->prev = p;

  vma_t *zero = vma_new(NULL, 0ul, 0, 0, -1, 0);
  vma_list_add_after(p, zero);

  dyn_start = vma_new((void *)0x80000000ul, 0ul, 0, 0, -1, 0);
  vma_list_add_after(zero, dyn_start);

  vma_t *kernel = vma_new((void *)0xc0000000ul, 0x40000000ul, 0, 0, -1, 0);
  vma_list_add_after(dyn_start, kernel);
}

void *user_mmap(void *addr, size_t length, int prot,
    int flags, int fd, off_t offset) {
  vma_t *left = NULL;
  length = ROUNDUP(length, 4096);
  if (flags & MAP_FIXED) {
    left = vma_list_new_fix_area(addr, length);
    assert(left != NULL);
  } else {
    left = vma_list_new_dyn_area(length);
    addr = left->addr + left->length;
    flags |= MAP_FIXED;
  }
  vma_t *vma = vma_new(addr, length, prot, flags, fd, offset);
  vma_list_add_after(left, vma);

  void *ret = mmap(addr, length, prot, flags, fd, offset);
  if (flags & MAP_FIXED) { assert(ret == addr); }
  return ret;
}

int user_munmap(void *addr, size_t length) {
  vma_t *p = vma_list_find_fix_area(addr, length);
  assert(p != NULL);
  vma_t *prev = p->prev;
  vma_t *next = p->next;
  prev->next = next;
  next->prev = prev;

  int ret = munmap(addr, length);
  assert(ret == 0);
  free(p);
  return ret;
}
