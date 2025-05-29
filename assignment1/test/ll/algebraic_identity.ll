; ModuleID = 'bc/algebraic_identity.bc'
source_filename = "cpp/algebraic_identity.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z23algebraic_identity_testiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = mul nsw i32 %0, 1
  %6 = add nsw i32 %5, 0
  %7 = sdiv i32 %6, %6
  %8 = add nsw i32 %7, 1
  %9 = sub nsw i32 %8, 1
  %10 = add nsw i32 %9, 5
  %11 = add nsw i32 1, %7
  %12 = sub nsw i32 %11, 1
  %13 = mul nsw i32 %12, 5
  ret i32 %7
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
