; ModuleID = 'bc/test7.optimized.bc'
source_filename = "cpp/test7.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3funiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  br label %4

4:                                                ; preds = %9, %3
  %.05 = phi i32 [ 0, %3 ], [ %10, %9 ]
  %.0 = phi i32 [ %0, %3 ], [ %8, %9 ]
  %.03 = phi i32 [ 0, %3 ], [ %12, %9 ]
  %5 = icmp slt i32 %.05, %1
  %6 = icmp slt i32 %.05, %1
  br i1 %5, label %7, label %13

7:                                                ; preds = %4
  %8 = add nsw i32 %.0, %1
  br label %11

9:                                                ; preds = %11
  %10 = add nsw i32 %.05, 1
  br label %4, !llvm.loop !6

11:                                               ; preds = %7
  %12 = add nsw i32 %.03, %1
  br label %9

13:                                               ; preds = %4
  br label %14

14:                                               ; preds = %18, %13
  %.04 = phi i32 [ 0, %13 ], [ %17, %18 ]
  %.01 = phi i32 [ 0, %13 ], [ %19, %18 ]
  %15 = icmp slt i32 %.01, %1
  br i1 %15, label %16, label %20

16:                                               ; preds = %14
  %17 = add nsw i32 %.04, %1
  br label %18

18:                                               ; preds = %16
  %19 = add nsw i32 %.01, 1
  br label %14, !llvm.loop !8

20:                                               ; preds = %14
  %21 = add nsw i32 %.0, %1
  %22 = add nsw i32 %21, %.03
  %23 = add nsw i32 %22, %.04
  ret i32 %23
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
