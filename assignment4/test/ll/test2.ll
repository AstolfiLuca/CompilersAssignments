; ModuleID = 'bc/test2.bc'
source_filename = "cpp/test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = icmp sgt i32 %3, 0
  br i1 %5, label %6, label %13

6:                                                ; preds = %4
  br label %7

7:                                                ; preds = %10, %6
  %.0 = phi i32 [ 0, %6 ], [ %9, %10 ]
  %8 = add nsw i32 %.0, 1
  %9 = add nsw i32 %.0, 1
  br label %10

10:                                               ; preds = %7
  %11 = icmp slt i32 %9, %3
  br i1 %11, label %7, label %12, !llvm.loop !6

12:                                               ; preds = %10
  br label %13

13:                                               ; preds = %12, %4
  %.03 = phi i32 [ %8, %12 ], [ %3, %4 ]
  %14 = icmp sgt i32 %3, 0
  br i1 %14, label %15, label %22

15:                                               ; preds = %13
  br label %16

16:                                               ; preds = %19, %15
  %.01 = phi i32 [ %1, %15 ], [ %17, %19 ]
  %.1 = phi i32 [ 0, %15 ], [ %18, %19 ]
  %17 = add nsw i32 %.01, %.03
  %18 = add nsw i32 %.1, 1
  br label %19

19:                                               ; preds = %16
  %20 = icmp slt i32 %18, %3
  br i1 %20, label %16, label %21, !llvm.loop !8

21:                                               ; preds = %19
  br label %22

22:                                               ; preds = %21, %13
  %.12 = phi i32 [ %17, %21 ], [ %1, %13 ]
  %23 = mul nsw i32 %.12, %2
  %24 = add nsw i32 %0, %23
  ret i32 %24
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 19.1.7 (++20250114103253+cd708029e0b2-1~exp1~20250114103309.40)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
