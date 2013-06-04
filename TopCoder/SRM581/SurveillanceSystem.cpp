/*
 * TopCoder SRM 581
 * Problem 250: SurveillanceSystem
 * Algorithm: Adhoc
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

 
class SurveillanceSystem {
public:
  int n;
  bool c[100];
  vector<int> a[100];
  int b[100];
  int ans[100];
	string getContainerInfo(string containers, vector <int> reports, int L) {		
    n = containers.length();
    REP(i, n)
      c[i] = containers[i] == 'X';    
    int cur = 0;
    REP(i, L)
      cur += c[i];
    a[cur].pb(0);
    FOR(i, L, n) {
      cur += c[i] - c[i - L];
      a[cur].pb(i - L + 1);
    }
    CLR(b, 0);
    REP(i, reports.size())
      b[reports[i]]++;
    CLR(ans, -1);
    REP(i, L + 1) {
      if (a[i].size() == b[i]) {
        REP(j, a[i].size())
          REP(k, L)
            ans[a[i][j] + k] = 1;
      } else if (b[i]) {
        REP(j, n) {
          if (ans[j] == 1)
            continue;
          int cnt = 0;
          REP(k, a[i].size())
            if (a[i][k] <= j && a[i][k] + L - 1 >= j)
              cnt++;
          if (b[i] > a[i].size() - cnt)
            ans[j] = 1;
          else if (cnt)
            ans[j] = 0;
        }
      }
    }
    string ret = "";
    REP(i, n)
      if (ans[i] == -1)
        ret += '-';
      else if (ans[i] == 0)
        ret += '?';
      else
        ret += '+';
    return ret;
	}
};
