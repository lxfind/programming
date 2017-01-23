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
#define INTDIST(x1, y1, x2, y2) (SQ((x1) - (x2)) + SQ((y1) - (y2)))
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

#define N 400
#define I1 20
#define I2 1000
int n, s, skip;
int a[N];
int p[N][2];
int d[N][N];
bool f[N];

inline int genRand(int index) {
  return rand() % (s - 2 * a[index] + 1) + a[index];
}

void place(vector<int> &placed, int index) {
  int minnewx, minnewy;
  int maxmin = INT_MIN;
  REP(i, I1) {
    int newx = genRand(index);
    int newy = genRand(index);
    int mind;
    REP(k, I2) {
      mind = INT_MAX;
      int minj;
      REP(j, placed.size()) {
        int dist = INTDIST(p[placed[j]][0], p[placed[j]][1], newx, newy);
        if (dist < mind) {
          mind = dist;
          minj = placed[j];
        }
      }
      if (newx > a[index] && p[minj][0] >= newx) {
        newx--;
      } else if (newx + a[index] < s && p[minj][0] <= newx) {
        newx++;
      }
      if (newy > a[index] && p[minj][1] >= newy) {
        newy--;
      } else if (newy + a[index] < s && p[minj][1] <= newy) {
        newy++;
      }
    }
    if (mind > maxmin) {
      maxmin = mind;
      minnewx = newx;
      minnewy = newy;
    }
  }
  p[index][0] = minnewx;
  p[index][1] = minnewy;
  placed.pb(index);
}

void process() {
  sort(a, a + n);
  p[0][0] = p[0][1] = a[0];
  p[1][0] = p[1][1] = s - a[1];
  p[2][0] = a[2];
  p[2][1] = s - a[2];
  p[3][0] = s - a[3];
  p[3][1] = a[3];
  vector<int> placed;
  REP(i, 4) placed.pb(i);
  srand(time(NULL));
  for (int i = n - skip * 2 - 1; i > 3; i--) {
    place(placed, i);
  }
  int mind = INT_MAX;
  REP(i, placed.size())
    FOR(j, i + 1, placed.size())
      mind = min(mind, INTDIST(p[i][0], p[i][1], p[j][0], p[j][1]));
}

int main() {
  cin >> n >> s >> skip;
  n *= 2;
  REP(i, n) cin >> a[i];
  process();
  vector<int> placed;
  CLR(f, 0);
  n /= 2;
  int left = skip;
  REP(i, n) {
    int r;
    cin >> r;
    if (i + left >= n) {
      left--;
      cout << -1 << " " << -1 << endl;
    } else {
      int j = 0;
      while (a[j] != r || f[j]) ++j;
      if (j >= n * 2 - skip * 2) {
        if (left) {
          left--;
          cout << -1 << " " << -1 << endl;
        } else {
          place(placed, j);
          f[j] = true;
          cout << p[j][0] << " " << p[j][1] << endl;
        }
      } else{
        cout << p[j][0] << " " << p[j][1] << endl;
        placed.pb(j);
        f[j] = true;
      }
    }
    fflush(stdout);
  }
  return 0;
}
