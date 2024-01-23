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

template<typename U, typename ... Args>
void print(U fst, Args ... args) {
  std::cout << fst;
  ((std::cout << ' ' << args), ...);
}

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

// get_border(s)[i] := length of the longest proper border of s[0: i + 1]
// vector<int> get_border(const string& s) {
//   vector<int> border = {0};
//   border.reserve(s.size());
//   int j = 0;
//   for (int i=1; i < s.size(); ++i) {
//     while (j > 0 && s[i] != s[j]) { j = border[j - 1]; }
//     if (s[i] == s[j]) { ++j; }
//     border.push_back(j);
//   }
//   return border;
// }

// get_border(s)[i] := length of the longest proper border of s[0: i]
// get_border("aba") = [-1, 0, 0, 1], because:
// - -1: no border of an empty string exists (s[0: 0] == "")
// -  0: only *proper* border of "a" is ""
// -  0: cannot be 1, because a != b (s[0] != s[1])
// -  1: "a" is the longest proper border of "aba"
vector<int> get_border(const string& s) {
  vector<int> border (s.size() + 1);
  border[0] = -1;
  int t = -1;
  for (size_t i=1; i <= s.size(); ++i) {
    // na slajdach jest s[t + 1] != s[i]; tutaj odejmujemy 1,
    // bo stringi indeksujemy od 0, nie od 1
    while (t >= 0 && s[t] != s[i - 1]) t = border[t];
    ++t;
    border[i] = t;
  }
  return border;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
 
  auto border = get_border(s);
  assert(border.size() == s.size() + 1);
  
  // lengths of borders of s is B[s|]|, B[B[|s|]], ...
  vector<int> brd_lens;
  for (auto brd_len = border.back(); brd_len > 0; brd_len = border[brd_len]) {
    brd_lens.push_back(brd_len);
  }
  assert (brd_lens.size() <= s.size() - 1);
  if (brd_lens.empty()) { println(1); println(s.size(), 1); return 0; }

  // counts[i] = number of times the border of length `i` occured
  vector<size_t> counts (s.size());

  //println(border);
  for (auto brd: border) {
    if (brd <= 0) { continue; }
    assert (brd < s.size());  // due to the borders being proper
    counts[brd]++;
  }

  for (size_t i=counts.size() - 1; i > 0; --i) {
    counts[border[i]] += counts[i];
  }

  // account for the borders being proper (i.e. count the first occurence)
  for (auto& c: counts) { c++; }


  println(brd_lens.size() + 1);
  for (auto it=brd_lens.rbegin(); it != brd_lens.rend(); ++it) {
    auto i = *it;
    println(i, counts[i]);
  }
  println(s.size(), 1);

  return 0;
}
