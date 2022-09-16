#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r) for(int i=(l);i<=(r);++i)
#define REP(i,n) FOR(i,0,(n)-1)
#define ssize(x) int(x.size())
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<'('<<p.first<<", "<<p.second<<')';}
template<class T>auto operator<<(ostream&o,T x)->decltype(x.end(),o){
	static_assert(not std::is_same_v<T, std::string>, "not for string");
	o<<'{';int i=0;for(auto e:x)o<<(", ")+2*!i++<<e;return o<<'}';}

auto operator<<(ostream&o, std::string x)->decltype(x.end(),o) {
	for (auto e:x) o << e;
	return o;
}
#ifdef DEBUG
#define debug(x...) cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<'\n';}(x)
#else
#define debug(...) {}
#endif
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int n;
    cin >> n;
 
    vector<int> a(n);
    int sum = 0;
    REP(i, n) {
        cin >> a[i];
        sum += a[i];
    }

    pair<int, char> p {2137, '*'};
    vector<int> t {1,2,3};
    vector<char> tt {'r','t','y'};
    //map<char, string> s{{'r', "raban"}, {'b', "balagan"}, {'t', "tygrys"}};
    string k = "manieczki";

    cout <<1<<2<<"pawel"<<4.5f<<'O'<<make_pair('a','b')<<4.5<<t<<tt<<
	    p<<k<<
	    vector<char>(2, 'a')<<map<int,int>();//<<s<<'\n';
    cout << sum << "\n";
}
