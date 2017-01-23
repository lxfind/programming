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

#define N 310
int n, x, y, m;
int arr[N];
map<int, set<LL> > dp[N];

typedef map<int, set<LL> >::iterator mi;
typedef set<LL>::iterator si;

inline long long gcd( long long a, long long b ) { return( b == 0 ? a : gcd( b, a % b ) ); }

LL solve() {
  for (int i = n - 1; i >= 0; --i) {
    dp[i].clear();
    int bound = min(n, i + 1 + m);
    LL cur = 0;
    FOR(j, i + 1, bound) {
      cur += arr[j - 1];
      for (mi itr1 = dp[j].begin(), e1 = dp[j].end();
          itr1 != e1; ++itr1) {
        int p = itr1->first;
        if (p == y) continue;
        for (si itr2 = itr1->second.begin(), e2 = itr1->second.end();
            itr2 != e2; ++itr2) {
          dp[i][p + 1].insert(gcd(*itr2, cur));
        }
      }
      cur = cur * 10;
    }
    if (bound == n) {
      dp[i][0].insert(cur + arr[n - 1]);
    }
  }
  LL ans = 0;
  for (mi itr1 = dp[0].begin(), e1 = dp[0].end(); itr1 != e1; ++itr1) {
    if (itr1->first < x || itr1->first > y) continue;
    for (si itr2 = itr1->second.begin(), e2 = itr1->second.end();
        itr2 != e2; ++itr2) {
      ans = max(ans, *itr2);
    }
  }
  return ans;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    string line;
    cin >> n >> line >> m >> x >> y;
    REP(i, n) arr[i] = line[i] - '0';
    cout << solve() << endl;
  }
  return 0;
}
