; ModuleID = 'bc/test2.optimized.bc'
source_filename = "cpp/test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3funiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = add nsw i32 %1, %2
  %5 = add nsw i32 %4, 1
  br label %6

6:                                                ; preds = %13, %3
  %.0 = phi i32 [ 0, %3 ], [ %14, %13 ]
  %7 = icmp eq i32 1, 1
  br i1 %7, label %8, label %15

8:                                                ; preds = %6
  %9 = icmp slt i32 %.0, 5
  br i1 %9, label %10, label %11

10:                                               ; preds = %8
  br label %13

11:                                               ; preds = %8
  %12 = add nsw i32 %1, 1
  br label %15

13:                                               ; preds = %10
  %14 = add nsw i32 %.0, 1
  br label %6, !llvm.loop !6

15:                                               ; preds = %11, %6
  ret i32 %2
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

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
