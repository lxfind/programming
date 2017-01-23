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

static struct IO {
        char tmp[1 << 10];
 
        // fast input routines
        char cur;
 
//#define nextChar() (cur = getc_unlocked(stdin))
//#define peekChar() (cur)
        inline char nextChar() { return cur = getc_unlocked(stdin); }
        inline char peekChar() { return cur; }
 
        inline operator bool() { return peekChar(); }
        inline static bool isBlank(char c) { return (c < '-' && c); }
        inline bool skipBlanks() { while (isBlank(nextChar())) {} return peekChar() != 0; }
 
        inline IO& operator >> (char & c) { c = nextChar(); return *this; }
 
        inline IO& operator >> (char * buf) {
                if (skipBlanks()) {
                        if (peekChar()) {
                                *(buf++) = peekChar();
                                while (!isBlank(nextChar())) *(buf++) = peekChar();
                        } *(buf++) = 0; } return *this; }
 
        inline IO& operator >> (string & s) {
                if (skipBlanks()) {     s.clear(); s += peekChar();
                        while (!isBlank(nextChar())) s += peekChar(); }
                return *this; }
 
        inline IO& operator >> (double & d) { if ((*this) >> tmp) sscanf(tmp, "%lf", &d); return *this; }
 
#define defineInFor(intType) \
        inline IO& operator >>(intType & n) { \
                if (skipBlanks()) { \
                        int sign = +1; \
                        if (peekChar() == '-') { \
                                sign = -1; \
                                n = nextChar() - '0'; \
                        } else \
                                n = peekChar() - '0'; \
                        while (!isBlank(nextChar())) { \
                                n += n + (n << 3) + peekChar() - 48; \
                        } \
                        n *= sign; \
                } \
                return *this; \
        }
 
defineInFor(int)
defineInFor(unsigned int)
defineInFor(long long)
 
        // fast output routines
 
//#define putChar(c) putc_unlocked((c), stdout)
        inline void putChar(char c) { putc_unlocked(c, stdout); }
        inline IO& operator << (char c) { putChar(c); return *this; }
        inline IO& operator << (const char * s) { while (*s) putChar(*s++); return *this; }
 
        inline IO& operator << (const string & s) { for (int i = 0; i < (int)s.size(); ++i) putChar(s[i]); return *this; }
 
        char * toString(double d) { sprintf(tmp, "%lf%c", d, '\0'); return tmp; }
        inline IO& operator << (double d) { return (*this) << toString(d); }
 
 
#define defineOutFor(intType) \
        inline char * toString(intType n) { \
                char * p = (tmp + 30); \
                if (n) { \
                        bool isNeg = 0; \
                        if (n < 0) isNeg = 1, n = -n; \
                        while (n) \
                                *--p = (n % 10) + '0', n /= 10; \
                        if (isNeg) *--p = '-'; \
                } else *--p = '0'; \
                return p; \
        } \
        inline IO& operator << (intType n) { return (*this) << toString(n); }
 
defineOutFor(int)
defineOutFor(long long)
 
#define endl ('\n')
#define cout __io__
#define cin __io__
} __io__;

#define N 32
int orig[N][N][N];
int maxA[N][N][N];
int minA[N][N][N];
int n, m;
int sums[N][N][N][N + 1];

int F(int A[N][N][N], int dx, int dy, int dz, int size) {
   int s = sums[dx][dy][dz][size];
   if (s == 0 || s == size * size * size) {
      return 1;
   }
   int result = 0;
   for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
           result += F(A, 
                          dx + i * size / 2, 
                          dy + j * size / 2, 
                          dz + k * size / 2,
                          size / 2);
        }
      }
   }
   return result;
}

int findMax() {
  int tmp = m;
  for (int size = n; size > 1; size /= 2) {
    for (int i = 0; i < n; i += size)
      for (int j = 0; j < n; j += size)
        for (int k = 0; k < n; k += size) {
          int sum = 0;
          REP(p, size)
            REP(q, size)
              REP(r, size)
                sum += maxA[i + p][j + q][k + r];
          sum = min(sum, size * size * size - sum);
          if (sum == 0 && tmp > 0) {
            maxA[i][j][k] = 1 - maxA[i][j][k];
            tmp--;
          }
        }
  }
  return F(maxA, 0, 0, 0, n);
}

