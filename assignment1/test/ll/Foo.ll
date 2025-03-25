; int foo(int a, int b) {
;   c = b + 1;
;   d = c - 1;    d = b
;   e = d + 10;
;   d = 11;
;   z = d+2;
;   f = a * 3;
;   g = e / 3;
;   return e;
; }

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %1, 1
  %4 = sub nsw i32 %3, 1
  %5 = add nsw i32 %4, 10
  %6 = mul nsw i32 %0, 3
  %7 = sdiv i32 %6, 3
  ret i32 %5
}