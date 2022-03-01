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

  REP(i, n) {
      ull y, x;
      cin >> y >> x;

      if (x == y) {
          println(x * x - (x - 1));
      } else if (x > y && x % 2 == 0) {
          println((x - 1) * (x - 1) + y);
      } else if (x > y) {
          println(x * x - (y - 1));
      } else if (x < y && y % 2 == 0) {
          println(y * y - (x - 1));
      } else {
          println((y - 1) * (y - 1) + x);
      }

    //   int ring = max(y, x);
    //   // now (ring - 1)^2 < num <= ring^2
    //   // this is ring^2 - (ring-1)^2 numbers
    //   // = ring2 - ring2 - 1 +2ring = 2 * ring - 1 numbers
      
    //   if (ring % 2 == 0) {
    //       // mamy od lewej ring liczb malejacych i potem w gore ring-1 malejacych
    //   } else {
    //       // mamy od lewej ring rosnacych i potem w gore ring-1 rosnacych
    //   }
  }

  return 0;
}