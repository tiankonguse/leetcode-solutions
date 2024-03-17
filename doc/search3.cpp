// 接下来需要进行三分
ll l = 1, r = n;
while (l < r) {     //[l, r];
  if (l + 3 > r) {  // 小于3，不够三分
    ll ansL = CalAns(l);
    ll ansR = CalAns(r);
    if (ansL < ansR) {
      r--;
    } else {
      l++;
    }
  } else {
    ll midl = l + (r - l) / 3;
    ll midr = r - (r - l) / 3;
    ll ansMidL = CalAns(i, k, midl);
    ll ansMidR = CalAns(i, k, midr);
    if (ansMidL > ansMidR) {  // 左边大
      l = midl;
    } else {
      r = midr;
    }
  }
}