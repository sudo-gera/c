#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <set>

using namespace std;

const int INF = 1e9;

void case1() {
	int n;
	cin >> n;
	vector <int> a(n);

	for (auto &i: a) {
		cin >> i;
	}

	sort(a.begin(), a.end());
	do {
		for (auto &i: a) {
			cout << i << " ";
		}
		cout << endl;
	} while (next_permutation(a.begin(), a.end()));
}

void case2() {
	int n;
	cin >> n;
	vector <int> a(n);
	for (auto &i: a) {
		cin >> i;
	}
	sort(a.begin(), a.end());

	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int q;
		cin >> q;
		cout << upper_bound(a.begin(), a.end(), q) - a.begin() << endl;
	}
}

void case3() {
	list <int> lst;
}

void case4() {
	int n;
	cin >> n;
	vector <int> a(n);
	for (auto &i: a) {
		cin >> i;
	}
	vector <int> dp(n + 1, INF);
	vector <int> p(n, -1);
	vector <int> id(n + 1, -1);
	dp[0] = -INF;
	for (int j = 0; j < a.size(); ++j) {
		int i = lower_bound(dp.begin(), dp.end(), a[j]) - dp.begin();
		dp[i] = a[j];
		p[j] = id[i - 1];
		id[i] = j;
	}

	vector <int> ans;

	int j = id[lower_bound(dp.begin(), dp.end(), INF) - dp.begin() - 1];

	while (j != -1) {
		ans.push_back(a[j]);
		j = p[j];
	}
	reverse(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for (auto &i: ans) {
		cout << i << " ";
	}
	cout << endl;
}

void case45() {
	vector <vector <map <int, string> > > gr;
	decltype(gr) gr1;	
}

bool cmp(int a, int b) {
	return a > b;
}

void case5() {
	set <int, decltype(&cmp)> st(cmp);
	st.insert(1);
	st.insert(2);
	st.insert(3);
	for (auto a: st) {
		cout << a << " ";
	}
	cout << endl;
}

void case6() {
	map <int, int, decltype(&cmp)> mp(cmp);
	mp[1000000000] = -2;
	mp[2] = 113;
	mp[113179] = 179113;
	for (auto p: mp) {
		cout << p.first << " " << p.second << endl;
	}
}

void case7() {
	int n;
	cin >> n;
	vector <int> a(n);
	vector <int> zip;
	for (auto &i: a) {
		cin >> i;
		zip.push_back(i);
	}
	sort(zip.begin(), zip.end());
	zip.erase(unique(zip.begin(), zip.end()), zip.end());
	for (auto &i: a) {
		cout << lower_bound(zip.begin(), zip.end(), i) - zip.begin() << " ";
	}
	cout << endl;
}	

void case8() {
	int n, m;
	cin >> n >> m;
	vector <vector <pair <int, int> > > gr(n);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u;
		--v;
		gr[u].push_back({v, w});
		gr[v].push_back({u, w});
	}
	vector <int> dist(n, INF);
	dist[0] = 0;
	set <pair <int, int> > st;
	st.insert({0, 0});
	while (!st.empty()) {
		int v = st.begin()->second;
		st.erase(st.begin());
		for (auto &p: gr[v]) {
			int u = p.first;
			int w = p.second;
			if (dist[v] + w < dist[u]) {
				st.erase({dist[u], u});
				dist[u] = dist[v] + w;
				st.insert({dist[u], u});
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << " " << dist[i] << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (true) {
		case8();
	}
}