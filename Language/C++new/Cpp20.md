# Cpp20新特性

## **语言特性**

### **1、比较运算<=>**

对于 (a <=> b)，如果a > b ，则运算结果>0，如果a < b，则运算结果<0，如果a==b，则运算结果等于0，注意下，运算符的结果类型会根据a和b的类型来决定，所以我们平时使用时候最好直接用auto，方便快捷。

```cpp
#include <compare>
#include <iostream>
 
int main() {
    double foo = 0.0;
    double bar = 1.0;
 
    auto res = foo <=> bar;
 
    if (res < 0)
        std::cout << "foo is less than bar";
    else if (res == 0)
        std::cout << "foo and bar are equal";
    else if (res > 0)
        std::cout << "foo is greater than bar";
}
```

输出：

```cpp
foo is less than bar
```

### 2、**指定初始化** ：

```cpp
struct A { int x; int y; int z; };
A a{.y = 2, .x = 1}; // error; designator order does not match declaration order
A b{.x = 1, .z = 2};
```

这种乱序初始化方式在C语言中可以，但是在C++中是不可以的，C++里一定要按顺序初始化。

### 3、**for循环括号里可以初始化** ：

```cpp
#include <iostream>
#include <vector>
 
int main() {
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
 
    for (const int& i : v) // access by const reference
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (auto i : v) // access by value, the type of i is int
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (auto n = v.size(); auto i : v) // the init-statement (C++20)
        std::cout << --n + i << ' ';
    std::cout << '\n';
}
```

**多了一个char8_t**类型，和普通的char没区别，就是容易区分出具体大小而已，就像int32_t与int一样。

### 4、 **[[no_unique_address]]**

 **[[likely]]和[[unlikely]]** ：在分支预测时，用于告诉编译器哪个分支更容易被执行，哪个不容易执行，方便编译器做优化。

```cpp
constexpr long long fact(long long n) noexcept {
    if (n > 1) [[likely]]
        return n * fact(n - 1);
    else [[unlikely]]
        return 1;
}
 
```

### **5、lambda表达式的捕获**

C++20之前[=]会隐式捕获this，而C++20需要显式捕获，这样[=, this]

```cpp
struct S2 { void f(int i); };
void S2::f(int i)
{
    [=]{};          // OK: by-copy capture default
    [=, &i]{};      // OK: by-copy capture, except i is captured by reference
    [=, *this]{};   // until C++17: Error: invalid syntax
                    // since c++17: OK: captures the enclosing S2 by copy
    [=, this] {};   // until C++20: Error: this when = is the default
                    // since C++20: OK, same as [=]
}
```

**lambda表达式可以使用模板：**

```cpp
// generic lambda, operator() is a template with two parameters
auto glambda = []<class T>(T a, auto&& b) { return a < b; };
 
// generic lambda, operator() is a template with one parameter pack
auto f = []<typename ...Ts>(Ts&& ...ts) {
   return foo(std::forward<Ts>(ts)...);
};
```

### **6、consteval**

consteval修饰的函数只会在编译期间执行，如果不能编译期间执行，则编译失败。

```cpp
consteval int f() { return 42; }
```

### **7、constinit**

断言一个变量有静态初始化，即零初始化和常量初始化，否则程序是有问题的。

```cpp
const char *g() { return "dynamic initialization"; }
constexpr const char *f(bool p) { return p ? "constant initializer" : g(); }
 
constinit const char *c = f(true); // OK
// constinit const char *d = f(false); // error
```

### **8、删除了在很多上下文中需要使用typename来消除类型歧义的要求**

```cpp
template<typename IterT>
void workWithIterator(IterT it){
    typename std::iterator_traits<IterT>::value_type tmp(*it); // C++20前
    std::iterator_traits<IterT>::value_type tmp(*it); // C++20
}
```

### **9、结构体直接初始化：**

```cpp
T object {arg1, arg2, ... }; // C++11
T object { .designator = arg1 , .designator { arg2 } ... }; // C++20
```

### **10、协程**

协程具体是什么不做过多介绍，它最大的特点就是可以使用顺序代码的逻辑执行异步的任务，让我们写异步代码非常的方便。

如果一个函数的定义有以下任何一种情况，那么它就是协程：

1. 使用co_await操作符暂停执行，直到恢复

