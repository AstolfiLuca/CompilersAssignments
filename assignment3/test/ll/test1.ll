; ModuleID = 'bc/test1.bc'
source_filename = "cpp/test1.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4, i32 noundef %5) #0 {
  %7 = add nsw i32 5, %5
  br label %8

8:                                                ; preds = %17, %6
  %.0 = phi i32 [ %4, %6 ], [ %20, %17 ]
  %9 = icmp slt i32 %.0, 5
  br i1 %9, label %10, label %21

10:                                               ; preds = %8
  %11 = add nsw i32 %7, %1
  %12 = icmp slt i32 %.0, 3
  br i1 %12, label %13, label %15

13:                                               ; preds = %10
  %14 = add nsw i32 %7, 3
  br label %21

15:                                               ; preds = %10
  %16 = add nsw i32 %11, 4
  br label %17

17:                                               ; preds = %15
  %18 = add nsw i32 %11, 1
  %19 = add nsw i32 %16, 2
  %20 = add nsw i32 %.0, 1
  br label %8, !llvm.loop !6

21:                                               ; preds = %13, %8
  ret i32 %1
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
