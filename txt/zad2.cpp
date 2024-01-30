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

vector<int> get_suffix_array(const string& s)
{
    int n = s.size();
    vector<int> sa(n), rank(n);
    for (int i = 0; i < n; i++) {
      rank[i] = s[i];
      sa[i] = i;
    }

    for(int k = 0; k < n; k ? k *= 2 : k = 1)
    {
        sort(sa.begin(), sa.end(), [&](int i, int j)
             {
                 if (rank[i] == rank[j])
                    return rank[(i + k) % n] < rank[(j + k) % n];
                 return rank[i] < rank[j];
             });
        vector<int> nrank(n);
        int r = 0;
        for(int i = 1; i < n; i++)
        {
            if(rank[sa[i]] != rank[sa[i - 1]]) r++;
            else if(rank[(sa[i] + k) % n] != rank[(sa[i - 1] + k) % n]) r++;
            nrank[sa[i]] = r;
        }
        rank = nrank;
    }
    return sa;
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
  /*
  auto saMine = get_suffix_array_brut(s);
  //println(sa, saMine);
  //cout << endl;
  assert(saMine.size() == s.size());
  assert(sa.size() == s.size());
  for (int i=0; i < sa.size(); ++i) {
    assert (sa[i] == saMine[i]);
  }
  */
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
  size_t end3 = end2 + 1 + s3.size();
  //println("end1:", end1, "end2:", end2);

  // cnti[j]: number of occurences of some suffixes of string i on sa[0:j)
  vector<size_t> cnt1={0}, cnt2={0}, cnt3={0};
  cnt1.reserve(sa.size() + 1);
  cnt2.reserve(sa.size() + 1);
  cnt3.reserve(sa.size() + 1);
  size_t n1=0, n2=0, n3=0;
  for (size_t i=0; i < sa.size(); ++i) {
    if (sa[i] < end1) {
      ++n1;
    } else if (end1 < sa[i] && sa[i] < end2) {
      ++n2;
    } else if (end2 < sa[i] && sa[i] < end3) {
      ++n3;
    }
    cnt1.push_back(n1);
    cnt2.push_back(n2);
    cnt3.push_back(n3);
  }

  vector<size_t> result (min_size + 1);

  // use the fact that lcp grows at most by 1 each step
  stack<size_t> prev_ind;
  size_t prev_lcp = lcp[0];
  assert (prev_lcp == 0);
  for (size_t i=1; i <= lcp.size(); ++i) {
    size_t cur_lcp = i < lcp.size() ? lcp[i] : 0;

    if (cur_lcp >= prev_lcp) {
      for (size_t j=prev_lcp + 1; j <= cur_lcp; ++j) {
        prev_ind.push({i});
      }
    } else {
      while (prev_ind.size() > cur_lcp) {
        auto ind = prev_ind.top();
        
        size_t n1 = cnt1[i + 1] - cnt1[ind],
               n2 = cnt2[i + 1] - cnt2[ind],
               n3 = cnt3[i + 1] - cnt3[ind];
        result[prev_ind.size()] = (result[prev_ind.size()]+n1*n2*n3) % MOD;
        prev_ind.pop();
      }
    }

    prev_lcp = cur_lcp;
  }

  print(result[1]);
  for (size_t i=2; i < result.size(); ++i) {
    print("", result[i]);
  }
  println("");

  return 0;
  for (size_t L=1; L <= min_size; ++L) {
    size_t l=0, r=0, result=0;
    while (l < lcp.size()) {
      while (l < lcp.size() && lcp[l] < L) { ++l; }
      if (l == lcp.size()) { continue; }
      r = l;
      while (r < lcp.size() && lcp[r] >= L) { ++r; }
      // lcp[l, r) is a valid range
      
      size_t n1=cnt1[r + 1]-cnt1[l], n2=cnt2[r+1]-cnt2[l], n3=cnt3[r+1]-cnt3[l];
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
