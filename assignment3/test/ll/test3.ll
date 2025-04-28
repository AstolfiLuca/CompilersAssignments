; ModuleID = 'bc/test3.bc'
source_filename = "cpp/test3.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3funiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  br label %4

4:                                                ; preds = %21, %3
  %.01 = phi i32 [ %2, %3 ], [ %15, %21 ]
  %5 = add nsw i32 %0, %1
  %6 = icmp sgt i32 %.01, 5
  br i1 %6, label %7, label %9

7:                                                ; preds = %4
  %8 = add nsw i32 %5, 1
  br label %22

9:                                                ; preds = %4
  %10 = sub nsw i32 %5, 1
  br label %11

11:                                               ; preds = %18, %9
  %.0 = phi i32 [ %10, %9 ], [ %17, %18 ]
  %12 = add nsw i32 %1, 1
  %13 = icmp sgt i32 %.0, 5
  br i1 %13, label %14, label %16

14:                                               ; preds = %11
  %15 = add nsw i32 %.01, 1
  br label %20

16:                                               ; preds = %11
  %17 = add nsw i32 %.0, 1
  br label %18

18:                                               ; preds = %16
  %19 = add nsw i32 %17, 5
  br label %11, !llvm.loop !6

20:                                               ; preds = %14
  br label %21

21:                                               ; preds = %20
  br label %4, !llvm.loop !8

22:                                               ; preds = %7
  ret i32 %8
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
