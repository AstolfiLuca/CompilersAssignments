; ModuleID = 'bc/test2.bc'
source_filename = "cpp/test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  br label %4

4:                                                ; preds = %6, %3
  %.03 = phi i32 [ 0, %3 ], [ %8, %6 ]
  %.0 = phi i32 [ %0, %3 ], [ %7, %6 ]
  %5 = icmp slt i32 %.03, %2
  br i1 %5, label %6, label %9

6:                                                ; preds = %4
  %7 = add nsw i32 %.0, %.03
  %8 = add nsw i32 %.03, 1
  br label %4, !llvm.loop !6

9:                                                ; preds = %4
  br label %10

10:                                               ; preds = %13, %9
  %.02 = phi i32 [ 0, %9 ], [ %12, %13 ]
  %.01 = phi i32 [ %1, %9 ], [ %11, %13 ]
  %11 = add nsw i32 %.01, %.02
  %12 = add nsw i32 %.02, 1
  br label %13

13:                                               ; preds = %10
  %14 = icmp slt i32 %12, %2
  br i1 %14, label %10, label %15, !llvm.loop !8

15:                                               ; preds = %13
  %16 = mul nsw i32 %11, %12
  %17 = add nsw i32 %.0, %16
  ret i32 %17
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