```cpp
task<> tcp_echo_server() {
  char data[1024];
  for (;;) {
    size_t n = co_await socket.async_read_some(buffer(data));
    co_await async_write(socket, buffer(data, n));
  }
}
```

2. 使用关键字co_yield暂停执行，返回一个值

```cpp
generator<int> iota(int n = 0) {
  while(true)
    co_yield n++;
}
```

3. 使用关键字co_return完成执行，返回一个值

```cpp
lazy<int> f() {
  co_return 7;
}
```

每个协程都必须有一个返回类型来满足以下的许多要求。

示例代码：

```cpp
#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>
 
auto switch_to_new_thread(std::jthread& out) {
  struct awaitable {
    std::jthread* p_out;
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<> h) {
      std::jthread& out = *p_out;
      if (out.joinable())
        throw std::runtime_error("Output jthread parameter not empty");
      out = std::jthread([h] { h.resume(); });
      // Potential undefined behavior: accessing potentially destroyed *this
      // std::cout << "New thread ID: " << p_out->get_id() << '\n';
      std::cout << "New thread ID: " << out.get_id() << '\n'; // this is OK
    }
    void await_resume() {}
  };
  return awaitable{&out};
}
 
struct task{
  struct promise_type {
    task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};
 
task resuming_on_new_thread(std::jthread& out) {
  std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << '\n';
  co_await switch_to_new_thread(out);
  // awaiter destroyed here
  std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
}
 
int main() {
  std::jthread out;
  resuming_on_new_thread(out);
}
```

限制：

协程不能使用可变参数、普通返回语句或占位符返回类型(auto或Concept)。Constexpr函数、构造函数、析构函数和主函数不能是协程。


### 11、**Modules** 

```cpp
// helloworld.cpp
export module helloworld;  // module declaration
import <iostream>;         // import declaration
 
export void hello() {      // export declaration
    std::cout << "Hello world!\n";
}
```

```cpp
// main.cpp
import helloworld;  // import declaration
 
int main() {
    hello();
}
```

### **12、using 可以引用enum**

```cpp
enum class Animal {
  kCat,
  kGog  
};
int main() {
    Animal animal;
    using enum Animal;
    switch(animal) {
        case kCat:
            break;
    }
}
```

### **14、Constraints and concepts**约束和概念

类模板、函数模板和非模板函数(通常是类模板的成员)可以与一个约束相关联，这个约束指定了对模板实参的要求，这些实参可用于选择最合适的函数重载和模板特化。

这些需求的命名被称为概念。每个概念都是一个谓词，在编译时计算，并成为模板接口的一部分，在那里它被用作约束：

```cpp
#include <string>
#include <cstddef>
#include <concepts>

template<typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};
 
struct meow {};
 
// Constrained C++20 function template:
template<Hashable T>
void f(T) {}

int main() {
  using std::operator""s;
  f("abc"s); // OK, std::string satisfies Hashable
  //f(meow{}); // Error: meow does not satisfy Hashable
}
```

缩写函数模板

```cpp
void f1(auto); // same as template<class T> void f(T)
void f2(C1 auto); // same as template<C1 T> void f2(T), if C1 is a concept
void f3(C2 auto...); // same as template<C2... Ts> void f3(Ts...), if C2 is a concept
void f4(const C3 auto*, C4 auto&); // same as template<C3 T, C4 U> void f4(const T*, U&);
template <class T, C U>
void g(T x, U y, C auto z); // same as template<class T, C U, C W> void g(T x, U y, W z);
```


## **新的library特性**

### **1、std::format系列**

std::format可用于替代printf，它的目的是补充现有的c++ I/O流库，并重用它的一些基础设施，如用户定义类型的重载插入操作符。

```cpp
std::string message = std::format("The answer is {}.", 42);
```

### **2、增加日历和时区的支持**

### 3、增加了 **std::atomic** ：让智能指针线程安全

### 4、**source_location** 

可作为__LINE__ 、__func__这些宏的替代：

```cpp
#include <iostream>
#include <string_view>
#include <source_location>
 
void log(const std::string_view message,
         const std::source_location& location = std::source_location::current())
{
    std::cout << "info: "
              << location.file_name() << "("
              << location.line() << ":"
              << location.column() << ") `"
              << location.function_name() << "` "
              << message << '\n';
}
 
