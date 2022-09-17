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

template<typename U, typename V>
std::ostream& operator<< (std::ostream& out, std::pair<U, V> x) {
  return out << '<' << x.first << ", " << x.second << '>';
}

template<typename ... Ts>
std::ostream& operator<< (std::ostream& out, std::tuple<Ts ...> x) {
  out << '{';
  auto printer = [&out](auto&& first, auto&& ... args) {
    out << first;
    ((out << ' ' << args), ...);
  };
  std::apply(printer, x);
  return out << '}';
}

template<typename T>
auto operator<< (std::ostream& out, T x) -> decltype(x.end(), out) {
  out << '{';
  if (x.size() > 0) {
    for (typename T::iterator it=x.begin(); it != std::prev(x.end()); ++it) {
      out << *it << ", ";
    }
    out << *std::prev(x.end());
  }
  return out << '}';
}

std::ostream& operator<< (std::ostream& out, std::string x) {
  for (auto c: x) { out << c; }
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
// this doesn't work in CSES' online judge
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
  //J(1)=1;
  //J(2n) = 2J(n)-1;
  //j(2n+1)=2J(n)+1;
  
  int step = 1, offset = 0, k=2;
  while (n) {
    for (int i=k; i <= n; i += k) {
      print(step * i + offset);
    }

    if (n % 2) { print(step + offset); offset += step; }
    else { offset -= step; }

    step *= 2;
    n /= 2;
  }
  
  println();

  /*
  pair<int, char> p {2137, '*'};
  vector<int> t {1, 2, 3};
  map<char, string> s {{'r', "raban"}, {'b', "balagan"}, {'t', "tygrys"}};
  println(1, 2, "pawel", 4.5f, 4.5, t, p, vector<char>(), map<int,int>(), s);

  vector<int> v (50);
  tuple<int, string, long double> mytuple {17, "siedemnascie", 17.9};
  println(mytuple);
  generate(v.begin(), v.end(), [] { return randint(-1,0); });
  println(v);
  */

  return 0;
}
