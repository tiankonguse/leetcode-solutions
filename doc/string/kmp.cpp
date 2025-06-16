// next[i] 前缀 [0,j] 的最长公共前后缀的长度
vector<int> next;
void get_next(const char *pat) {
    for(int i=1,k; pat[i]; ++i) {
        for(k=next[i-1]; k>=0 && pat[i]!=pat[k+1]; k=next[k]);
        if(pat[k+1] == pat[i])
            next[i]=k+1;
    }
}
int kmp(const char* str, const char* pat) {
    next.resize(strlen(pat)+1, -1);
    get_next(pat);
    int i=0, j=0;
    while( str[i] && pat[j] ) {
        if( pat[j] == str[i] ) {
            ++i;
            if(!pat[++j]){
                return i-j;
            }
        } else if(j == 0)
            ++i;
        else
            j = next[j-1]+1;
    }
    return -1;
}