#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool m[25];

int main() {
  int n = 5;
  cout << n << endl;
  for (int i = 0; i < 25; i++)
    m[i] = 0;
  for (int i = 0; i < 25; i++) {
    int x;
    while (m[x = rand() % 25]);
    cout << x << endl;
    m[x] = 1;
  }
}
