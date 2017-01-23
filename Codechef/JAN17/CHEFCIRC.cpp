/**
 * Smallest k-enclosing circle
 * Based on paper:
 * "Computing the smallest k-enclosing circle and related problems"
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
#define FORD(i,a,b) for (int i = (a); i >= (b); i--)
#define FORL(i,s,t) for(L i=(s); i<(t); i++)
#define BUG puts("here!!!")
#define STOP system("pause")
#define file_r(x) freopen(x, "r", stdin)
#define file_w(x) freopen(x, "w", stdout)
#define EPS 1e-10
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
        inline bool skipBlanks() { while (isBlank(nextChar())); return peekChar() != 0; }
 
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

#define N 501

int m, n;
pair<double, double> p[N];

inline bool compare(pair<double, int> p1, pair<double, int> p2) {
  return LS(p1.first, p2.first);
}

bool satisfy(double r) {
  int maxDepth = 0;
  REP(i, n) {
    int maxDepth = 0;
    REP(j, n) {
      if (!BG(DIST(p[j].first, p[j].second, p[i].first + r, p[i].second), r))
        maxDepth++;
    }
    //cout << i << " " << maxDepth << endl;

    vector<pair<double, int> > is;
    REP(j, n) {
      double d = DIST(p[i].first, p[i].second, p[j].first, p[j].second);
      if (BG(d, 2 * r)) {
        continue;
      }
      if (EQ(d, 0)) {
        continue;
      }
      double angle = atan2(p[j].second - p[i].second, p[j].first - p[i].first);
      if (NEG(angle)) {
        angle += 2 * PI;
      }
      if (EQ(d, 2 * r)) {
        if (EQ(p[i].second, p[j].second)) {
          // Touching on the right-most point
          is.pb(mp(angle, -1));
        } else {
          is.pb(mp(angle, 0));  // enter and exit
        }
        continue;
      }
      double delta = acos(d / 2 / r);
      double small = angle - delta;
      if (NEG(small)) {
        small += 2 * PI;
      }
      double big = angle + delta - 2 * PI;
      if (NEG(big)) {
        big += 2 * PI;
      }
      is.pb(mp(small, 1));  // enter
      is.pb(mp(big, -1)); // exit
    }
    sort(is.begin(), is.end(), compare);
    
    int j = 0;
    int depth = maxDepth;
    while (j < is.size()) {
      double cur = is[j].first;
      int totalEnter = 0;
      int totalExit = 0;
      while (j < is.size() && EQ(is[j].first, cur)) {
        if (is[j].second >= 0) {
          totalEnter++;
        }
        if (is[j].second <= 0) {
          totalExit++;
        }
        j++;
      }
      depth += totalEnter;
      maxDepth = max(depth, maxDepth);
      depth -= totalExit;
      //cout << "(" << j << " " << maxDepth << ")" << endl;
      if (maxDepth >= m) return true;
    }
    if (maxDepth >= m) return true;
  }
  return false;
}

double calc() {
  double minx = 2000;
  double miny = 2000;
  double maxx = -2000;
  double maxy = -2000;
  REP(i, n) {
    minx = fmin(minx, p[i].first);
    miny = fmin(miny, p[i].second);
    maxx = fmax(maxx, p[i].first);
    maxy = fmax(maxy, p[i].second);
  }
  int start = 0;
  int end = (int)ceil(DIST(minx, miny, maxx, maxy) / 2 * 100);
  while (start != end) {
    int mid = (start + end ) / 2;
    //cout << start << " " << end << " " << mid << endl;
    if (satisfy(((double)mid) / 100)) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  return ((double)start) / 100;
}

bool lineIntersect( double x[], double y[], double r[] )
{
    double n[2]; n[0] = y[3] - y[2]; n[1] = x[2] - x[3];
    double denom = n[0] * ( x[1] - x[0] ) + n[1] * ( y[1] - y[0] );
    if( fabs( denom ) < EPS ) return false;
    double num = n[0] * ( x[0] - x[2] ) + n[1] * ( y[0] - y[2] );
    double t = -num / denom;
    r[0] = x[0] + t * ( x[1] - x[0] );
    r[1] = y[0] + t * ( y[1] - y[0] );
    return true;
}

double circle3pts( double x[], double y[], double r[] )
{
    double lix[4], liy[4];
    lix[0] = 0.5 * ( x[0] + x[1] ); liy[0] = 0.5 * ( y[0] + y[1] );
    lix[1] = lix[0] + y[1] - y[0];  liy[1] = liy[0] + x[0] - x[1];
    lix[2] = 0.5 * ( x[1] + x[2] ); liy[2] = 0.5 * ( y[1] + y[2] );
    lix[3] = lix[2] + y[2] - y[1];  liy[3] = liy[2] + x[1] - x[2];
    if( !lineIntersect( lix, liy, r ) ) return -1.0;
    return sqrt(
        ( r[0] - x[0] ) * ( r[0] - x[0] ) +
        ( r[1] - y[0] ) * ( r[1] - y[0] ) );
}

bool inCircle(pair<double, double> point, double x, double y, double r) {
  return !BG(DIST(point.first, point.second, x, y), r);
}

bool equal(pair<double, double> p1, pair<double, double> p2) {
  return EQ(p1.first, p2.first) && EQ(p1.second, p2.second);
}

bool valid(double x, double y, double r) {
  int c = 0;
  REP(i, n) {
    if (inCircle(p[i], x, y, r)) c++;
  }
  return c >= m;
}

double brute() {
  double minr = 1e10;
  REP(i, n) {
    // One point
    if (valid(p[i].first, p[i].second, 0)) minr = 0;

    // Two point
    FOR(j, i + 1, n) {
      if (equal(p[i], p[j])) continue;
      double cx = (p[i].first + p[j].first) / 2;
      double cy = (p[i].second + p[j].second) / 2;
      double r = DIST(p[i].first, p[i].second, p[j].first, p[j].second) / 2;
      if (valid(cx, cy, r)) minr = fmin(minr, r);
      
      // Three point
      FOR(k, j + 1, n) {
        if (equal(p[i], p[k]) || equal(p[j], p[k])) continue;
        double tmpx[3] = {p[i].first, p[j].first, p[k].first};
        double tmpy[3] = {p[i].second, p[j].second, p[k].second};
        double arr[2];
        r = circle3pts(tmpx, tmpy, arr);
        //cout << i << " " << j << " " << k << " " << r << endl;
        if (r == -1) continue;
        if (valid(arr[0], arr[1], r)) minr = fmin(minr, r);
      }
    }
  }
  return minr;
}

void test() {
  srand(time(NULL));
  REP(i, 10000) {
    n = rand() % 4 + 1;
    m = rand() % n + 1;
    REP(j, n) {
      //p[j].first = ((double)(rand() % 200000000)) / 100000 - 1000;
      //p[j].second = ((double)(rand() % 200000000)) / 100000 - 1000;
      p[j].first = rand() % 5;
      p[j].second = rand() % 5;
    }
    double ans1 = calc();
    double ans2 = brute();
    if (fabs(ans1 - ans2) > 0.01) {
      cout << n << " " << m << endl;
      REP(j, n) {
        cout << p[j].first << " " << p[j].second << endl;
      }
      cout << ans1 << " " << ans2 << endl;
      return;
    }
  }
}

void real_main() {
  cin >> n >> m;
  REP(i, n) {
    cin >> p[i].first >> p[i].second;
  }
  //cout << brute();
  cout << calc();
}

int main() {
  real_main();
  //test();
  return 0;
}
