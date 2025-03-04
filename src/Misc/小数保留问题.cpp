#include <iostream>
 
using namespace std;
要得到四舍五入小数点后的结果，我们可以将小数转换为整数来处理，然后再转换为小数。
// 用于四舍五入
int round_0 (double n)
{
  // 若为负数，则先化为正数再进行四舍五入
  if (n > 0)
    return n - int(n) >= 0.5 ? int(n)+1 : int(n);
  else
    return -n - int(-n) >= 0.5 ? -(int(-n) + 1) : -int(-n);
}
 
int main()
{
  double a = 1.2345;
  double b = 1.2355;
  double n_a = -1.2345;
  double n_b = -1.2355;
 
  a = round_0(a * 100.0) / 100.0;
  b = round_0(b * 100.0) / 100.0;
  n_a = round_0(n_a * 100.0) / 100.0;
  n_b = round_0(n_b * 100.0) / 100.0;
 
  cout << a << endl;  // 1.23
  cout << b << endl;  // 1.24
  cout << n_a << endl;  //-1.23
  cout << n_b << endl;  // -1.24
  return 0;
}