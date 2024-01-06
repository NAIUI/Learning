### 一、IO库

#### 1、管理输出缓冲

```C++
1、在每个输出操作后，可用操作符unitbuf设置流的内部状态，来清空缓冲区。默认对cerr设置，立即刷新。
    
2、一个输出流可能被关联到另一个流。在这种情况下，当读写被关联的流时，关联到的流的缓冲区会被刷新。默认cin和cerr都关联到cout,因此，读cin或写cerr都会导致cout的缓冲区刷新。
    
3、endl:换行并刷新
   ends:插入一个空字符，刷新
   flush:刷新，不添加任何字符
       
4、unitbuf：每次写操作执行一次flush
	cout << unitbuf;
	cout << nounitbuf  // 返回
        
```

#### 2、文件输入输出

```C++
1、创建文件流对象时，可以提供文件名（可选），并且open自动调用:
	ifstream in(ifile);		// 关联到ifile文件
	ofstream out;	// 未关联
	out.open(ifile + ".copy"); 	// 关联
	if (out) 	// 判断open()成功与否,对一个已经关联的流调用open将失败。
     in.close();		// 关闭文件

2、当一个fstream对象被销毁时，close会自动调用。
    
3、保留被ofstream打开的文件中已有的数据唯一方式是显式指定app或in模式。
ofstream app("file", ofstream::app);
ofstream app("file", ofstream::out | ofstream::app);
```

### 二、顺序容器

#### 1、顺序容器概述

```C++
1、deque：双端队列。支持快速随机访问。
2、list：双端链表。
3、forward_list：单向链表。无size操作。
```

#### 2、容器概述

```C++
1、创建一个容器为另一个容器的拷贝时，两容器类型及其元素类型必须匹配。不过若传递迭代器参数拷贝一个范围，不要求，只要能将拷贝元素转换。
```

#### 3、顺序容器操作

```C++
1、emplace函数在容器中直接构造函数。传递给emplace函数的参数必须与元素类型的构造函数相匹配。
    
2、在容器中访问元素的成员函数（front、back、at和下标）返回的都是引用。
    
3、resize：改变容器大小。删除多余元素或者进行初始化新容器空间。
  
```

#### 4、容器适配器

```C++
1、stack、queue、priority_queue：前两基于deque实现，后基于vector实现。
```



### 三、泛型算法

#### 1、back_inserter

```C++
vector<int> vec;
fill_n(back_inserter(vec), 10, 0);
```

#### 2、定制操作

```C++
// sort按长度排序
bool isShorter(const string &s1, const string &s2) return s1.size() < s2.size();
sort(words.begin(), words.end(), isShorter);
```

#### 3、lambda

```C++
1、可调用对象：函数、函数指针、lambda、重载了函数调用运算符的类。

2、[capture list](parameter list) -> return type {function body}

3、如果lambda的函数体包含任何一个单一return语句之外的内容，且未指定返回类型，则返回void。
    
4、捕获列表只用于局部非static变量，lambda可以直接使用局部static变量和在它所在函数之外声明的名字。
```

#### 4、参数绑定

```C++
1、标准库bind函数
auto newCallable = bind(callable, arg_list);

2、使用placeholders名字
using std::placeholders::_1;
using namespace namespace_name; --- using namespace std::placeholders;

3、传递给bind一个对象而又不拷贝它，使用ref函数(返回一个对象，包含给定的引用)。
for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' '));
```

#### 5、迭代器

```C++
1、插入迭代器：back_inserter、front_inserter、inserter。
// it 是由 inserter 生成的迭代器
*it = val;
// 等价于
it = c.insert(it, val);
++it;

2、iostream迭代器：istream_iterator、ostream_iterator
```



### 四、关联容器

#### 1、关联容器概述

```C++
1、为了使用自己定义的操作，在定义multiset时我们必须提供两个类型：关键字类型Sales_data,以及比较操作类型-应该是一种函数指针。当定义此容器类型的对象时，需要提供想要使用的操作的指针。
multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
// 此处，使用decltype来指出自定义操作的类型。当用decltype来获得一个函数指针类型时，必须加上一个*来指出我们要使用一个给出函数类型的指针。
// 用compareIsbn代替&compareIsbn作为构造函数的参数，函数名字可自动转化为指针。

2、pair类型，数据成员是public的（first，second），可以使用普通的成员符号来访问。
make_pair(v1, v2); 	// 返回一个用v1和v2初始化的pair。pair的类型从v1和v2的类型推断出来。
```

