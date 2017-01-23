/**
 * Dynamic Programming
 */
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

#define N 100010
int dp[N];
int t[N];

int main() {
  int n;
  dp[0] = 0;
  t[0] = 0;
  cin >> n;
  FOR(i, 1, n + 1) {
    int x;
    cin >> x;
    t[i] = x;
    int m = dp[i - 1] + 20;
    int* prev90 = lower_bound(t, t + i, x - 89);
    int dp90 = prev90 == t ? 0 : dp[prev90 - t - 1];
    m = min(m, dp90 + 50);
    int *prev1440 = lower_bound(t, t + i, x - 1439);
    int dp1440 = prev1440 == t ? 0 : dp[prev1440 - t - 1];
    m = min(m, dp1440 + 120);
    dp[i] = m;
  }
  FOR(i, 1, n + 1) {
    cout << dp[i] - dp[i - 1] << endl;
  }
  return 0;
}
