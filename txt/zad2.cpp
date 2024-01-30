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

vector<size_t> get_suffix_array_brut(const string& s) {
  vector<pair<string, size_t>> suffixes;
  for (size_t i=0; i < s.size(); ++i) {
    suffixes.push_back({s.substr(i), i});
  }
  sort(suffixes.begin(), suffixes.end());
  
  vector<size_t> result;
  for (auto& [_, i]: suffixes) { result.push_back(i); }
  return result;
}


vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> get_suffix_array2(const string& s) {
  vector<int> sorted_shifts = sort_cyclic_shifts(s);
  //sorted_shifts.erase(sorted_shifts.begin());
  return sorted_shifts;
}


vector<int> get_suffix_array(const string& s) {
  return get_suffix_array2(s);
}

vector<size_t> get_lcp_array_brut(const string& s, const vector<int>& sa) {
  vector<size_t> result;
  for (size_t i=0; i < sa.size() - 1; ++i) {
    size_t lcp = 0;
    while (
      sa[i] + lcp < s.size()
      && sa[i + 1] + lcp < s.size()
      && s[sa[i] + lcp] == s[sa[i + 1] + lcp]
    ) {
      ++lcp;
    }

    result.push_back(lcp);
  }

  return result;
}

vector<size_t> get_lcp_array(const string& s, const vector<int>& sa) {
    size_t n = s.size();
    vector<size_t> rank(n);
    for (size_t i=0; i < n; ++i) { rank[sa[i]] = i; }

    vector<size_t> lcp(n - 1);
    size_t k = 0;
    for (size_t i=0; i < n; ++i) {
      if (rank[i] == 0) { continue; }
      auto iprim = sa[rank[i] - 1];
      while (s[i + k] == s[iprim + k]) { ++k; }
      lcp[rank[i] - 1] = k;
      if (k) { --k; }
    }
    return lcp;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s1, s2, s3;
  cin >> s1 >> s2 >> s3;
  size_t min_size = min({s1.size(), s2.size(), s3.size()});
  string s = s1 + "1" + s2 + "2" + s3 + "3";

  auto sa = get_suffix_array(s);
  
  auto saMine = get_suffix_array_brut(s);
  //println(sa, saMine);
  //cout << endl;
  assert(saMine.size() == s.size());
  assert(sa.size() == s.size());
  for (int i=0; i < sa.size(); ++i) {
    assert (sa[i] == saMine[i]);
  }
  
  auto lcp = get_lcp_array(s, sa);

  /* 
  auto lcpMine = get_lcp_array_brut(s, sa);
  //println(lcp, lcpMine);
  //cout << endl;
  assert(lcpMine.size() == sa.size() - 1);
  assert(lcp.size() == sa.size() - 1);
  assert (lcpMine.size() == lcp.size());
  for (int i=0; i < lcp.size(); ++i) {
    assert (lcp[i] == lcpMine[i]);
  }
  */


  size_t MOD = 1000000007;

  size_t end1 = s1.size();
  size_t end2 = end1 + 1 + s2.size();
  //println("end1:", end1, "end2:", end2);

  //println(sa);
  //println(lcp);

  for (size_t L=1; L <= min_size; ++L) {
    size_t l=0, r=0, result=0;
    while (l < lcp.size()) {
      while (l < lcp.size() && lcp[l] < L) { ++l; }
      if (l == lcp.size()) { continue; }
      r = l;
      while (r < lcp.size() && lcp[r] >= L) { ++r; }
      // lcp[l, r) is a valid range
      //println("Found range for L =", L, ":", l, r);

      size_t n1=0, n2=0, n3=0;
      for (size_t i=l; i <= r; ++i) {
        //println("sa[i]=", sa[i]);
        if (sa[i] < end1) {
          //println("s1");
          ++n1;
        } else if (end1 < sa[i] && sa[i] < end2) {
          //println("s2");
          ++n2;
        } else if (end2 < sa[i]) {
          //println("s3");
          ++n3;
        }
      }

      result = (result + n1 * n2 * n3) % MOD;

      l = r;
    }
    if (L == 1) {
      print(result);
    } else {
      print("", result);
    }
  }
  println("");

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
