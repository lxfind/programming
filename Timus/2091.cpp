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

int a[100][100];

int main() {
  int n, m;
  cin >> n >> m;
  REP(i, n)
    REP(j, m)
      cin >> a[i][j];

  int ans = INT_MAX;
  int mini = 0, minj = 0;
  REP(i, m)
    FOR(j, i + 1, m) {
      int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
      REP(k, n) {
        if (a[k][i]) {
          if (a[k][j]) {
            s1++;
          } else {
            s2++;
          }
        } else if (a[k][j]) {
          s3++;
        } else {
          s4++;
        }
      }
      int result = max(max(max(s1, s2), s3), s4);
      if (result < ans) {
        ans = result;
        mini = i;
        minj = j;
      }
    }
  cout << ans << endl;
  cout << (mini + 1) << " " << (minj + 1);
  return 0;
}
