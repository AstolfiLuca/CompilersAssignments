; ModuleID = 'bc/test5.optimized.bc'
source_filename = "cpp/test5.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = alloca [10 x i32], align 16
  %6 = alloca [10 x i32], align 16
  br label %7

7:                                                ; preds = %14, %4
  %.01 = phi i32 [ 0, %4 ], [ %15, %14 ]
  %8 = icmp slt i32 %.01, 10
  %9 = icmp slt i32 %.01, 10
  br i1 %8, label %10, label %22

10:                                               ; preds = %7
  %11 = add nsw i32 %0, %1
  %12 = sext i32 %.01 to i64
  %13 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %12
  store i32 %11, ptr %13, align 4
  br label %16

14:                                               ; preds = %16
  %15 = add nsw i32 %.01, 1
  br label %7, !llvm.loop !6

16:                                               ; preds = %10
  %17 = sext i32 %.01 to i64
  %18 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 %17
  %19 = load i32, ptr %18, align 4
  %20 = sext i32 %.01 to i64
  %21 = getelementptr inbounds [10 x i32], ptr %6, i64 0, i64 %20
  store i32 %19, ptr %21, align 4
  br label %14

22:                                               ; preds = %7
  %23 = add nsw i32 %2, %3
  %24 = getelementptr inbounds [10 x i32], ptr %5, i64 0, i64 0
  %25 = load i32, ptr %24, align 16
  %26 = getelementptr inbounds [10 x i32], ptr %6, i64 0, i64 0
  %27 = load i32, ptr %26, align 16
  %28 = add nsw i32 %25, %27
  %29 = add nsw i32 %28, %23
  ret i32 %29
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
