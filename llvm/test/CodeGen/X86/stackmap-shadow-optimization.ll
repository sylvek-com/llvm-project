; RUN: llc < %s -mtriple=x86_64-apple-darwin -mcpu=corei7 | FileCheck %s

; Check that the X86 stackmap shadow optimization is only outputting a 3-byte
; nop here. 8-bytes are requested, but 5 are covered by the code for the call to
; bar.  However, the frame teardown and the return do not count towards the
; stackmap shadow as the call return counts as a branch target so must flush
; the shadow.
define void @shadow_optimization_test() {
entry:
; CHECK-LABEL:  shadow_optimization_test:
; CHECK:        callq   _bar
; CHECK-NOT:    nop
; CHECK:        callq   _bar
; CHECK:        nop
; CHECK:        retq
  call void @bar()
  tail call void (i64, i32, ...)* @llvm.experimental.stackmap(i64 0, i32 8)
  call void @bar()
  ret void
}

declare void @llvm.experimental.stackmap(i64, i32, ...)
declare void @bar()
