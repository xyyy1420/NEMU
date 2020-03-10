#include <monitor/difftest.h>

static inline void difftest_skip_delay_slot(void) {
  difftest_skip_dut(2, 1);
}

static inline make_EHelper(j) {
  difftest_skip_delay_slot();

  rtl_j(s, s->jmp_pc);

  print_asm_template1(j);
}

static inline make_EHelper(jal) {
  difftest_skip_delay_slot();

  rtl_addi(s, s0, &cpu.pc, 8);
  rtl_sr(s, 31, s0, 4);
  rtl_j(s, s->jmp_pc);

  print_asm_template1(jal);
}

static inline make_EHelper(jr) {
  difftest_skip_delay_slot();

  rtl_jr(s, dsrc1);

  print_asm_template2(jr);
}

static inline make_EHelper(jalr) {
  difftest_skip_delay_slot();

  rtl_addi(s, s0, &cpu.pc, 8);
  rtl_sr(s, id_dest->reg, s0, 4);
  rtl_jr(s, dsrc1);

  print_asm_template2(jalr);
}

static inline make_EHelper(bne) {
  difftest_skip_delay_slot();

  rtl_jrelop(s, RELOP_NE, dsrc1, dsrc2, s->jmp_pc);

  print_asm_template3(bne);
}

static inline make_EHelper(beq) {
  difftest_skip_delay_slot();

  rtl_jrelop(s, RELOP_EQ, dsrc1, dsrc2, s->jmp_pc);

  print_asm_template3(beq);
}

static inline make_EHelper(blez) {
  difftest_skip_delay_slot();

  rtl_jrelop(s, RELOP_LE, dsrc1, dsrc2, s->jmp_pc);

  print_asm_template3(blez);
}

static inline make_EHelper(bltz) {
  difftest_skip_delay_slot();

  rtl_li(s, s0, 0);
  rtl_jrelop(s, RELOP_LT, dsrc1, s0, s->jmp_pc);

  print_asm_template3(bltz);
}

static inline make_EHelper(bgtz) {
  difftest_skip_delay_slot();

  rtl_jrelop(s, RELOP_GT, dsrc1, dsrc2, s->jmp_pc);

  print_asm_template3(blez);
}

static inline make_EHelper(bgez) {
  difftest_skip_delay_slot();

  rtl_li(s, s0, 0);
  rtl_jrelop(s, RELOP_GE, dsrc1, s0, s->jmp_pc);

  print_asm_template3(bltz);
}