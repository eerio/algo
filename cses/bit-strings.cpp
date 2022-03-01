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
#define mod 1'000'000'007

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


int pow_mod(int a, int n) {
    if (n == 0) { return 1; }
    if (n == 1) { return a % mod; }
    
    if (n % 2 == 0) { ull t = pow_mod(a, n / 2) % mod; return (t * t) % mod; }
    else { return (a * pow_mod(a, n - 1)) % mod; }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  println(pow_mod(2, n));

  return 0;
}