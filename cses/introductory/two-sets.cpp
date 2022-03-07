#include <algorithm>
#include <iostream>
#include <cassert>
#include <climits>
#include <random>
#include <list>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <stack>
#include <map>
#include <string>

#define FOR(i, a, b) for (decltype(b) i=(a); i < (b); ++i)
#define REP(i, n) for (decltype(n) i=0; i < (n); ++i)

template<typename u, typename v>
std::ostream& operator<< (std::ostream& out, const std::pair<u, v>& x) {
  out << '<' << x.first << ", " << x.second << '>';
  return out;
}

template<typename u>
std::ostream& operator<< (std::ostream& out, const std::vector<u>& x) {
  out << '[';
  if (x.size() > 0) {
    for (size_t i=0; i < x.size() - 1; ++i) { out << x[i] << ", "; }
    out << x[x.size() - 1];
  }
  out << ']';
  return out;
}

template<typename u, typename v>
std::ostream& operator<< (std::ostream& out, const std::map<u, v>& x) {
  out << '{';
  if (x.size() > 0) {
    for (auto it=x.begin(); it != prev(x.end()); ++it) {
      out << it->first << ": " << it->second << ", ";
    }
    auto it = std::prev(x.end());
    out << it->first << ": " << it->second;
  }
  out << '}';
  return out;
}

template<typename ... Args>
void print(Args ... args) { ((std::cout << args << ' '), ...); }

template<typename ... Args>
void println(Args ... args) { print(args...); std::cout << '\n'; }

using namespace std;
using ll = long long int;
using ull = unsigned long long int;

// uncomment to fix seed for reproducibility / execution time
#define FIX_RNGSEED
#ifdef FIX_RNGSEED
  mt19937_64 mt(42);
#else
  random_device real_rnd;
  mt19937_64 mt(real_rnd());
#endif

// return from uniform distribution on [l, r]
int randint(int l, int r) { uniform_int_distribution<int> dist (l, r); return dist(mt); }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  if (n % 4 == 1 || n % 4 == 2) { println("NO"); return 0; }
  
    //   n = 4k + 0: ok
    //   n = 4k + 1: bad
    //   n = 4k + 2: bad
    //   n = 4k + 3: ok

    //     4 = 4*1: k=1; 
    //     j=1..2; 2, 4
    //     j=1..2; 1, 3

    //   a = sum_{j=1..2k} 2j = 2 (2k)(2k + 1) / 2 = 2k * (2k + 1)
    //   b = sum_{j=1..2k} (2j-1) =2k * (2k + 1) - 2k = 2k * 2k
    //   a - b = 2k

    if (n % 4 == 0) {
        println("YES");
        println(n / 2);
        FOR(i, 1, n / 4 + 1) { print(i, n - i + 1); }
        println();
        println(n / 2);
        FOR(i, n / 4 + 1, n / 2 + 1) { print(i, n - i  + 1); }
        println();
    }

    if (n % 4 == 3) {
        println("YES");

        int k = (n - 3) / 4;

        println(n / 2 + 1);

        // tutaj nie drukuj 4k, wydrukuj 2k
        FOR(i, 1, k + 1) {
            if (4*k-i+1 == 4 * k) { print(i); }
            else { print(i, 4*k - i + 1); }
        }
        if (k != 0) { print(2 * k); }
        println(n-2, n-1);

        println(n / 2);
        FOR(i, k + 1, 2 * k + 1) {
            // nie drukuj 2k, wydrukuj 4k
            if (i == 2 * k) { print(4*k -i +1); }
            else { print(i, 4*k - i + 1); }
        }
        if (n - 3) { print(n - 3); }
        println(n);
    }


  return 0;
}