#ifndef LARGE_INTER
#define LARGE_INTER

#include<string>
#include<iostream>
using namespace std;
const int max = 100001;  //���10w
struct Large_Inter
{
	char *Inter ;//�洢������,0�Ŵ����
	unsigned int length;//real size
       //���캯��
	Large_Inter(const Large_Inter &c);  
	Large_Inter() :length(0)
	{
		Inter = new char[2*max];//�洢������,0�Ŵ����
		for (int i = 0; i < 2*max; ++i)
		{
			Inter[i] = 0;
		}			
	};
	~Large_Inter()
	{
		delete[]Inter;
	}
	//���ַ�����ʼ��
    void init(char*p);
	
	//�ȽϷ�����
	bool operator <(const Large_Inter&n);
	bool operator ==(const Large_Inter&n);
	bool operator > (const Large_Inter &n);
	Large_Inter operator = (const Large_Inter &n);
	Large_Inter abs() const;//�����ֵ
	//������
	void print();
	//�ӷ�ʵ�ֳ���
	void sum(Large_Inter&result,const Large_Inter&add);
	//����ʵ�ֳ���
	void sub(Large_Inter&result, Large_Inter&sub2);
	//�˷�ʵ�ֳ���
	void multip(Large_Inter&result, Large_Inter&mult2);
     //����ʵ�ֳ���
	void div(Large_Inter&result, Large_Inter&div2);

private:
	void init(const Large_Inter &c);
	//�ӷ�ʵ��������
	void sum_main(const char*add1, int len1, const char*add2, int len2, Large_Inter&result);
	//����ʵ��������
	void sub_main(const char*sub1, int len1, const char*sub2, int len2, char *result);
	//�˷�ʵ��������
	void mult_bit(const char*str1, const char bit2, int len1, int carry, Large_Inter&result);
	void mult(const char* str1, const char*str2, int len1, int len2, Large_Inter&result);
	//����ʵ��������
	void div_main(Large_Inter &div1, Large_Inter &div2 ,Large_Inter&result);
};



#endif // !LARGE_INTER
