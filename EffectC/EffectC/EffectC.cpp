﻿#include <iostream>

using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TextBlock
{
public:
	TextBlock()
		: m_len(10)
		, m_vaild(false)
	{
		m_str = new char[10];
		strcpy(m_str, "String!!");
	}

	~TextBlock()
	{
		delete m_str;
		m_str = nullptr;
	}
	
	char& operator[](int position) const { return m_str[position]; }
	
	char* Get_String() const { return m_str; }
	char* Get_String() { return m_str; }

	const int& Get_length() const
	{
		if (false == m_vaild)
		{
			m_len = strlen(m_str);
			m_vaild = true;
		}

		return m_len;
	}

	int& Get_length()
	{
		return const_cast<int&>(static_cast<const TextBlock&>(*this).Get_length());
	}

private:
	char*			m_str;
	string			m_string;
	mutable int		m_len;
	mutable bool	m_vaild;
};


int main()
{
	const TextBlock tb;

	char* p = &tb[0];

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 필기 테스트 복기
//10 - 8 - 5 - 2 - 2 - 3 - 3 - 3 => 최대 64점..
//확신하지 못하는 게 크다.
//가상함수테이블의 크기가 들어가는지 몰랐다니 댕청...
//class A
//{
//public:
//	A() {};
//	virtual ~A() {};
//
//	static int sA;
//	char a;
//};
//
//class B : public A
//{
//public:
//	B() {};
//	virtual ~B() {};
//	float b;
//};
//
//class C : public B
//{
//public:
//	C() {};
//	virtual ~C() {};
//};
//cout << sizeof(A) << sizeof(B) << sizeof(C) << endl;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 유클리드 호제법
//int gcd(int p_lhs, int p_rhs)
//{
//	return p_lhs % p_rhs == 0 ? p_rhs : gcd(p_rhs, p_lhs % p_rhs);
//}
//
//int gcm(int p_lhs, int p_rhs)
//{
//	return (p_lhs * p_rhs) / gcd(p_lhs, p_rhs);
//}
//
//int main()
//{
//	cout << gcd(1071, 1029) << endl;
//	cout << gcm(12, 20) << endl;
//
//	return 0;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 암시적 형변환의 예
//class A
//{
//public:
//	A() = default;
//	~A() = default;
//	explicit A(int p_num)
//		: m_iNum(p_num) {}
//
//public:
//	inline const int& Get_Num() { return m_iNum; }
//
//private:
//	int m_iNum;
//};
//
//void ShowClassA(A p_a)
//{
//	cout << p_a.Get_Num() << endl;
//}
//
//int main()
//{
//	// 암시적 형변환의 예
//	//ShowClassA(5);
//}