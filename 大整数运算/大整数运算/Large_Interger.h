#ifndef LARGE_INTER
#define LARGE_INTER

#include<string>
#include<iostream>
using namespace std;
const int max = 100001;  //最大10w
struct Large_Inter
{
	char *Inter ;//存储大整数,0号存符号
	unsigned int length;//real size
       //构造函数
	Large_Inter(const Large_Inter &c);  
	Large_Inter() :length(0)
	{
		Inter = new char[2*max];//存储大整数,0号存符号
		for (int i = 0; i < 2*max; ++i)
		{
			Inter[i] = 0;
		}			
	};
	~Large_Inter()
	{
		delete[]Inter;
	}
	//用字符串初始化
    void init(char*p);
	
	//比较符重载
	bool operator <(const Large_Inter&n);
	bool operator ==(const Large_Inter&n);
	bool operator > (const Large_Inter &n);
	Large_Inter operator = (const Large_Inter &n);
	Large_Inter abs() const;//求绝对值
	//输出结果
	void print();
	//加法实现程序
	void sum(Large_Inter&result,const Large_Inter&add);
	//减法实现程序
	void sub(Large_Inter&result, Large_Inter&sub2);
	//乘法实现程序
	void multip(Large_Inter&result, Large_Inter&mult2);
     //除法实现程序
	void div(Large_Inter&result, Large_Inter&div2);

private:
	void init(const Large_Inter &c);
	//加法实现主程序
	void sum_main(const char*add1, int len1, const char*add2, int len2, Large_Inter&result);
	//减法实现主程序
	void sub_main(const char*sub1, int len1, const char*sub2, int len2, char *result);
	//乘法实现主程序
	void mult_bit(const char*str1, const char bit2, int len1, int carry, Large_Inter&result);
	void mult(const char* str1, const char*str2, int len1, int len2, Large_Inter&result);
	//除法实现主程序
	void div_main(Large_Inter &div1, Large_Inter &div2 ,Large_Inter&result);
};



#endif // !LARGE_INTER
