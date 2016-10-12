#include<iostream>
#include<algorithm>
#include<string>
#include<sstream>
#include<cctype>
#include <ctime>
using namespace std;
const unsigned int max_search = 100000000;//һ������
const long long upperbond = 2038074750;    //ɸ������
const long long maxn = upperbond / 6 + 1;//ֻ����6n-1,6n+1,��ռ1/3
bool isprime_n[maxn];                       //��¼��Ӧnum=6n-1
bool isprime_p[maxn];                     //��¼��Ӧnum=6n+1
long long prime;
//bool *isprme_n=judge_pn;
//bool *isprme_p=judge_pp;
/*class basic_bit_operation
{
const int DEFAULT_BOOLS_LENGTH = 8;
char byte_data = 0;
public:
static void bool_to_bit(bool data,int index)
{
int cache = data ? 1 : 0;
byte_data |= (char)(cache << index);
}

static bool bit_to_bool(int index)
{
bool cache = (char)(1 << index);
return cache == (cache & byte_data);
}
};*/
void sieve(long long &n, long long &upper_bond)//iΪtrue��ʾ������iΪfalse��ʾ����
{
	if (n == 1)prime = 2;
	if(n == 2 ) prime = 3;                    //��5��ʼɸ
	const long long nn = (upper_bond + 1) / 6, np = (upper_bond - 1) / 6;
	long long c = 2;              //5�ǵ���������,��5��ʼ����,c��ʾ��ǰ�����˵ڼ�������
	long long i = 1;
	long long  j(1);               //��ʱ����
	register int t(0);
	for (; i <= nn; ++i)    //5��Ӧ�±�Ϊ1 ; ����6n-1
	{
		if (!isprime_n[i])
		{
			++c;
			if (n == c)
			{
				prime = 6 * i - 1;
				return;
			}
			{
				t = 6 * i - 1;                           //�����ϵ��ÿ�κ���6i-1
				j = 6 * i*i;
				while (j + 8 * t <= nn)                    //8��λһ�飬����û��ʱ��λѹ���ˣ������ֶ�ģ��
				{
					isprime_n[j] = true;
					isprime_n[j + t] = true;
					isprime_n[j + 2 * t] = true;
					isprime_n[j + 2 * t + t] = true;
					isprime_n[j + 4 * t] = true;
					isprime_n[j + 4 * t+t] = true;
					isprime_n[j + 4 * t+2*t] = true;
					isprime_n[j + 4 * t+2*t+t] = true;
					j = j + 8 * t;
				}
				while (j <= nn)
				{
					isprime_n[j] = true;
					j = j + t;
				}
				j = 6 * i*i - 2 * i;
				while (j + 8 * t <= np)
				{
					isprime_p[j] = true;
					isprime_p[j + t] = true;
					isprime_p[j + 2 * t] = true;
					isprime_p[j + 2 * t + t] = true;
					isprime_p[j + 4 * t] = true;
					isprime_p[j + 4 * t + t] = true;
					isprime_p[j + 4 * t + 2 * t] = true;
					isprime_p[j + 4 * t + 2 * t + t] = true;
					j = j + 8 * t;
				}
				while (j <= np)
				{
					isprime_p[j] = true;
					j = j + t;
				}
			}
		}
		if (!isprime_p[i])
		{
			++c;
			if (n == c)
			{
				prime = 6 * i + 1;
				return;
			}
			{
				t = 6 * i + 1;                           //�����ϵ��ÿ�κ���6i+1
				j = 6 * i*i + 2 * i;
				while (j + 8 * t <= np)
				{
					isprime_p[j] = true;
					isprime_p[j + t] = true;
					isprime_p[j + 2 * t] = true;
					isprime_p[j + 2 * t + t] = true;
					isprime_p[j + 4 * t] = true;
					isprime_p[j + 4 * t + t] = true;
					isprime_p[j + 4 * t + 2 * t] = true;
					isprime_p[j + 4 * t + 2 * t + t] = true;
					j = j + 8 * t;
				}
				while (j <= np)
				{
					isprime_p[j] = true;
					j = j + t;
				}
				j = 6 * i*i + 6 * i + 1;
				while (j + 8 * t <= nn)
				{
					isprime_n[j] = true;
					isprime_n[j + t] = true;
					isprime_n[j + 2 * t] = true;
					isprime_n[j + 2 * t + t] = true;
					isprime_n[j + 4 * t] = true;
					isprime_n[j + 4 * t + t] = true;
					isprime_n[j + 4 * t + 2 * t] = true;
					isprime_n[j + 4 * t + 2 * t + t] = true;
					j = j + 8 * t;
				}
				while (j <= nn)
				{
					isprime_n[j] = true;
					j = j + t;
				}
			}
		}
	}	
}
bool input(long long &n)                    //���������Ѱ�ҵ��������
{
	string input,temp_input;
	stringstream ss;
	int k=0;                             //�����ж������ַ����Ƿ�Ϊ������
	unsigned int num;                 //����Ĳ���
	input.clear();
	ss.clear();
	cout << "������Ҫ�ҵ���n������";
	cin >> input;
	switch (input[0])
	{
	case '+':
		temp_input = input.substr(1);
		input = temp_input;
		break;
	case'-':
		cerr << "error input!" << endl;
		return false;
	}
	for (k = 0; k<input.size() && isdigit(input[k]); ++k);
	ss << input;
	ss >> num;
	if (num >max_search || num < 1 || k != input.size())
	{
		cerr << "error input!" << endl;
		return false;
	}
	n = num;
	return true;
}
void get_upper_bond(long long &n, long long  &upper_bond)
{
	if (n<1000)                                  //һǧ
		upper_bond = 7929;
    else if (n < 5000)                           //��ǧ
        upper_bond = 48620;
	else if (n < 10000)                          //һ��
		upper_bond = 104740;
	else if (n < 100000)                          //ʮ��
		upper_bond = 1299719;
	else if(n<500000)                            //50��
		upper_bond = 7368795;
	else if (n < 1000000)                         //100w
		upper_bond = 15485870;
	else if (n < 2500000)                         //250w
		upper_bond = 41161749;
	else if(n<5000000)                           //500w
		upper_bond = 86028130;
	else if (n<8500000)                           //850w
		upper_bond = 151048979;
	else if(n<10000000)                          //1000w
		upper_bond =179424680;
	else if (n<15000000)                          //1500w
		upper_bond = 275604551;
	else if (n<20000000)                          //2000w
		upper_bond = 373587893;
	else if (n<25000000)                          //2500w
		upper_bond = 472882037;
	else if (n<30000000)                          //3000w
		upper_bond = 573259400;
	else if (n<35000000)                          //3500w
		upper_bond = 674506081;
	else if (n<40000000)                          //4000w
		upper_bond = 776531411;
	else if (n<45000000)                          //4500w
		upper_bond = 879190757;
	else if(n<50000000)                          // 5000w
		upper_bond =982451660;
	else if (n<55000000)                          // 5500w
		upper_bond = 1086218500;
	else if(n<60000000)                         //6000w
		upper_bond =1190494769;
	else if (n<65000000)                         //6500w
		upper_bond = 1295202459;
	else if(n<70000000)                         //7000w
		upper_bond =1400305347;
	else if (n<75000000)                         //7500w
		upper_bond = 1505776949;
	else if (n<80000000)                         //8000w
		upper_bond = 1611623783;
	else if(n<85000000)                         //8500w
		upper_bond =1717783157;
	else if (n<90000000)                         //9000w
		upper_bond = 1824261419;
	else if (n<95000000)                         //9500w
		upper_bond = 1931045223;
}
int main()
{
	long long n(max_search), upper_bond(upperbond);
//	double start, end, time;
	if (input(n))
	{
		//start = clock();
		//cout << "����������,���Ժ󡭡�" << endl;
		get_upper_bond(n,upper_bond);
		sieve(n, upper_bond);
	//	end = clock();
	//	time = (double)(end - start) / CLOCKS_PER_SEC;
	//	cout << time << endl;
		cout << "��" << n << "������Ϊ��" << prime << endl;
        return 0;
	}
	else
	{
		return 1;
	}
	
}