#### 2、关联容器操作

```C++
1、额外类型
key_type、mapped_type、value_type(key_type 或 pair<const key_type, mapped_type>)。

2、解引用一个关联容器迭代器时，得到一个类型为容器的value_type的值的引用。
```



### 五、动态内存

#### 1、智能指针

```c++
// shared_ptr：允许多个指针指向同一个对象。
// unique_ptr：“独占”所指的对象。
// weak_ptr：伴随类，弱引用，指向shared_ptr所管理的对象。
```

#### 2、shared_ptr

```C++
1、make_shared<T> (args) : 返回一个shared_ptr，指向一个动态分配的类型为T的对象。使用args初始化对象。
2、shared_ptr<T>p(q) : p是shared_ptr q的拷贝；此操作会递增q中的计数器。q中的指针必须能转换为T*。
3、p = q : p和q都是shared_ptr，所保存的指针必须能相互转换。此操作会递减p的引用计数，递增q的引用计数；若p的引用计数变为0，将其管理的原内存释放。
4、p.unique() : 若p.use_count() 为1，返回true；否则返回false。
5、p.use_count() : 返回与p共享对象的智能指针数量。
```

#### 3、new和delete

```C++
1、new返回一个指向该对象的指针。
int *pi = new int;	// 内置类型，未初始化。
int *pi = new int(1024);

2、delete表达式接受一个指针：销毁给定的指针对象，释放对应的内存。
```

#### 4、shared_ptr 和 new 结合使用

```C++
shared_ptr<int> p2(new int (42));
// 接受指针参数的智能指针构造函数是explicit的，不能将一个内置指针隐式转换为一个智能指针，必须使用直接初始化。
shared_ptr<int> p2 = new int(42); 	// 错误。用int* 隐私转换。因此函数调用、返回值也是。
```

#### 5、unique_ptr

```C++
1、定义unique_ptr时，需要绑定到一个new返回的指针。必须直接初始化。
2、不支持拷贝或者赋值。
3、可以调用release或reset将指针所有权从一个（非const）unique转移给另一个unique。
u.release()	//	u放弃对指针的控制权，返回指针，并将u置为空。
u.reset()	//  释放u指向的对象
u.reset(q)	//	如果提供了内置指针q，令u指向这个对象,否则将u置为空。
    
4、可以拷贝或赋值一个将要被销毁的unique_ptr.
unique_ptr<int> clone(int p){
	return unique_ptr<int>(new int(p));
    
    // unique_ptr<int> ret(new int(p));
    // return ret;
}
```

#### 6、weak_ptr

```C++
1、指向一个shared_ptr管理的对象，不改变引用计数。
    
2、由于对象可能不存在，不能直接访问对象，必须调用lock。
```

#### 7、动态数组

```C++
1、为了用一个unique_ptr管理动态数组，必须在对象类型后面跟一堆空方括号
unique_ptr<int []> up(new int[10]);
2、不能用点和箭头成员运算符，可以用下标。
    
3、shared_ptr管理动态数组，必须提供自己定义的删除器。
```



### 六、拷贝控制

#### 1、拷贝、赋值与销毁

```C++
1、当定义一个类时，我们显示或隐式地指出在此类型的对象拷贝、移动、赋值和销毁时做什么。一个类通过定义五种特殊的成员函数来控制这些操作，包括：拷贝构造函数、拷贝赋值运算符、移动构造函数、移动赋值运算符和析构函数。
```

#### 2、拷贝构造函数

```C++
1、一个构造函数的第一个参数是自身类类型的引用，且任何额外参数都有默认值。
class Foo{
public:
    Foo();			    // 默认构造函数
    Foo(const Foo&);	 // 拷贝构造函数
}

2、拷贝初始化
string dots(10, '');					// 直接初始化
string s(dots);							// 直接初始化
string s2 = dots;						// 拷贝初始化
string null_book = "9-9999-99999-9";	  // 拷贝初始化
string nines = string(100, '9');		  // 拷贝初始化
// 当使用直接初始化时，编译器使用普通的函数匹配来选择与提供的参数最匹配的构造函数。使用拷贝初始化时，编译器将右侧运算对象拷贝到正在创建的对象中，如果需要的话进行类型转换。
// 拷贝初始化通常使用拷贝构造函数完成。
```

