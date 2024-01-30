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
/*
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
*/
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
static void radixPass(int* a, int* b, int* r, int n, int K)
{// count occurrences
int* c = new int[K + 1]; // counter array
for (int i = 0; i <= K; i++) c[i] = 0; // reset counters
for (int i = 0; i < n; i++) c[r[a[i]]]++; // count occurrences
for (int i = 0, sum = 0; i <= K; i++) // exclusive prefix sums
{int t = c[i]; c[i] = sum; sum += t; }
for (int i = 0; i < n; i++) b[c[r[a[i]]]++] = a[i]; // sort
delete [] c;
}
// find the suffix array SA of s[0..n-1] in {1..K}ˆn
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void suffixArray(int* s, int* SA, int n, int K) {
int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
int* s12 = new int[n02 + 3]; s12[n02]= s12[n02+1]= s12[n02+2]=0;
int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
int* s0 = new int[n0];
int* SA0 = new int[n0];
// generate positions of mod 1 and mod 2 suffixes
// the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
for (int i=0, j=0; i < n+(n0-n1); i++) if (i%3 != 0) s12[j++] = i;
// lsb radix sort the mod 1 and mod 2 triples
radixPass(s12 , SA12, s+2, n02, K);
radixPass(SA12, s12 , s+1, n02, K);
radixPass(s12 , SA12, s , n02, K);
// find lexicographic names of triples
int name = 0, c0 = -1, c1 = -1, c2 = -1;
for (int i = 0; i < n02; i++) {
if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2)
{name++; c0 = s[SA12[i]]; c1 = s[SA12[i]+1]; c2 = s[SA12[i]+2]; }
if (SA12[i] % 3 == 1) { s12[SA12[i]/3] = name; } // left half
else {s12[SA12[i]/3 + n0] = name; } // right half
}
// recurse if names are not yet unique
if (name < n02) {
suffixArray(s12, SA12, n02, name);
// store unique names in s12 using the suffix array
for (int i = 0; i < n02; i++) s12[SA12[i]] = i + 1;
} else // generate the suffix array of s12 directly
for (int i = 0; i < n02; i++) SA12[s12[i] - 1] = i;
// stably sort the mod 0 suffixes from SA12 by their first character
for (int i=0, j=0; i < n02; i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
radixPass(s0, SA0, s, n0, K);
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
delete [] s12; delete [] SA12; delete [] SA0; delete [] s0;
}


vector<int> get_suffix_array(const string &s) {
    int n = s.size();
    if (n == 0)
        return {};
    if (n == 1)
        return {0};
    vector<int> t(n + 3);
    for (int i = 0; i < n; i++)
        t[i] = s[i];
    vector<int> sa(n);
    suffixArray(t.data(), sa.data(), n, 256);
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
          result[lcpupd] = (result[lcpupd] + n1 * n2 * n3) % MOD;
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
