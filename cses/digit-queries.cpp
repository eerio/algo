#include <algorithm>
#include <bitset>
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

// binary exponentiation
ull binpow(int base, unsigned int exp) {
    if (exp == 0) { return 1; }
    
    if (exp % 2 == 0) { ull aux = binpow(base, exp / 2); return aux * aux; }
    else { return base * binpow(base, exp - 1); }
}


ull len(int k) {
    return (binpow(10, k) * (9 * k - 1) + 1) / 9;
}

int solve(ull k) {
    int digs;
    FOR(i, 1, 17) {
        if (len(i - 1) < k && k <= len(i)) { digs = i; break; }
    }

    ull pos=(k - len(digs - 1) - 1) / digs, digit=(k - len(digs - 1) - 1) % digs;

    // println("k:", k, "digs:", digs, "pos:", pos, "dig:",digit);
    ull num = binpow(10, digs - 1) + pos;
    return num / binpow(10, digs - digit - 1) % 10;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> q;

  REP(i, q) {
      ull k;
      cin >> k;
      
      println(solve(k));
  }

  return 0;
}