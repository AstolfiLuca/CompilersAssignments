; ModuleID = 'bc/test6.optimized.bc'
source_filename = "cpp/test6.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooii(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 10, %1
  br label %4

4:                                                ; preds = %13, %2
  %.03 = phi i32 [ 0, %2 ], [ %14, %13 ]
  %.01 = phi i32 [ undef, %2 ], [ %.1, %13 ]
  %.0 = phi i32 [ %0, %2 ], [ 5, %13 ]
  %5 = icmp slt i32 %.03, 10
  %6 = icmp slt i32 %.03, 10
  br i1 %5, label %7, label %17

7:                                                ; preds = %4
  %8 = add nsw i32 %.0, %.01
  %9 = icmp sgt i32 %8, 0
  br i1 %9, label %10, label %11

10:                                               ; preds = %7
  br label %12

11:                                               ; preds = %7
  br label %12

12:                                               ; preds = %11, %10
  %.1 = phi i32 [ 10, %10 ], [ 20, %11 ]
  br label %15

13:                                               ; preds = %15
  %14 = add nsw i32 %.03, 1
  br label %4, !llvm.loop !6

15:                                               ; preds = %12
  %16 = add nsw i32 %.03, 1
  br label %13

17:                                               ; preds = %4
  ret i32 %.0
}

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #1 {
  %1 = call noundef i32 @_Z3fooii(i32 noundef 1, i32 noundef 2)
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
