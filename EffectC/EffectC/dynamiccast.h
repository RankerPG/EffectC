#pragma once
//
//class CBase
//{
//public:
//	virtual void func() {}
//};
//
//class CDerived : public CBase
//{
//public:
//	CDerived()
//		: CBase() {}
//
//public:
//	void Print()
//	{
//		using namespace std;
//
//		cout << "print func" << endl;
//	}
//};

// 자식 객체를 void*로 가지고 있으려 했으나 이 역시도 캐스팅 필요
// 템플릿으로 하자니 인수의 무한 루프라 실패
// 객체 컨테이너가 맞는 방법 같다
