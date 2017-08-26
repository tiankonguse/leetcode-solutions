/*************************************************************************
  > File Name: 42893.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 13:50 2017/8/23
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

struct Point{
    int x,y,z;
    Point(int x = 0,int y = 0,int z = 0){
        this->x = x;
        this->y = y;
        this->z =z;
    }
    void read(){
        scanf("%d%d%d",&x,&y,&z);
    }
};


struct Line{
    Point x1, x2;
    Line(){
        
    }
    Line(Point& x1, Point&x2){
        this->x1 = x1;
        this->x2 = x2;
    }
    void read(){
        x1.rea();
        x2.rea();
    }
};

int getInc(int from, int to){
    if(from > to){
        return -1;
    }
    if(from < to){
        return 1;
    }
    return 0;
}


int AB(Point& A, Point& B){
    return () && && () && ();
}


bool isInLine(Point& p, Line& l){
    Point a = Point(p.x - l.x1.x, p.y - l.x1.y, p.z - l.x1.z);
    Point b = Point(p.x - l.x2.x, p.y - l.x2.y, p.z - l.x2.z);
    
    if(a.y* b.z == a.z * b.y && a.z*b.x == a.x*b.z && a.x*b.y == a.y*b.x){
        return true;
    } else{
        return 0;
    }
    
}

void findIntPoint(Line& l, vector<Point>& pointList1){
    int incX = getInc(l.x1.x, l.x2.x);
    int incY = getInc(l.x1.y, l.x2.y);
    int incZ = getInc(l.x1.z, l.x2.z);
    
    for(int x = l.x1.x; x <= l.x2.x; x += incX){
        for(int y = l.x1.y; y <= l.x2.y; y += incY){
            for(int z = l.x1.z; z <= l.x2.z; z += incZ){
                Point p(x,y,z);
                if(isInLine(p, l)){
                    pointList1.push_back(p);
                }
            }
        }
    }
    
    
}

int main() {
    int t;
    int n;
    LL val;
    
    scanf("%d", &t);
    while(t--){
        Line l1, l2;
        l1.read();
        l2.read();
        
        vector<Point> pointList1;
        vector<Point> pointList2;
        
        findIntPoint(l1, pointList1);
        findIntPoint(l2, pointList2);
        
        int ans;
        for(int i = 0; i < pointList1.size(); i++){
            for(int j = 0; j < pointList2.size(); j++){
                l = getLen(pointList1[i], pointList2[j]);
            }
        }
        
        
        
        
        
    }
    return 0;
}
