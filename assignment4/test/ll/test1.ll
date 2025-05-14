; ModuleID = 'bc/test1.bc'
source_filename = "cpp/test1.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooii(i32 noundef %0, i32 noundef %1) #0 {
  br label %3

3:                                                ; preds = %7, %2
  %.02 = phi i32 [ 0, %2 ], [ %8, %7 ]
  %.0 = phi i32 [ %0, %2 ], [ %6, %7 ]
  %4 = icmp slt i32 %.02, 10
  br i1 %4, label %5, label %9

5:                                                ; preds = %3
  %6 = add nsw i32 %.0, %.02
  br label %7

7:                                                ; preds = %5
  %8 = add nsw i32 %.02, 1
  br label %3, !llvm.loop !6

9:                                                ; preds = %3
  br label %10

10:                                               ; preds = %14, %9
  %.03 = phi i32 [ 0, %9 ], [ %15, %14 ]
  %.01 = phi i32 [ %1, %9 ], [ %13, %14 ]
  %11 = icmp slt i32 %.03, 10
  br i1 %11, label %12, label %16

12:                                               ; preds = %10
  %13 = add nsw i32 %.01, %.03
  br label %14

14:                                               ; preds = %12
  %15 = add nsw i32 %.03, 1
  br label %10, !llvm.loop !8

16:                                               ; preds = %10
  %17 = icmp sgt i32 %.0, %.01
  br i1 %17, label %18, label %19

18:                                               ; preds = %16
  br label %19

19:                                               ; preds = %18, %16
  %.04 = phi i32 [ %.0, %18 ], [ 0, %16 ]
  br label %20

20:                                               ; preds = %24, %19
  %.05 = phi i32 [ 0, %19 ], [ %25, %24 ]
  %.1 = phi i32 [ %.04, %19 ], [ %23, %24 ]
  %21 = icmp slt i32 %.05, 10
  br i1 %21, label %22, label %26

22:                                               ; preds = %20
  %23 = add nsw i32 %.1, %.05
  br label %24

24:                                               ; preds = %22
  %25 = add nsw i32 %.05, 1
  br label %20, !llvm.loop !9

26:                                               ; preds = %20
  %27 = add nsw i32 %.0, %.01
  ret i32 %27
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 19.1.1 (1ubuntu1)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
