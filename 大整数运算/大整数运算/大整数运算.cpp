// 大整数运算.cpp : 定义控制台应用程序的入口点。
//
#include"Large_Interger.h"
#include<ctype.h>
#include<time.h>
char flag(0);
char remain(0);    //输入还剩几行
void Large_Inter::init(const Large_Inter &c)
{
	
	for (int i = 0; i < max; i++)
		Inter[i] = c.Inter[i];
	length = c.length;
}
Large_Inter::Large_Inter(const Large_Inter &c) :length(0)
{
	Inter = new char[2*max];//存储大整数,0号存符号
	init(c);
}

Large_Inter Large_Inter::operator = (const Large_Inter &c)         //复制控制
{
	init(c);
	return *this;
}
bool Large_Inter::operator>(const Large_Inter&n)
{
	if (Inter[0] > n.Inter[0])   //+ ASCII > -
		return true;
	if (Inter[0] < n.Inter[0])
		return false;
	if (Inter[0] == '+')
	{
		if (length>n.length)
			return true;
		if (length < n.length)
			return false;
		for (int i(1); i <= length; i++)
		{
			if (Inter[i]>n.Inter[i])return true;
			if (Inter[i] < n.Inter[i])return false;
		}
		return false;
	}
	else
	{
		if (length>n.length)
			return false;
		if (length < n.length)
			return true;
		for (int i(1); i <= length; i++)
		{
			if (Inter[i]>n.Inter[i])return false;
			if (Inter[i] < n.Inter[i])return true;
		}
		return false;
	}
}
bool Large_Inter::operator==(const Large_Inter&n)
{
	if (length != n.length)return false;
	for (unsigned int i(0); i <= length; ++i)
	{
		if (Inter[i] != n.Inter[i])return false;
	}
	return true;
}
bool Large_Inter::operator<(const Large_Inter&n)
{
	if (*this > n || *this==n)return false;
	return true;
}
 Large_Inter Large_Inter::abs() const
{
	 Large_Inter t(*this);
	 t.Inter[0] = '+';
	 return t;
}
//初始化
void Large_Inter::init(char *p)
{//录入的ASCII为48
	if (strlen(p) - 1 == 0)
		length = 1;
	else
	{
		length = strlen(p) - 1;
		int i(1);
		for (i = 1; i <= length; i++)
			Inter[i] = p[i] - 48;
	}
	if (p[0] == '+')  //输入的正数带符号
	{
		Inter[0] = '+';
	}
	else if (p[0] == '-')
	{
		Inter[0] = '-';
	}
	else cerr << "Error Input!" << endl;
}

void Large_Inter::print()
{
	int i(0);
	if (length == 0)return;
	if (Inter[i++] == '-')cout << "-";
	for (; i<length; i++)           //跳过除最后一个外可能的0
	   if (Inter[i] != 0)break;
	for (; i <= length; i++)
		cout << Inter[i]+0;
	 cout << endl;
}

