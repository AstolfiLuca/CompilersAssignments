; ModuleID = 'bc/test1.optimized.bc'
source_filename = "cpp/test1.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4, i32 noundef %5) #0 {
  br label %7

7:                                                ; preds = %13, %6
  %.0 = phi i32 [ %4, %6 ], [ %14, %13 ]
  %8 = icmp slt i32 %.0, 5
  br i1 %8, label %9, label %15

9:                                                ; preds = %7
  %10 = icmp slt i32 %.0, 3
  br i1 %10, label %11, label %12

11:                                               ; preds = %9
  br label %15

12:                                               ; preds = %9
  br label %13

13:                                               ; preds = %12
  %14 = add nsw i32 %.0, 1
  br label %7, !llvm.loop !6

15:                                               ; preds = %11, %7
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
