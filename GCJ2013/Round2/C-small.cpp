/*
 * Google Code Jam 2013 Round 2
 * Problem C: Erdos–Szekeres (Small)
 * Algorithm: DP + DFS, O(N/A)
 * Copyright (C) 2013, Xun Li (lxfind@gmail.com)
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

#define N 2000
int a[N], b[N], incc[N], decc[N], x[N];
int n;

bool solve(int i) {
  if (i == n + 1) {
    REP(j, n)
      if (x[j] == 0)
        return false;
    return true;
  }
  vector<int> v;
  decc[n - 1] = 1;
  FORD(j, n - 2, 0) {
    int best = 1;
    FOR(k, j + 1, n)
      if (x[k] != 0 && (x[j] == 0 || x[j] > x[k]))
        best = max(best, decc[k] + 1);
    decc[j] = best;
  }
  incc[0] = 1;
  FOR(j, 1, n) {
    int best = 1;
    REP(k, j)
      if (x[k] != 0 && (x[j] == 0 || x[j] > x[k]))
        best = max(best, incc[k] + 1);
    incc[j] = best;
  }
  REP(j, n) {
    if (a[j] == incc[j] && b[j] == decc[j] && !x[j]) {
      v.pb(j);
    }
  }
  REP(j, v.size()) {
    x[v[j]] = i;
    if (solve(i + 1))
      return true;
    x[v[j]] = 0;
  }
  return false;
}

int main()
{
  int t;
  cin >> t;
  FOR(tt, 1, t + 1) {
    scanf("%d", &n);
    REP(i, n)
      scanf("%d", a + i);
    REP(i, n)
      scanf("%d", b + i);
    CLR(x, 0);
    solve(1);
    cout << "Case #" << tt << ":"; 
    REP(i, n)
      cout << " " << x[i];
    cout << endl;
  }
  return 0;
}