//四则运算
void Large_Inter::sum_main(const char*add1, int len1, const char*add2, int len2, Large_Inter&result)
{//假定len1<=len2,注意result首位可能有一个0；
	int carry(0);//进位
	int x(0);    //存放每一位相加后的结果
	int j(result.length);    //记录result相应位数
	for (; len1 > 0; --len1)
	{
		x = add1[len1] + add2[len2] + carry;
		result.Inter[j--] = x % 10;
		carry = x / 10;
		--len2;
	}
	for (; len2 > 0; --len2)          //add2剩下的加上前一位的进位，或者照抄到result中
	{
		x = add2[len2] + carry;
		result.Inter[j--] = x % 10;
		carry = x / 10;               
	}
	result.Inter[j--] = carry;           //最后一位进位
}
void Large_Inter::sum(Large_Inter&result,const Large_Inter&add2)
{
	char temp[2*max] = { 0 };
	if (length > add2.length)
		result.length=length+1;
	else
	{
		result.length = add2.length + 1;
	}                                       //结果位数最多比最长的多一
	if (Inter[0] == add2.Inter[0])
	{
		result.Inter[0] = Inter[0];
		if (length < add2.length)
			sum_main(Inter, length, add2.Inter, add2.length, result);
		else
			sum_main(add2.Inter, add2.length, Inter, length, result);
	}
	else
	{
		if (abs() > add2.abs())
		{
			int i(length+add2.length - 1);
			sub_main(Inter, length, add2.Inter, add2.length, temp);
			result.Inter[0] = Inter[0];
			//搬数组
			for (; i >= 0; i--)
			  if (temp[i] != 0)
				break;                 //除去前面0
			for (int j(0); j <= i; j++)
				result.Inter[j + 1] = temp[i - j];
			result.length = i + 1;
		}
		else if (abs() < add2.abs())
		{
			int i(length + add2.length - 1);
			sub_main(add2.Inter, add2.length, Inter, length, temp);
			result.Inter[0] = add2.Inter[0];
			//搬数组
			for (; i >= 0; i--)
			if (temp[i] != 0)
				break;                 //除去前面0
			for (int j(0); j <= i; j++)
				result.Inter[j + 1] = temp[i - j];
			result.length = i + 1;
		}
		else                           //相等直接为0
		{
			result.length = 1;
			result.Inter[0] = '+';
			result.Inter[1] = 0;
		}
	}
}
void Large_Inter::sub_main(const char*sub1, int len1, const char*sub2, int len2, char *result)
{
	//算法类似加法，只不过改为减去借位的值,假定len2<len1。但不知道多少位，不妨倒过来放
	int borrow(0);
	int x(0);
	int j(0);
	for (; len2 > 0; --len2,--len1)
	{
		x = sub1[len1] - sub2[len2] - borrow;//从最低位减起.
		if (x < 0)
		{
			x += 10;
			borrow = 1;
		}
		else
			borrow = 0;
		result[j++] = x % 10;
	}
	for (; len1>0; --len1)
	{
		x = sub1[len1] - borrow;
		if (x < 0)
		{
			borrow = 1;
			x += 10;
		}
		result[j++] = x % 10;
	}
}
void Large_Inter::sub(Large_Inter&result, Large_Inter&sub2)
{   //为了除法，要保证两个操作数不能被改变
	char flag;
	if (sub2.Inter[0] == '-')
	{
		flag = '-';
		sub2.Inter[0] = '+';
	}
	else
	{
		flag = '+';
		sub2.Inter[0] = '-';
	}
	sum(result, sub2);
	sub2.Inter[0] = flag;
}
void Large_Inter::mult_bit(const char*str1, const char bit2, int len1, int last, Large_Inter&result)
{//一位整数与str相乘，结果放在result上，result[last]放上一轮结果,用于这一轮更新,正序存放，结果可能有冗余位。
	int carry(0);//前一位进位
	int i(len1-1);
	int x(0);
	for (; i >= 0; --i)   //last共后移len1次
	{
		x = str1[i] * bit2 + carry + result.Inter[result.length - last];
		result.Inter[result.length-last] = x % 10;
		carry = x / 10;
		last++;
	}
	while (carry)
	{
		x = result.Inter[result.length-last] + carry;
		carry = x / 10;
		result.Inter[result.length-last] = x % 10;
		last++;
	}

}
void Large_Inter::mult(const char* str1, const char*str2, int len1, int len2, Large_Inter&result)
{
	int i(len2 - 1);
	for (; i >= 0; --i)
		mult_bit(str1, str2[i], len1, len2 - i - 1, result);//result从0号位开始存放结果，每次更新时起始下标往后挪一个。len2-i-1从0开始，一直到len2-1
}
void Large_Inter::multip(Large_Inter&result, Large_Inter&mult2)
{
	result.length = length + mult2.length;
	int i(0);
	int j(0);
	if (Inter[0] != mult2.Inter[0])
		result.Inter[0] = '-';
	else
		result.Inter[0] = '+';
	mult(Inter + 1, mult2.Inter + 1, length, mult2.length, result);        //从数值位开始传递
}
void Large_Inter::div_main(Large_Inter &div1, Large_Inter &div2, Large_Inter&result)
{   //要求div1>div2
	int len1 = div1.length, len2 = div2.length;
	int temp(0);                  //除数补0的个数+1
	//判断结果的位数
	int i(1);
	for (; i <= len2; ++i)
	{
		if (div1.Inter[i] > div2.Inter[i])
		{
			result.length = len1 - len2 + 1;
			break;
		}
		else if (div1.Inter[i]<div2.Inter[i])
		{
			result.length = len1 - len2;
			break;
		}
	}
	if (i>len2)
		result.length = len1 - len2+1;
	while (div1>div2||div1==div2)
	{
		Large_Inter temporary_result;
		for (i=1; i <= len2; ++i)
		{
			if (div1.Inter[i] > div2.Inter[i])
			{
				temp = len1 - len2 + 1;
				break;
			}
			else if (div1.Inter[i]<div2.Inter[i])
			{
				temp = len1 - len2;
				break;
			}
		}
		if (i>len2)
			temp = len1 - len2+1;
		div2.length = div2.length + temp - 1;                   //为除数补0
		div1.sub(temporary_result, div2);
		result.Inter[result.length - temp + 1] += 1;             //减了几次相应位结果就为多少，+1保证从1号位开始
		div2.length = len2;                                      //恢复除数，保证除数不变
		div1 = temporary_result;
		len1 = div1.length;                                       //更新被除数                      
	}
	

}
void Large_Inter::div(Large_Inter&result, Large_Inter&div2)
{
	if (div2.Inter[1] == 0 && div2.Inter[2] == 0)
	{
		cerr << "Divisor cannot be Zero!" << endl;
		return;
	}
	Large_Inter div_temp1 = abs();
	Large_Inter div_temp2 = div2.abs(); 
	if (Inter[0] == div2.Inter[0])
		result.Inter[0] = '+';
	else
		result.Inter[0] = '-';
	if (div_temp1 == div_temp2)
	{
		result.Inter[1] = 1;
		result.length = 1;
		return;
	}
	else if (div_temp1 < div_temp2)
	{
		result.Inter[0] = '+';
		result.Inter[1] = 0;
		result.length = 1;
		return;
	}
	else
		div_main(div_temp1, div_temp2, result);
}