#### 3、析构函数

```C++
1、没有返回值，也不接受参数。因此不能被重载。
2、成员按初始化顺序的逆序销毁。
3、成员在析构函数体之后隐含的析构阶段被销毁。在整个对象销毁过程中，析构函数作为成员销毁步骤之外的另一部分进行。
```

#### 4、定义删除的函数

```C++
1、虽然声明了它们，但不能以任何方式使用它们。在函数的参数列表后面加上=delete

2、新标准之前，类通过将其拷贝构造函数和拷贝赋值运算符声明为private来阻止拷贝。
```

#### 5、行为像值的类

```C++
1、赋值运算符通常组合了析构函数和构造函数的操作。类似析构函数，赋值操作会销毁左侧运算对象的资源。类似拷贝构造函数，赋值操作会从右侧运算对象拷贝数据。
HashPtr& HashPtr::operator=(const HashPtr &rhs)
{
    auto newp = new string (*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
}
```

#### 6、行为像指针的类

```C++
class HashPtr{
public:
    // 构造函数分配新的string和新的计数器，将计数器置为1
    HashPtr(const std::string &s = std::string()):
      ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    // 拷贝构造函数拷贝三个数据成员，并递增计数器
    HashPtr(const HashPtr &p):
      ps(p.ps), i(p.i), use(p.use)  { ++*use; }
    HashPtr &operator=(const HashPtr&);
    ~HashPtr();
private:
    std::string *ps;
    int i;
    std::size_t *use;	// 用来记录有多少个对象共享*ps的成员
}
HashPtr::~HashPtr()
{
	if (--*use == 0){	// 如果引用计数变为0
		delete ps;		// 释放string内存
        delete use;		// 释放计数器内存
    }
}
HashPtr& HashPtr::operator=(const HashPtr &rhs)
{
	++*rhs.use;			// 递增右侧运算符对象的引用计数
    if (--*use == 0){
		delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}
```



### 七、重载运算与类型转换

#### 1、基本概念

```C++
// 一个非成员运算符函数的等价调用
data1 + data2;
operator+(data1, data2);

// 显式调用成员运算符函数
data1 += data2;
data1.operator+=(data2);

1、通常情况下，不应重载逗号、取地址、逻辑与和逻辑或运算符
    
2、当我们把运算符定义成成员函数时，它的左侧运算对象必须是运算符所属类的一个对象。
string s = "world";
string t = s + "!";
string u = "hi " + s;	// 如果+是string的成员，错误
```

#### 2、重载输出运算符<<

```C++
1、输出运算符的第一个形参是一个非常量ostream对象的引用；第二个形参是一个常量的引用。
ostream &operator<<(ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

2、与iostream标准库兼容的输入输出运算符必须是普通的非成员函数，而不能是类的成员函数。
```

#### 3、重载输入运算符>>

```C++
1、输入运算符必须处理输入可能失败的情况，而输出运算符不需要。
```

#### 4、算术和关系运算符

```C++
1、如果类同时定义了算术运算符和相关的复合赋值运算符，使用复合赋值来实现算术运算符。
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}
```

#### 5、递增和递减运算符

```C++
1、后置版本接受一个额外的（不被使用）int类型的形参。
2、为了与内置版本保持一致，后置运算符应该返回对象的原值，返回的形式是一个值而非引用。
StrBlobPtr StrBlobPtr::operator++(int)
{
	StrBlobPtr ret = *this;
    ++*this;
    return ret;
}
```

#### 6、函数调用运算符

```C++
1、函数调用运算符必须是成员函数。一个类可以定义多个不同版本的调用运算符，相互之间应该在参数数量或类型上有所区别。
    
// 传入一个临时的函数对象用于执行两个string对象的>比较运算
sort(svec.begin(), svec.end(), greater<string>());

2、标准库规定其函数对象对于指针同样适用
vector<string *> nameTable;
// 错误
sort(nameTable.begin(), nameTable.end(), [](string *a, string *b) {return a<b;});
// 正确
sort(nameTable.begin(), nameTable.end(), less<string*>());
// 关联容器使用less<key_type>对元素排序，因此可定义一个指针的set或map而无需直接声明less。
```



