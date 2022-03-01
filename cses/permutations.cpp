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

//   1: 1
//   2: x
//   3: x
//   4: 3142
//   5: 31425
//   6: 415263

  if (n == 1) { println(1); return 0; }
  if (n == 2 || n == 3) { println("NO SOLUTION"); return 0; }
  
  FOR(i, 1, n / 2 + 1) {
      print(n / 2 + i);
      print(i);
  }

  if (n % 2 != 0) { print(n); }

  println();

  return 0;
}