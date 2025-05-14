; ModuleID = 'bc/test3.bc'
source_filename = "cpp/test3.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  br label %4

4:                                                ; preds = %12, %3
  %.04 = phi i32 [ 0, %3 ], [ %13, %12 ]
  %.01 = phi i32 [ %0, %3 ], [ %7, %12 ]
  %5 = icmp slt i32 %.04, %2
  br i1 %5, label %6, label %14

6:                                                ; preds = %4
  %7 = add nsw i32 %.01, %.04
  %8 = icmp sgt i32 %7, 10
  br i1 %8, label %9, label %11

9:                                                ; preds = %6
  %10 = add nsw i32 %7, %1
  br label %23

11:                                               ; preds = %6
  br label %12

12:                                               ; preds = %11
  %13 = add nsw i32 %.04, 1
  br label %4, !llvm.loop !6

14:                                               ; preds = %4
  br label %15

15:                                               ; preds = %18, %14
  %.03 = phi i32 [ 0, %14 ], [ %17, %18 ]
  %.02 = phi i32 [ %1, %14 ], [ %16, %18 ]
  %16 = add nsw i32 %.02, %.03
  %17 = add nsw i32 %.03, 1
  br label %18

18:                                               ; preds = %15
  %19 = icmp slt i32 %17, %2
  br i1 %19, label %15, label %20, !llvm.loop !8

20:                                               ; preds = %18
  %21 = mul nsw i32 %16, %17
  %22 = add nsw i32 %.01, %21
  br label %23

23:                                               ; preds = %20, %9
  %.0 = phi i32 [ %10, %9 ], [ %22, %20 ]
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
!5 = !{!"Ubuntu clang version 19.1.1 (1ubuntu1)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
