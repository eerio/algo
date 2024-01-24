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


/*
 * Opis: O(n \log n) lub O(n \alpha),
 * 	Dla słowa \texttt{abaab\#} (hash jest aby to zawsze liście były stanami kończącymi)
 * 	stworzy \texttt{sons[0]=\{(\#,10),(a,4),(b,8)\}, sons[4]=\{(a,5),(b,6)\}, sons[6]=\{(\#,7),(a,2)\}, sons[8]=\{(\#,9),(a,3)\}},
 * 	reszta sons'ów pusta, \texttt{slink[6]=8} i reszta slink'ów $0$
 * 	(gdzie slink jest zdefiniowany dla nie-liści jako wierzchołek zawierający ten suffix bez ostatniej literki),
 * 	\texttt{up\_edge\_range[2]=up\_edge\_range[3]=(2,5), up\_edge\_range[5]=(3,5)} i reszta jednoliterowa.
 * 	Wierzchołek 1 oraz suffix wierzchołków jest roboczy.
 * 	Zachodzi \texttt{up\_edge\_range[0]=(-1,-1), parent[0]=0, slink[0]=1}.
 */
struct SuffixTree {
	const int n;
	const vector<int> &_in;
	vector<map<int, int>> sons;
	vector<pair<int, int>> up_edge_range;
	vector<int> parent, slink;
	int tv = 0, tp = 0, ts = 2, la = 0;
  // number of sentinels of given type (1, 2, 3) in subtree
  vector<vector<int>> num_sentinels_below;
  vector<size_t> sentinel_pos;
  vector<unsigned long long int > sums;

  void set_num_sentinels(int i) {
    println("set num sentinels:", i);
    if (sons[i].empty()) {
      int from = up_edge_range[i].first;

      int n_sent = 1;
      assert (from != -1);
      if (from <= sentinel_pos[1]) { n_sent++; }
      if (from <= sentinel_pos[0]) { n_sent++; }
      num_sentinels_below[i][n_sent] = 1;
      return;
    } 
    
    for (auto [k, child]: sons[i]) {
      set_num_sentinels(child);
    }

    for (int n_sent: {1, 2, 3}) {
      for (auto [k, child]: sons[i]) {
        num_sentinels_below[i][n_sent]+=num_sentinels_below[child][n_sent];
      }
    }
   
    sums[i] = num_sentinels_below[i][1] * num_sentinels_below[i][2] * num_sentinels_below[i][3];
    for (auto [k, child]: sons[i]) {
      sums[i] = (sums[i] + sums[child]) % 1000000007;
    }
    println("sums[", i, "] = ", sums[i]);
    //sums[i] %= 1000000007;
  }

  void solve() {
    set_num_sentinels(0);
    if (sons[0].empty()) { return; }
    int result = 0;
    // length 1
    deque<int> todo;
    for (auto [k, child]: sons[0]) {
      todo.push_back(child);
      result = (result + sums[child]) % 1000000007;
    }
    print(result);

    // lengths >= 2
    while (!todo.empty()) {
      deque<int> new_todo;
      int layer_result = 0;
      while(!todo.empty()) {
        auto node = todo.front();
        todo.pop_front();
        layer_result = (layer_result + sums[node]) % 1000000007;
        for (auto [k, child]: sons[node]) { new_todo.push_back(child); }
      }

      print("", layer_result);
      todo = new_todo;
    }
    println("");
  }

	void ukkadd(int c) {
		auto &lr = up_edge_range;
suff:
		if (lr[tv].second < tp) {
			if (sons[tv].find(c) == sons[tv].end()) {
				sons[tv][c] = ts; lr[ts].first = la; parent[ts++] = tv;
				tv = slink[tv]; tp = lr[tv].second + 1; goto suff;
			}
			tv = sons[tv][c]; tp = lr[tv].first;
		}
		if (tp == -1 || c == _in[tp])
			tp++;
		else {
			lr[ts + 1].first = la; parent[ts + 1] = ts;
			lr[ts].first = lr[tv].first; lr[ts].second = tp - 1;
			parent[ts] = parent[tv]; sons[ts][c] = ts + 1; sons[ts][_in[tp]] = tv;
			lr[tv].first = tp; parent[tv] = ts;
			sons[parent[ts]][_in[lr[ts].first]] = ts; ts += 2;
			tv = slink[parent[ts - 2]]; tp = lr[ts - 2].first;
			while (tp <= lr[ts - 2].second) {
				tv = sons[tv][_in[tp]]; tp += lr[tv].second - lr[tv].first + 1;
			}
			if (tp == lr[ts - 2].second + 1)
				slink[ts - 2] = tv;
			else
				slink[ts - 2] = ts;
			tp = lr[tv].second - (tp - lr[ts-2].second) + 2; goto suff;
		}
	}
	// Remember to append string with a hash.
	SuffixTree(const vector<int> &in, int alpha, vector<size_t> sentinels)
		: n(int(in.size())), _in(in), sons(2 * n + 1), sentinel_pos(sentinels), 
		up_edge_range(2 * n + 1, pair(0, n - 1)), parent(2 * n + 1), slink(2 * n + 1), num_sentinels_below(2 * n + 1, vector<int>(4)), sums(2 * n + 1) {
		up_edge_range[0] = up_edge_range[1] = {-1, -1};
		slink[0] = 1;
		// When changing map to vector, fill sons exactly here with -1 and replace if in ukkadd with sons[tv][c] == -1.
		REP(ch, alpha)
			sons[1][ch] = 0;
		for(; la < n; ++la)
			ukkadd(in[la]);
	}
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s1, s2, s3;
  cin >> s1 >> s2 >> s3; 
  
  string s = s1 + "1" + s2 + "2" + s3 + "3";
  auto st = SuffixTree(vector<int>(s.begin(), s.end()), 'z', {s1.size(), s1.size() + 1 + s2.size(), s1.size() + 1 + s2.size() + 1 + s3.size()});

  st.solve();

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
