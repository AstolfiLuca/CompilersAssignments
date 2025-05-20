; ModuleID = 'bc/test2.bc'
source_filename = "cpp/test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = icmp sgt i32 %3, 0
  br i1 %5, label %6, label %12

6:                                                ; preds = %4
  br label %7

7:                                                ; preds = %9, %6
  %.0 = phi i32 [ 0, %6 ], [ %8, %9 ]
  %8 = add nsw i32 %.0, 1
  br label %9

9:                                                ; preds = %7
  %10 = icmp slt i32 %8, %3
  br i1 %10, label %7, label %11, !llvm.loop !6

11:                                               ; preds = %9
  br label %12

12:                                               ; preds = %11, %4
  %.1 = phi i32 [ %8, %11 ], [ 0, %4 ]
  %13 = icmp sgt i32 %3, 0
  br i1 %13, label %14, label %20

14:                                               ; preds = %12
  br label %15

15:                                               ; preds = %17, %14
  %.01 = phi i32 [ %1, %14 ], [ %16, %17 ]
  %16 = add nsw i32 %.01, %3
  br label %17

17:                                               ; preds = %15
  %18 = icmp slt i32 %.1, %3
  br i1 %18, label %15, label %19, !llvm.loop !8

19:                                               ; preds = %17
  br label %20

20:                                               ; preds = %19, %12
  %.12 = phi i32 [ %16, %19 ], [ %1, %12 ]
  %21 = mul nsw i32 %.12, %2
  %22 = add nsw i32 %0, %21
  ret i32 %22
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
