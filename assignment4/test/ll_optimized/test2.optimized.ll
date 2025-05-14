; ModuleID = 'bc/test2.optimized.bc'
source_filename = "cpp/test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = icmp sgt i32 5, 0
  br i1 %4, label %5, label %11

5:                                                ; preds = %3
  br label %6

6:                                                ; preds = %8, %5
  %.02 = phi i32 [ 0, %5 ], [ %7, %8 ]
  %7 = add nsw i32 %.02, 1
  br label %8

8:                                                ; preds = %6
  %9 = icmp slt i32 %7, 5
  br i1 %9, label %6, label %10, !llvm.loop !6

10:                                               ; preds = %8
  br label %11

11:                                               ; preds = %10, %3
  br label %12

12:                                               ; preds = %15, %11
  %.01 = phi i32 [ %1, %11 ], [ %13, %15 ]
  %.0 = phi i32 [ 0, %11 ], [ %14, %15 ]
  %13 = add nsw i32 %.01, %.0
  %14 = add nsw i32 %.0, 1
  br label %15

15:                                               ; preds = %12
  %16 = icmp slt i32 %14, %2
  br i1 %16, label %12, label %17, !llvm.loop !8

17:                                               ; preds = %15
  %18 = mul nsw i32 %13, %14
  %19 = add nsw i32 %0, %18
  ret i32 %19
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
