; ModuleID = 'bc/test2.bc'
source_filename = "cpp/test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) #0 {
  %6 = icmp sgt i32 %4, 0
  br i1 %6, label %7, label %13

7:                                                ; preds = %5
  br label %8

8:                                                ; preds = %10, %7
  %.0 = phi i32 [ 0, %7 ], [ %9, %10 ]
  %9 = add nsw i32 %.0, 1
  br label %10

10:                                               ; preds = %8
  %11 = icmp slt i32 %9, %4
  br i1 %11, label %8, label %12, !llvm.loop !6

12:                                               ; preds = %10
  br label %13

13:                                               ; preds = %12, %5
  br label %14

14:                                               ; preds = %17, %13
  %.02 = phi i32 [ %3, %13 ], [ %16, %17 ]
  %.01 = phi i32 [ %1, %13 ], [ %15, %17 ]
  %15 = add nsw i32 %.01, %.02
  %16 = add nsw i32 %.02, 1
  br label %17

17:                                               ; preds = %14
  %18 = icmp slt i32 %16, %2
  br i1 %18, label %14, label %19, !llvm.loop !8

19:                                               ; preds = %17
  %20 = mul nsw i32 %15, %2
  %21 = add nsw i32 %0, %20
  ret i32 %21
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
