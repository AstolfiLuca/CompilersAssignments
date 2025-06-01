; ModuleID = 'bc/test7.optimized.bc'
source_filename = "cpp/test7.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3funiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  br label %4

4:                                                ; preds = %8, %3
  %.05 = phi i32 [ 0, %3 ], [ %9, %8 ]
  %.0 = phi i32 [ %0, %3 ], [ %7, %8 ]
  %.03 = phi i32 [ 0, %3 ], [ %11, %8 ]
  %.02 = phi i32 [ %2, %3 ], [ %13, %8 ]
  %.04 = phi i32 [ 0, %3 ], [ %15, %8 ]
  %5 = icmp slt i32 %.05, %1
  br i1 %5, label %6, label %16

6:                                                ; preds = %4
  %7 = add nsw i32 %.0, %1
  br label %10

8:                                                ; preds = %14
  %9 = add nsw i32 %.05, 1
  br label %4, !llvm.loop !6

10:                                               ; preds = %6
  %11 = add nsw i32 %.03, %1
  br label %12

12:                                               ; preds = %10
  %13 = add nsw i32 %.02, %.02
  br label %14

14:                                               ; preds = %12
  %15 = add nsw i32 %.04, %1
  br label %8

16:                                               ; preds = %4
  br label %17

17:                                               ; preds = %21, %16
  %.01 = phi i32 [ 0, %16 ], [ %22, %21 ]
  %.1 = phi i32 [ %.0, %16 ], [ %20, %21 ]
  %18 = icmp slt i32 %.01, %1
  br i1 %18, label %19, label %23

19:                                               ; preds = %17
  %20 = add nsw i32 %.1, %1
  br label %21

21:                                               ; preds = %19
  %22 = add nsw i32 %.01, 1
  br label %17, !llvm.loop !8

23:                                               ; preds = %17
  %24 = add nsw i32 %.1, %1
  %25 = add nsw i32 %24, %.03
  %26 = add nsw i32 %25, %.04
  ret i32 %26
}

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #1 {
  %1 = call noundef i32 @_Z3funiii(i32 noundef 1, i32 noundef 2, i32 noundef 3)
  ret i32 %1
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

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
