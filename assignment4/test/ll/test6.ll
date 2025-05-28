; ModuleID = 'bc/test6.bc'
source_filename = "cpp/test6.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooi(i32 noundef %0) #0 {
  br label %2

2:                                                ; preds = %6, %1
  %.02 = phi i32 [ 0, %1 ], [ %7, %6 ]
  %.01 = phi i32 [ undef, %1 ], [ %5, %6 ]
  %3 = icmp slt i32 %.02, 10
  br i1 %3, label %4, label %8

4:                                                ; preds = %2
  %5 = add nsw i32 %.02, 2
  br label %6

6:                                                ; preds = %4
  %7 = add nsw i32 %.02, 1
  br label %2, !llvm.loop !6

8:                                                ; preds = %2
  br label %9

9:                                                ; preds = %13, %8
  %.03 = phi i32 [ 0, %8 ], [ %14, %13 ]
  %.0 = phi i32 [ %0, %8 ], [ %12, %13 ]
  %10 = icmp slt i32 %.03, 10
  br i1 %10, label %11, label %15

11:                                               ; preds = %9
  %12 = add nsw i32 %.01, 1
  br label %13

13:                                               ; preds = %11
  %14 = add nsw i32 %.03, 1
  br label %9, !llvm.loop !8

15:                                               ; preds = %9
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
