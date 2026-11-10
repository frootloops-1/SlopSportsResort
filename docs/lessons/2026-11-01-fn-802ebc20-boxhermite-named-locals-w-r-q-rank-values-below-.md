# fn_802EBC20: BoxHermite named locals w/r/q rank values below the shared 0.0f constant

- status: works
- tags: fpr,named-locals,inline,fn_802EBC20,RPBox
- scope: Pack/RPSports/RPBoxScene/RPBox_802eb834
- source: batch 2026-11-01

symptom: 98.8%: FPR register choice plus one lfs schedule swap in the trans lerp
cause: locals in an inline get ascending vregs in declaration order; colouring is descending; the 1.0f span, h*dy+y0 and t*z-c must colour after the 0.0f constant so they must be named locals
fix: BoxHermite locals b,dy,d,w,t,r,t2,c,a,h,t2x,q with w=x1-x0, r=h*dy+y0, q=t*z-c; no marker (same style as sibling BoxHermite2). Dead: statement reordering only, y,z,x order
