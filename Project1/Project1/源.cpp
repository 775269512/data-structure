
#include<stdlib.h>
#include<algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = (int)1e5 + 5;
const int MOD = 99971;
int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch<'0' || ch>'9') { if (ch == '-')f = -1; ch = getchar(); }
	while (ch >= '0'&&ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
int a[MAXN];
int nxt[MAXN];
int cal[MAXN][48];
int tree[MAXN << 2][48], flag[MAXN << 2];
void pushup(int rt) {
	for (int i = 0; i<48; i++) {
		tree[rt][i] = tree[lson][(i + flag[lson] + 48) % 48] + tree[rson][(i + flag[rson] + 48) % 48];
		if (tree[rt][i] >= MOD)tree[rt][i] -= MOD;
	}
}
void build(int l, int r, int rt) {
	flag[rt] = 0;
	if (l == r) {
		for (int i = 0; i<48; i++) {
			tree[rt][i] = cal[a[l]][i];
		}
		return;
	}
	int mid = l + r >> 1;
	build(l, mid, lson);
	build(mid + 1, r, rson);
	pushup(rt);
}
void update(int l, int r, int x, int y, int rt) {
	if (l == x && r == y) {
		flag[rt]++;
		if (flag[rt] == 48)flag[rt] = 0;
		return;
	}
	int mid = l + r >> 1;
	if (y <= mid)update(l, mid, x, y, lson);
	else if (x>mid)update(mid + 1, r, x, y, rson);
	else update(l, mid, x, mid, lson), update(mid + 1, r, mid + 1, y, rson);
	pushup(rt);
}
int query(int l, int r, int x, int y, int rt, int sum) {
	if (l == x && r == y) {
		return tree[rt][(flag[rt] + sum) % 48];
	}
	int mid = l + r >> 1;
	int re = 0;
	if (y <= mid)re = query(l, mid, x, y, lson, sum + flag[rt]);
	else if (x>mid)re = query(mid + 1, r, x, y, rson, sum + flag[rt]);
	else re = query(l, mid, x, mid, lson, sum + flag[rt]) + query(mid + 1, r, mid + 1, y, rson, sum + flag[rt]);
	if (re >= MOD)re -= MOD;
	return re;
}
int main()
{
	int t;
	t = read();
	for (int i = 1; i<MOD; i++)nxt[i] = 1ll * i*i*i%MOD;
	for (int i = 1; i<MOD; i++) {
		cal[i][0] = i;
		for (int j = 1; j<48; j++) {
			cal[i][j] = nxt[cal[i][j - 1]];
		}
	}
	while (t--) {
		int n, m;
		n = read();
		m = read();
		for (int i = 1; i <= n; i++) {
			a[i] = read();
			a[i] %= MOD;
		}
		build(1, n, 1);
		for (int i = 1; i <= m; i++) {
			int op, l, r;
			op = read(); l = read(); r = read();
			if (op & 1) {
				update(1, n, l, r, 1);
			}
			else {
				printf("%d\n", query(1, n, l, r, 1, 0));
			}
		}
	}
	return 0;
}
