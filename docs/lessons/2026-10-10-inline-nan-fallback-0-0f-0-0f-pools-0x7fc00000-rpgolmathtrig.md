# Inline NaN fallback: -(0.0f/0.0f) pools 0x7FC00000 (RPGolMathTrig)

- status: works
- tags: rpgolmathtrig,nan,sdata2
- scope: RPGolMathTrig
- source: sonnet

symptom: file-static NaN object creates separate symbol, lfs mismatch
cause: NW4R_MATH_QNAN idiom is an inline expression
fix: return -(0.0f/0.0f) inline
