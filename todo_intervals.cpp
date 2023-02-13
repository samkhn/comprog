// Intervals (array subsets)
// 
// Here are the six scenarios you'll see:
// (1) a and b do not overlap: a.end < b.begin
//  [  a  ][  b  ]
// (2) a and b overlap, b ends after a: a.begin <= b.begin & a.end < b.end
//  [  a  ]
//    [  b  ]
// (3) a overlaps completely with b:
//  [   a   ]
//    [ b ]
// (4) a and b overlap, a ends after b
//    [  a  ]
//  [  b  ]
// (5) b completely overlaps a
//    [ a ]
//  [   b   ]
// (6) a and b do not overlap: b.end < a.begin
//  [ b ][ a ]
//
// TODO: sort array of intervals by starting point
// TODO: check if two intervals overlap
// TODO: merge overlapping intervals
// TODO: rmq?
// TODO: https://emre.me/coding-patterns/merge-intervals/

int main() {
  return 0;
}