int main(int, char*[])
{
    log("Hello world!");
}
```

###  5、**span**

 类模板span可以表示一个片段。

```cpp
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <span>
 
template<class T, std::size_t N> [[nodiscard]]
constexpr auto slide(std::span<T,N> s, std::size_t offset, std::size_t width) {
    return s.subspan(offset, offset + width <= s.size() ? width : 0U);
}
 
template<class T, std::size_t N, std::size_t M> [[nodiscard]]
constexpr bool starts_with(std::span<T,N> data, std::span<T,M> prefix) {
    return data.size() >= prefix.size() 
        && std::equal(prefix.begin(), prefix.end(), data.begin());
}
 
template<class T, std::size_t N, std::size_t M> [[nodiscard]]
constexpr bool ends_with(std::span<T,N> data, std::span<T,M> suffix) {
    return data.size() >= suffix.size() 
        && std::equal(data.end() - suffix.size(), data.end(), 
                      suffix.end() - suffix.size());
}
 
template<class T, std::size_t N, std::size_t M> [[nodiscard]]
constexpr bool contains(std::span<T,N> span, std::span<T,M> sub) {
    return std::search(span.begin(), span.end(), sub.begin(), sub.end())
        != span.end();
}
 
void print(const auto& seq) {
    for (const auto& elem : seq) std::cout << elem << ' ';
    std::cout << '\n';
}
 
