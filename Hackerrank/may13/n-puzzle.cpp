/*
 * HackerRank May Challenge 2013
 * Problem D: N Puzzle
 * Algorithm: Random Walk, Adhoc
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

#define MU (cnt++, mvs.pb(0))
#define MD (cnt++, mvs.pb(1))
#define ML (cnt++, mvs.pb(2))
#define MR (cnt++, mvs.pb(3))

bool f[7][7];
int a[6][6];
int tmp[6][6];
int k;
vector<int> mvs;
int cnt;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char names[4][6] = {"UP", "DOWN", "LEFT", "RIGHT"};

void dump() {
  return;
  FOR(i, 1, k + 1) {
    FOR(j, 1, k + 1)
      cout << a[i][j] << " ";
    cout << endl;
  }
  cout << endl;
}

Pi find(int x) {
  FOR(i, 1, k + 1)
    FOR(j, 1, k + 1)
      if (a[i][j] == x)
        return mp(i, j);
}

void move0(int si, int sj, int ti, int tj) {
//  printf("Moving from (%d %d) to (%d %d)\n", si, sj, ti, tj);
  CLR(tmp, 0);
  tmp[si][sj] = -1;
  queue<Pi> q;
  q.push(mp(si, sj));
  bool finish = false;
  while (!finish) {
    Pi x = q.front();
    q.pop();
    REP(i, 4) {
      int nexti = x.first + dir[i][0];
      int nextj = x.second + dir[i][1];     
      if (!f[nexti][nextj] && !tmp[nexti][nextj]) {
        tmp[nexti][nextj] = i + 1;
        q.push(mp(nexti, nextj));
      }
      if (nexti == ti && nextj == tj) {
        finish = true; break;
      }
    }
  }
  vector<int> v;
  int x = 0;
  while (tmp[ti][tj] != -1) {
    v.pb(tmp[ti][tj] - 1);
    swap(x, a[ti][tj]);
    int d = tmp[ti][tj] - 1;
    d += (d & 1)?-1:1;
    ti += dir[d][0];
    tj += dir[d][1];
  }
  a[ti][tj] = x;
  FORD(i, v.size() - 1, 0) {
    cnt++; mvs.pb(v[i]);
  }
  dump();
}

// 0 is at (ti, tj) in the beginning, number is at (si, sj)
// Now we want to move number to 0's location
void move(int si, int sj, int ti, int tj) {
  int x = a[si][sj];
  move0(ti, tj, si, sj);
  while (a[ti][tj] != x) {
    Pi p = find(x);
    int ioff = 0, joff = 0;
    if (p.first > ti && !f[p.first - 1][p.second]) {
      ioff = -1;
    } else if (p.first < ti && !f[p.first + 1][p.second]) {
      ioff = 1;
    } else if (p.second > tj && !f[p.first][p.second - 1]) {
      joff = -1;
    } else if (p.second < tj && !f[p.first][p.second + 1]) {
      joff = 1;
    } else {
      assert(0);
    }
    f[p.first][p.second] = 1;
    move0(si, sj, p.first + ioff, p.second + joff);
    f[p.first][p.second] = 0;
    move0(p.first + ioff, p.second + joff, p.first, p.second);
    si = p.first; sj = p.second;
  }
}

void random_walk() {
  Pi p = find(0);
  int x = rand() % 5;
  bool moved = false;
  int i = p.first;
  int j = p.second;
  while (!moved) {
    REP(d, 4) {
      int nexti = i + dir[d][0];
      int nextj = j + dir[d][1];
      if (!f[nexti][nextj])
        if (!(x--)) {
          mvs.pb(d);
          swap(a[i][j], a[nexti][nextj]);
          moved = true;
          break;
        }
    }
  }
}

int main()
{
  scanf("%d", &k);
  FOR(i, 1, k + 1)
    FOR(j, 1, k + 1)
      scanf("%d", &a[i][j]);
  CLR(f, 0);
  REP(i, k + 1)
    f[0][i] = f[k + 1][i] = f[i][0] = f[i][k + 1] = 1;
  int num = k * k - 1;
  cnt = 0;
  dump();
  FORD(i, k, 2)
    FORD(j, k, 1)
      if (i > 2) {
        if (j > 2) {
          Pi p = find(0);
          move0(p.first, p.second, i, j);
          Pi pt = find(num--);
          move(pt.first, pt.second, i, j);
          f[i][j] = 1;
        } else if (j == 2) {    
          while (1) {
            Pi p = find(0);
            move0(p.first, p.second, i, 1);
            Pi pt = find(num);
            move(pt.first, pt.second, i, 1);
            if ((a[i][2] == 0 && a[i - 1][2] == num - 1) || a[i][2] == num - 1) {
              REP(i, 10)
                random_walk();              
            } else {
              break;
            }
          }
          f[i][1] = 1;
          Pi p = find(0);
          move0(p.first, p.second, i - 1, 1);
          Pi pt = find(num - 1);
          move(pt.first, pt.second, i - 1, 1);
          f[i - 1][1] = 1;
          p = find(0);
          move0(p.first, p.second, i, 2);
          f[i][1] = 0;
          move0(i, 2, i, 1);
          f[i][2] = 1;
          f[i - 1][1] = 0;
          move0(i, 1, i - 1, 1);
          f[i][1] = 1;
          num -= 2;
        }
      } else if (j > 2) {
        while (1) {
          Pi p = find(0);
          move0(p.first, p.second, 1, j);
          Pi pt = find(num);
          move(pt.first, pt.second, 1, j);
          if ((a[2][j] == 0 && a[2][j - 1] == num - k) || a[2][j] == num - k) {
            REP(i, 10)
              random_walk();            
          } else {
            break;
          }
        }
        f[1][j] = 1;
        Pi p = find(0);
        move0(p.first, p.second, 1, j - 1);
        Pi pt = find(num - k);
        move(pt.first, pt.second, 1, j - 1);
        f[1][j - 1] = 1;
        p = find(0);
        move0(p.first, p.second, 2, j);
        f[1][j] = 0;
        move0(2, j, 1, j);
        f[2][j] = 1;
        f[1][j - 1] = 0;
        move0(1, j, 1, j - 1);
        f[1][j] = 1;
        num--;
      } else {
        while (a[1][1] != 0 || a[1][2] != 1 || a[2][1] != k)
          random_walk();
      }
  dump();
  cout << mvs.size() << endl;
  REP(i, mvs.size())
    cout << names[mvs[i]] << endl;
  return 0;
}