### 八、面向对象程序设计

#### 1、概述

```C++
1、c++11新标准允许派生类显示地注明将使用哪个成员函数改写基类的虚函数，形参列表后加override。
double net_price(std::size_t) const override;

2、使用基类的引用（或指针）调用一个虚函数时将发生动态绑定。
```

#### 2、定义基类和派生类

```C++
1、基类通常应该定义一个虚析构函数。
2、任何构造函数之外的非静态函数都可以是虚函数。
3、派生类不能直接初始化基类继承而来的成员
Bulk_quote(const std::string& book, double p,
           std::size_t qty, double disc) : 
		  Quote(book, p), min_qty(qty), discount(disc) { }

4、派生类声明包含类名但不包含派生列表
    class Bulk_quote : public Quote;	  // 错误
	class Bulk_quote;					// 正确
5、防止继承：final
    class NoDerived final { /* */ };		// NoDerived不能作为基类
```

#### 3、虚函数

```C++
1、动态绑定只有通过指针或引用调用虚函数时才发生。普通类型的表达式调用虚函数在编译时将调用的版本确定下来。
```

#### 4、访问控制与继承

```C++
1、protected：希望与派生类分享但是不想被其他公共访问使用的成员。派生类的成员或友元只能通过派生类对象来访问基类的受保护成员。派生类对于一个基类对象中的受保护成员没有任何访问特权。
class Base{
protected:
    int prot_men;
};
class Sneaky : public Base{
    friend void clobber(Sneaky&);	// 正确
    friend void clobber(Base&);		// 错误
    int j;
}

2、派生类访问说明符的目的是控制派生类用户对于基类成员的访问权限。
Pub_Derv d1;		// 继承自Base的成员是public的
Priv_Derv d2;		// 继承自Base的成员是private的
d1.pub_mem;			// 正确
d2.pub_mem;			// 错误

3、派生类访问说明符还可以控制继承自派生类的新类的访问权限。
struct Derived_from_Private : public Priv_Derv{
	int use_base() {return prot_mem;}	// 错误
}
```



### 九、模板与泛型编程

#### 1、函数模板

```C++
template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

1、模板类型参数可以用来指定返回类型或函数的参数类型
template <typename T> T foo(T* p)
{
	T tmp = *p;
    // ...
    return tmp;
}

2、非类型模板参数的模板实参必须是常量表达式。

3、泛型代码两个重要原则：
    模板中的函数参数是const的引用
    函数体中的条件判断仅使用<比较运算

4、模板编译：编译器遇到模板定义时，不生成代码。实例化才生成。
```

#### 2、类模板

```C++
1、类模板的成员函数
template <typename T>
ret-type Blob<T>::member-name(parm-list)

2、遇到类名才进入类的作用域。
    
3、类模板和友元
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T>
	bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T> class Blob{
    friend class BlobPtr<T>;
    friend bool operator==<T>
        	(const Blob<T>&, const Blob<T>&);
    // ...
};
```

#### 3、模板参数

```C++
1、在模板内不能重用模板参数名。
template <typename A, typename B> void f(A a, B b)
{
    double B;  // 错误：重声明模板参数类型
}

2、默认情况下，C++语言假定通过作用域运算符访问的名字不是类型。显示：使用typename
template <typename T>
typaname T::value_type top(const T& c)
{
	if (!c.empty())
        return c.back();
    else
        return typename T::value_type(); // 生成值初始化的元素
}
```

#### 4、成员模板

```C++
1、一个类可以包含本身是模板的成员函数。成员模板不能是虚函数。
```

#### 5、控制实例化

```C++
1、显示实例化形式：
extern template daclaration;	// 实例化声明
template declaration;		//	实例化定义
// 例如
extern template class Blob<string>;			// 声明
template int compare(const int&, const int&);		// 定义

2、编译器遇到extern模板声明，不会再本文件生成实例化代码。将一个实例化声明未extern其它位置有非extern声明（定义），多个extern声明一个定义。
```

