/*
 * HackerRank May Challenge 2013
 * Problem C: Cut Tree
 * Algorithm: Tree DP, O(n^3)
 * Copyright (C) 2013, Xun Li (lxfind@gmail.com)
 */

#include <set>
#include <bitset>
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
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <sstream>
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
#define setmin(a, b) (a = min(a, b))
#define setmax(a, b) (a = max(a, b))
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

#define N 51
int n;
vector<int> g[N];
LL dp[N][N];
LL tmp[N];

void solve(int cur, int par) {
  dp[cur][0] = 1;
  REP(i, g[cur].size()) {
    int x = g[cur][i];
    if (x == par)
      continue;
    solve(x, cur);
    FORD(j, n - 1, 0)
      tmp[j + 1] = dp[cur][j];
    tmp[0] = 0;
    REP(j, n)
      REP(k, n - j)
        tmp[j + k] += dp[cur][j] * dp[x][k];
    REP(j, n)
      dp[cur][j] = tmp[j];
    FORD(j, n - 1, 0)
      dp[x][j + 1] = dp[x][j];
    dp[x][0] = 0;
  }
}

int main()
{
  int k;
  scanf("%d %d", &n, &k);
  REP(i, n - 1) {
    int x, y;
    scanf("%d %d", &x, &y);
    g[x].pb(y); g[y].pb(x);
  }
  CLR(dp, 0);
  solve(1, 0);
  /*
  FOR(i, 1, n + 1)
    REP(j, n)
      if (dp[i][j])
        printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);*/
  LL ans = 0;
  FOR(i, 1, n + 1)
    REP(j, k + 1)
      ans += dp[i][j];
  cout << ans + 1;
  return 0;
}

