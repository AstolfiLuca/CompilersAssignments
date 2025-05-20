; ModuleID = 'bc/test5.optimized.bc'
source_filename = "cpp/test5.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = alloca [10 x i32], align 16
  %6 = alloca [10 x i32], align 16
  br label %7

7:                                                ; preds = %13, %4
  %.01 = phi i32 [ 0, %4 ], [ %14, %13 ]
  %8 = icmp slt i32 %.01, 10
  br i1 %8, label %9, label %15

9:                                                ; preds = %7
  %10 = add nsw i32 %0, %1
  %11 = sext i32 %.01 to i64
  %12 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %11
  store i32 %10, ptr %12, align 4
  br label %13

13:                                               ; preds = %9
  %14 = add nsw i32 %.01, 1
  br label %7, !llvm.loop !6

15:                                               ; preds = %7
  br label %16

16:                                               ; preds = %26, %15
  %.0 = phi i32 [ 0, %15 ], [ %27, %26 ]
  %17 = icmp slt i32 %.0, 10
  br i1 %17, label %18, label %28

18:                                               ; preds = %16
  %19 = add nsw i32 %.0, 1
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %20
  %22 = load i32, ptr %21, align 4
  %23 = add nsw i32 %22, %1
  %24 = sext i32 %.0 to i64
  %25 = getelementptr inbounds [10 x i32], ptr %6, i64 0, i64 %24
  store i32 %23, ptr %25, align 4
  br label %26

26:                                               ; preds = %18
  %27 = add nsw i32 %.0, 1
  br label %16, !llvm.loop !8

28:                                               ; preds = %16
  %29 = add nsw i32 %0, %3
  ret i32 %29
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 19.1.1 (1ubuntu1)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
