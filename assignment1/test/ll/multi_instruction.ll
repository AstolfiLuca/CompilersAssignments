; ModuleID = 'bc/multi_instruction.bc'
source_filename = "cpp/multi_instruction.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z35multi_instruction_optimizazion_testiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  %5 = add nsw i32 %0, 1
  %6 = sub nsw i32 %5, 1
  %7 = add nsw i32 %6, 5
  %8 = add nsw i32 1, %0
  %9 = sub nsw i32 %8, 1
  %10 = add nsw i32 %9, 5
  %11 = sub nsw i32 %0, 1
  %12 = add nsw i32 %11, 1
  %13 = add nsw i32 %12, 5
  %14 = add nsw i32 -1, %0
  %15 = add nsw i32 %14, 1
  %16 = add nsw i32 %15, 5
  %17 = sub nsw i32 1, %0
  %18 = sub nsw i32 1, %17
  %19 = add nsw i32 %18, 5
  %20 = mul nsw i32 %0, 3
  %21 = sdiv i32 %20, 3
  %22 = add nsw i32 %21, 5
  %23 = mul nsw i32 3, %0
  %24 = sdiv i32 %23, 3
  %25 = add nsw i32 %24, 5
  %26 = add nsw i32 1, %0
  %27 = add nsw i32 -1, %26
  %28 = add nsw i32 %27, 5
  %29 = sub nsw i32 -1, %0
  %30 = sub nsw i32 -1, %29
  %31 = add nsw i32 %30, 5
  %32 = sub nsw i32 %0, 1
  %33 = add nsw i32 1, %32
  %34 = add nsw i32 %33, 5
  %35 = add nsw i32 1, %0
  %36 = sub nsw i32 1, %35
  %37 = add nsw i32 %36, 5
  %38 = sub nsw i32 -1, %0
  %39 = add nsw i32 -1, %38
  %40 = add nsw i32 %39, 5
  %41 = sub nsw i32 1, %0
  %42 = add nsw i32 1, %41
  %43 = add nsw i32 %42, 5
  ret i32 %37
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 19.1.1 (1ubuntu1~24.04.2)"}
