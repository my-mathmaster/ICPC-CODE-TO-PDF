-g
-Wall -Wextra
-Wshadow #防止局部变量不小心遮盖其他变量
-Wformat=2 #防止printf/scanf 写错
-Wconversion #防止意外的类型转换
-Wstack-usage=1 #看栈空间使用情况
-fsanitize=undefined #查找未定义行为
-fsanitize=address #查数组越界
-D_GLIBCXX_DEBUG : STL debug mode
-Wl,--stack=1073741824
-fsanitize=undefined fsanitize-undefined-trap-on-error
# Windows
#define deb(x) (void)(cerr << "L" << __LINE__ << ": "<< #x << " = " << (x) << endl)
建议直接使用GDB 的命令行，-g,建议禁用优化。GDB 的常用命令有：
> b (breakpoint) 行号/函数名
> r (run) [< 输入文件名]
> n (next)
> s (step)
> c (continue)
> p (print) 表达式
> d (disp) 表达式
> cond (condition) 断点编号表达式
> bt (backtrace)
> fr (frame) 栈帧编号
> gcov/-ftest-coverage -fprofile-arcs:代码覆盖率检测
可以看代码中每一行被执行的次数
> gprof/-pg:代码剖析,可以看函数执行时间占总时间的百分
比
> gprof 输出的是时间，但只能精确到函数
> gcov 精确到行，但只能输出调用次数