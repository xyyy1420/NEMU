/***************************************************************************************
* Copyright (c) 2020-2022 Institute of Computing Technology, Chinese Academy of Sciences
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifdef CONFIG_RVV

void vp_set_dirty();

// vector
static inline def_DHelper(OP_V) { // 10_101, same to R
  decode_op_r(s, id_src1, s->isa.instr.r.rs1, true);
  decode_op_r(s, id_src2, s->isa.instr.r.rs2, true);
  decode_op_r(s, id_dest, s->isa.instr.r.rd, false);
  // decode_op_r(id_dest, decinfo.isa.instr.v_vd, false);
}

static inline def_DHelper(vsetvl) {
  //vp_set_dirty();
  uint8_t op = s->isa.instr.v_opv4.v_bigbit;
  switch (op){
    case 0b00:
    case 0b01:
        rtl_li(s, &id_src2->val, s->isa.instr.v_opv2.v_zimm);
        print_Dop(id_src2->str, OP_STR_SIZE, "%d", s->isa.instr.v_opv2.v_zimm);
        break;
    case 0b10:
        rtl_lr(s, &id_src2->val, id_src2->reg, 4);
        print_Dop(id_src2->str, OP_STR_SIZE, "%ld", id_src2->val);
        break;
    case 0b11:
        rtl_li(s, &id_src1->val, s->isa.instr.v_opv4.v_zimm5);
        rtl_li(s, &id_src2->val, s->isa.instr.v_opv4.v_zimm);
        print_Dop(id_src1->str, OP_STR_SIZE, "%d", s->isa.instr.v_opv4.v_zimm5);
        print_Dop(id_src2->str, OP_STR_SIZE, "%d", s->isa.instr.v_opv4.v_zimm);
        break;
  }
}

def_THelper(vrwxunary0_dispatch) {
    def_INSTR_TAB("?????? ? 00000 ????? ??? ????? ????? ??", vmvsx);
    def_INSTR_TAB("?????? ? ????? 00000 ??? ????? ????? ??", vmvxs);
    def_INSTR_TAB("?????? ? ????? 10000 ??? ????? ????? ??", vcpop);
    def_INSTR_TAB("?????? ? ????? 10001 ??? ????? ????? ??", vfirst);

    return EXEC_ID_inv;
}

def_THelper(vxunary0_dispatch) {
    s->src_vmode = SRC_VI;

    def_INSTR_TAB("?????? ? ????? 00010 ??? ????? ????? ??", vzextvf8);
    def_INSTR_TAB("?????? ? ????? 00011 ??? ????? ????? ??", vsextvf8);
    def_INSTR_TAB("?????? ? ????? 00100 ??? ????? ????? ??", vzextvf4);
    def_INSTR_TAB("?????? ? ????? 00101 ??? ????? ????? ??", vsextvf4);
    def_INSTR_TAB("?????? ? ????? 00110 ??? ????? ????? ??", vzextvf2);
    def_INSTR_TAB("?????? ? ????? 00111 ??? ????? ????? ??", vsextvf2);

    return EXEC_ID_inv;
}

def_THelper(vmunary0_dispatch) {
    def_INSTR_TAB("?????? ? ????? 00001 ??? ????? ????? ??", vmsbf);
    def_INSTR_TAB("?????? ? ????? 00010 ??? ????? ????? ??", vmsof);
    def_INSTR_TAB("?????? ? ????? 00011 ??? ????? ????? ??", vmsif);
    def_INSTR_TAB("?????? ? ????? 10000 ??? ????? ????? ??", viota);
    def_INSTR_TAB("?????? ? ????? 10001 ??? ????? ????? ??", vid);

    return EXEC_ID_inv;
}

def_THelper(vwfunary0_dispatch) {
    def_INSTR_TAB("?????? ? ????? 00000 ??? ????? ????? ??", vfmvfs);

    return EXEC_ID_inv;
}

def_THelper(vrfunary0_dispatch) {
    def_INSTR_TAB("?????? ? 00000 ????? ??? ????? ????? ??", vfmvsf);

    return EXEC_ID_inv;
}

def_THelper(vfunary0_dispatch) {
    def_INSTR_TAB("?????? ? ????? 00000 ??? ????? ????? ??", vfcvt_xufv);
    def_INSTR_TAB("?????? ? ????? 00001 ??? ????? ????? ??", vfcvt_xfv);
    def_INSTR_TAB("?????? ? ????? 00010 ??? ????? ????? ??", vfcvt_fxuv);
    def_INSTR_TAB("?????? ? ????? 00011 ??? ????? ????? ??", vfcvt_fxv);
    def_INSTR_TAB("?????? ? ????? 00100 ??? ????? ????? ??", vfcvt_rtz_xufv);
    def_INSTR_TAB("?????? ? ????? 00101 ??? ????? ????? ??", vfcvt_rtz_xfv);
    def_INSTR_TAB("?????? ? ????? 01000 ??? ????? ????? ??", vfwcvt_xufv);
    def_INSTR_TAB("?????? ? ????? 01001 ??? ????? ????? ??", vfwcvt_xfv);
    def_INSTR_TAB("?????? ? ????? 01010 ??? ????? ????? ??", vfwcvt_fxuv);
    def_INSTR_TAB("?????? ? ????? 01011 ??? ????? ????? ??", vfwcvt_fxv);
    def_INSTR_TAB("?????? ? ????? 01100 ??? ????? ????? ??", vfwcvt_ffv);
    def_INSTR_TAB("?????? ? ????? 01110 ??? ????? ????? ??", vfwcvt_rtz_xufv);
    def_INSTR_TAB("?????? ? ????? 01111 ??? ????? ????? ??", vfwcvt_rtz_xfv);
    def_INSTR_TAB("?????? ? ????? 10000 ??? ????? ????? ??", vfncvt_xufw);
    def_INSTR_TAB("?????? ? ????? 10001 ??? ????? ????? ??", vfncvt_xfw);
    def_INSTR_TAB("?????? ? ????? 10010 ??? ????? ????? ??", vfncvt_fxuw);
    def_INSTR_TAB("?????? ? ????? 10011 ??? ????? ????? ??", vfncvt_fxw);
    def_INSTR_TAB("?????? ? ????? 10100 ??? ????? ????? ??", vfncvt_ffw);
    def_INSTR_TAB("?????? ? ????? 10110 ??? ????? ????? ??", vfncvt_rod_ffw);
    def_INSTR_TAB("?????? ? ????? 10111 ??? ????? ????? ??", vfncvt_rtz_xufw);
    def_INSTR_TAB("?????? ? ????? 11000 ??? ????? ????? ??", vfncvt_rtz_xfw);

    return EXEC_ID_inv;
}

def_THelper(vfunary1_dispatch) {
    s->src_vmode = SRC_V;
    
    def_INSTR_TAB("?????? ? ????? 00000 ??? ????? ????? ??", vfsqrt_v);
    def_INSTR_TAB("?????? ? ????? 00100 ??? ????? ????? ??", vfrsqrt7_v);
    def_INSTR_TAB("?????? ? ????? 00101 ??? ????? ????? ??", vfrec7_v);
    def_INSTR_TAB("?????? ? ????? 10000 ??? ????? ????? ??", vfclass_v);

    return EXEC_ID_inv;
}

//vector
def_THelper(vopivv) {
  if (!vp_enable()) {
    return EXEC_ID_inv;
  }
  def_INSTR_TAB("000000 ? ????? ????? ??? ????? ????? ??", vadd);
  def_INSTR_TAB("000010 ? ????? ????? ??? ????? ????? ??", vsub);
  def_INSTR_TAB("000011 ? ????? ????? ??? ????? ????? ??", vrsub);
  def_INSTR_TAB("000100 ? ????? ????? ??? ????? ????? ??", vminu);
  def_INSTR_TAB("000101 ? ????? ????? ??? ????? ????? ??", vmin);
  def_INSTR_TAB("000110 ? ????? ????? ??? ????? ????? ??", vmaxu);
  def_INSTR_TAB("000111 ? ????? ????? ??? ????? ????? ??", vmax);
  def_INSTR_TAB("001001 ? ????? ????? ??? ????? ????? ??", vand);
  def_INSTR_TAB("001010 ? ????? ????? ??? ????? ????? ??", vor);
  def_INSTR_TAB("001011 ? ????? ????? ??? ????? ????? ??", vxor);
  def_INSTR_TAB("001100 ? ????? ????? ??? ????? ????? ??", vrgather);
  def_INSTR_TAB("001110 ? ????? ????? ??? ????? ????? ??", vrgatherei16);
  def_INSTR_TAB("001111 ? ????? ????? ??? ????? ????? ??", vslidedown);
  def_INSTR_TAB("010000 ? ????? ????? ??? ????? ????? ??", vadc);
  def_INSTR_TAB("010001 ? ????? ????? ??? ????? ????? ??", vmadc);
  def_INSTR_TAB("010010 ? ????? ????? ??? ????? ????? ??", vsbc);
  def_INSTR_TAB("010011 ? ????? ????? ??? ????? ????? ??", vmsbc);
  def_INSTR_TAB("010111 ? ????? ????? ??? ????? ????? ??", vmerge);
  def_INSTR_TAB("011000 ? ????? ????? ??? ????? ????? ??", vmseq);
  def_INSTR_TAB("011001 ? ????? ????? ??? ????? ????? ??", vmsne);
  def_INSTR_TAB("011010 ? ????? ????? ??? ????? ????? ??", vmsltu);
  def_INSTR_TAB("011011 ? ????? ????? ??? ????? ????? ??", vmslt);
  def_INSTR_TAB("011100 ? ????? ????? ??? ????? ????? ??", vmsleu);
  def_INSTR_TAB("011101 ? ????? ????? ??? ????? ????? ??", vmsle);
  def_INSTR_TAB("011110 ? ????? ????? ??? ????? ????? ??", vmsgtu);
  def_INSTR_TAB("011111 ? ????? ????? ??? ????? ????? ??", vmsgt);
  def_INSTR_TAB("100000 ? ????? ????? ??? ????? ????? ??", vsaddu);
  def_INSTR_TAB("100001 ? ????? ????? ??? ????? ????? ??", vsadd);
  def_INSTR_TAB("100010 ? ????? ????? ??? ????? ????? ??", vssubu);
  def_INSTR_TAB("100011 ? ????? ????? ??? ????? ????? ??", vssub);
  def_INSTR_TAB("100101 ? ????? ????? ??? ????? ????? ??", vsll);
  def_INSTR_TAB("100111 ? ????? ????? ??? ????? ????? ??", vsmul);
  def_INSTR_TAB("101000 ? ????? ????? ??? ????? ????? ??", vsrl);
  def_INSTR_TAB("101001 ? ????? ????? ??? ????? ????? ??", vsra);
  def_INSTR_TAB("101011 ? ????? ????? ??? ????? ????? ??", vssra);
  def_INSTR_TAB("101100 ? ????? ????? ??? ????? ????? ??", vnsrl);
  def_INSTR_TAB("101101 ? ????? ????? ??? ????? ????? ??", vnsra);
  def_INSTR_TAB("101110 ? ????? ????? ??? ????? ????? ??", vnclipu);
  def_INSTR_TAB("101111 ? ????? ????? ??? ????? ????? ??", vnclip);
  def_INSTR_TAB("101010 ? ????? ????? ??? ????? ????? ??", vssrl);
  def_INSTR_TAB("110000 ? ????? ????? ??? ????? ????? ??", vwredsumu);
  def_INSTR_TAB("110001 ? ????? ????? ??? ????? ????? ??", vwredsum);
  def_INSTR_TAB("111000 ? ????? ????? ??? ????? ????? ??", vdotu);
  def_INSTR_TAB("111001 ? ????? ????? ??? ????? ????? ??", vdot);
  def_INSTR_TAB("111100 ? ????? ????? ??? ????? ????? ??", vwsmaccu);
  def_INSTR_TAB("111101 ? ????? ????? ??? ????? ????? ??", vwsmacc);
  def_INSTR_TAB("111110 ? ????? ????? ??? ????? ????? ??", vwsmaccsu);
  def_INSTR_TAB("111111 ? ????? ????? ??? ????? ????? ??", vwsmaccus);
  
  return EXEC_ID_inv;
  //longjmp_raise_intr(EX_II);
}

def_THelper(vopivx) {
  if (!vp_enable()) {
    return EXEC_ID_inv;
  }
  def_INSTR_TAB("000000 ? ????? ????? ??? ????? ????? ??", vadd);
  def_INSTR_TAB("000010 ? ????? ????? ??? ????? ????? ??", vsub);
  def_INSTR_TAB("000011 ? ????? ????? ??? ????? ????? ??", vrsub);
  def_INSTR_TAB("000100 ? ????? ????? ??? ????? ????? ??", vminu);
  def_INSTR_TAB("000101 ? ????? ????? ??? ????? ????? ??", vmin);
  def_INSTR_TAB("000110 ? ????? ????? ??? ????? ????? ??", vmaxu);
  def_INSTR_TAB("000111 ? ????? ????? ??? ????? ????? ??", vmax);
  def_INSTR_TAB("001001 ? ????? ????? ??? ????? ????? ??", vand);
  def_INSTR_TAB("001010 ? ????? ????? ??? ????? ????? ??", vor);
  def_INSTR_TAB("001011 ? ????? ????? ??? ????? ????? ??", vxor);
  def_INSTR_TAB("001100 ? ????? ????? ??? ????? ????? ??", vrgather);
  def_INSTR_TAB("001110 ? ????? ????? ??? ????? ????? ??", vslideup);
  def_INSTR_TAB("001111 ? ????? ????? ??? ????? ????? ??", vslidedown);
  def_INSTR_TAB("010000 ? ????? ????? ??? ????? ????? ??", vadc);
  def_INSTR_TAB("010001 ? ????? ????? ??? ????? ????? ??", vmadc);
  def_INSTR_TAB("010010 ? ????? ????? ??? ????? ????? ??", vsbc);
  def_INSTR_TAB("010011 ? ????? ????? ??? ????? ????? ??", vmsbc);
  def_INSTR_TAB("010111 ? ????? ????? ??? ????? ????? ??", vmerge);
  def_INSTR_TAB("011000 ? ????? ????? ??? ????? ????? ??", vmseq);
  def_INSTR_TAB("011001 ? ????? ????? ??? ????? ????? ??", vmsne);
  def_INSTR_TAB("011010 ? ????? ????? ??? ????? ????? ??", vmsltu);
  def_INSTR_TAB("011011 ? ????? ????? ??? ????? ????? ??", vmslt);
  def_INSTR_TAB("011100 ? ????? ????? ??? ????? ????? ??", vmsleu);
  def_INSTR_TAB("011101 ? ????? ????? ??? ????? ????? ??", vmsle);
  def_INSTR_TAB("011110 ? ????? ????? ??? ????? ????? ??", vmsgtu);
  def_INSTR_TAB("011111 ? ????? ????? ??? ????? ????? ??", vmsgt);
  def_INSTR_TAB("100000 ? ????? ????? ??? ????? ????? ??", vsaddu);
  def_INSTR_TAB("100001 ? ????? ????? ??? ????? ????? ??", vsadd);
  def_INSTR_TAB("100010 ? ????? ????? ??? ????? ????? ??", vssubu);
  def_INSTR_TAB("100011 ? ????? ????? ??? ????? ????? ??", vssub);
  def_INSTR_TAB("100101 ? ????? ????? ??? ????? ????? ??", vsll);
  def_INSTR_TAB("100111 ? ????? ????? ??? ????? ????? ??", vsmul);
  def_INSTR_TAB("101000 ? ????? ????? ??? ????? ????? ??", vsrl);
  def_INSTR_TAB("101001 ? ????? ????? ??? ????? ????? ??", vsra);
  def_INSTR_TAB("101011 ? ????? ????? ??? ????? ????? ??", vssra);
  def_INSTR_TAB("101100 ? ????? ????? ??? ????? ????? ??", vnsrl);
  def_INSTR_TAB("101101 ? ????? ????? ??? ????? ????? ??", vnsra);
  def_INSTR_TAB("101110 ? ????? ????? ??? ????? ????? ??", vnclipu);
  def_INSTR_TAB("101111 ? ????? ????? ??? ????? ????? ??", vnclip);
  def_INSTR_TAB("101010 ? ????? ????? ??? ????? ????? ??", vssrl);
  def_INSTR_TAB("110000 ? ????? ????? ??? ????? ????? ??", vwredsumu);
  def_INSTR_TAB("110001 ? ????? ????? ??? ????? ????? ??", vwredsum);
  def_INSTR_TAB("111000 ? ????? ????? ??? ????? ????? ??", vdotu);
  def_INSTR_TAB("111001 ? ????? ????? ??? ????? ????? ??", vdot);
  def_INSTR_TAB("111100 ? ????? ????? ??? ????? ????? ??", vwsmaccu);
  def_INSTR_TAB("111101 ? ????? ????? ??? ????? ????? ??", vwsmacc);
  def_INSTR_TAB("111110 ? ????? ????? ??? ????? ????? ??", vwsmaccsu);
  def_INSTR_TAB("111111 ? ????? ????? ??? ????? ????? ??", vwsmaccus);
  
  return EXEC_ID_inv;
  //longjmp_raise_intr(EX_II);
}

def_THelper(vopivi) {
  if (!vp_enable()) {
    return EXEC_ID_inv;
  }
  def_INSTR_TAB("000000 ? ????? ????? ??? ????? ????? ??", vadd);
  def_INSTR_TAB("000010 ? ????? ????? ??? ????? ????? ??", vsub);
  def_INSTR_TAB("000011 ? ????? ????? ??? ????? ????? ??", vrsub);
  def_INSTR_TAB("000100 ? ????? ????? ??? ????? ????? ??", vminu);
  def_INSTR_TAB("000101 ? ????? ????? ??? ????? ????? ??", vmin);
  def_INSTR_TAB("000110 ? ????? ????? ??? ????? ????? ??", vmaxu);
  def_INSTR_TAB("000111 ? ????? ????? ??? ????? ????? ??", vmax);
  def_INSTR_TAB("001001 ? ????? ????? ??? ????? ????? ??", vand);
  def_INSTR_TAB("001010 ? ????? ????? ??? ????? ????? ??", vor);
  def_INSTR_TAB("001011 ? ????? ????? ??? ????? ????? ??", vxor);
  def_INSTR_TAB("001100 ? ????? ????? ??? ????? ????? ??", vrgather);
  def_INSTR_TAB("001110 ? ????? ????? ??? ????? ????? ??", vslideup);
  def_INSTR_TAB("001111 ? ????? ????? ??? ????? ????? ??", vslidedown);
  def_INSTR_TAB("010000 ? ????? ????? ??? ????? ????? ??", vadc);
  def_INSTR_TAB("010001 ? ????? ????? ??? ????? ????? ??", vmadc);
  def_INSTR_TAB("010010 ? ????? ????? ??? ????? ????? ??", vsbc);
  def_INSTR_TAB("010011 ? ????? ????? ??? ????? ????? ??", vmsbc);
  def_INSTR_TAB("010111 ? ????? ????? ??? ????? ????? ??", vmerge);
  def_INSTR_TAB("011000 ? ????? ????? ??? ????? ????? ??", vmseq);
  def_INSTR_TAB("011001 ? ????? ????? ??? ????? ????? ??", vmsne);
  def_INSTR_TAB("011010 ? ????? ????? ??? ????? ????? ??", vmsltu);
  def_INSTR_TAB("011011 ? ????? ????? ??? ????? ????? ??", vmslt);
  def_INSTR_TAB("011100 ? ????? ????? ??? ????? ????? ??", vmsleu);
  def_INSTR_TAB("011101 ? ????? ????? ??? ????? ????? ??", vmsle);
  def_INSTR_TAB("011110 ? ????? ????? ??? ????? ????? ??", vmsgtu);
  def_INSTR_TAB("011111 ? ????? ????? ??? ????? ????? ??", vmsgt);
  def_INSTR_TAB("100000 ? ????? ????? ??? ????? ????? ??", vsaddu);
  def_INSTR_TAB("100001 ? ????? ????? ??? ????? ????? ??", vsadd);
  def_INSTR_TAB("100010 ? ????? ????? ??? ????? ????? ??", vssubu);
  def_INSTR_TAB("100011 ? ????? ????? ??? ????? ????? ??", vssub);
  def_INSTR_TAB("100101 ? ????? ????? ??? ????? ????? ??", vsll);
  def_INSTR_TAB("100111 ? ????? ????? ??? ????? ????? ??", vmvnr);
  def_INSTR_TAB("101000 ? ????? ????? ??? ????? ????? ??", vsrl);
  def_INSTR_TAB("101001 ? ????? ????? ??? ????? ????? ??", vsra);
  def_INSTR_TAB("101011 ? ????? ????? ??? ????? ????? ??", vssra);
  def_INSTR_TAB("101100 ? ????? ????? ??? ????? ????? ??", vnsrl);
  def_INSTR_TAB("101101 ? ????? ????? ??? ????? ????? ??", vnsra);
  def_INSTR_TAB("101110 ? ????? ????? ??? ????? ????? ??", vnclipu);
  def_INSTR_TAB("101111 ? ????? ????? ??? ????? ????? ??", vnclip);
  def_INSTR_TAB("101010 ? ????? ????? ??? ????? ????? ??", vssrl);
  def_INSTR_TAB("110000 ? ????? ????? ??? ????? ????? ??", vwredsumu);
  def_INSTR_TAB("110001 ? ????? ????? ??? ????? ????? ??", vwredsum);
  def_INSTR_TAB("111000 ? ????? ????? ??? ????? ????? ??", vdotu);
  def_INSTR_TAB("111001 ? ????? ????? ??? ????? ????? ??", vdot);
  def_INSTR_TAB("111100 ? ????? ????? ??? ????? ????? ??", vwsmaccu);
  def_INSTR_TAB("111101 ? ????? ????? ??? ????? ????? ??", vwsmacc);
  def_INSTR_TAB("111110 ? ????? ????? ??? ????? ????? ??", vwsmaccsu);
  def_INSTR_TAB("111111 ? ????? ????? ??? ????? ????? ??", vwsmaccus);
  
  return EXEC_ID_inv;
  //longjmp_raise_intr(EX_II);
}

def_THelper(vopm) {
  if (!vp_enable()) {
    return EXEC_ID_inv;
  }
  def_INSTR_TAB("000000 ? ????? ????? ??? ????? ????? ??", vredsum);
  def_INSTR_TAB("000001 ? ????? ????? ??? ????? ????? ??", vredand);
  def_INSTR_TAB("000010 ? ????? ????? ??? ????? ????? ??", vredor);
  def_INSTR_TAB("000011 ? ????? ????? ??? ????? ????? ??", vredxor);
  def_INSTR_TAB("000100 ? ????? ????? ??? ????? ????? ??", vredminu);
  def_INSTR_TAB("000101 ? ????? ????? ??? ????? ????? ??", vredmin);
  def_INSTR_TAB("000110 ? ????? ????? ??? ????? ????? ??", vredmaxu);
  def_INSTR_TAB("000111 ? ????? ????? ??? ????? ????? ??", vredmax);
  def_INSTR_TAB("001000 ? ????? ????? ??? ????? ????? ??", vaaddu);
  def_INSTR_TAB("001001 ? ????? ????? ??? ????? ????? ??", vaadd);
  def_INSTR_TAB("001010 ? ????? ????? ??? ????? ????? ??", vasubu);
  def_INSTR_TAB("001011 ? ????? ????? ??? ????? ????? ??", vasub);

  def_INSTR_TAB("001110 ? ????? ????? ??? ????? ????? ??", vslide1up);
  def_INSTR_TAB("001111 ? ????? ????? ??? ????? ????? ??", vslide1down);
  
  def_INSTR_TAB("010000 ? ????? ????? ??? ????? ????? ??", vrwxunary0_dispatch);
  def_INSTR_TAB("010010 ? ????? ????? ??? ????? ????? ??", vxunary0_dispatch);
  def_INSTR_TAB("010100 ? ????? ????? ??? ????? ????? ??", vmunary0_dispatch);
  def_INSTR_TAB("010111 ? ????? ????? ??? ????? ????? ??", vcompress);
  def_INSTR_TAB("011000 ? ????? ????? ??? ????? ????? ??", vmandnot);
  def_INSTR_TAB("011001 ? ????? ????? ??? ????? ????? ??", vmand);
  def_INSTR_TAB("011010 ? ????? ????? ??? ????? ????? ??", vmor);
  def_INSTR_TAB("011011 ? ????? ????? ??? ????? ????? ??", vmxor);
  def_INSTR_TAB("011100 ? ????? ????? ??? ????? ????? ??", vmornot);
  def_INSTR_TAB("011101 ? ????? ????? ??? ????? ????? ??", vmnand);
  def_INSTR_TAB("011110 ? ????? ????? ??? ????? ????? ??", vmnor);
  def_INSTR_TAB("011111 ? ????? ????? ??? ????? ????? ??", vmxnor);
  def_INSTR_TAB("100000 ? ????? ????? ??? ????? ????? ??", vdivu);
  def_INSTR_TAB("100001 ? ????? ????? ??? ????? ????? ??", vdiv);
  def_INSTR_TAB("100010 ? ????? ????? ??? ????? ????? ??", vremu);
  def_INSTR_TAB("100011 ? ????? ????? ??? ????? ????? ??", vrem);
  def_INSTR_TAB("100100 ? ????? ????? ??? ????? ????? ??", vmulhu);
  def_INSTR_TAB("100101 ? ????? ????? ??? ????? ????? ??", vmul);
  def_INSTR_TAB("100110 ? ????? ????? ??? ????? ????? ??", vmulhsu);
  def_INSTR_TAB("100111 ? ????? ????? ??? ????? ????? ??", vmulh);
  def_INSTR_TAB("101001 ? ????? ????? ??? ????? ????? ??", vmadd);
  def_INSTR_TAB("101011 ? ????? ????? ??? ????? ????? ??", vnmsub);
  def_INSTR_TAB("101101 ? ????? ????? ??? ????? ????? ??", vmacc);
  def_INSTR_TAB("101111 ? ????? ????? ??? ????? ????? ??", vnmsac);
  def_INSTR_TAB("110000 ? ????? ????? ??? ????? ????? ??", vwaddu);
  def_INSTR_TAB("110001 ? ????? ????? ??? ????? ????? ??", vwadd);
  def_INSTR_TAB("110010 ? ????? ????? ??? ????? ????? ??", vwsubu);
  def_INSTR_TAB("110011 ? ????? ????? ??? ????? ????? ??", vwsub);
  def_INSTR_TAB("110100 ? ????? ????? ??? ????? ????? ??", vwaddu_w);
  def_INSTR_TAB("110101 ? ????? ????? ??? ????? ????? ??", vwadd_w);
  def_INSTR_TAB("110110 ? ????? ????? ??? ????? ????? ??", vwsubu_w);
  def_INSTR_TAB("110111 ? ????? ????? ??? ????? ????? ??", vwsub_w);
  def_INSTR_TAB("111000 ? ????? ????? ??? ????? ????? ??", vwmulu);
  def_INSTR_TAB("111010 ? ????? ????? ??? ????? ????? ??", vwmulsu);
  def_INSTR_TAB("111011 ? ????? ????? ??? ????? ????? ??", vwmul);
  def_INSTR_TAB("111100 ? ????? ????? ??? ????? ????? ??", vwmaccu);
  def_INSTR_TAB("111101 ? ????? ????? ??? ????? ????? ??", vwmacc);
  def_INSTR_TAB("111110 ? ????? ????? ??? ????? ????? ??", vwmaccus);
  def_INSTR_TAB("111111 ? ????? ????? ??? ????? ????? ??", vwmaccsu);

  return EXEC_ID_inv;
}

def_THelper(vopfvv) {
  if (!vp_enable()) {
    return EXEC_ID_inv;
  }
  // longjmp_raise_intr(EX_II);
  def_INSTR_TAB("000000 ? ????? ????? ??? ????? ????? ??", vfadd);
  def_INSTR_TAB("000001 ? ????? ????? ??? ????? ????? ??", vfredusum);
  def_INSTR_TAB("000010 ? ????? ????? ??? ????? ????? ??", vfsub);
  def_INSTR_TAB("000011 ? ????? ????? ??? ????? ????? ??", vfredosum);
  def_INSTR_TAB("000100 ? ????? ????? ??? ????? ????? ??", vfmin);
  def_INSTR_TAB("000101 ? ????? ????? ??? ????? ????? ??", vfredmin);
  def_INSTR_TAB("000110 ? ????? ????? ??? ????? ????? ??", vfmax);
  def_INSTR_TAB("000111 ? ????? ????? ??? ????? ????? ??", vfredmax);
  def_INSTR_TAB("001000 ? ????? ????? ??? ????? ????? ??", vfsgnj);
  def_INSTR_TAB("001001 ? ????? ????? ??? ????? ????? ??", vfsgnjn);
  def_INSTR_TAB("001010 ? ????? ????? ??? ????? ????? ??", vfsgnjx);
  def_INSTR_TAB("010000 ? ????? ????? ??? ????? ????? ??", vwfunary0_dispatch);
  def_INSTR_TAB("010010 ? ????? ????? ??? ????? ????? ??", vfunary0_dispatch);
  def_INSTR_TAB("010011 ? ????? ????? ??? ????? ????? ??", vfunary1_dispatch);
  def_INSTR_TAB("011000 ? ????? ????? ??? ????? ????? ??", vmfeq);
  def_INSTR_TAB("011001 ? ????? ????? ??? ????? ????? ??", vmfle);
  def_INSTR_TAB("011011 ? ????? ????? ??? ????? ????? ??", vmflt);
  def_INSTR_TAB("011100 ? ????? ????? ??? ????? ????? ??", vmfne);
  def_INSTR_TAB("100000 ? ????? ????? ??? ????? ????? ??", vfdiv);
  def_INSTR_TAB("100100 ? ????? ????? ??? ????? ????? ??", vfmul);
  def_INSTR_TAB("101000 ? ????? ????? ??? ????? ????? ??", vfmadd);
  def_INSTR_TAB("101001 ? ????? ????? ??? ????? ????? ??", vfnmadd);
  def_INSTR_TAB("101010 ? ????? ????? ??? ????? ????? ??", vfmsub);
  def_INSTR_TAB("101011 ? ????? ????? ??? ????? ????? ??", vfnmsub);
  def_INSTR_TAB("101100 ? ????? ????? ??? ????? ????? ??", vfmacc);
  def_INSTR_TAB("101101 ? ????? ????? ??? ????? ????? ??", vfnmacc);
  def_INSTR_TAB("101110 ? ????? ????? ??? ????? ????? ??", vfmsac);
  def_INSTR_TAB("101111 ? ????? ????? ??? ????? ????? ??", vfnmsac);
  def_INSTR_TAB("110000 ? ????? ????? ??? ????? ????? ??", vfwadd);
  def_INSTR_TAB("110001 ? ????? ????? ??? ????? ????? ??", vfwredusum);
  def_INSTR_TAB("110010 ? ????? ????? ??? ????? ????? ??", vfwsub);
  def_INSTR_TAB("110011 ? ????? ????? ??? ????? ????? ??", vfwredosum);
  def_INSTR_TAB("110100 ? ????? ????? ??? ????? ????? ??", vfwadd_w);
  def_INSTR_TAB("110110 ? ????? ????? ??? ????? ????? ??", vfwsub_w);
  def_INSTR_TAB("111000 ? ????? ????? ??? ????? ????? ??", vfwmul);
  def_INSTR_TAB("111100 ? ????? ????? ??? ????? ????? ??", vfwmacc);
  def_INSTR_TAB("111101 ? ????? ????? ??? ????? ????? ??", vfwnmacc);
  def_INSTR_TAB("111110 ? ????? ????? ??? ????? ????? ??", vfwmsac);
  def_INSTR_TAB("111111 ? ????? ????? ??? ????? ????? ??", vfwnmsac);

  return EXEC_ID_inv;
}

def_THelper(vopfvf) {
  if (!vp_enable()) {
    return EXEC_ID_inv;
  }
  // longjmp_raise_intr(EX_II);
  def_INSTR_TAB("000000 ? ????? ????? ??? ????? ????? ??", vfadd);
  def_INSTR_TAB("000010 ? ????? ????? ??? ????? ????? ??", vfsub);
  def_INSTR_TAB("000100 ? ????? ????? ??? ????? ????? ??", vfmin);
  def_INSTR_TAB("000110 ? ????? ????? ??? ????? ????? ??", vfmax);
  def_INSTR_TAB("001000 ? ????? ????? ??? ????? ????? ??", vfsgnj);
  def_INSTR_TAB("001001 ? ????? ????? ??? ????? ????? ??", vfsgnjn);
  def_INSTR_TAB("001010 ? ????? ????? ??? ????? ????? ??", vfsgnjx);
  def_INSTR_TAB("001110 ? ????? ????? ??? ????? ????? ??", vfslide1up);
  def_INSTR_TAB("001111 ? ????? ????? ??? ????? ????? ??", vfslide1down);
  def_INSTR_TAB("010000 ? ????? ????? ??? ????? ????? ??", vrfunary0_dispatch);
  def_INSTR_TAB("010111 ? ????? ????? ??? ????? ????? ??", vfmerge);
  def_INSTR_TAB("011000 ? ????? ????? ??? ????? ????? ??", vmfeq);
  def_INSTR_TAB("011001 ? ????? ????? ??? ????? ????? ??", vmfle);
  def_INSTR_TAB("011011 ? ????? ????? ??? ????? ????? ??", vmflt);
  def_INSTR_TAB("011100 ? ????? ????? ??? ????? ????? ??", vmfne);
  def_INSTR_TAB("011101 ? ????? ????? ??? ????? ????? ??", vmfgt);
  def_INSTR_TAB("011111 ? ????? ????? ??? ????? ????? ??", vmfge);
  def_INSTR_TAB("100000 ? ????? ????? ??? ????? ????? ??", vfdiv);
  def_INSTR_TAB("100001 ? ????? ????? ??? ????? ????? ??", vfrdiv);
  def_INSTR_TAB("100100 ? ????? ????? ??? ????? ????? ??", vfmul);
  def_INSTR_TAB("100111 ? ????? ????? ??? ????? ????? ??", vfrsub);
  def_INSTR_TAB("101000 ? ????? ????? ??? ????? ????? ??", vfmadd);
  def_INSTR_TAB("101001 ? ????? ????? ??? ????? ????? ??", vfnmadd);
  def_INSTR_TAB("101010 ? ????? ????? ??? ????? ????? ??", vfmsub);
  def_INSTR_TAB("101011 ? ????? ????? ??? ????? ????? ??", vfnmsub);
  def_INSTR_TAB("101100 ? ????? ????? ??? ????? ????? ??", vfmacc);
  def_INSTR_TAB("101101 ? ????? ????? ??? ????? ????? ??", vfnmacc);
  def_INSTR_TAB("101110 ? ????? ????? ??? ????? ????? ??", vfmsac);
  def_INSTR_TAB("101111 ? ????? ????? ??? ????? ????? ??", vfnmsac);
  def_INSTR_TAB("110000 ? ????? ????? ??? ????? ????? ??", vfwadd);
  def_INSTR_TAB("110010 ? ????? ????? ??? ????? ????? ??", vfwsub);
  def_INSTR_TAB("110100 ? ????? ????? ??? ????? ????? ??", vfwadd_w);
  def_INSTR_TAB("110110 ? ????? ????? ??? ????? ????? ??", vfwsub_w);
  def_INSTR_TAB("111000 ? ????? ????? ??? ????? ????? ??", vfwmul);
  def_INSTR_TAB("111100 ? ????? ????? ??? ????? ????? ??", vfwmacc);
  def_INSTR_TAB("111101 ? ????? ????? ??? ????? ????? ??", vfwnmacc);
  def_INSTR_TAB("111110 ? ????? ????? ??? ????? ????? ??", vfwmsac);
  def_INSTR_TAB("111111 ? ????? ????? ??? ????? ????? ??", vfwnmsac);

  return EXEC_ID_inv;
}

def_THelper(vsetvl_dispatch) {
  def_INSTR_TAB("0?????? ????? ????? ??? ????? 1010111", vsetvli);
  def_INSTR_TAB("11????? ????? ????? ??? ????? 1010111", vsetivli);
  def_INSTR_TAB("1000000 ????? ????? ??? ????? 1010111", vsetvl);
  return EXEC_ID_inv;
}

// All RVV instructions decode start from here
def_THelper(OP_V) { // 10_101
  switch (s->isa.instr.i.funct3) {
    case 0 : s->src_vmode = SRC_VV; break;
    case 1 : s->src_vmode = SRC_VV; break;
    case 2 : s->src_vmode = SRC_VV; break;
    case 3 : s->src_vmode = SRC_VI; break;
    case 4 : s->src_vmode = SRC_VX; break;
    case 5 : s->src_vmode = SRC_VF; break;
    case 6 : s->src_vmode = SRC_VX; break;
  }

  s->v_width = 1 << vtype->vsew;
  s->vm = s->isa.instr.v_opv1.v_vm; //1 for without mask; 0 for with mask

  /*
  switch(s->isa.instr.i.funct3) {
    EX(0x0, vopi) EX(0x1, vopf) EX(0x2, vopm) EX(0x3, vopi) EX(0x4, vopi) EX(0x5, vopf) EX(0x6, vopm) IDEX(0x7, vsetvl, vsetvl)
  }
  */
  def_INSTR_TAB("??????? ????? ????? 000 ????? ????? ??", vopivv);
  def_INSTR_TAB("??????? ????? ????? 001 ????? ????? ??", vopfvv);
  def_INSTR_TAB("??????? ????? ????? 010 ????? ????? ??", vopm);
  def_INSTR_TAB("??????? ????? ????? 011 ????? ????? ??", vopivi);
  def_INSTR_TAB("??????? ????? ????? 100 ????? ????? ??", vopivx);
  def_INSTR_TAB("??????? ????? ????? 101 ????? ????? ??", vopfvf);
  def_INSTR_TAB("??????? ????? ????? 110 ????? ????? ??", vopm);
  def_INSTR_IDTAB("??????? ????? ????? 111 ????? ????? ??", vsetvl, vsetvl_dispatch);
  return EXEC_ID_inv;
}

#endif // CONFIG_RVV
