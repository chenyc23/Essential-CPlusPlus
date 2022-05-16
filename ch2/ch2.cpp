#include<iostream>
#include<string>
#include<limits>
#include<vector>

using namespace std;

/*
template<class T>
void swap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}
*/

void display_vec(const vector<int> &vec){
    for(int i=0;i<vec.size();++i){
        cout << vec[i] << " ";
    }
    cout << endl;
}

bool practice_2_01_func(int pos, int &elem){
    if(pos<1 || pos>46){
        elem = 0;
        return false;
    }
    elem = 1;
    int num_1=1,num_2=1;
    for(int i=3;i<=pos;++i){
        elem = num_1 + num_2;
        num_2 = num_1;
        num_1 = elem;
    }
    return true;
}

// 允许多次输入斐波那契数列的位置值，返回该位置的斐波那契值
void practice_2_01_main(){
    string str;
    while(1){
        cin >> str;
        if(str=="#")
            return ;
        else{
            int pos = stoi(str);
            int result;
            if(practice_2_01_func(pos,result)){
                cout << "element # " << pos
                     << " is " << result << endl;
            }
            else{
                cout <<"Sorry. Could not calculate element "
                     << pos << endl;
            }
        }
    }  
}

// 书上冒泡排序的例子
void example_02_bubble_sort(vector<int> &vec){
    for(int ix=0; ix<vec.size(); ++ix)
        for(int jx=ix+1;jx<vec.size();++jx){
            if(vec[ix]>vec[jx])
                swap(vec[ix],vec[jx]);
        }
}
// 书上冒泡排序的例子主函数
void example_02(){
    int ia[8] = {8,34,3,13,1,21,5,2};
    vector<int> vec(ia,ia+8);
    
    cout << "vector before sort: ";
    display_vec(vec);

    example_02_bubble_sort(vec);

    cout << "vector after  sort: ";
    display_vec(vec);
}

// 打印信息模板函数
template <typename elemType>
void display_message(const string &msg, const vector<elemType> &vec){
    cout << msg;
    for(int ix=0; ix<vec.size(); ++ix){
        elemType t = vec[ix];
        cout << t << " ";
    }
}

// 检验元素个数是否合理,如果合理，并且未被计算，就进行求值
inline bool practice_2_02_is_num_valid(int pos, vector<int> &elem){
    if(pos<1 || pos>64){
        cout << "Sorry. Could not calculate element "
             << pos << endl;
        return false;
    }
    if(pos>elem.size()){
        return true;
    }
    return false;
}
// 根据输入的pos计算Pentagonal数列,并把结果放入传入的vector内
void practice_2_02_calc_elem(int pos, vector<int> &elem){
    if(practice_2_02_is_num_valid(pos,elem)){
        for(int ix=elem.size(); ix<pos; ++ix){
            int num = ix+1;
            elem.push_back(num*(3*num-1)/2);
        }
    }
}
// 根据输入vector,打印vector内的数据
void practice_2_02_disp_elem(const vector<int> &elem, string str){
    if(elem.size()>0){
        cout << str << endl;
        for(int ix=0; ix<elem.size();ix++){
            cout << elem[ix] << " ";
        }
        cout << endl;
    }   
}

// Pentagonal数列
void practice_2_02_main(){
    vector<int> result;
    string str;
    
    while(1){
        cout << "Please enter the position of Pentagonal: # ";
        cin >> str;
        if(str =="#"){
            return ;
        }
        else{   
            int pos = stoi(str);
            practice_2_02_calc_elem(pos,result);
            practice_2_02_disp_elem(result,"int");
        }       
    }    
}

// 以局部静态变量vector存储数列元素
const vector<int>* practice_2_04_setPentagonal(int val){
    static vector<int> vec;
    if(val<1 || val>64){
        return &vec;
    }
    else{
        for(int ix=vec.size(); ix<val; ++ix){
            int num = ix+1;
            vec.push_back(num*(3*num-1)/2);
        }
    }
    return &vec;
}

// 根据索引值，获得vector里的内容
int practice_2_04_getvalfromindex(int pos, const vector<int>*vec){
    if(vec==nullptr){
        cout << "the pointer is nullptr" <<endl;
    }
    if(pos>(*vec).size()){
        cout << "the index is out of range" << endl;
    }
    return (*vec)[pos-1];
}
void practice_2_04_main(){
    const vector<int> *v = practice_2_04_setPentagonal(8);
    if(v == nullptr){
        cout << "v is nullptr" << endl;
    }
    cout << practice_2_04_getvalfromindex(4,v) << endl;
}

// 各种取最大值的声明
void practice_2_05_declare(){
    int max(int a, int b);
    float max(float a, float b);
    string max(const string &a, const string &b);
    int max(const vector<int> &v);
    float max(const vector<float> &v);
    string max(const vector<string> &v);
    int max(const int *arr[], int size);
    char max(const char *arr[], int size);
    float max(const float *arr[], int size); 
}

// 模板函数取最大值
template<typename T>
T origin_max(const T &a, const T &b){
    return (a > b) ? a : b;
}
// 模板函数取最大值
template<typename T>
T vec_max(const vector<T> &vec){
    T max = vec[0];
    for(auto v : vec){
        if(max<v)
            max=v;
    }
    return max;
}
// 模板函数取最大值
template<typename T>
T arr_max(const T* arr,int size){
    T temp=arr[0];
    for(int ix=0;ix<size;ix++){
        if(arr[ix]>temp)
            temp = arr[ix];
    }
    return temp;
}
// 测试取最大值模板函数
void practice_2_06_main(){
    cout << origin_max<int>(1,2) << endl;
    cout << origin_max<float>(1.2f,2.4f) << endl;
    cout << origin_max<string>("abc","abcd") << endl;

    vector<int> vec={1,2,4,9,22};
    cout << vec_max<int>(vec) << endl;
    vector<float> vec_f={1.1f,2.3f,4.2f,9.1f,22.5f};
    cout << vec_max<float>(vec_f) << endl;
    vector<string> vec_s={"avs","abc","anld","abcd"};
    cout << vec_max<string>(vec_s) << endl;

    int arr_int[] = {1,2,3,8,4};
    cout << arr_max(arr_int,5) << endl;
    float arr_float[] = {1.2f,2.4f,3.6f,8.4f};
    cout << arr_max(arr_float,4) << endl;
    char arr_char[] = {'R','U','N','O'};
    cout << arr_max(arr_char,4) << endl;
}

int main(){
    //practice_2_01_main();
    //example_02();
    //practice_2_02_main();
    //practice_2_04_main();
    practice_2_06_main();
    system("pause");
}