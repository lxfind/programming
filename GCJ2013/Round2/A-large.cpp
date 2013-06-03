/*
 * Google Code Jam 2013 Round 2
 * Problem A: Ticket Swapping (Large, offline)
 * Algorithm: Greedy, Endpoint Sorting, O(MlogM)
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

#define MOD 1000002013
inline LL cost(LL o, LL e, LL p, LL n) {
  return (2 * n - (e - o - 1)) * (e - o) / 2 % MOD * p % MOD;
}

int main()
{
  int t;
  cin >> t;
  FOR(tt, 1, t + 1) {
    int n, m;
    cin >> n >> m;
    vector<Pi> v;
    LL orig = 0;
    REP(i, m) {
      int o, e, p;
      cin >> o >> e >> p;
      v.pb(mp(o, -p));
      v.pb(mp(e, p));
      orig = (orig + cost(o, e, p, n)) % MOD;
    }
    sort(v.begin(), v.end());
    priority_queue<Pi> pq;
    LL ans = 0;
    REP(i, v.size()) {
      Pi x = v[i];
      if (x.second < 0) {
        pq.push(mp(x.first, -x.second));
      } else {
        while (x.second) {
          Pi y = pq.top();
          int p = min(y.second, x.second);
          pq.pop();
          ans = (ans + cost(y.first, x.first, p, n)) % MOD;
          if (y.second > p)
            pq.push(mp(y.first, y.second - p));
          x.second -= p;
        }
      }
    }
    cout << "Case #" << tt << ": " << ((orig - ans + MOD) % MOD);
    cout << endl;
  }
  return 0;
}

