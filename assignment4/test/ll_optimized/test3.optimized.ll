; ModuleID = 'bc/test3.optimized.bc'
source_filename = "cpp/test3.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooiiii(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3) #0 {
  br label %5

5:                                                ; preds = %10, %4
  %.02 = phi i32 [ 0, %4 ], [ %6, %10 ]
  %.0 = phi i32 [ %0, %4 ], [ %7, %10 ]
  %.01 = phi i32 [ %1, %4 ], [ %13, %10 ]
  %6 = add nsw i32 %.02, 1
  %7 = add nsw i32 %.0, %6
  %8 = add nsw i32 %.02, 1
  %9 = add nsw i32 %.01, 1
  br label %12

10:                                               ; preds = %14
  %11 = icmp slt i32 %6, %3
  br i1 %11, label %5, label %15, !llvm.loop !6

12:                                               ; preds = %5
  %13 = sub nsw i32 %9, %8
  br label %14

14:                                               ; preds = %12
  br label %10

15:                                               ; preds = %10
  %16 = mul nsw i32 %13, %2
  %17 = add nsw i32 %7, %16
  ret i32 %17
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
