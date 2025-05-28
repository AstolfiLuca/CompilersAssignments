; ModuleID = 'bc/test5.optimized.bc'
source_filename = "cpp/test5.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = alloca [10 x i32], align 16
  %6 = alloca [10 x i32], align 16
  br label %7

7:                                                ; preds = %15, %4
  %.04 = phi i32 [ 0, %4 ], [ %16, %15 ]
  %8 = icmp slt i32 %.04, 10
  br i1 %8, label %9, label %17

9:                                                ; preds = %7
  %10 = sext i32 %.04 to i64
  %11 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %10
  %12 = load i32, ptr %11, align 4
  %13 = sext i32 %.04 to i64
  %14 = getelementptr inbounds [10 x i32], ptr %6, i64 0, i64 %13
  store i32 %12, ptr %14, align 4
  br label %15

15:                                               ; preds = %9
  %16 = add nsw i32 %.04, 1
  br label %7, !llvm.loop !6

17:                                               ; preds = %7
  br label %18

18:                                               ; preds = %28, %17
  %.03 = phi i32 [ 0, %17 ], [ %29, %28 ]
  %19 = icmp slt i32 %.03, 10
  br i1 %19, label %20, label %30

20:                                               ; preds = %18
  %21 = add nsw i32 %.03, 1
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds [10 x i32], ptr %6, i64 0, i64 %22
  %24 = load i32, ptr %23, align 4
  %25 = add nsw i32 %.03, 1
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %26
  store i32 %24, ptr %27, align 4
  br label %28

28:                                               ; preds = %20
  %29 = add nsw i32 %.03, 1
  br label %18, !llvm.loop !8

30:                                               ; preds = %18
  br label %31

31:                                               ; preds = %37, %30
  %.02 = phi i32 [ 11, %30 ], [ %38, %37 ]
  %.0 = phi i32 [ %0, %30 ], [ %36, %37 ]
  %32 = icmp sge i32 %.02, 0
  br i1 %32, label %33, label %39

33:                                               ; preds = %31
  %34 = sext i32 %.02 to i64
  %35 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %34
  %36 = load i32, ptr %35, align 4
  br label %37

37:                                               ; preds = %33
  %38 = add nsw i32 %.02, -1
  br label %31, !llvm.loop !9

39:                                               ; preds = %31
  br label %40

40:                                               ; preds = %46, %39
  %.01 = phi i32 [ 11, %39 ], [ %47, %46 ]
  %41 = icmp sge i32 %.01, 0
  br i1 %41, label %42, label %48

42:                                               ; preds = %40
  %43 = sub nsw i32 %.01, 1
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %44
  store i32 %1, ptr %45, align 4
  br label %46

46:                                               ; preds = %42
  %47 = add nsw i32 %.01, -1
  br label %40, !llvm.loop !10

48:                                               ; preds = %40
  %49 = add nsw i32 %.0, %3
  ret i32 %49
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
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