int main()
{
    constexpr int a[] { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    constexpr int b[] { 8, 7, 6 };
 
    for (std::size_t offset{}; ; ++offset) {
        constexpr std::size_t width{6};
        auto s = slide(std::span{a}, offset, width);
        if (s.empty())
            break;
        print(s);
    }
 
    static_assert(starts_with(std::span{a}, std::span{a,4})
        && starts_with(std::span{a+1, 4}, std::span{a+1,3})
        && !starts_with(std::span{a}, std::span{b})
        && !starts_with(std::span{a,8}, std::span{a+1,3})
        && ends_with(std::span{a}, std::span{a+6,3})
        && !ends_with(std::span{a}, std::span{a+6,2})
        && contains(std::span{a}, std::span{a+1,4})
        && !contains(std::span{a,8}, std::span{a,9}));
}
```

### 6、 **endian**

可获取当前平台是大端序还是小端序

```cpp
#include <bit>
#include <iostream>
 
int main() {
 
    if constexpr (std::endian::native == std::endian::big) {
        std::cout << "big-endian" << '\n';
    }
    else if constexpr (std::endian::native == std::endian::little) {
        std::cout << "little-endian"  << '\n';
    }
    else {
        std::cout << "mixed-endian"  << '\n';
    }
 
}
```

### 7、make_shared 支持构造数组

### **8、std::remove_cvref**

去除CV，去除引用

```cpp
#include <iostream>
#include <type_traits>
 
int main()
{
    std::cout << std::boolalpha
              << std::is_same_v<std::remove_cvref_t<int>, int> << '\n'
              << std::is_same_v<std::remove_cvref_t<int&>, int> << '\n'
              << std::is_same_v<std::remove_cvref_t<int&&>, int> << '\n'
              << std::is_same_v<std::remove_cvref_t<const int&>, int> << '\n'
              << std::is_same_v<std::remove_cvref_t<const int[2]>, int[2]> << '\n'
              << std::is_same_v<std::remove_cvref_t<const int(&)[2]>, int[2]> << '\n'
              << std::is_same_v<std::remove_cvref_t<int(int)>, int(int)> << '\n';
}
结果全是true
```

 **std::to_address** ：获得由p表示的地址，而不形成对p所指向的对象的引用。

 **线程同步** ：

* barrier：屏障
* latch：CountDownLatch
* counting_semaphore：信号量

 **std::jthread** ：之前的std::thread在析构时如果没有join或者detach会crash，而jthread在析构时会自动join。jthread也可以取消线程：request_stop()。

C++20也引进了一些中断线程执行的相关类：

* stop_token：查询线程是否中断
* stop_source：请求线程停止运行
* stop_callback：stop_token执行时，可以触发的[回调函数](https://www.zhihu.com/search?q=%E5%9B%9E%E8%B0%83%E5%87%BD%E6%95%B0&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra=%7B%22sourceType%22%3A%22answer%22%2C%22sourceId%22%3A1813428455%7D)

 **basic_osyncstream** ：它是对std::basic_syncbuf的再包装，直接使用std::cout多线程下可能出现数据交叉，osyncstream不会发生这种情况。

```cpp
{
    std::osyncstream synced_out(std::cout); // synchronized wrapper for std::cout
    synced_out << "Hello, ";
    synced_out << "World!";
    synced_out << std::endl; // flush is noted, but not yet performed
    synced_out << "and more!\n";
} // characters are transferred and std::cout is flushed
```

**string的系列操作**

* string::starts_with
* string::ends_with
* string_view::starts_with
* string::view::ends_with

```cpp
#include <iostream>
#include <string_view>
#include <string>
 
template <typename PrefixType>
void test_prefix_print(const std::string& str, PrefixType prefix)
{
    std::cout << '\'' << str << "' starts with '" << prefix << "': " <<
        str.starts_with(prefix) << '\n';
}
 
int main()
{
    std::boolalpha(std::cout);  
    auto helloWorld = std::string("hello world");
 
    test_prefix_print(helloWorld, std::string_view("hello"));
 
    test_prefix_print(helloWorld, std::string_view("goodbye"));
 
    test_prefix_print(helloWorld, 'h');
 
    test_prefix_print(helloWorld, 'x');
}
```

**std::assume_aligned**

```cpp
template< std::size_t N, class T >
[[nodiscard]] constexpr T* assume_aligned(T* ptr);
```

指定多少字节对齐，来进一步生成有效的代码。

```cpp
void f(int* p) {
   int* p1 = std::assume_aligned<256>(p);
   // Use p1, not p, to ensure benefit from the alignment assumption.
   // However, the program has undefined behavior if p is not aligned
   // regardless of whether p1 is used.
}
```

 **bind_front** ：和使用std::bind绑定第一个参数效果类似，可以绑定前x个参数

 **std::ssize** ：signed size

```cpp
#include <iostream>
#include <vector>
#include <iterator>
 
int main() 
{
    std::vector<int> v = { 3, 1, 4 };
    std::cout << std::size(v) << '\n'; 
 
    int a[] = { -5, 10, 15 };
    std::cout << std::size(a) << '\n';
 
    // since C++20 the signed size (ssize) can avail
    auto i = std::ssize(v);
    for (--i; i != -1; --i) {
        std::cout << v[i] << ' ';
    }
    std::cout << "\n" "i = " << i << '\n';
}
```

**midpoint **函数计算中位数

**[lerp函数](https://www.zhihu.com/search?q=lerp%E5%87%BD%E6%95%B0&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra=%7B%22sourceType%22%3A%22answer%22%2C%22sourceId%22%3A1813428455%7D)**计算线性差值：

```cpp
constexpr double lerp( double a, double b, double t) noexcept {
    return a + t * (b - a);
}
```

 **Ranges库：** ranges库提供了用于处理元素范围的组件，包括各种视图适配器。表示连续元素或者连续元素的片段。

```cpp
#include <ranges>
#include <iostream>
 
int main()
{
    auto const ints = {0,1,2,3,4,5};
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };
 
    // "pipe" syntax of composing the views:
    for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
        std::cout << i << ' ';
    }
 
    std::cout << '\n';
 
    // a traditional "functional" composing syntax:
    for (int i : std::views::transform(std::views::filter(ints, even), square)) {
        std::cout << i << ' ';
    }
}
输出：
0 4 16
0 4 16
```

 **std::is_bounded_array** ：检查数组是不是有界

std::is_unbounded_array

```cpp
#include <iostream>
#include <type_traits>
 
class A {};
 
int main() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_bounded_array_v<A> << '\n';
    std::cout << std::is_bounded_array_v<A[]> << '\n';
    std::cout << std::is_bounded_array_v<A[3]> << '\n';
    std::cout << std::is_bounded_array_v<float> << '\n';
    std::cout << std::is_bounded_array_v<int> << '\n';
    std::cout << std::is_bounded_array_v<int[]> << '\n';
    std::cout << std::is_bounded_array_v<int[3]> << '\n';
}
```

在numbers头文件中定义了一些 **数学常量** ：

* e
* log2e
* log10e
* pi
* inv_pi
* inv_sqrtpi
* ln2
* ln10
* sqrt2
* sqrt3
* inv_sqrt3
* egamma
* phi