map<int, int> findMin(int dx, int dy, int dz, int size) {
  int sum = sums[dx][dy][dz][size];;
  sum = min(sum, size * size * size - sum);
  map<int, int> ret;
  ret[1] = sum;
  if (sum == 0) return ret;
  if (size == 2) {
    ret[8] = 0;
    return ret;
  }

  map<int, int> subs;
  vector<pair<int, int> > all;
  REP(i, 2)
    REP(j, 2)
      REP(k, 2) {
        map<int, int> sub = findMin(
          dx + i * size / 2, dy + j * size / 2,
          dz + k * size / 2, size / 2);
        if (i + j + k == 0) {
          subs = sub;
          continue;
        }
        map<int, int> newsubs;
        for (map<int, int>::iterator I1 = subs.begin(), E1 = subs.end();
            I1 != E1; ++I1) {
          for (map<int, int>::iterator I2 = sub.begin(), E2 = sub.end();
              I2 != E2; ++I2) {
            int key = I1->first + I2->first;
            int value = I1->second + I2->second;
            if (value > m) continue;
            if (newsubs.find(key) != newsubs.end()) {
              newsubs[key] = min(newsubs[key], value);
            } else {
              newsubs[key] = value;
            }
          }
      }
      subs = newsubs;
    }
  subs[1] = sum;
  return subs;
}

void brute(int refmin, int refmax) {
  int maxv = 0;
  int minv = INT_MAX;
  REP(i, 256) {
    int tmp = i;
    int dist = 0;
    REP(a, n)
      REP(b, n)
        REP(c, n) {
          maxA[a][b][c] = tmp % 2;
          dist += maxA[a][b][c] != orig[a][b][c];
          tmp /= 2;
        }
    if (dist <= m) {
      int v = F(maxA, 0, 0, 0, n);
      maxv = max(v, maxv);
      minv = min(v, minv);
    }
  }
  if (refmin != minv || refmax != maxv) {
    REP(i, n) {
      REP(j, n) {
        REP(k, n) cout << orig[i][j][k] << " ";
        cout << endl;
      }
      cout << endl;
    }
    cout << m << endl;
    cout << "mine: max=" << refmax << " min=" << refmin << endl;
    cout << "brute: max=" << maxv << " min=" << minv << endl;
    exit(1);
  }
}

int getMin() {
  map<int, int> ret = findMin(0, 0, 0, n);
  int minv = F(orig, 0, 0, 0, n);
  cout << (int)ret.size() << endl;
  for (map<int, int>::iterator I = ret.begin(), E = ret.end(); I != E; ++I) {
    if (I->second <= m) {
      minv = min(minv, I->first);
    }
  }
  return minv;
}

void test() {
  n = 2;
  FOR(i, 1, 9) {
    m = i;
    REP(j, 256) {
      int tmp = j;
      REP(a, n)
        REP(b, n)
          REP(c, n) {
            orig[a][b][c] = maxA[a][b][c] = tmp % 2;
            tmp /= 2;
          }
      int refmax = findMax();
      int refmin = getMin();
      brute(refmin, refmax);
    }
  }
}

void prepare() {
  REP(i, n)
    REP(j, n)
      REP(k, n)
        sums[i][j][k][1] = orig[i][j][k];
  for (int size = 2; size <= n; size *= 2) {
    for (int i = 0; i < n; i += size)
      for (int j = 0; j < n; j += size)
        for (int k = 0; k < n; k += size) {
          sums[i][j][k][size] = 0;
          REP(a, 2)
            REP(b, 2)
              REP(c, 2)
                sums[i][j][k][size] += sums[i + a * size / 2][j + b * size / 2][k + c * size / 2][size / 2];
        }
  }
}

int main() {
  cin >> n >> m;
  int sum = 0;
  REP(a, n)
    REP(b, n)
      REP(c, n) {
        cin >> orig[a][b][c];
        sum += orig[a][b][c];
        maxA[a][b][c] = minA[a][b][c] = orig[a][b][c];
      }
  prepare();
  sum = min(sum, n * n * n - sum);
  int maxv = findMax();
  int minv = sum <= m ? 1 : getMin();
  cout << minv << " " << maxv;
  return 0;
}
