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
const int maxn = 1e5 + 10 ;
const int inf = 1e9 ;
int N , L , R , dn[maxn] , seg[maxn*4] , tmp[maxn] , parent[maxn] ;
vector<ii> we[maxn] , er[maxn] ;

int dfs( int a , int dad )
{
	dn[a] = 1 ;
	parent[a] = dad ;
	for( auto i : er[a] )
		if( i.fi != dad )
			dn[a] += dfs( i.fi , a ) ;
	return dn[a] ; 
}
int get_center( int a , int dad )
{
	fill( dn , 0 ) ;
	fill( parent , 0 ) ;
	dfs( a , dad ) ;
	
	int maks = 0 , ret = -1 ;
	
	for( int i=1 ; i<=N ; i++ ){
		if( !dn[i] ) continue ;
		int curmaks = dn[a] - dn[i] ;
		for( auto j : er[i] ) 
			if( j.fi != parent[i] )
				umax( curmaks , dn[j.fi] ) ;
		
		//~ cout << i << " : " << curmaks << endl ;
		
		if( ret == -1 || curmaks < maks ) {
			maks = curmaks ;
			ret = i ;
		}
		//~ cout << dg(ret) << dg(maks) << endl ;
	}
	return ret ;
}
void init( int k , int f , int l )
{
	seg[k] = -inf ;
	if( f == l ) return ;
	init( 2*k ,  f , o ) ;
	init( 2*k+1 ,  o+1 , l ) ;
	return ;
}
int upd( int k , int f , int l , int a , int b )
{
	if( a < f || l < a ) return seg[k] ;
	if( f == l ){
		umax( seg[k] , b ) ;
		return seg[k] ;
	}
	return seg[k] = max( upd( 2*k , f , o , a , b ) , upd(2*k+1 , o+1 , l , a , b) ) ;
} 
int find( int k , int f , int l , int a , int b )
{
	if( b < f || l < a ) return -inf ;
	if( a <= f && l <= b ) return seg[k] ;
	return max( find( 2*k , f , o , a , b ) , find( 2*k , o+1 , l , a , b ) ) ;
}
void f( int a , int dad , int root , int beauty , int len )
{
	umax( tmp[len] , beauty ) ;
	for( ii i : er[a] )
		if( i.fi != dad && i.fi != root )
			f( i.fi , a , root , beauty+i.se , len+1 ) ;
	return ;
}
int solve( int a , int dad , int median )
{
	for( int i=1 ; i<=N ; i++ ){
		er[i].clear(); 
		for( int j = 0 ; j < sz(we[i]) ; j++ )
			er[i].pb( ii( we[i][j].fi , (we[i][j].se>=median)?1:-1 ) ) ;
	}
	
	int C = get_center( a , dad ) ;
	//~ cout << dg(a) << dg(dad) << dg(C) << endl ;
	assert( C != -1 ) ;
	
	init( 1 , 1 , N ) ;
	
	for( auto i : er[C] ){  
		
		for( int j=1 ; j<=N ; j++ ) tmp[j] = -inf ;
		tmp[0] = 0 ;
		f( i.fi , C , dad , i.se , 1 ) ;
		cout << i.fi << endl ;
		for( int i=0 ; i<N ; i++ ) cout << dg(i) << tmp[i] << endl ;  
		for( int j=0 ; j<N ; j++ )
			if( tmp[j] + find( 1 , 1 , N , L-j , R-j ) >= 0 )
				return 1 ;
		
		for( int j=0 ; j<N ; j++ )
			upd( 1 , 1 , N , j , tmp[j] ) ;
		
	}
	
	for( auto i : er[a] )
		if( i.fi != dad && solve( i.fi , a , median ) ) return 1 ;
	
	return 0 ; 
}
int can( int a )
{
	return solve( 1 , 0 , a ) ;
}
int main()
{
	
	int b = 1e9 , e = 0 ;
	cin >> N  >> L >> R ;
	for( int i=1 ; i<N ; i++ ){
		int _a , _b , _c  ;
		cin >> _a >> _b >> _c ;
		er[_a].pb( ii( _b , _c ) ) ;
		er[_b].pb( ii( _a , _c ) ) ;
		umin( b , _c ) ;
		//~ cout << dg(b) << dg(c) << endl ;
		umax( e , _c ) ;
	}
	
	//~ int C = get_center( 1 , 0 ) ;
	//~ cout << C << endl ;
	//~ for( int i=1 ; i<=N ; i++ ) cout << dg(i) << dn[i] << " " << parent[i] << endl ;
	//~ 
	//~ return 0 ;
	
	cout << dg(can(2)) << endl ;
	
	for( int step = 0 ; step < 20 ; step++ ){
		int m = ( b + e ) >> 1 ;
		if( can( m ) ) b = m ;
		else e = m ;
	}
	
	cout << b << endl ;
	
	return 0;
}
