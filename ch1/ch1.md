# 1.基础和文件读写

## 运算符

> .（dot成员运算符）
> 

如果不是通过指针找成员，通过实例找的话，就用这个符号

> ->(arrow成员运算符)
> 

如果是通过指针找成员，就用arrow成员运算符

## 指针

> 通常指针具有以下的形式
type_of_object_pointed_to * name_of_pointer_object
> 

左边是指向的类型，中间一个星号，右边是指针的名字。指针可以指向STL标准库里的东西

`vector<int> *pv = 0` 

- 取vector第0个元素`(*pv)[0]`

> 创建指针数组
> 

```cpp
vector<int> *seq_addrs[ seq_cnt ] = {
	&fibonacci,  &lucas,  &pell
	&triangular, &square, &pentagonal
};
```

seq_addr是一个array, 其元素类型是`vector<int>*` 。 seq_addrs[0] 的值是Fibonacci这个vector的地址。seq_addrs[1] 的值是lucas这个vector的地址。

## 文件的读写

### 写文件

> ofstream（供输出用的file stream）
> 

```cpp
#include<fstream>

// 如果指定的文件不存在，便会有一个文件被产生，并打开供输出使用。
ofstream outfile("seq_data.txt");
```

> 默认模式打开ofstream
> 

如果文件存在，就会被打开用于输出。而文件中原来的数据会被丢弃

> 追加模式打开ofstream（append mode）
> 

`ios_base::app` ,进行写入之前，**一定要判断文件**是否正常打开。

```cpp
#include<fstream>
// 如果指定的文件不存在，便会有一个文件被产生，并打开供输出使用。
ofstream outfile("seq_data.txt", ios_base::app);

//进行写入之前，一定要判断文件是否正常打开
if(!outfile)
		cerr << "unable to save session data!\n"
else{
		outfile << usr_name  << ' '
					  << num_tries << ' '
						<< num_right << endl;
}
```

> 操作符（manipulator）
> 

事先定义好的操纵符，`endl`, `hex`, `oct`, `seprecision(n)` 操作符并不会将数据写到iostream，也不会从中读取数据，作用是在iostream上执行某些操作。

- endl操作符，会插入一个换行符，并清除输出缓冲区

### 读文件

> ifstream（供输入的file stream）
> 

```cpp
#include<fstream>

// 如果指定的文件不存在，便会有一个文件被产生，并打开供输出使用。
ifstream infile("seq_data.txt");
```

> 默认模式读取文件
> 

如果文件读取成功，则文件的写入位置被设定在起始处。没有成功就会返回false

```cpp
#include<fstream>

// 如果指定的文件不存在，便会有一个文件被产生，并打开供输出使用。
ifstream infile("seq_data.txt");
int num_tris = 0;
int num_cor = 0;

if(!infile){
	//文件打开失败
}
else{
		string name;
		int nt; //number_tris
		int nc; //number_correct
		
		while(infile >> name){
				infile >> nt >> nc // 先读string,再读数字
				if(name == usr_name){
					// 找到目标人物
					cout << "Welcome back," << usr_name  
							 << "your current score is" << nc
							 << " out of" << nt <<"\nGood Luck!\n";
					num_tris = nt;
					num_cor = nc;
				}
		}
}
```

### 读写同时

```cpp
#include<fstream>

// 如果指定的文件不存在，便会有一个文件被产生，并打开供输出使用。
fstream iofile("seq_data.txt",ios_base::in|ios_base::app);

if(!iofile)
	//文件打开失败
else{
	//将文件重新定位至起始处
	iofile.seekg(0);
}
```

> `iofile.seekg(0)` 会将文件重新定位到起始处
> 

但是写文件的时候，有没有这一行都是从文件末尾开始写的。（因为有ios_base::app）

## 查找某个类型的最大最小值

记一下头文件和调用的方法

```cpp
#include<limits>

int max_int = numeric_limits<int>::max();
double min_db1 = numeric_limits<double>::min();
```