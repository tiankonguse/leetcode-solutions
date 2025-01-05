#include <bits/stdc++.h>

#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

const int INF = 1e9+7;
int N;
struct node{
	node *lc, *rc;
	int l, r, sum, lz, mx;
	node():lc(NULL), rc(NULL), l(0), r(N), sum(0), lz(-INF), mx(0){}
	void ext(){
		if(lc==NULL){
			lc = new node();
			rc = new node();
			lc->l = l, lc->r = l+r>>1;
			rc->l = (l+r>>1)+1, rc->r = r;
		}
	}
};

void apply(node *&t){
	if(t->l!=t->r) t->ext();
	if(t->lz>-INF){
		t->sum = t->mx = (t->r-t->l+1)*t->lz;
		if(t->l!=t->r){
			t->lc->lz = t->lz;
			t->rc->lz = t->lz;
		}
		t->lz = -INF;
	}
}

void modify(node *&t, int l, int r, int val){
	apply(t);
	if(t->l > r || t->r < l) return;
	if(t->l >= l && t->r <= r){
		t->sum = t->mx = (t->r-t->l+1)*val;
		if(t->l!=t->r){
			t->ext();
			t->lc->lz = val;
			t->rc->lz = val;
		}
		return;
	}
	t->ext();
	modify(t->lc,l,r,val);
	modify(t->rc,l,r,val);
	t->sum = t->lc->sum + t->rc->sum;
	t->mx = max(t->lc->mx, t->lc->sum + t->rc->mx);
}



int query(node *&t, int val){
	apply(t);
	if(t->l==t->r){
		if(t->mx > val) return t->l-1;
		return t->l;
	}
	apply(t->lc);
	if(t->lc->mx > val) return query(t->lc,val);
	return query(t->rc,val-t->lc->sum);	
}


int main(){
	fastio 	
	cin >> N;
	node *t = new node();
	char q;
	while(cin >> q){
		if(q=='E') return 0;
		if(q=='Q'){
			int val;
			cin >> val;
			cout << query(t,val) << "\n";
		}else{
			int l,r,d;
			cin >> l >> r >> d;
			modify(t,l,r,d);
		}
	}
}