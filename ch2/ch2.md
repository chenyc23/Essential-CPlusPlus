# 2.函数相关

# 函数

## 内存相关

---

当调用一个函数时，会再内存中建立起一块特殊区域，被称为“程序堆栈”。这块特殊的区域提供了每个函数参数的存储空间。它也提供了函数所定义的每个对象的内存空间。（局部对象）一旦函数完成，这块内存就会被释放掉。或者说是从程序堆栈中pop出来。

对象如果再函数之外声明，则具有file scope。对象如果拥有file scope。（全局对象）从声明点到文件末尾都是可见的。拥有file scope的对象也具有所谓的static extent，即该对象的内存在main()开始执行之前就已经分配好了，可以一直存在至程序结束。

**动态内存管理:** 动态内存的部分，不是由系统自动管理的。由程序的空闲空间(free store)分配而来，有时也称为heap memory(堆内存)。这种内存必须由程序员自行管理，分配通过new，释放通过delete来完成。

c++不存在从heap分配数组的同时为其元素设定初值。

## 函数参数

---

**指针参数**和**引用参数**的重要差异：

- 指针可能（也可能不）指向某个实际对象，解地址操作之前**一定**要判断指针非空。
- 引用，则必定会代表某个对象，所以不需要检查

函数的**默认值**

- 默认值的解析操作是从最右边开始的，也就是默认值参数的右边必须也是默认值参数
- 默认值只能被指定一次，可以在函数声明处，也可以在函数定义处。但不能在两个地方都指定。visiblity更好的做法就是在函数**声明处**指定默认值。

函数内定义**局部静态变量**，在函数内部定义，函数退出后，内存并不会被释放。下一次调用函数的时候，这个定义的局部静态变量还是存在的，里面的值就是上一次调用的值。

## 函数模板

---

function template以关键词`template`开始，其后紧接着成对的尖括号（<>）包围起来的一个或多个标识符。这些标识符用以表示我们希望推迟决定的数据类型。用户每次利用这一模板，都**必须**提供确实的类型信息

```cpp
template <typename elemType>
void display_message(const string &msg, const vector<elemType> &vec){
    cout << msg;
    for(int ix=0; ix<vec.size(); ++ix){
        elemType t = vec[ix];
        cout << t << " ";
    }
}
```

运行过程是绑定，如果输入的是vector<int>的参数，那么elemType和int就会绑定。就会生成一份把elemType替换为int的代码，进行运行。再来vector<string>类型的话，就会再生成一份新的代码。

函数模板同样也可以进行函数重载

## 函数重载

---

参数列表（parameter list）不同的两个或多个函数可以拥有相同的函数名称。

返回类型是不能用来区分两个相同名称的函数。因为参数列表相同的时候，编译器无法判断调用哪个函数。所以返回类型不同是没用的

```cpp
void display_message(char);
void display_message(const string&);
void display_message(const string&, int);
void display_message(const string&, int, int);
```

## 函数指针

---

所谓函数指针，其形式相当复杂。它必须指明其所指函数的返回类型及参数列表。如果想要指向的函数参数列表的内容是`int`，返回类型是`const vector<int>*`

```cpp
const vector<int>* *seq_ptr(int); //这是错的，这还是一个函数，返回类型是**指针的指针

const vector<int>* (*seq_ptr)(int); //这是对的，用括号改变优先级，这就是一个函数指针了
```

由函数指针指向的函数，其调用方式和一般的函数相同，也就是说

```cpp
const vector<int> *pseq = seq_ptr(pos);
```

这样会间接调用seq_ptr所指向的函数。更保险一点的做法是进行一次检验。判断指针是否为空

```cpp
// 保险的做法
if(seq_ptr){
	const vector<int> *pseq = seq_ptr(pos);
}
```

函数名称就是函数的地址。同样还可以定义函数指针的数组。

```cpp
//seq_array是个数组，里面放了函数指针
const vector<int>* (*seq_array[])(int) = {
	fibo_seq,   lucas_seq,  pell_seq
	triang_seq, square_seq, pent_seq
}

//调用的时候
int seq_index = 0;
while(next_seq == true){
	seq_ptr = seq_array[seq_index++]
}
```

枚举类型进行辅助记忆

```cpp
enum ns_type{
	ns_fibon, ns_lucas,  ns_pell,
	ns_trian, ns_square, ns_pent
};
//之后取用函数指针的时候就能更直观了
seq_ptr = seq_array[ ns_pell ];
```

## 设定头文件
---
举个例子，如果再numseq.h文件中，想要声明刚才定义的函数指针的数组。如果像下面这样写的话

```cpp
const int seq_cnt = 6;
// 会被编译器认为是定义
const vector<int>* (*seq_array)[seq_cnt](int)//错误，这并不会被认为是声明。

extern const vector<int>* (*seq_array)[seq_cnt](int) //正确，这是一个声明
```

一般来说，定义只有一份。但有两个例外

- inline函数，为了能够扩展inline函数的内容，在每个调用点上，编译器都要取得其定义。所以必须将inline函数的定义放在头文件中。
- 上面代码例子中的seq_cnt，它是一个const object。const object的定义只要一出文件之外便不可见。这意味着可以在多个代码文件中定义，不会导致任何错误。

头文件分成尖括号和双引号

1. 尖括号
    - 标准或者项目专属头文件，编译器搜索的时候，会在某些默认的磁盘目录中寻找
    - 如果在不同的磁盘目录，用尖括号
2. 双引号
    - 被认为是用户提供的头文件，搜索文件时，会由要包含此文件所在的磁盘目录开始寻找
    - 如果在同一磁盘目录，用双引号