#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <iomanip>
#include <cassert>
#include <cstdio>
#include <vector>
#include <string>	
#include <stack>
#include <queue>
#include <ctime>
#include <cmath>
#include <list>
#include <map>
#include <set>

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n' 
#define all(x) x.begin(),x.end()
#define fill(x,y) memset((x),(y) ,sizeof(x))
#define type(x) __typeof(x.begin())
#define sz(x) (int)x.size()
#define o ((f+l)/2)
#define dg(x) #x << ": " << x << " " 
#define umax(x,y) (x)=max((x),(y))
#define NEW(x) (x *)calloc(1,sizeof(x))
#define umin(x,y) (x)=min((x),(y))
#define tmax(x,y,z) max((x),max((y),(z))) 
#define tmin(x,y,z) min((x),min((y),(z))) 
#define PI (M_PI)

using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef long long int Lint;
const int maxn = 2e6 + 10 ;
int N , M ;
string s , t ;
struct node{
	int isEnd ;
	node *n[26] , *dn[26] , *f ;
}*root;
typedef pair<char,node *> pp;
pp ans[maxn] ;

void buildfall()
{
	queue<node *> q ;
	root->f = root ;
	q.push( root ) ;
	while( !q.empty() ){
		node *p = q.front();
		q.pop();
		for( int i=0 ; i<26 ; i++ )
			if( p->n[i] ){
				node *fall = p ;
				while( fall != root ){
					fall = fall->f ;
					if( fall->n[i] ) {
						fall = fall->n[i] ;
						break;
					}
				}
				p->n[i]->f = fall ;
				q.push( p->n[i] );
			}
	} 
	return ;
}
// Branching
node *get( node *p , int a )
{
	if( p->n[a] ) return p->n[a] ;
	if( p->dn[a] ) return p->dn[a] ;
	if( p == root ) return root ;
	return p->dn[a] = get( p->f , a ) ;
}
int main()
{
	
	freopen("censor.in","r",stdin);
	freopen("censor.out","w",stdout);
	
	//~ ios_base::sync_with_stdio( false ) ;
	//~ cin.tie(NULL);
	
	root = new node ( ) ;
	
	cin >> s >> N ;
	
	for( int i=1 ; i<=N ; i++ ){
		cin >> t ;
		node *p = root ;
		//~ printf("#\n");
		for( int j=0 ; j<sz(t) ; j++ ){
			//~ printf("aaaa\n");
			if( !p->n[t[j]-'a'] ) {p->n[t[j]-'a'] = new node () ;}
			//~ printf("bbbbbbb\n");
			p = p->n[t[j]-'a'] ;
		}
		p->isEnd = sz(t) ; 
	}
	
	
	buildfall() ;
	
	node *p = root ;
	for( int i=0 ; i<sz(s) ; i++ )
	{
		p = get( p , s[i]-'a' ) ;
		//~ while( !p->n[s[i]-'a'] && p != root ) p = p->f ;
		//~ if( p->n[s[i]-'a'] ) p = p->n[s[i]-'a'] ;
		ans[++M] = pp( s[i] , p ) ;
		if( p->isEnd ){
			M -= p->isEnd ;
			if( M < 0 ) while( 1 ) ;
			p = ans[M].se ;
		}
	}
	
	for( int i=1 ; i<=M ; i++ ) cout << ans[i].fi ;
	cout << endl ;
	
	return 0;
}
