
// 判断三点是否在一条直线上
bool isLine(vector<int>& p1, vector<int>& p2, vector<int>& p3) {
  int x1 = p1[0], y1 = p1[1];
  int x2 = p2[0], y2 = p2[1];
  int x3 = p3[0], y3 = p3[1];
  return (y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1) == 0;
}


// 求三点形成的三角形的圆心
void getCenter(vector<int>& p1, vector<int>& p2, vector<int>& p3, double& x,
               double& y, double& r) {
  double x1 = p1[0], y1 = p1[1];
  double x2 = p2[0], y2 = p2[1];
  double x3 = p3[0], y3 = p3[1];
  x = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) -
       (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) /
      (2.0 * ((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1)));
  y = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) -
       (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) /
      (2.0 * ((y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1)));
  r = (x1 - x) * (x1 - x + (y1 - y) * (y1 - y));
}