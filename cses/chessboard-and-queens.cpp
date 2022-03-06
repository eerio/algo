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

bool is_safe(vector<vector<char>> board, int y, int x) {
  // check if field blocked
  if (board[y][x] == '*') { return false; }

  // check row
  for (int x2=0; x2 < x; ++x2) { if (board[y][x2] == 'x') { return false; } }

  // check rising diagonal
  for (int x2=x, y2=y; x2 >= 0 && y2 >= 0; --x2, --y2) {
    if (board[y2][x2] == 'x') { return false; }
  }

  int n = board.size();
  // check falling diagonal
  for (int x2=x, y2=y; x2 >= 0 && y2 < n; --x2, ++y2) {
    if (board[y2][x2] == 'x') { return false; }
  }

  return true;
}

int _n_queens(vector<vector<char>> board, int x) {
  int n = board.size();
  int result = 0;

  if (x >= n) { return 1; }
  
  for (int y=0; y < n; ++y) {
    if (is_safe(board, y, x)) {
      board[y][x] = 'x';

      result += _n_queens(board, x + 1);
      // it couldn't be '*' or 'x' because is_safe would fail
      board[y][x] = '.';
    }
  }

  return result;
}

int n_queens(vector<vector<char>> board) {
  return _n_queens(board, 0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  unsigned int n = 8;

  vector<vector<char>> board (n);

  REP(i, n) {
    string s;
    cin >> s;
    
    REP(j, n) { board[i].push_back(s[j]); }
  }

  println(n_queens(board));

  return 0;
}