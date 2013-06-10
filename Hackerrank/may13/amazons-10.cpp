/*
 * HackerRank May Challenge 2013
 * Problem F: Amazons
 * Algorithm: Heuristic Search, DFS Scanning
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
#define MID(x,y) ( ( x + y ) >> 1 )
#define L(x) ( x << 1 )
#define R(x) ( x << 1 | 1 )
#define REP(i,t) for(int i=0; i<(t); i++)
#define FOR(i,s,t) for(int i=(s); i<(t); i++)
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

using namespace std;
typedef unsigned long long ULL;
typedef long long LL;
typedef pair<double, double> Pd;
typedef pair<int, int> Pi;
typedef pair<LL, LL> Pl;

#define TIMES_PER_SEC (2.1e9)

unsigned long long rdtsc()
{
    unsigned long long time;
    __asm__ volatile ("rdtsc" : "=A" (time));
    return time;
}
double last_time = 0, accu_time = 0;
double gettime()
{
  double ret = (double)rdtsc()/TIMES_PER_SEC;
  if (ret < last_time - 1) {
    accu_time += (((long long)(1) << 32) - 1) / TIMES_PER_SEC;
  }
  last_time = ret;
  return ret + accu_time;
}

#define INF INT_MAX / 2
#define LEVEL 10
#define CANDSIZE 5

struct Move {
  Pi from, to, land;
  Move() {}
  Move(Pi f, Pi t, Pi l): from(f), to(t), land(l) {}
};

//status: 0: unknown, 1: must win, -1: must lose
struct Node {  
  vector<pair<int, Node*> > cand;
  Move m, bestm;
  int best, status;
  double score;
  Node() {
    score = best = INF;
    status = 0;
  }
};

const int dir[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
char b[10][10];
Node root;
double start;

inline bool empty(char b[10][10], int i, int j) {
  return i >= 0 && i < 10 && j >= 0 && j < 10 && b[i][j] == '-';
}

inline bool cmp(pair<Pi, Move> p1, pair<Pi, Move> p2) {
  return p1.first < p2.first;
}

int calc(char b[10][10], char p) {
  int score = 0;
  REP(i, 10)
    REP(j, 10)
      if (b[i][j] == p)
        REP(k, 8) {
          int ii = i, jj = j;
          while (1) {
            ii += dir[k][0]; jj += dir[k][1];
            if (empty(b, ii, jj)) {
              swap(b[i][j], b[ii][jj]);
              REP(d, 8) {
                int iii = ii, jjj = jj;
                while (1) {
                  iii += dir[d][0]; jjj += dir[d][1];
                  if (empty(b, iii, jjj))
                    score++;
                  else
                    break;
                }
              }
              swap(b[i][j], b[ii][jj]);
            } else
              break;
          }
        }      
  return score;
}

void dump(char p) {
  cout << p << "'s turn" << endl;
  REP(i, 10) {
    REP(j, 10)
      cout << b[i][j];
    cout << endl;
  }
  cout << endl;
}

void evaluate(Node* node, char p) {
  vector<pair<Pi, Move> > v;
  char opp = p == 'W'?'B':'W';
  REP(i, 10)
    REP(j, 10)
      if (b[i][j] == p)
        REP(k, 8) {
          int ii = i, jj = j;
          while (1) {
            ii += dir[k][0]; jj += dir[k][1];
            if (empty(b, ii, jj)) {
              swap(b[i][j], b[ii][jj]);
              REP(d, 8) {
                int iii = ii, jjj = jj;
                while (1) {
                  iii += dir[d][0]; jjj += dir[d][1];
                  if (empty(b, iii, jjj)) {
                    b[iii][jjj] = '.';
                    v.push_back(mp(mp(calc(b, opp), -calc(b, p)), Move(mp(i, j), mp(ii, jj), mp(iii, jjj))));
                    b[iii][jjj] = '-';
                  } else
                    break;
                }
              }
              swap(b[i][j], b[ii][jj]);
            } else
              break;
          }
        }      
  sort(v.begin(), v.end(), cmp);
  if (!v.empty())
    node->score = node->best = v[0].XX;
  REP(i, min(CANDSIZE, int(v.size()))) {
    Move& m = v[i].second;
    Node* newnode = new Node();
    newnode->m = m;
    node->cand.push_back(mp(v[i].XX, newnode));
    if (v[i].XX == 0)
      break;
  }
  if (v.size() == 0)
    node->status = -1;
  else {
    if (node->best == 0)
      node->status = 1;
    node->bestm = v[0].second;
  }
}

void evaluate(Node* node, char p, int level) {
  char opp = p == 'W' ? 'B' : 'W'; 
  if (level == 0) {
    evaluate(node, p);
  } else if (node->status == 0) {
    node->score = INF;
    for (vector<pair<int, Node*> >::iterator itr = node->cand.begin(); itr != node->cand.end();) {
      swap(b[itr->second->m.from.first][itr->second->m.from.second],
           b[itr->second->m.to.first][itr->second->m.to.second]);
      b[itr->second->m.land.first][itr->second->m.land.second] = '.';
      evaluate(itr->second, opp, level - 1);
      b[itr->second->m.land.first][itr->second->m.land.second] = '-';
      swap(b[itr->second->m.from.first][itr->second->m.from.second],
           b[itr->second->m.to.first][itr->second->m.to.second]);
      if (itr->second->status == 1) {
        itr = node->cand.erase(itr);
      } else if (itr->second->status == -1) {
        node->status = 1;
        break;
      } else {
        if (itr->first / itr->second->score < node->score) {
          node->score = itr->first / itr->second->score;
          node->bestm = itr->second->m;
        }
        itr++;
        if (gettime() - start > 2.3)
          break;
      }
    }
    if (node->status == 0) {
      if (node->cand.empty())
        node->status = -1;
    }
  }
}

void nextMove( string player, int x, int y, vector <string> board){
  start = gettime();
  REP(i, 10)
    REP(j, 10)
      b[i][j] = board[i][j];
  REP(i, LEVEL) {
    evaluate(&root, player[0], i);
    //printf("after level %d status=%d\n", i, root.status);
  }
  printf("%c%d %c%d %c%d\n", root.bestm.from.second + 'a', 9 - root.bestm.from.first,
    root.bestm.to.second + 'a', 9 - root.bestm.to.first,
    root.bestm.land.second + 'a', 9 - root.bestm.land.first);
}

int main() {
  string player;
  int x,y;
  cin >> player >> x >> y;
  vector <string> board;

  for(int i=0; i<x; i++) {
      string s; cin >> s;
      board.push_back(s);
  }

  nextMove( player, x, y, board);

  return 0;
}