//输入控制
bool Input_Judge(char*str1, char &Operator, char* str2)
{
	char input(0);
	int i(0);

	string isoperation;
	//左操作数
	cout << "please input the expression:" << endl;
	input = getchar();
    //看第一个符号位
	if (input == EOF)
	{
		flag = 1;
		std::cin.clear();
		std::cin.sync();
		return false;
	}
	if (!isdigit(input)&&input != '+' &&input != '-')
	{
		remain = 2;
		cerr << "Error Input!" << endl;
		std::cin.clear();
		std::cin.sync();
		return false;
	}
	else if (input == '-')
		str1[i++] = '-';
	else
	{
		str1[i++] = '+';
		if (input != '0')
		{
			str1[i++] = input;
		}
	}

	   while ((input = getchar()) != '\n')                                             
	{
		   if (!isdigit(input))
		   {
			   remain = 2;
			   cerr << "Error Input!" << endl;
			   std::cin.clear();
			   std::cin.sync();
			   return false;
		   }
		else 
		{
			if (i <max && input!='0')
			{
				str1[i] = input;
				++i;
			}
			else
			{
				remain = 2;
				std::cin.clear();
				std::cin.sync();
				cerr << "Input Overflow!" << endl;
				return false;
			}
		}
	 }
	   str1[i] = '\0';
	
	//右操作数
	i = 0,input=0;
	
	//看第一个符号位
	cin >> input;
	if (!isdigit(input) && input != '+' &&input != '-')
	{
		remain = 1;
		std::cin.clear();
		std::cin.sync();
		cerr << "Error Input!" << endl;
		return false;
	}
	else if (input == '-')
		str2[i++] = '-';
	else
	{
		str2[i++] = '+';
		if (input != '0')
		{
			str2[i++] = input;
		}
	}
	while ((input = getchar()) != '\n')
	{
		if (!isdigit(input))
		{
			remain = 1;
			std::cin.clear();
			std::cin.sync();
			cerr << "Error Input!" << endl;
			return false;
		}
		else 
		{
			if (i < max &&input != '0')
			{
				str2[i] = input;
				++i;
			}
			else
			{
				remain = 1;
				std::cin.clear();
				std::cin.sync();
				cerr << "Input Overflow!" << endl;
				return false;
			}
		}
	}
	str2[i] = '\0';
	//操作符
	getline(cin, isoperation);  //操作符必须单独成行
	if (isoperation.size() != 1)
	{
		std::cin.clear();
		std::cin.sync();
		cerr << "Error Input!" << endl;
		return false;
	}
	else
		input = isoperation[0];
	if (input != '+' &&input != '-'&&input != '*'&&input != '/')
	{
		std::cin.clear();
		std::cin.sync();
		cerr << "Error Input!" << endl;
		return false;
	}
	else
		Operator = input;
	return true;
}
int main()
{
	while (true)
	{
		Large_Inter result,op1,op2;
	    string trash;
		char *str1=new char[max];//第一个操作数
	    char Operator(0);//运算符
	    char *str2=new char[max];//第二个操作数

		if (!Input_Judge(str1, Operator, str2))
		{
			if (flag == 1)                       //遇到EOF
			{
				system("pause");
				return 1;
			}
			else if (flag == 0)
			{
				switch (remain)
				{
				case 1:getline(cin,trash);break;
				case 2:getline(cin, trash); getline(cin, trash); break;
				default:
					break;
				}
			}
		}
		op1.init(str1);
		op2.init(str2);
		switch (Operator)
		{
		case'+':op1.sum(result, op2); break;
		case'-':op1.sub(result, op2); break;
		case'*':op1.multip(result, op2); break;
		case'/':op1.div(result, op2); break;
		default:
			cerr << "Erorr Operand" << endl;
			break;
		}
		result.print();
		delete[]str1;
		delete[] str2;
		cout << "以上为一次测试结果-----------------------------------------------------------" << endl;
		system("pause");
	}
	/*
	//测试代码段
	Large_Inter result, op1, op2;
	string trash;
	long double start, end;
	int i = 0;
	char *str1 = new char[max];//第一个操作数
	char Operator(0);//运算符
	char *str2 = new char[max];//第二个操作数
	str1[0] = '+';
	str2[0] = '+';
	for (i=1; i < 100000; ++i)
	{
	str1[i] = '9';
	str2[i] = '1';
	}
	str1[i] = '\0';
	str2[i] = '\0';
	op1.init(str1);
	op2.init(str2);
	Operator = '/';
	start=clock();
	op1.div(result, op2);
	end=clock();
	cout << (double)((end - start) / CLOCKS_PER_SEC)<<endl;

	result.print();
	system("pause");*/
	return 0;
}

