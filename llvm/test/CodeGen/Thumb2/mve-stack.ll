; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=thumbv8.1m.main-arm-none-eabi -mattr=+mve -verify-machineinstrs %s -o - | FileCheck %s

define arm_aapcs_vfpcc void @vstrw32() {
; CHECK-LABEL: vstrw32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #16
; CHECK-NEXT:    sub sp, #16
; CHECK-NEXT:    vmov.i32 q0, #0x0
; CHECK-NEXT:    mov r0, sp
; CHECK-NEXT:    vstrw.32 q0, [sp, #8]
; CHECK-NEXT:    bl func
; CHECK-NEXT:    add sp, #16
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [4 x i32], align 2
  %g = getelementptr inbounds [4 x i32], [4 x i32]* %d, i32 0, i32 2
  %b = bitcast i32* %g to <4 x i32>*
  store <4 x i32> zeroinitializer, <4 x i32>* %b, align 2
  %arraydecay = getelementptr inbounds [4 x i32], [4 x i32]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i32*)*)(i32* %arraydecay)
  ret void
}

define arm_aapcs_vfpcc void @vstrh16() {
; CHECK-LABEL: vstrh16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #16
; CHECK-NEXT:    sub sp, #16
; CHECK-NEXT:    vmov.i32 q0, #0x0
; CHECK-NEXT:    mov r0, sp
; CHECK-NEXT:    vstrh.16 q0, [sp, #4]
; CHECK-NEXT:    bl func
; CHECK-NEXT:    add sp, #16
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [8 x i16], align 2
  %g = getelementptr inbounds [8 x i16], [8 x i16]* %d, i32 0, i32 2
  %b = bitcast i16* %g to <8 x i16>*
  store <8 x i16> zeroinitializer, <8 x i16>* %b, align 2
  %arraydecay = getelementptr inbounds [8 x i16], [8 x i16]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i16*)*)(i16* %arraydecay)
  ret void
}

define arm_aapcs_vfpcc void @vstrb8() {
; CHECK-LABEL: vstrb8:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #16
; CHECK-NEXT:    sub sp, #16
; CHECK-NEXT:    vmov.i32 q0, #0x0
; CHECK-NEXT:    mov r0, sp
; CHECK-NEXT:    vstrh.16 q0, [sp, #2]
; CHECK-NEXT:    bl func
; CHECK-NEXT:    add sp, #16
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [16 x i8], align 2
  %g = getelementptr inbounds [16 x i8], [16 x i8]* %d, i32 0, i32 2
  %b = bitcast i8* %g to <16 x i8>*
  store <16 x i8> zeroinitializer, <16 x i8>* %b, align 2
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i8*)*)(i8* %arraydecay)
  ret void
}

define arm_aapcs_vfpcc void @vstrh32() {
; CHECK-LABEL: vstrh32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #8
; CHECK-NEXT:    sub sp, #8
; CHECK-NEXT:    mov r0, sp
; CHECK-NEXT:    vmov.i32 q0, #0x6
; CHECK-NEXT:    vstrh.32 q0, [r0, #4]
; CHECK-NEXT:    bl func
; CHECK-NEXT:    add sp, #8
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [4 x i16], align 2
  %g = getelementptr inbounds [4 x i16], [4 x i16]* %d, i32 0, i32 2
  %b = bitcast i16* %g to <4 x i16>*
  store <4 x i16> <i16 6, i16 6, i16 6, i16 6>, <4 x i16>* %b, align 2
  %arraydecay = getelementptr inbounds [4 x i16], [4 x i16]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i16*)*)(i16* %arraydecay)
  ret void
}

define arm_aapcs_vfpcc void @vstrb32() {
; CHECK-LABEL: vstrb32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #8
; CHECK-NEXT:    sub sp, #8
; CHECK-NEXT:    add r0, sp, #4
; CHECK-NEXT:    vmov.i32 q0, #0x6
; CHECK-NEXT:    vstrb.32 q0, [r0, #2]
; CHECK-NEXT:    bl func
; CHECK-NEXT:    add sp, #8
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [4 x i8], align 2
  %g = getelementptr inbounds [4 x i8], [4 x i8]* %d, i32 0, i32 2
  %b = bitcast i8* %g to <4 x i8>*
  store <4 x i8> <i8 6, i8 6, i8 6, i8 6>, <4 x i8>* %b, align 2
  %arraydecay = getelementptr inbounds [4 x i8], [4 x i8]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i8*)*)(i8* %arraydecay)
  ret void
}

define arm_aapcs_vfpcc void @vstrb16() {
; CHECK-LABEL: vstrb16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #8
; CHECK-NEXT:    sub sp, #8
; CHECK-NEXT:    mov r0, sp
; CHECK-NEXT:    vmov.i32 q0, #0x0
; CHECK-NEXT:    vstrb.16 q0, [r0, #2]
; CHECK-NEXT:    bl func
; CHECK-NEXT:    add sp, #8
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [8 x i8], align 2
  %g = getelementptr inbounds [8 x i8], [8 x i8]* %d, i32 0, i32 2
  %b = bitcast i8* %g to <8 x i8>*
  store <8 x i8> zeroinitializer, <8 x i8>* %b, align 2
  %arraydecay = getelementptr inbounds [8 x i8], [8 x i8]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i8*)*)(i8* %arraydecay)
  ret void
}


