#include<iostream>
#include<string.h>
#include<array>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

void example_1_01(){
    string user_name;
    cout << "Please enter your first name: ";
    cin >> user_name;
    //cout << '\n';
    cout << "Hello, " 
         << user_name 
         << "... and goodbye!" << endl;
}

//读取用户输入的姓名并显示
void practice_1_04(){
    string first_name, last_name;
    cout << "Please enter your first name and last name: ";
    cin >> first_name >> last_name;
    //cout << '\n';
    cout << "Hello, " 
         << first_name 
         << last_name
         << "... and goodbye!" << endl;
}

// 读取用户输入的姓名并和预设的比较，如果一样就输出一些内容
// c语言的字符串
void  practice_1_05_01(){
    char c_target_name[] ="Bob";
    char enter_name[100];
    cout << "Please enter your name: ";
    cin >> enter_name;
    if(strcmp(c_target_name,enter_name)==0){
        cout << "Hello, "    << enter_name 
             << " Welcome back" << endl;
    }
    else{
        cout << "Hello, " << enter_name << endl;
    }
}

// 读取用户输入的姓名并和预设的比较，如果一样就输出一些内容
// c++的字符串
void  practice_1_05_02(){
    string target_name = "John";
    cout << "Please enter your name: ";
    string enter_name;
    cin >> enter_name;
    if(enter_name == target_name){
        cout << "Hello, "    << enter_name 
             << " Welcome back" << endl;
    }
    else{
        cout << "Hello, " << enter_name << endl;
    }
}

// 读取一行整数（个数未知）读入array和vector中
// 遍历并计算平均值和总和值
void  practice_1_06(){
    array<int,100> arr_values;
    vector<int> vec_values;
    int temp;
    int index = 0;

    cin >> temp;
    arr_values[index++] = temp;
    vec_values.push_back(temp);

    while(cin.get()!='\n'){
        cin >> temp;
        arr_values[index++] = temp;
        vec_values.push_back(temp);
    }

    int sum_array=0,sum_vector=0;
    double ave_array=0.0,ave_vector=0.0;

    for(int i=0;i<index;i++){
        sum_array  += arr_values[i];
        sum_vector += vec_values[i];
    }
    if(index!=0){
        ave_array  = double(sum_array) /double(index);
        ave_vector = double(sum_vector)/double(index);
    }

    cout << "sum of array is "       << sum_array
         << " average of array is "  << ave_array
         << "\nsum of vector is "    << sum_vector
         << " average of vector is " << ave_vector << endl;   
}

// 打开文本文件,读取到vector<string>中
// 遍历显示
// 然后使用sort函数，将排序后的结果输出到另一个文件中
void practice_1_07(){
    ifstream infile("essay.txt");
    ofstream outfile("out_essay.txt");

    if(!infile || !outfile){
        return ;
    }
    else{
        vector<string> file_content;
        string temp;
        while(infile >> temp){
            file_content.push_back(temp);
        }
        
        for(int i=0;i<file_content.size();i++){
            cout << file_content[i] <<" ";
            //outfile << file_content[i];
        }

        sort(file_content.begin(),file_content.end());
        for(int i=0;i<file_content.size();i++){
            
            outfile << file_content[i] << " ";
        }

    }
}

int main(){
    //example_1_01();
    //practice_1_04();
    //practice_1_05_01();
    //practice_1_05_02();
    //practice_1_06();
    practice_1_07();
    
    system("pause");
}