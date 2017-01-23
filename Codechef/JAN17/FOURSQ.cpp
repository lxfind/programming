/**
 * Segment Tree
 * 3-Square-Sum Problem
 * 4-Square-Sum Problem
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

#define N 100010
#define M 300000
#define T 1000000000LL
int n, q, width, size;
LL p;
LL a[M];

inline LL mult(LL x, LL y) {
  if (x > T || y > T) {
    LL x1 = x / T;
    LL x2 = x % T;
    LL y1 = y / T;
    LL y2 = y % T;
    return (T * T % p * x1 % p * y1 +
      y2 * T % p * x1 + x2 * T % p * y1 +
      x2 * y2) % p;
  } else {
    return x * y % p;
  }
}

inline int left(int i) { return 2 * i - size - 1; }
inline int right(int i) { return 2 * i - size; }
inline void merge(int index) {
  int child = 2 * index - size;
  LL x = a[child - 1];
  LL y = a[child];
  if (y == -1) {
    a[index] = x;
  } else {
    a[index] = mult(x, y);
  }
}

void prepare() {
  width = 1;
  while (width < n) {
    width = width << 1;
  }
  size = width * 2 - 1;

  int i = width;
  int w = width / 2;
  while (w) {
    REP(j, w) {
      int index = i + j;
      merge(index);
    }
    i += w;
    w = w >> 1;
  }
}

void update(int x, int y) {
  a[x] = y % p;
  int base = width;
  int w = width / 2;
  x /= 2;
  while (w) {
    merge(x + base);
    base += w;
    w /= 2;
    x /= 2;
  }
}

long long factor[100000], fcnt;
              
long long gcd(long long a,long long b)      
{      
    return b?gcd(b,a%b):a;      
}      
              
long long Mul_Mod(long long a,long long b,long long n)      
{      
    long long  exp = a%n, res = 0;      
    while(b)      
    {      
        if(b&1)      
        {      
            res += exp;      
            if(res>n) res -= n;      
        }      
        exp <<= 1;      
        if(exp>n)      
            exp -= n;      
              
        b>>=1;      
    }      
    return res;      
}      
              
long long Pow_Mod(long long a,long long b,long long c)      
{      
    long long k = 1;      
    while(b)      
    {      
        if(b&1)      
            k = Mul_Mod(k,a,c);      
        a = Mul_Mod(a,a,c);      
        b>>=1;      
    }      
    return k;      
}      
              
bool Miller_Rabbin(long long n)      
{      
    if(n==2)return 1;      
    if(n<2||!(n&1))return 0;      
              
    long long a, u=n-1, x, y;      
    int t=0;      
    while(u%2==0){      
        t++;      
        u/=2;      
    }      
    srand(100);      
    for(int i=0;i<12;i++)      
    {      
        a = rand() % (n-1) + 1;      
        x = Pow_Mod(a, u, n);      
        for(int j=0;j<t;j++)      
        {      
            y = Mul_Mod(x, x, n);      
            if ( y == 1 && x != 1 && x != n-1 )      
                return false; //must not      
            x = y;      
        }      
        if( y!=1) return false;      
    }      
    return true;      
}      

void pollard_brent(long long n)      
{      
    long long d=1;
    srand(100);      
    if (Miller_Rabbin(n))      
    {      
        factor[fcnt++]=n;      
        return;
    }      
    for (long long x=rand()%(n-1)+1,y=x,k=0,i=1,ran=120;;k++)      
    {      
        x=(Mul_Mod(x,x,n)+ran)%n;      
        d=gcd((x-y+n)%n,n);//keep d positive      
        if (1<d && d<n)      
            break;      
        if (x==y)      
        {      
            ran--;      
        }      
        if (k==i)      
        {      
            y=x;      
            i<<=1;      
        }      
    }      
    pollard_brent(d);      
    pollard_brent(n/d);      
}

void findAns(LL num) {
  /*
  int fcnt = 0;
  pollard_brent(num);
  LL base = 1;
  LL tmp = num;
  REP(i, fcnt) {
    int times = 0;
    while (tmp % factor[i] == 0) {
      times++;
      tmp /= factor[i];
      if (times % 2 == 0) {
        base *= factor[i];
      }
    }
  }
  num = num / base / base;
  */
  LL base = 1;
  while (num > 0 && num % 4 == 0) {
    base *= 2;
    num /= 4;
  }
  while (num > 0 && num % 9 == 0) {
    base *= 3;
    num /= 9;
  }
  LL first = floor(sqrt(num));
  LL rem;
  while (1) {
    rem = num - first * first;
    LL tmp = rem;
    while (tmp != 0 && tmp % 4 == 0) tmp /= 4;
    if (tmp % 8 != 7) {
      break;
    }
    first--;
  }
  LL second = floor(sqrt(rem));
  while (1) {
    LL rem2 = rem - second * second;
    LL third = floor(sqrt(rem2));
    while (third >= 0) {
      LL rem3 = rem2 - third * third;
      LL fourth = floor(sqrt(rem3));
      if (fourth > third) break;
      if (fourth * fourth == rem3) {
        cout << first * base << " " << second * base << " " <<
                third * base << " " << fourth * base << endl;
        return;
      }
      third--;
    }
    second--;
  }
}

void calc(int l, int r) {
  LL result = 1;
  while (l <= r) {
    int step = 2;
    int base = 0;
    int w = width;
    while (l % step == 0 && l + step - 1 <= r) {
      step *= 2;
      base += w;
      w /= 2;
    }
    step /= 2;
    result = mult(result, a[base + l / step]);
    l += step;
  }
  findAns(result);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    CLR(a, -1);
    cin >> n >> q >> p;
    REP(i, n) cin >> a[i];
    prepare();
    REP(i, q) {
      int c;
      cin >> c;
      if (c == 1) {
        int x, y;
        cin >> x >> y;
        update(x - 1, y);
      } else {
        int l, r;
        cin >> l >> r;
        calc(l - 1, r - 1);
      }
    }
  }
  return 0;
}
