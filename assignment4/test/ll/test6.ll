; ModuleID = 'bc/test6.bc'
source_filename = "cpp/test6.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooii(i32 noundef %0, i32 noundef %1) #0 {
  br label %3

3:                                                ; preds = %11, %2
  %.03 = phi i32 [ 0, %2 ], [ %12, %11 ]
  %.01 = phi i32 [ undef, %2 ], [ %.1, %11 ]
  %.0 = phi i32 [ %0, %2 ], [ 5, %11 ]
  %4 = icmp slt i32 %.03, 10
  br i1 %4, label %5, label %13

5:                                                ; preds = %3
  %6 = add nsw i32 %.0, %.01
  %7 = icmp sgt i32 %6, 0
  br i1 %7, label %8, label %9

8:                                                ; preds = %5
  br label %10

9:                                                ; preds = %5
  br label %10

10:                                               ; preds = %9, %8
  %.1 = phi i32 [ 10, %8 ], [ 20, %9 ]
  br label %11

11:                                               ; preds = %10
  %12 = add nsw i32 %.03, 1
  br label %3, !llvm.loop !6

13:                                               ; preds = %3
  %14 = add nsw i32 10, %1
  br label %15

15:                                               ; preds = %19, %13
  %.02 = phi i32 [ 0, %13 ], [ %20, %19 ]
  %16 = icmp slt i32 %.02, 10
  br i1 %16, label %17, label %21

17:                                               ; preds = %15
  %18 = add nsw i32 %.02, 1
  br label %19

19:                                               ; preds = %17
  %20 = add nsw i32 %.02, 1
  br label %15, !llvm.loop !8

21:                                               ; preds = %15
  ret i32 %.0
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
