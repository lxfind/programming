/*
 * CodeForces Round 186 Div2
 * Problem D: Ilya and Roads
 * Algorithm: DP, O(N^3)
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

#define N 301
#define INF LLONG_MAX / 2
LL dp[N][N];
LL cost[N][N];

int main()
{
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  FOR(i, 1, n + 1)
    FOR(j, i, n + 1)
      cost[i][j] = INF;    
  REP(i, m) {
    int l, r;
    LL c;
    scanf("%d %d %lld", &l, &r, &c);
    cost[l][r] = min(cost[l][r], c);
  }
  FORD(i, n - 1, 1)
    FOR(j, 1, n - i + 2) {
      if (j > 1)
        cost[j][j + i - 1] = min(cost[j][j + i - 1], cost[j - 1][j + i - 1]);
      if (j + i - 1 < n)
        cost[j][j + i - 1] = min(cost[j][j + i - 1], cost[j][j + i]);
    }
  REP(i, n + 1) {
    FOR(j, 1, n + 1)
      dp[i][j] = INF;
  }
  dp[0][0] = 0;
  FOR(i, 1, n + 1) {
    REP(j, i)
      dp[i][j] = dp[i - 1][j];
    REP(j, i)
      REP(p, i)
        dp[i][p + i - j] = min(dp[i][p + i - j], dp[j][p] + cost[j + 1][i]);
  }
  /*
  FOR(i, 1, n + 1)
    REP(j, i + 1)
      if (dp[i][j] != INF)
        printf("dp[%d][%d] = %lld\n", i, j, dp[i][j]);*/
  LL ans = INF;
  FOR(i, k, n + 1)
    ans = min(ans, dp[n][i]);
  if (ans == LLONG_MAX / 2)
    cout << -1;
  else
    cout << ans;
  return 0;
}

