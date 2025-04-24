; ModuleID = 'bc/test1.optimized.bc'
source_filename = "cpp/test1.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #0 {
  %1 = add nsw i32 3, 5
  %2 = add nsw i32 %1, 1
  br label %3

3:                                                ; preds = %9, %0
  %.0 = phi i32 [ 0, %0 ], [ %11, %9 ]
  %4 = icmp slt i32 %.0, 5
  br i1 %4, label %5, label %12

5:                                                ; preds = %3
  %6 = icmp slt i32 %.0, 3
  br i1 %6, label %7, label %8

7:                                                ; preds = %5
  br label %9

8:                                                ; preds = %5
  br label %9

9:                                                ; preds = %8, %7
  %.01 = phi i32 [ 2, %7 ], [ 3, %8 ]
  %10 = add nsw i32 %.01, 2
  %11 = add nsw i32 %.0, 1
  br label %3, !llvm.loop !6

12:                                               ; preds = %3
  ret i32 5
}

attributes #0 = { mustprogress noinline norecurse nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 19.1.7 (++20250114103320+cd708029e0b2-1~exp1~20250114103432.75)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
