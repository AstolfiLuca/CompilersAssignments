; ModuleID = 'bc/test2.optimized.bc'
source_filename = "cpp/test2.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z3fooi(i32 noundef %0) #0 {
  %2 = icmp sgt i32 %0, 0
  br i1 %2, label %3, label %10

3:                                                ; preds = %1
  br label %4

4:                                                ; preds = %7, %3
  %.03 = phi i32 [ 0, %3 ], [ %5, %7 ]
  %.01 = phi i32 [ 0, %3 ], [ %6, %7 ]
  %5 = add nsw i32 %.03, %.01
  %6 = add nsw i32 %.01, 1
  br label %7

7:                                                ; preds = %4
  %8 = icmp slt i32 %6, %0
  br i1 %8, label %4, label %9, !llvm.loop !6

9:                                                ; preds = %7
  br label %10

10:                                               ; preds = %9, %1
  %.14 = phi i32 [ %5, %9 ], [ 0, %1 ]
  %11 = icmp sgt i32 %0, 0
  br i1 %11, label %12, label %19

12:                                               ; preds = %10
  br label %13

13:                                               ; preds = %16, %12
  %.12 = phi i32 [ 0, %12 ], [ %15, %16 ]
  %.0 = phi i32 [ 0, %12 ], [ %14, %16 ]
  %14 = add nsw i32 %.0, %.12
  %15 = add nsw i32 %.12, 1
  br label %16

16:                                               ; preds = %13
  %17 = icmp slt i32 %15, %0
  br i1 %17, label %13, label %18, !llvm.loop !8

18:                                               ; preds = %16
  br label %19

19:                                               ; preds = %18, %10
  %.1 = phi i32 [ %14, %18 ], [ 0, %10 ]
  %20 = add nsw i32 %.14, %.1
  ret i32 %20
}

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #1 {
  %1 = call noundef i32 @_Z3fooi(i32 noundef 4)
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
!5 = !{!"Ubuntu clang version 19.1.7 (++20250114103253+cd708029e0b2-1~exp1~20250114103309.40)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
