; ModuleID = 'assignment1/opt2/test/strength_reduction.cpp'
source_filename = "assignment1/opt2/test/strength_reduction.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local noundef i32 @_Z23strength_reduction_testii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %6 = load i32, ptr %3, align 4
  %7 = mul nsw i32 %6, 15
  store i32 %7, ptr %3, align 4
  %8 = load i32, ptr %3, align 4
  %9 = mul nsw i32 %8, 9
  store i32 %9, ptr %3, align 4
  %10 = load i32, ptr %3, align 4
  %11 = mul nsw i32 %10, 6
  store i32 %11, ptr %3, align 4
  %12 = load i32, ptr %3, align 4
  %13 = mul nsw i32 %12, -15
  store i32 %13, ptr %3, align 4
  %14 = load i32, ptr %4, align 4
  %15 = sdiv i32 %14, 15
  store i32 %15, ptr %5, align 4
  %16 = load i32, ptr %4, align 4
  %17 = sdiv i32 %16, 16
  store i32 %17, ptr %4, align 4
  %18 = load i32, ptr %4, align 4
  ret i32 %18
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main() #1 {
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  %2 = call noundef i32 @_Z23strength_reduction_testii(i32 noundef 3, i32 noundef 44)
  ret i32 %2
}

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Debian clang version 17.0.6 (++20231208085813+6009708b4367-1~exp1~20231208085906.81)"}
