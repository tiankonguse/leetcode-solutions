/*************************************************************************
  > File Name: 4sum.cpp
  > Author: tiankonguse(skyyuan)
  > Mail: i@tiankonguse.com 
  > Created Time: 2015年06月 9日 12:58:23
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
class Solution {
    map<int,int>valTimes;//<val, times>
    vector<int>valList;
    typedef pair<int, int> PairInt;
    typedef vector<PairInt>VecTwoNum;
    typedef map<int, VecTwoNum> MapSumToVal;

    MapSumToVal twoSumMap;
    MapSumToVal targetMap;

    struct Dot{
        int a,b,c,d;
        Dot(int a,int b, int c, int d):a(a),b(b),c(c),d(d){
        }

        Dot():a(0),b(0),c(0),d(0){}

        bool operator==(const Dot&t2)const{
            return a==t2.a && b==t2.b && c==t2.c && d==t2.d;
        }
        
        vector<int> toVec(){
            vector<int> tmp;
            tmp.push_back(a);
            tmp.push_back(b);
            tmp.push_back(c);
            tmp.push_back(d);
            return tmp;
        }

        bool operator<(const Dot &t2)const {
            if(a != t2.a){
                return a < t2.a;
            }
            if(b != t2.b){
                return b < t2.b;
            }
            if(c != t2.c){
                return c < t2.c;
            }
            if(d != t2.d){
                return d < t2.d;
            }
            return d < t2.d;
        }
    };
    vector<vector<int> >ans;
    vector<Dot>realAns;
    int target;


    void init(vector<int>& nums){
        valTimes.clear();
        valList.clear();
        twoSumMap.clear();
        targetMap.clear();
        ans.clear();
        realAns.clear();


        for(int i=0;i<nums.size();i++){
            if(valTimes.find(nums[i]) == valTimes.end()){
                valTimes[nums[i]] = 1;
                valList.push_back(nums[i]);
            }else{
                valTimes[nums[i]]++;
            }
        }
        sort(valList.begin(), valList.end());

        int first, second, sum, firstNum;
        for(int i=0;i<valList.size();i++){
            first = valList[i];
            firstNum = valTimes[first];
            for(int j=i;j<valList.size();j++){
                second = valList[j];
                if(first == second && firstNum == 1){
                    continue;
                }
                sum = first + second;
                twoSumMap[sum];
                twoSumMap[sum].push_back(make_pair(first, second));

                sum = target - sum;
                targetMap[sum];
                targetMap[sum].push_back(make_pair(first, second));
            }
        }
    }

    void addAns(int a, int b, int c, int d){
        realAns.push_back(Dot(a,b,c,d));
    }
    void addAns(PairInt& first, PairInt& second){
        int a,b,c,d;
        a = first.first;
        b = first.second;
        c = second.first;
        d = second.second;
        if(a > b){
            swap(a, b);
        }
        if(c > d){
            swap(c, d);
        }
        if(a > c){
            swap(a,c);
        }
        if(b > d){
            swap(b, d);
        }
        if(b > c){
            swap(b, c);
        }
        // now a<=b<=c<=d
        
        int aNum, bNum, cNum, dNum;
        aNum = valTimes[a];
        bNum = valTimes[b];
        cNum = valTimes[c];
        dNum = valTimes[d];

        if(a == b){
            if(b == c){
                if(c == d){
                    if(aNum >= 4){
                        addAns(a,b,c,d);
                    }
                }else{
                    if(aNum >= 3){
                        addAns(a,b,c,d);
                    } 
                }
            }else{
                if(c == d){
                    if(aNum >=2 && cNum >= 2){
                        addAns(a,b,c,d);
                    }
                }else{
                    if(aNum >= 2){
                        addAns(a,b,c,d);
                    }
                }
            }
        }else{
            if(b == c){
                if(c == d){
                    if(bNum >= 3){
                        addAns(a,b,c,d);
                    }   
                }else{
                    if(bNum >= 2){
                        addAns(a,b,c,d);
                    }
                }
            }else{
                if(c == d){
                    if(cNum >= 2){
                        addAns(a,b,c,d);
                    } 
                }else{
                    addAns(a,b,c,d);
                }
            }
        }
    }

    void addAns(VecTwoNum& firstTwoNum, VecTwoNum& secondTwoNum){
        for(int i=0;i<firstTwoNum.size(); i++){
            for(int j=0; j<secondTwoNum.size(); j++){
                addAns(firstTwoNum[i], secondTwoNum[j]);
            }
        }
    }

public:
    vector<vector<int> > fourSum(vector<int>& nums, int target) {
        this->target = target;
        init(nums);

        for(MapSumToVal::iterator i = twoSumMap.begin(); i != twoSumMap.end(); i++){
            MapSumToVal::iterator j = targetMap.find(i->first);
            if(j == targetMap.end()){
                continue;
            }
            addAns(i->second, j->second);
        }

        sort(realAns.begin(), realAns.end());
        realAns.erase(unique(realAns.begin(), realAns.end()), realAns.end());
        
        for(int i=0;i<realAns.size();i++){
            ans.push_back(realAns[i].toVec());
        }
        
        return ans;
    }
};

void output(char const* name, vector<int>&data){
    printf("%s:", name);
    for(int i=0;i<data.size();i++){
        printf("%d ", data[i]);
    }
    printf("\n");
}

void output(char const* name, vector<vector<int> >&data){
    printf("%s: %d\n", name, data.size());
    for(int i=0;i<data.size();i++){
        output("    ", data[i]);
    }
    printf("\n");
}

void test(vector<int>&data, int target){
    Solution work;
    vector<vector<int> >ans;
    ans = work.fourSum(data, target);
    
    output("data", data);
    output("ans", ans);
}

int main() {
    Solution work;
    vector<int>data;
    int target;


    data = {-1, -2, 3, 1};
    target = 1;
    test(data, target);

    data = {1,0,-1,0,-2,2};
    target = 0;
    test(data, target);


    data = {91277418,66271374,38763793,4092006,11415077,60468277,1122637,72398035,-62267800,22082642,60359529,-16540633,92671879,-64462734,-55855043,-40899846,88007957,-57387813,-49552230,-96789394,18318594,-3246760,-44346548,-21370279,42493875,25185969,83216261,-70078020,-53687927,-76072023,-65863359,-61708176,-29175835,85675811,-80575807,-92211746,44755622,-23368379,23619674,-749263,-40707953,-68966953,72694581,-52328726,-78618474,40958224,-2921736,-55902268,-74278762,63342010,29076029,58781716,56045007,-67966567,-79405127,-45778231,-47167435,1586413,-58822903,-51277270,87348634,-86955956,-47418266,74884315,-36952674,-29067969,-98812826,-44893101,-22516153,-34522513,34091871,-79583480,47562301,6154068,87601405,-48859327,-2183204,17736781,31189878,-23814871,-35880166,39204002,93248899,-42067196,-49473145,-75235452,-61923200,64824322,-88505198,20903451,-80926102,56089387,-58094433,37743524,-71480010,-14975982,19473982,47085913,-90793462,-33520678,70775566,-76347995,-16091435,94700640,17183454,85735982,90399615,-86251609,-68167910,-95327478,90586275,-99524469,16999817,27815883,-88279865,53092631,75125438,44270568,-23129316,-846252,-59608044,90938699,80923976,3534451,6218186,41256179,-9165388,-11897463,92423776,-38991231,-6082654,92275443,74040861,77457712,-80549965,-42515693,69918944,-95198414,15677446,-52451179,-50111167,-23732840,39520751,-90474508,-27860023,65164540,26582346,-20183515,99018741,-2826130,-28461563,-24759460,-83828963,-1739800,71207113,26434787,52931083,-33111208,38314304,-29429107,-5567826,-5149750,9582750,85289753,75490866,-93202942,-85974081,7365682,-42953023,21825824,68329208,-87994788,3460985,18744871,-49724457,-12982362,-47800372,39958829,-95981751,-71017359,-18397211,27941418,-34699076,74174334,96928957,44328607,49293516,-39034828,5945763,-47046163,10986423,63478877,30677010,-21202664,-86235407,3164123,8956697,-9003909,-18929014,-73824245};
    target = -236727523;
    test(data, target);

    return 0;
}
