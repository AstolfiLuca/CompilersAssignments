; ModuleID = 'bc/test5.bc'
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

16:                                               ; preds = %24, %15
  %.0 = phi i32 [ 0, %15 ], [ %25, %24 ]
  %17 = icmp slt i32 %.0, 10
  br i1 %17, label %18, label %26

18:                                               ; preds = %16
  %19 = sext i32 %.0 to i64
  %20 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %19
  %21 = load i32, ptr %20, align 4
  %22 = sext i32 %.0 to i64
  %23 = getelementptr inbounds [10 x i32], ptr %6, i64 0, i64 %22
  store i32 %21, ptr %23, align 4
  br label %24

24:                                               ; preds = %18
  %25 = add nsw i32 %.0, 1
  br label %16, !llvm.loop !8

26:                                               ; preds = %16
  %27 = add nsw i32 %2, %3
  %28 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 0
  %29 = load i32, ptr %28, align 16
  %30 = getelementptr inbounds [10 x i32], ptr %6, i64 0, i64 0
  %31 = load i32, ptr %30, align 16
  %32 = add nsw i32 %29, %31
  %33 = add nsw i32 %32, %27
  ret i32 %33
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
