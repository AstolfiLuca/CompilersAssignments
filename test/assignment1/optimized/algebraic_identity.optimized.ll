; ModuleID = 'algebraic_identity.optimized.bc'
source_filename = "algebraic_identity.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local noundef i32 @_Z23algebraic_identity_testv() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 1, ptr %1, align 4
  %6 = load i32, ptr %1, align 4
  %7 = add nsw i32 %6, 0
  store i32 %6, ptr %1, align 4
  %8 = load i32, ptr %1, align 4
  %9 = add nsw i32 %8, 1
  store i32 %9, ptr %2, align 4
  %10 = load i32, ptr %1, align 4
  %11 = add nsw i32 0, %10
  store i32 %10, ptr %1, align 4
  %12 = load i32, ptr %1, align 4
  %13 = add nsw i32 %12, 2
  store i32 %13, ptr %3, align 4
  %14 = load i32, ptr %1, align 4
  %15 = mul nsw i32 %14, 1
  store i32 %15, ptr %1, align 4
  %16 = load i32, ptr %1, align 4
  %17 = add nsw i32 %16, 3
  store i32 %17, ptr %4, align 4
  %18 = load i32, ptr %1, align 4
  %19 = mul nsw i32 1, %18
  store i32 %19, ptr %1, align 4
  %20 = load i32, ptr %1, align 4
  %21 = add nsw i32 %20, 4
  store i32 %21, ptr %5, align 4
  %22 = load i32, ptr %1, align 4
  ret i32 %22
}

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 19.1.1 (1ubuntu1)"}
