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

#define N 100

int n, m;
map<int, int> g[N];
bool f[N];
int d[N];
int prevv[N];

void addEdge(int x, int y, int z) {
  x--;
  y--;
  if (g[x].find(y) == g[x].end()) {
    g[x][y] = g[y][x] = z;
  } else {
    g[x][y] = g[y][x] = min(g[x][y], z);
  }
}

void dijkstra(int start, int end) {
  CLR(f, 0);
  CLR(d, -1);
  CLR(prevv, -1);
  d[start] = 0;
  while (1) {
    int mind = INT_MAX;
    int mink = -1;
    REP(k, n) {
      if (!f[k] && d[k] != -1 && d[k] < mind) {
        mind = d[k];
        mink = k;
      }
    }
    if (mink == -1 || mink == end) break;
    for (map<int, int>::iterator I = g[mink].begin(), E = g[mink].end();
        I != E; ++I) {
      if (d[I->first] == -1 || d[I->first] >= d[mink] + I->second) {
        d[I->first] = d[mink] + I->second;
        prevv[I->first] = mink;
      }
    }
    f[mink] = true;
  }
}

void solve() {
  int ans = INT_MAX;
  vector<int> sequence;
  REP(i, n) {
    if (g[i].size() > 1) {
      map<int, int>::iterator itr = g[i].begin();
      int j = itr->first;
      int init = itr->second;
      g[i].erase(itr);
      g[j].erase(i);

      dijstra(i, j);
      if (d[j] != -1) {
        
        if (d[j] + init < ans) {
          ans = d[j] + init;
          sequence.clear();
          int tmp = j;
          do {
            sequence.pb(tmp);
            tmp = prevv[tmp];
          } while (tmp != i);
          sequence.pb(i);
        }
      } else {
        while (g[i].size() > 0) {
          map<int, int>::iterator itr = g[i].begin();
          int j = itr->first;
          g[i].erase(itr);
          g[j].erase(i);
        }
      }
    }
  }
  if (sequence.size()) {
    REP(i, sequence.size()) {
      if (i) cout << " ";
      cout << sequence[i] + 1;
    }
  } else {
    cout << "No solution.";
  }
  cout << endl;
}

int main() {
  while (1) {
    cin >> n;
    if (n == -1) break;
    REP(i, n) g[i].clear();
    cin >> m;
    REP(i, m) {
      int x, y, z;
      cin >> x >> y >> z;
      addEdge(x, y, z);
    }
    solve();
  }
  return 0;
}
