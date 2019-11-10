//#include <iostream>
//#include <chrono>
//#include <numeric>
//#include <vector>
//
//using namespace std;
//
//class CInvestment
//{
//private:
//	CInvestment()
//	{
//		m_pNum = new int;
//		*m_pNum = 10;
//	}
//public:
//	~CInvestment()
//	{
//		if (nullptr != m_pNum)
//		{
//			delete m_pNum;
//			m_pNum = nullptr;
//		}
//	}
//
//	static CInvestment* Create()
//	{
//		CInvestment* pInst = new CInvestment();
//
//		return pInst;
//	}
//
//private:
//	int* m_pNum;
//};
//
//shared_ptr<CInvestment> g_Inst;
//
//class CBase
//{
//public:
//	CBase() = default;
//	~CBase() = default;
//
//private:
//	CBase(const CBase& rhs) = default;
//
//public:
//	int		m_iNum;
//};
//
//class CDerived : private CBase
//{
//public:
//	CDerived()
//	{
//		m_iNum = 10;
//	}
//};
//
//class CDerived2 : public CDerived
//{
//public:
//	CDerived2()
//	{
//		//m_iNum = 10;
//	}
//};
//
//void RAIIFunc()
//{
//	vector<shared_ptr<CInvestment>> vec;
//
//	for (int i = 0; i < 3; ++i)
//	{
//		shared_ptr<CInvestment> pInst(CInvestment::Create());
//		vec.push_back(pInst);
//	}
//
//	g_Inst = vec[0];
//}
//
//int main()
//{
//	//auto_ptr<CInvestment> pInst(CInvestment::Create());
//
//	//auto_ptr<CInvestment> pCpy = pInst;
//
//	//RAIIFunc();
//
//	CDerived child;
//
//	CDerived2 child2;
//
//	return 0;
//}