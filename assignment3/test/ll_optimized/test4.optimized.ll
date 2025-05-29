; ModuleID = 'bc/test4.optimized.bc'
source_filename = "cpp/test4.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = icmp sgt i32 %0, 5
  br i1 %3, label %4, label %6

4:                                                ; preds = %2
  %5 = add nsw i32 %0, 3
  br label %8

6:                                                ; preds = %2
  %7 = sub nsw i32 %0, 3
  br label %8

8:                                                ; preds = %6, %4
  %.01 = phi i32 [ %5, %4 ], [ %7, %6 ]
  br label %9

9:                                                ; preds = %11, %8
  %.02 = phi i32 [ 0, %8 ], [ %12, %11 ]
  %.0 = phi i32 [ %0, %8 ], [ %13, %11 ]
  %10 = icmp sgt i32 %.0, 0
  br i1 %10, label %11, label %14

11:                                               ; preds = %9
  %12 = add nsw i32 %.02, %.01
  %13 = add nsw i32 %.0, -1
  br label %9, !llvm.loop !6

14:                                               ; preds = %9
  %15 = add nsw i32 %.0, %.02
  %16 = add nsw i32 %15, %.01
  ret i32 %16
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
