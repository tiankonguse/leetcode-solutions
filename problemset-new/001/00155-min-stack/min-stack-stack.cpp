class MinStack {
    stack<int> minSta;
    stack<int> valSta;
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        if(minSta.empty()){
            minSta.push(x);
        }else{
            minSta.push(min(x, minSta.top()));
        }
        valSta.push(x);
    }
    
    void pop() {
        minSta.pop();
        valSta.pop();
    }
    
    int top() {
        return valSta.top();
    }
    
    int getMin() {
        return minSta.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
