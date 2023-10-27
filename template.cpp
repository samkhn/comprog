#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;
using str = string;

using pii = pair<int, int>;
#define mp make_pair

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;
using Vi = V<int>;
// TODO: replace Vb with bitset?
using Vb = V<bool>;
using Vpii = V<pii>;

#define Sz(x) static_cast<int>(x.size())
#define All(x) begin(x), end(x)
#define SorA(x) sort(All(x))
#define Rsz resize
#define PB push_back
#define Ft front()
#define Bk back()

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a);
#define ROF(i, a, b) for (int i = (b)-1; i >= a; --i)
#define R0F(i, a) ROF(i, 0, a);
// Repeat
#define Rep(a) F0R(_, a)
#define Each(a, x) for (auto& a: x)

const int MOD = 1e9+7;
const db PI = acos((db)-1);
mt19937 rng(0);

tcT> bool CkMin(T& a, const T& b) {
  return b < a ? a = b, 1 : 0; }  // set a = min(a, b);
tcT> bool CkMax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0; }  // set a = max(a, b);

int main() {
  cin.tie(0)->sync_with_stdio(0);
  // SOLVE
}
