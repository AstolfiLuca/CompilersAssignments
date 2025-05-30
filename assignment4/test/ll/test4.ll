; ModuleID = 'bc/test4.bc'
source_filename = "cpp/test4.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3funiii(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  br label %4

4:                                                ; preds = %8, %3
  %.03 = phi i32 [ 0, %3 ], [ %9, %8 ]
  %.0 = phi i32 [ %0, %3 ], [ %7, %8 ]
  %5 = icmp slt i32 %.03, %1
  br i1 %5, label %6, label %10

6:                                                ; preds = %4
  %7 = add nsw i32 %.0, %1
  br label %8

8:                                                ; preds = %6
  %9 = add nsw i32 %.03, 1
  br label %4, !llvm.loop !6

10:                                               ; preds = %4
  br label %11

11:                                               ; preds = %15, %10
  %.02 = phi i32 [ 0, %10 ], [ %16, %15 ]
  %.1 = phi i32 [ %.0, %10 ], [ %14, %15 ]
  %12 = icmp slt i32 %.02, %1
  br i1 %12, label %13, label %17

13:                                               ; preds = %11
  %14 = add nsw i32 %.1, %1
  br label %15

15:                                               ; preds = %13
  %16 = add nsw i32 %.02, 1
  br label %11, !llvm.loop !8

17:                                               ; preds = %11
  br label %18

18:                                               ; preds = %22, %17
  %.01 = phi i32 [ 0, %17 ], [ %23, %22 ]
  %.2 = phi i32 [ %.1, %17 ], [ %21, %22 ]
  %19 = icmp slt i32 %.01, %2
  br i1 %19, label %20, label %24

20:                                               ; preds = %18
  %21 = add nsw i32 %.2, %1
  br label %22

22:                                               ; preds = %20
  %23 = add nsw i32 %.01, 1
  br label %18, !llvm.loop !9

24:                                               ; preds = %18
  %25 = add nsw i32 %.2, %1
  ret i32 %25
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
!9 = distinct !{!9, !7}
