#include <set>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#define MID(x,y) ( ( x + y ) >> 1 )
#define L(x) ( x << 1 )
#define R(x) ( x << 1 | 1 )
#define REP(i,t) for(int i=0; i<(t); i++)
#define FOR(i,s,t) for(int i=(s); i<(t); i++)
#define FORD(i,a,b) for (int i = (a); i >= (b); i--)
#define FORL(i,s,t) for(L i=(s); i<(t); i++)
#define BUG puts("here!!!")
#define STOP system("pause")
#define file_r(x) freopen(x, "r", stdin)
#define file_w(x) freopen(x, "w", stdout)
#define EPS 1e-6
#define EQ(a, b) (fabs((a) - (b)) <= EPS)
#define POS(a) ((a) >= EPS)
#define NEG(a) ((a) <= -EPS)
#define BG(a, b) ((a) - (b) >= EPS)
#define LS(a, b) ((b) - (a) >= EPS)
#define CLR(a, x) memset( a, x, sizeof( a ) )
#define PI (atan(1.0) * 4)
#define SQ(x) ((x) * (x))
#define DIST(x1, y1, x2, y2) (sqrt(SQ((x1) - (x2)) + SQ((y1) - (y2))))
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define LOG2(x) (log(x) / log(2))
#define XX first.first
#define XY first.second
#define YX second.first
#define YY second.second

using namespace std;
typedef unsigned long long ULL;
typedef long long LL;
typedef pair<double, double> Pd;
typedef pair<int, int> Pi;
typedef pair<LL, LL> Pl;

int main() {
  int n, m;
  cin >> n >> m;
  int v1, v2, h1, h2, vmax = 0, hmax = 0;
  cin >> v1;
  REP(i, n - 2) {
    int x;
    cin >> x;
    vmax = max(vmax, x);
  }
  cin >> v2;
  cin >> h1;
  REP(i, m - 2) {
    int x;
    cin >> x;
    hmax = max(hmax, x);
  }
  cin >> h2;
  int ans = min(h1, v2);
  ans = max(ans, min(v1, h2));
  if (n > 2) {
    ans = max(ans, min(min(h1, h2), vmax));
  }
  if (m > 2) {
    ans = max(ans, min(min(v1, v2), hmax));
  }
  cout << ans;
  return 0;
}
