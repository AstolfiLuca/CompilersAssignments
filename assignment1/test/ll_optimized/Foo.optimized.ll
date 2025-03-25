; ModuleID = 'bc/Foo.optimized.bc'
source_filename = "ll/Foo.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = add nsw i32 %1, 1
  %4 = sub nsw i32 %3, 1
  %5 = add nsw i32 %1, 10
  %6 = mul nsw i32 %0, 3
  %7 = sdiv i32 %6, 3
  ret i32 %5
}
