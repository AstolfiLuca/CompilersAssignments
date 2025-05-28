; ModuleID = 'bc/test6.optimized.bc'
source_filename = "cpp/test6.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 10, %1
  br label %4

4:                                                ; preds = %12, %2
  %.03 = phi i32 [ 0, %2 ], [ %13, %12 ]
  %.01 = phi i32 [ undef, %2 ], [ %.1, %12 ]
  %.0 = phi i32 [ %0, %2 ], [ 5, %12 ]
  %5 = icmp slt i32 %.03, 10
  br i1 %5, label %6, label %21

6:                                                ; preds = %4
  %7 = add nsw i32 %.0, %.01
  %8 = icmp sgt i32 %7, 0
  br i1 %8, label %9, label %10

9:                                                ; preds = %6
  br label %11

10:                                               ; preds = %6
  br label %11

11:                                               ; preds = %10, %9
  %.1 = phi i32 [ 10, %9 ], [ 20, %10 ]
  br label %17

12:                                               ; preds = %17
  %13 = add nsw i32 %.03, 1
  br label %4, !llvm.loop !6

14:                                               ; No predecessors!
  br label %15

15:                                               ; preds = %19, %14
  %16 = icmp slt i32 %.03, 10
  br i1 %16, label %17, label %21

17:                                               ; preds = %11, %15
  %18 = add nsw i32 %.03, 1
  br label %12

19:                                               ; No predecessors!
  %20 = add nsw i32 %.03, 1
  br label %15, !llvm.loop !8

21:                                               ; preds = %4, %15
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
!5 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
