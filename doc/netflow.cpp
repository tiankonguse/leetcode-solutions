/****************************************\
* Author : ztx
* Title  :
* ALG    : ISAP
* CMT    :
* Time   :
\****************************************/

#include <cstdio>

typedef long long ll ;

int CH , NEG ;
template<typename TP>inline void read(TP& ret) {
    ret = NEG = 0 ; while (CH=getchar() , CH<'!') ;
    if (CH == '-') NEG = true , CH = getchar() ;
    while (ret = ret*10+CH-'0' , CH=getchar() , CH>'!') ;
    if (NEG) ret = -ret ;
}

#include <cstring>

#define  maxN  ____LL
#define  maxM  ____LL
#define  infi  0x________LL

struct FST { int to , next ; ll flow ; } e[maxM<<1] ;
int star[maxN] , tote ;
inline void FST_init() { memset(star , 0 , sizeof star) ; tote = 1 ; }
inline void AddEdge(int u , int v , ll cap) {
	e[++tote].to = v ; e[tote].flow = cap ; e[tote].next = star[u] ; star[u] = tote ;
	e[++tote].to = u ; e[tote].flow = 0 ; e[tote].next = star[v] ; star[v] = tote ;
}

#define  min(x,y) ((x)<(y)?(x):(y))
int N , S , T ;
int h[maxN] , vh[maxN] ;

ll dfs(int u , ll flowu) {
int p , tmp = h[u]+1 ;
ll flow = 0 , flowv ;
	if (u == T) return flowu ;
	for (p = star[u] ; p ; p = e[p].next) {
		if (e[p].flow && (h[e[p].to]+1==h[u])) {
			flowv = dfs(e[p].to , min(flowu-flow , e[p].flow)) ;
			flow += flowv ; e[p].flow -= flowv ; e[p^1].flow += flowv ;
			if (flow==flowu || h[S]==N) return flow ;
		}
	}
	for (p = star[u] ; p ; p = e[p].next)
		if (e[p].flow) tmp = min(tmp , h[e[p].to]) ;
	if (--vh[h[u]] == 0) h[S] = N ;
	else ++ vh[h[u]=tmp+1] ;
	return flow ;
}

ll SAP() {
	ll ret = 0 ;
	memset(vh , 0 , sizeof vh) ;
	memset(h , 0 , sizeof h) ;
	vh[S] = N ;
	while (h[S] < N) ret += dfs(S , infi) ;
	return ret ;
}

int main() {
//	#define READ
	#ifdef  READ
		freopen(".in" ,"r",stdin ) ;
		freopen(".out","w",stdout) ;
	#endif
	FST_init() ;
	#ifdef  READ
		fclose(stdin) ; fclose(stdout) ;
	#else
		getchar() ; getchar() ;
	#endif
	return 0 ;
}