define arm_aapcs_vfpcc <4 x i32> @vldrw32() {
; CHECK-LABEL: vldrw32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #16
; CHECK-NEXT:    sub sp, #16
; CHECK-NEXT:    mov r0, sp
; CHECK-NEXT:    bl func
; CHECK-NEXT:    vldrw.u32 q0, [sp, #8]
; CHECK-NEXT:    add sp, #16
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [4 x i32], align 2
  %arraydecay = getelementptr inbounds [4 x i32], [4 x i32]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i32*)*)(i32* %arraydecay)
  %g = getelementptr inbounds [4 x i32], [4 x i32]* %d, i32 0, i32 2
  %b = bitcast i32* %g to <4 x i32>*
  %l = load <4 x i32>, <4 x i32>* %b, align 2
  ret <4 x i32> %l
}

define arm_aapcs_vfpcc <8 x i16> @vldrh16() {
; CHECK-LABEL: vldrh16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #16
; CHECK-NEXT:    sub sp, #16
; CHECK-NEXT:    mov r0, sp
; CHECK-NEXT:    bl func
; CHECK-NEXT:    vldrh.u16 q0, [sp, #4]
; CHECK-NEXT:    add sp, #16
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [8 x i16], align 2
  %arraydecay = getelementptr inbounds [8 x i16], [8 x i16]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i16*)*)(i16* %arraydecay)
  %g = getelementptr inbounds [8 x i16], [8 x i16]* %d, i32 0, i32 2
  %b = bitcast i16* %g to <8 x i16>*
  %l = load <8 x i16>, <8 x i16>* %b, align 2
  ret <8 x i16> %l
}

define arm_aapcs_vfpcc <16 x i8> @vldrb8() {
; CHECK-LABEL: vldrb8:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r7, lr}
; CHECK-NEXT:    push {r7, lr}
; CHECK-NEXT:    .pad #16
; CHECK-NEXT:    sub sp, #16
; CHECK-NEXT:    mov r0, sp
; CHECK-NEXT:    bl func
; CHECK-NEXT:    vldrh.u16 q0, [sp, #2]
; CHECK-NEXT:    add sp, #16
; CHECK-NEXT:    pop {r7, pc}
entry:
  %d = alloca [16 x i8], align 2
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i8*)*)(i8* %arraydecay)
  %g = getelementptr inbounds [16 x i8], [16 x i8]* %d, i32 0, i32 2
  %b = bitcast i8* %g to <16 x i8>*
  %l = load <16 x i8>, <16 x i8>* %b, align 2
  ret <16 x i8> %l
}

define arm_aapcs_vfpcc <4 x i16> @vldrh32() {
; CHECK-LABEL: vldrh32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r4, lr}
; CHECK-NEXT:    push {r4, lr}
; CHECK-NEXT:    .pad #8
; CHECK-NEXT:    sub sp, #8
; CHECK-NEXT:    mov r4, sp
; CHECK-NEXT:    mov r0, r4
; CHECK-NEXT:    bl func
; CHECK-NEXT:    vldrh.u32 q0, [r4, #4]
; CHECK-NEXT:    add sp, #8
; CHECK-NEXT:    pop {r4, pc}
entry:
  %d = alloca [4 x i16], align 2
  %arraydecay = getelementptr inbounds [4 x i16], [4 x i16]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i16*)*)(i16* %arraydecay)
  %g = getelementptr inbounds [4 x i16], [4 x i16]* %d, i32 0, i32 2
  %b = bitcast i16* %g to <4 x i16>*
  %l = load <4 x i16>, <4 x i16>* %b, align 2
  ret <4 x i16> %l
}

define arm_aapcs_vfpcc <4 x i8> @vldrb32() {
; CHECK-LABEL: vldrb32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r4, lr}
; CHECK-NEXT:    push {r4, lr}
; CHECK-NEXT:    .pad #8
; CHECK-NEXT:    sub sp, #8
; CHECK-NEXT:    add r4, sp, #4
; CHECK-NEXT:    mov r0, r4
; CHECK-NEXT:    bl func
; CHECK-NEXT:    vldrb.u32 q0, [r4, #2]
; CHECK-NEXT:    add sp, #8
; CHECK-NEXT:    pop {r4, pc}
entry:
  %d = alloca [4 x i8], align 2
  %arraydecay = getelementptr inbounds [4 x i8], [4 x i8]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i8*)*)(i8* %arraydecay)
  %g = getelementptr inbounds [4 x i8], [4 x i8]* %d, i32 0, i32 2
  %b = bitcast i8* %g to <4 x i8>*
  %l = load <4 x i8>, <4 x i8>* %b, align 2
  ret <4 x i8> %l
}

define arm_aapcs_vfpcc <8 x i8> @vldrb16() {
; CHECK-LABEL: vldrb16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    .save {r4, lr}
; CHECK-NEXT:    push {r4, lr}
; CHECK-NEXT:    .pad #8
; CHECK-NEXT:    sub sp, #8
; CHECK-NEXT:    mov r4, sp
; CHECK-NEXT:    mov r0, r4
; CHECK-NEXT:    bl func
; CHECK-NEXT:    vldrb.u16 q0, [r4, #2]
; CHECK-NEXT:    add sp, #8
; CHECK-NEXT:    pop {r4, pc}
entry:
  %d = alloca [8 x i8], align 2
  %arraydecay = getelementptr inbounds [8 x i8], [8 x i8]* %d, i32 0, i32 0
  call arm_aapcs_vfpcc void bitcast (void (...)* @func to void (i8*)*)(i8* %arraydecay)
  %g = getelementptr inbounds [8 x i8], [8 x i8]* %d, i32 0, i32 2
  %b = bitcast i8* %g to <8 x i8>*
  %l = load <8 x i8>, <8 x i8>* %b, align 2
  ret <8 x i8> %l
}

declare dso_local arm_aapcs_vfpcc void @func(...)