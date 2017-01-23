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


long long factor[120],num = 0;
              
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
        factor[num++]=n;      
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

int main()
{
  LL n;
  cin >> n;
  if (n > 1) {
    pollard_brent(n);
  }
  int ans = 0;
  REP(i, num) {
    while (n % factor[i] == 0) {
      ans++;
      n /= factor[i];
    }
  }
  if (ans == 20) {
    cout << "Yes";
  } else {
    cout << "No";
  }
  return 0;
}


