#include "biginteger.h"

typedef long long ll;
const ll MOD = 998244353; // most popular "good" prime number
ll add(ll x, ll y)
{
	x += y;
	if (x >= MOD) return x - MOD;
	return x;
}
ll sub(ll x, ll y)
{
	x -= y;
	if (x < 0) return x + MOD;
	return x;
}
ll mult(ll x, ll y)
{
	return (x * y) % MOD;
}
ll binPow(ll x, ll p)
{
	if (p == 0) return 1;
	if (p == 2 || (p & 1)) return mult(x, binPow(x, p - 1));
	return binPow(binPow(x, p / 2), 2);
}
ll modRev(ll x)
{
	return binPow(x, MOD - 2);
}

const int LOG = 18;
const int N = 1 << LOG;
ll w[N + 5];
int rev[N + 5];

void initFFT()
{
	// finding root
	ll W = -1;
	for (ll x = 2;; x++)
	{
		ll y = x;
		for (int i = 1; i < LOG; i++)
			y = mult(y, y);
		// y = x ** (n / 2)
		// so, y != 1
		// but y ** 2 == 1
		if (y == MOD - 1)
		{
			W = x;
			break;
		}
	}
	if (W == -1) throw;
	w[0] = 1;
	for (int i = 1; i < N; i++)
		w[i] = mult(w[i - 1], W); // no precision errors now

	int k = 0;
	rev[0] = 0;
	for (int mask = 1; mask < N; mask++)
	{
		if (mask >> (k + 1)) k++; // k - the most significant bit of mask
		rev[mask] = rev[mask ^ (1 << k)] ^ (1 << (LOG - 1 - k));
	}
}

ll F[2][N]; // maintain two layers
void FFT(ll *A, int k) // n = (1 << k)
{
	int L = 1 << k;
	// rearrange coefficients
	for (int mask = 0; mask < L; mask++)
		F[0][rev[mask] >> (LOG - k)] = A[mask];
	int t = 0, nt = 1; // t - current, nt - new
	for (int lvl = 0; lvl < k; lvl++)
	{
		int len = 1 << lvl;
		for (int st = 0; st < L; st += (len << 1))
			for (int i = 0; i < len; i++)
			{
				ll summand = mult(F[t][st + len + i], w[i << (LOG - 1 - lvl)]);
				F[nt][st + i] = add(F[t][st + i], summand);
				F[nt][st + len + i] = sub(F[t][st + i], summand);
			}
		swap(t, nt); // change layers
	}
	for (int i = 0; i < L; i++)
		A[i] = F[t][i];
}

vector<ll> multiply(vector<ll> A, vector<ll> B)
{
	int sz1 = (int)A.size(), sz2 = (int)B.size();
	int k = 0;
	// deg(A) = sz1 - 1, deg(B) = sz2 - 1, deg(AB) = sz1 + sz2 - 2
	while((1 << k) < (sz1 + sz2 - 1)) k++;
	int L = 1 << k;
	ll C[L], D[L];
	for (int i = 0; i < L; i++)
		C[i] = D[i] = 0;
	for (int i = 0; i < sz1; i++)
		C[i] = A[i];
	for (int i = 0; i < sz2; i++)
		D[i] = B[i];
	FFT(C, k);
	FFT(D, k);
	for (int i = 0; i < L; i++)
		C[i] = mult(C[i], D[i]);
	FFT(C, k);
	reverse(C + 1, C + L);
	vector<ll> res;
	res.resize(sz1 + sz2 - 1);
	// important change here
	// we should divide by L modulo MOD
	ll rL = modRev(L);
	for (int i = 0; i < sz1 + sz2 - 1; i++)
		res.push_back(mult(C[i], rL));
	return res;
}

int main(){
	string q,e;
	cin>>q>>e;
	for (auto&w:q){
		w-='0';
	}
	for (auto&w:e){
		w-='0';
	}
	reverse(q.begin(),q.end());
	reverse(e.begin(),e.end());
	int64_t a,s;
	a=1;
	s=q.size()+e.size();
	while(s){
		a*=2;
		s/=2;
	}
	q.resize(a,0);
	e.resize(a,0);
	vector<ll> z(q.begin(),q.end()),x(e.begin(),e.end());
	print(z,x)
	z=multiply(z,x);
	reverse(z.begin(),z.end());
	print(z)
}
