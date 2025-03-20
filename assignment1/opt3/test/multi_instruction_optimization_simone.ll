define dso_local noundef i32 @_Z35multi_instruction_optimizazion_testv(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %0, 1  ; b = a + 1
  %4 = sub nsw i32 %3, 1  ; c = b - 1
  %5 = mul nsw i32 %1, 2  ; e = d * 2
  %6 = sdiv i32 %5, 2    ; f = e / 2
  ret i32 %0
}
