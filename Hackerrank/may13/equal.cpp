/*
 * HackerRank May Challenge 2013
 * Problem B: Equal
 * Algorithm: DP, Adhoc
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

int dp[2000];
int a[10000];

int main()
{
  CLR(dp, 0);
  dp[1] = dp[2] = dp[5] = 1;
  dp[3] = dp[4] = 2;
  FOR(i, 6, 2000)
    dp[i] = min(min(dp[i - 1], dp[i - 2]), dp[i - 5]) + 1;
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    REP(i, n)
      scanf("%d", a + i);
    int smi = 0;
    REP(i, n)
      if (a[i] < a[smi])
        smi = i;
    int ans = INT_MAX;
    REP(j, 10) {
      int cur = dp[j];
      REP(i, n)
        if (i != smi)
          cur += dp[a[i] - a[smi] + j];
      ans = min(ans, cur);
    }
    printf("%d\n", ans);
  }
  return 0;
}

