/*
 * CodeChef June Challenge 2013
 * Problem B: Collecting Magical Berries
 * Algorithm: Delta Encoding, Binary Index Tree, Combinatorial, O(log(N))
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


class BIT {
 public:
  int* tree;
  int s;
  BIT(int size) {
    tree = new int[size + 1];
    s = size;
  }
  void update(int idx ,int val){
    while (idx <= s){
      tree[idx] += val;
      idx += (idx & -idx);
    }
  }
  int read(int idx){
    int sum = 0;
    while (idx > 0){
      sum += tree[idx];
      idx -= (idx & -idx);
    }
    return sum;
  }
};

#define N 100001
#define M 3000001
#define MOD 3046201
char cmd[7];
int a[N];
int sum[N];
int pm[M];

template< class Int >
struct Triple
{
    Int d, x, y;
    Triple( Int q, Int w, Int e ) : d( q ), x( w ), y( e ) {}
};

template< class Int >
Triple< Int > egcd( Int a, Int b )
{
    if( !b ) return Triple< Int >( a, Int( 1 ), Int( 0 ) );
    Triple< Int > q = egcd( b, a % b );
    return Triple< Int >( q.d, q.y, q.x - a / b * q.y );
}

template< class Int >
Int inverse( Int a, Int n )
{
    Triple< Int > t = egcd( a, n );
    if( t.d > Int( 1 ) ) return Int( 0 );
    Int r = t.x % n;
    return( r < Int( 0 ) ? r + n : r );
}

int powmod( long long b, int p, int m )
{
    long long r = 1;
    for( int i = ( 1 << 30 ); i; i >>= 1 )
    {
        r *= r; r %= m;
        if( p & i ) { r *= b; r %= m; }
    }
    return ( int )r;
}

int main() {
  int n;
  cin >> n;
  FOR(i, 1, n + 1)
    cin >> a[i];
  sum[0] = 0;
  FOR(i, 1, n + 1)
    sum[i] = sum[i - 1] + a[i];
  pm[0] = 1;
  FOR(i, 1, n * 30 + 1)
    pm[i] = pm[i - 1] * LL(i) % MOD;
  BIT* bit = new BIT(n);
  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> cmd >> x >> y;
    if (cmd[0] == 'c') {
      bit->update(x, y - a[x]);
      a[x] = y;
    } else {
      int s = sum[y] - sum[x - 1] + bit->read(y) - bit->read(x - 1);
      int cnt = y - x + 1;
      int p = s % cnt;
      int q = s / cnt;
      int ans = LL(pm[cnt]) * inverse(pm[p], MOD) % MOD * inverse(pm[cnt - p], MOD) % MOD
      * pm[s] % MOD * inverse(pm[p * (q + 1)], MOD) % MOD * inverse(pm[s - p * (q + 1)], MOD) % MOD
      * pm[p * (q + 1)] % MOD * powmod(inverse(pm[q + 1], MOD), p, MOD) % MOD
      * pm[(cnt - p) * q] % MOD * powmod(inverse(pm[q], MOD), cnt - p, MOD) % MOD;
      cout << ans << endl;
    }
  }
  return 0;
}
