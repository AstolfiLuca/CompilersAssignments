; ModuleID = 'bc/test2.bc'
source_filename = "cpp/test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = icmp sgt i32 %3, 0
  br i1 %5, label %6, label %14

6:                                                ; preds = %4
  %7 = add nsw i32 %3, %2
  br label %8

8:                                                ; preds = %11, %6
  %.03 = phi i32 [ 0, %6 ], [ %10, %11 ]
  %9 = add nsw i32 %.03, 1
  %10 = add nsw i32 %.03, 1
  br label %11

11:                                               ; preds = %8
  %12 = icmp slt i32 %10, %3
  br i1 %12, label %8, label %13, !llvm.loop !6

13:                                               ; preds = %11
  br label %14

14:                                               ; preds = %13, %4
  %.14 = phi i32 [ %10, %13 ], [ 0, %4 ]
  %15 = add nsw i32 %.14, 1
  %16 = icmp sgt i32 %3, 0
  br i1 %16, label %17, label %25

17:                                               ; preds = %14
  br label %18

18:                                               ; preds = %22, %17
  %.2 = phi i32 [ 0, %17 ], [ %21, %22 ]
  %.01 = phi i32 [ %1, %17 ], [ %19, %22 ]
  %.0 = phi i32 [ %15, %17 ], [ %20, %22 ]
  %19 = add nsw i32 %.01, %.0
  %20 = add nsw i32 %.0, 1
  %21 = add nsw i32 %.2, 1
  br label %22

22:                                               ; preds = %18
  %23 = icmp slt i32 %21, %3
  br i1 %23, label %18, label %24, !llvm.loop !8

24:                                               ; preds = %22
  br label %25

25:                                               ; preds = %24, %14
  %.12 = phi i32 [ %19, %24 ], [ %1, %14 ]
  %.1 = phi i32 [ %20, %24 ], [ %15, %14 ]
  %26 = add nsw i32 %0, %.12
  %27 = add nsw i32 %26, %3
  %28 = add nsw i32 %27, %.1
  ret i32 %28
}

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #1 {
  %1 = call noundef i32 @_Z3fooiiii(i32 noundef 1, i32 noundef 2, i32 noundef 3, i32 noundef 4)
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
