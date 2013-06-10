/*
 * HackerRank May Challenge 2013
 * Problem E: k-balance number
 * Algorithm: DP, Math
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

#define MOD 1000000007
#define ADD(a, b) ((((a) % MOD) + ((b) % MOD)) % MOD)
#define MUL(a, b) ((((a) % MOD) * ((b) % MOD)) % MOD)

ULL dpcnt[20][200];
ULL dpsum[20][200];
ULL tens[20];
ULL L, R;
int K;

void pre() {
  CLR(dpcnt, 0);
  CLR(dpsum, 0);
  tens[0] = 1;
  FOR(i, 1, 19)
    tens[i] = tens[i - 1] * 10;
  dpcnt[0][0] = 1;
  dpsum[0][0] = 0;
  FOR(i, 1, 19) {
    REP(j, 10)
      REP(k, (i - 1) * 9 + 1) {
        dpcnt[i][j + k] = ADD(dpcnt[i][j + k], dpcnt[i - 1][k]);
        dpsum[i][j + k] = ADD(dpsum[i][j + k], ADD(dpsum[i - 1][k], MUL(j, MUL(dpcnt[i - 1][k], tens[i - 1]))));
      }
  }
}

ULL accumulate(ULL a, ULL b) {
  if (a > b)
    return 0;
  if ((a & 1) == (b & 1))
    return MUL((a + b) / 2, b - a + 1);
  else
    return MUL((b - a + 1) / 2, a + b);
}

int log10(ULL x) {
  int r = 0;
  while (x) {
    x /= 10;
    r++;
  }
  return r;
}

int get(ULL x, int d) {
  return int((x % tens[d]) / tens[d - 1]);
}

bool isbalanced(ULL x) {
  int sum1 = 0;
  FOR(i, 1, K + 1)
    sum1 += get(x, i);
  int r = log10(x);
  int sum2 = 0;
  REP(i, K)
    sum2 += get(x, r - i);
  return sum1 == sum2;
}

ULL calc1(ULL prev, int choice, int star, int rest, int sum) {
  if (sum < 0)
    return 0;
  ULL ans = 0;
  prev = MUL(prev, tens[choice + star + rest]);
  REP(i, 9 * choice + 1) {
    ULL cnt1 = dpcnt[choice][i];
    ULL sum1 = MUL(dpsum[choice][i], tens[star + rest]);
    ULL cnt2 = tens[star] % MOD;
    ULL sum2 = MUL(accumulate(0, cnt2 - 1), tens[rest]);
    ULL cnt3 = dpcnt[rest][sum + i];
    ULL sum3 = dpsum[rest][sum + i];
    ULL cnt = MUL(MUL(cnt1, cnt2), cnt3);
    ans = ADD(ans, MUL(cnt, prev));
    ans = ADD(ans, MUL(MUL(cnt2, cnt3), sum1));
    ans = ADD(ans, MUL(MUL(cnt1, cnt3), sum2));
    ans = ADD(ans, MUL(MUL(cnt1, cnt2), sum3));
  }
  return ans;
}

ULL calc(int r, ULL prev) {
  assert(prev > 0);
  if (r == 0) {
    if (isbalanced(prev))
      return prev;
    else
      return 0;
  }
  int t = log10(prev);
  int sum1 = 0;
  REP(i, min(K, t))
    sum1 += get(prev, t - i);
  int sum2 = 0;
  FORD(i, K - r, 1)
    sum2 += get(prev, i);

  ULL ans = 0;
  if (t >= K) {
    if (r > K) {
      ans = calc1(prev, 0, r - K, K, sum1);
    } else {
      ans = calc1(prev, 0, 0, r, sum1 - sum2);
    }
  } else {
    if (r >= K + K - t) {
      ans = calc1(prev, K - t, r - K - K + t, K, sum1);
    } else if (r >= K) {
      ans = calc1(prev, r - K, K - (r - (K - t)), r - (K - t), sum1);
    } else {
      ans = calc1(prev, 0, K - t, r - (K - t), sum1 - sum2);
    }
  }
  return ans;
}

ULL calc(int r, ULL prev, int d1, int d2) {
  if (d1 > d2)
    return 0;
  ULL ans = 0;
  FOR(i, d1, d2 + 1) {
    ans = ADD(ans, calc(r - 1, prev * 10 + i));
  }
  return ans;
}

ULL solve() {
  int r = log10(R);
  while (r && get(L, r) == get(R, r))
    r--;
  ULL ans = 0;  
  if (isbalanced(L))
    ans = ADD(ans, L);
  if (isbalanced(R) && L != R)
    ans = ADD(ans, R);
  if (L == R)
    return ans;
  ULL prev = L / tens[r - 1];  
  FORD(i, r - 1, 1) {
    ans = ADD(ans, calc(i, prev, get(L, i) + 1, 9));
    prev = prev * 10 + get(L, i);
  }

  prev = R / tens[r - 1];
  FORD(i, r - 1, 1) {
    ans = ADD(ans, calc(i, prev, 0, get(R, i) - 1));
    prev = prev * 10 + get(R, i);
  }

  ans = ADD(ans, calc(r, L / tens[r], get(L, r) + 1, get(R, r) - 1));
  return ans;
}

int main()
{
  pre();
  cin >> L >> R >> K;
  ULL ans = 0;
  if (L < tens[K])
    ans = accumulate(L, min(R, tens[K] - 1));
  if (R >= tens[K]) {
    L = max(L, tens[K]);
    ans = ADD(ans, solve());
  }
  cout << ans;
  return 0;
}

