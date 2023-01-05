#include<bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
#define ll      long long
#define pb      push_back
#define TT ll time;        cin >> time; while(time--)
#define FastIo  ios_base::sync_with_stdio(false);cin.tie(NULL) ;
const ll int INF = 5e18 , nmax = 2501 , block = 350 , N = 1e5+10 , mod = 998244353;
#ifndef ONLINE_JUDGE
#include "algodebug.h"
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

struct node
{
  int one, two , three ;
}tree[4*N];
int lazy[4*N] ;

void push_down(int n, int b, int e){
  int l = n*2 , r = n*2 +1 ;
  if(lazy[n]){
    if(lazy[n]%3 == 1){
        ll temp = tree[n].one;
        tree[n].one = tree[n].three ;
        tree[n].three = tree[n].two ;
        tree[n].two = temp ;
    }
    if(lazy[n]%3 == 2){
      ll temp = tree[n].three;
      tree[n].three = tree[n].one ; 
      tree[n].one = tree[n].two;
      tree[n].two = temp;
     
    }
    if(b != e){
      lazy[l]+=lazy[n] ;
      lazy[r]+=lazy[n] ;
    }
  }
  lazy[n] = 0 ;
}

void build(int n , int b, int e){
  if(b == e){
    tree[n].one = 0 ;
    tree[n].two = 0 ;
    tree[n].three = 1 ;
    return ;
  }
  int mid = (b + e) / 2 , l = n*2 , r = n*2+1 ;
  build(l , b, mid) ;
  build(r , mid+1 , e) ;
  tree[n].three = tree[l].three + tree[r].three ;
  tree[n].two = tree[l].two + tree[r].two ;
  tree[n].one = tree[l].one + tree[r].one ;
  return ;
}

void update(int n, int b, int e , int l1 , int r1){
   push_down(n , b, e) ;
   if(l1 > e or r1 < b) return ;
   if(l1 <= b and  r1 >= e){
        ll temp = tree[n].three ;
        tree[n].three = tree[n].two ;
        tree[n].two = tree[n].one ;
        tree[n].one = temp ;
        if(b != e) lazy[(n*2)]++ , lazy[(n*2+1)]++ ;
        return ;
   }
   int mid = (b + e) / 2 , l = n*2 , r = l + 1 ;
   update(l , b, mid, l1 , r1) ;
   update(r, mid + 1, e , l1, r1) ;
   tree[n].three = tree[l].three + tree[r].three ;
   tree[n].two = tree[l].two + tree[r].two ;
   tree[n].one = tree[l].one + tree[r].one ;
   return;
}

int query(int n , int b, int e, int l1 , int r1){
  push_down(n, b , e) ;
  if(r1 < b or l1 > e) return 0 ;
  if(l1 <= b and r1 >=e){
    return tree[n].three ;
  }
  int mid = (b + e) / 2 , l = n*2 , r = l + 1 ;
  return query(l , b , mid , l1 , r1 ) + query(r , mid+1, e, l1, r1) ;
}





int main(){

    int tt = 1 ;
    TT{

      int n , q ;
      scanf("%d %d", &n , &q) ;
      build(1, 1, n) ;
      
      vector < int > ans ;
      for( int i = 0 ; i < q; i++){
        int x, y , z ;
        scanf("%d %d %d", &x, &y, &z) ;
        if(x == 0) update(1, 1, n , y+1, z+1) ;
        else  ans.pb(query(1, 1, n , y+1, z+1)) ;
      }
      printf("Case %d:\n", tt++);
      for( int i = 0 ; i < ans.size() ; i++) printf("%d\n", ans[i]);
      memset(tree, 0 , sizeof(tree)) ;
      memset(lazy, 0 , sizeof(lazy)) ;

}
    return 0 ;
}
