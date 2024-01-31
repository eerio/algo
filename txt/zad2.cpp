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
//#define FIX_RNGSEED
//#ifdef FIX_RNGSEED
//mt19937_64 mt(42);
//#else
// this doesn't work in CSES' online judge
  //random_device real_rnd;
  //mt19937_64 mt(real_rnd());
//#endif

// return from uniform distribution on [l, r]
//int randint(int l, int r) { uniform_int_distribution<int> dist (l, r); return dist(mt); }



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

inline bool leq(int a1, int a2, int b1, int b2) // lexicographic order
{return(a1 < b1 || a1 == b1 && a2 <= b2); } // for pairs
inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3)
{return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3)); } // and triples

// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
void radixPass(
  const vector<int>& a,
  vector<int>& b,
  const vector<int>& r,
  size_t r_offset,
  size_t n,
  size_t K
) {
  // counter array
  vector<size_t> c (K + 1); 
  // count occurrences
  for (size_t i = 0; i < n; ++i) { c[r[r_offset + a[i]]]++; }
  // exclusive prefix sums
  for (size_t i = 0, sum = 0; i <= K; i++) {
    auto t = c[i];
    c[i] = sum;
    sum += t;
  }
  // sort
  for (size_t i = 0; i < n; ++i) {
    b[c[r[r_offset + a[i]]]++] = a[i];
  }
}

// find the suffix array SA of s[0..n-1] in {1..K}ˆn
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void suffixArray(const vector<int>& s, vector<int>& SA, size_t n, int K) {
  // Part 1: Partition the suffixes of s into three categories: S0, S1, S2
  // sizes of the partitions S0, S1, S2
  size_t n0 = (n + 2) / 3;
  size_t n1 = (n + 1) / 3;
  size_t n2 = n / 3;
  size_t n02 = n0 + n2;

  vector<int> s0 (n0);
  vector<int> s12 (n02 + 3);
  s12[n02] = s12[n02 + 1] = s12[n02 + 2] = 0;

  vector<int> SA0 (n0);
  vector<int> SA12 (n02 + 3);
  SA12[n02] = SA12[n02 + 1] = SA12[n02 + 2] = 0;

  // Construct a new string s12 to sort the sample suffixes
  for (size_t s_pos=0, s12_pos=0; s_pos < (n % 3 == 1 ? n + 1 : n); ++s_pos) {
    if (s_pos % 3 != 0) {
      s12[s12_pos++] = s_pos;
    }
  }

  // Sort the triples of s12
  // treat 3 characters of s12 as one ,,character'' - LSD radix sort
  // in 3 steps, the 2/1/0 parameter gives offset to the `s` array;
  // i.e. first the triples will be sorted by i+2 (LSD) digit, then i+1
  // and then ith
  radixPass(s12,  SA12, s, 2, n02, K);
  radixPass(SA12, s12 , s, 1, n02, K);
  radixPass(s12,  SA12, s, 0, n02, K);

  // Rename the triples with their ranks to obtain a new string
  int name = 0, c0 = -1, c1 = -1, c2 = -1;
  for (size_t i = 0; i < n02; ++i) {
    if (s[SA12[i]] != c0 || s[SA12[i] + 1] != c1 || s[SA12[i] + 2] != c2) {
      ++name;
      c0 = s[SA12[i]];
      c1 = s[SA12[i] + 1];
      c2 = s[SA12[i] + 2];
    }
    if (SA12[i] % 3 == 1) { s12[SA12[i] / 3] = name; } // left half
    else { s12[SA12[i] / 3 + n0] = name; } // right half
  }
  // If any of the characters of s12 are the same, recursively sort
  // the suffixes of SA12
  if (name < n02) {
    suffixArray(s12, SA12, n02, name);
  // store unique names in s12 using the suffix array
  for (int i = 0; i < n02; i++) s12[SA12[i]] = i + 1;
  } else // generate the suffix array of s12 directly
  for (int i = 0; i < n02; i++) SA12[s12[i] - 1] = i;
  // stably sort the mod 0 suffixes from SA12 by their first character
  for (int i=0, j=0; i < n02; i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
  radixPass(s0, SA0, s, 0, n0, K);
  // merge sorted SA0 suffixes and sorted SA12 suffixes
  for (int p=0, t=n0-n1, k=0; k < n; k++) {
#define GetI() (SA12[t] < n0 ? SA12[t]*3+1: (SA12[t] - n0) * 3 + 2)
  int i = GetI(); // pos of current offset 12 suffix
  int j = SA0[p]; // pos of current offset 0 suffix
  if (SA12[t] < n0 ? // different compares for mod 1 and mod 2 suffixes
  leq(s[i], s12[SA12[t] + n0], s[j], s12[j/3]) :
  leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
  {// suffix from SA12 is smaller
  SA[k] = i; t++;
  if (t == n02) // done --- only SA0 suffixes left
  for (k++; p < n0; p++, k++) SA[k] = SA0[p];
  } else {// suffix from SA0 is smaller
  SA[k] = j; p++;
  if (p == n0) // done --- only SA12 suffixes left
  for (k++; t < n02; t++, k++) SA[k] = GetI();
  }
  }
}


vector<int> get_suffix_array(const string &s) {
    size_t n = s.size();
    if (n == 0) { return {}; }
    if (n == 1) { return {0}; }
    vector<int> t(n + 3);
    for (size_t i = 0; i < n; ++i) { t[i] = s[i]; }
    vector<int> sa(n);
    suffixArray(t, sa, n, 256);
    return sa;
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

  stack<tuple<size_t, size_t, size_t>> prev_ind;
  size_t prev_lcp = lcp[0];
  assert (prev_lcp == 0);
  for (size_t i=1; i <= lcp.size(); ++i) {
    size_t cur_lcp = i < lcp.size() ? lcp[i] : 0;

    if (cur_lcp > prev_lcp) {
      // at index i, islands for lengths [prev_lcp+1, ..., cur_lcp] begins
      prev_ind.push({prev_lcp + 1, cur_lcp, i});
    } else {
      while (!prev_ind.empty() && get<1>(prev_ind.top()) > cur_lcp) {
        auto [start, end, ind] = prev_ind.top();
        prev_ind.pop();
        
        size_t n1 = cnt1[i + 1] - cnt1[ind],
               n2 = cnt2[i + 1] - cnt2[ind],
               n3 = cnt3[i + 1] - cnt3[ind];

        for (size_t lcpupd = max(cur_lcp + 1, start); lcpupd <= end; ++lcpupd) {
          result[lcpupd] = (result[lcpupd] + (((n1 * n2) % MOD) * n3) % MOD) % MOD;
        }

        if (cur_lcp >= start) {
          prev_ind.push({start, cur_lcp, ind});
        }
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
}
