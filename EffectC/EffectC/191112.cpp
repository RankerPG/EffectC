//#include <iostream>
//#include <chrono>
//#include <numeric>
//
//using namespace std;
//
//class CBase
//{
//public:
//	virtual void f1() = 0
//	{
//		cout << "pure f1" << endl;
//	}
//
//	virtual void f1(int p_n)
//	{
//		cout << p_n << endl;
//	}
//
//	virtual void f2()
//	{
//		cout << "base f2" << endl;
//	}
//
//	virtual void f3()
//	{
//		cout << "base f2" << endl;
//	}
//
//	virtual void f3(double p_n)
//	{
//		cout << "f3" << p_n << endl;
//	}
//};
//
//class CDerived : public CBase
//{
//public:
//	using CBase::f1;
//	using CBase::f3;
//
//public:
//	virtual void f1()
//	{
//		cout << "derived f1" << endl;
//	}
//
//	virtual void f3(double p_n)
//	{
//		cout << "derived f3" << endl;
//	}
//};
//
//// private 상속 시 전달 함수 사용
////class CDerived : private CBase
////{
////public:
////	virtual void f1()
////	{
////		CBase::f1(10);
////	}
////};
//
//int main()
//{
//	CDerived d;
//
//	d.f1();
//	d.CBase::f1();
//	d.f1(10);
//
//	d.f2();
//
//	d.f3();
//	d.f3(10.0);
//
//	return 0;
//}