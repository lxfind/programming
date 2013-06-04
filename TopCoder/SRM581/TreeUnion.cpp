/*
 * TopCoder SRM 581
 * Problem 500: TreeUnion
 * Algorithm: Probability
 * Copyright (C) 2013, Xun Li (lxfind@gmail.com)
 */

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define MID(x,y) ( ( x + y ) >> 1 )
#define L(x) ( x << 1 )
#define R(x) ( x << 1 | 1 )
#define REP(i,t) for(int i=0; i<(t); i++)
#define FOR(i,s,t) for(int i=(s); i<(t); i++)
#define FORD(i,s,t) for(int i=(s); i>=(t); i--)
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
#define LOG2(x) (log(x) / log(2))
#define XX first.first
#define XY first.second
#define YX second.first
#define YY second.second
#define pb push_back

using namespace std;
typedef unsigned long long ULL;
typedef long long LL;
typedef pair<double, double> Pd;
typedef pair<int, int> Pi;
typedef pair<LL, LL> Pl; 

vector<int> splitInts(string str) {
  istringstream iss(str);
  int x;
  vector<int> ret;
  while (iss >> x)
    ret.push_back(x);
  return ret;
}

vector<int> splitInts(vector<string> strs) {
  string str = "";
  REP(i, strs.size())
    str += strs[i];
  return splitInts(str);
}

#define N 500
class TreeUnion {
public:
  int n;
  vector<int> t1[N];
  vector<int> t2[N];
  int d1[N + 1];
  int d2[N + 1];

  void dfs(int cur, int par, int deg, vector<int> t[N], int d[N + 1]) {
    d[deg]++;
    REP(i, t[cur].size())
      if (t[cur][i] != par)
        dfs(t[cur][i], cur, deg + 1, t, d);
  }

  void calcdist(vector<int> t[N], int d[N + 1]) {
    CLR(d, 0);
    REP(i, n) {
      dfs(i, -1, 1, t, d);
    }
    FOR(i, 2, n + 1)
      d[i] /= 2;
  }
	double expectedCycles(vector <string> tree1, vector <string> tree2, int K) {
    if (K == 3)
      return 0;
		vector<int> v1 = splitInts(tree1);
    vector<int> v2 = splitInts(tree2);
    n = v1.size() + 1;
    REP(i, n - 1) {
      t1[v1[i]].pb(i + 1);
      t1[i + 1].pb(v1[i]);
    }
    REP(i, n - 1) {
      t2[v2[i]].pb(i + 1);
      t2[i + 1].pb(v2[i]);
    }
    calcdist(t1, d1);
    calcdist(t2, d2);
    double tmp = 1 / double(n) / double(n - 1) * 2;
    double ans = 0;
    FOR(i, 2, K - 1)
      ans += tmp * d1[i] * d2[K - i];
    return ans;
	}
};
