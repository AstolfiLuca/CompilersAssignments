; ModuleID = 'bc/test3.bc'
source_filename = "cpp/test3.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  br label %5

5:                                                ; preds = %8, %4
  %.02 = phi i32 [ 0, %4 ], [ %6, %8 ]
  %.0 = phi i32 [ %0, %4 ], [ %7, %8 ]
  %6 = add nsw i32 %.02, 1
  %7 = add nsw i32 %.0, %6
  br label %8

8:                                                ; preds = %5
  %9 = icmp slt i32 %6, %3
  br i1 %9, label %5, label %10, !llvm.loop !6

10:                                               ; preds = %8
  br label %11

11:                                               ; preds = %20, %10
  %.13 = phi i32 [ 0, %10 ], [ %12, %20 ]
  %.01 = phi i32 [ %1, %10 ], [ %.1, %20 ]
  %12 = add nsw i32 %.13, 1
  %13 = add nsw i32 %.01, 1
  %14 = icmp sgt i32 %13, 0
  br i1 %14, label %15, label %17

15:                                               ; preds = %11
  %16 = sub nsw i32 %13, %12
  br label %19

17:                                               ; preds = %11
  %18 = add nsw i32 %13, %12
  br label %19

19:                                               ; preds = %17, %15
  %.1 = phi i32 [ %16, %15 ], [ %18, %17 ]
  br label %20

20:                                               ; preds = %19
  %21 = icmp slt i32 %12, %3
  br i1 %21, label %11, label %22, !llvm.loop !8

22:                                               ; preds = %20
  %23 = mul nsw i32 %.1, %2
  %24 = add nsw i32 %7, %23
  ret i32 %24
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
