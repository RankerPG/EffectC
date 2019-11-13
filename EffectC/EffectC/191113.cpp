//#include <iostream>
//#include <chrono>
//#include <numeric>
//#include <functional>
//
//using namespace std;
//
//// NVI
//class CNVI
//{
//public:
//	CNVI(int p_hp)
//		: m_iHP(p_hp) {}
//	~CNVI() = default;
//
//public:
//	const int& Get_HP() const { return m_iHP; }
//
//	void Wrapper_Damage(int p_damage)
//	{
//		cout << "사전 HP : " << m_iHP << endl;
//
//		Damage(p_damage);
//
//		cout << "사후 HP : " << m_iHP << endl;
//	}
//
//private:
//	virtual void Damage(int p_damage)
//	{
//		m_iHP -= p_damage;
//	}
//
//protected: // private으로 할 수 업나?
//	int		m_iHP;
//};
//
//class CClient : public CNVI
//{
//public:
//	CClient(int p_hp)
//		: CNVI(p_hp) {}
//	~CClient() = default;
//
//private:
//	virtual void Damage(int p_damage)
//	{
//		m_iHP -= p_damage * 2;
//	}
//};
//
//// func pointer 전략 패턴
//class CContext
//{
//private:
//	//typedef void (*Print)(int);
//	typedef function<float(float)> Print;
//public:
//	CContext() {}
//	CContext(Print p_print)
//		: m_print(p_print) {}
//
//public:
//	void Set_Print(Print p_print) { m_print = p_print; }
//
//public:
//	float Wrapper_Print(float p_n) { return m_print(p_n); }
//
//	float Member_Print(float p_n)
//	{
//		cout << "This is Member Print : " << p_n << endl;
//
//		return p_n;
//	}
//
//private:
//	Print m_print;
//};
//
//int Func_1(int p_n)
//{
//	cout << "This is Func_1 : " << p_n << endl;
//
//	return p_n;
//}
//
//float Func_2(float p_n)
//{
//	cout << "This is Func_2 : " << p_n << endl;
//
//	return p_n;
//}
//
////
//class B
//{
//public:
//	virtual void f() { cout << "B's func" << endl; }
//	virtual void fDefault(int i = 10) { cout << i << endl; }
//};
//
//class D : public B
//{
//public: // private으로 접근 제어자를 하면 private이라 접근하지 못한다는 에러가 발생한다.
//	using B::f;
//
//public:
//	virtual void f(int i) { cout << "D's func " << i << endl; }
//	virtual void fDefault(int i = 20) { cout << i << endl; }
//};
//
//int main()
//{
//	//NVI
//	//CNVI c(10);
//	//CClient c2(10);
//
//	//c.Wrapper_Damage(5);
//
//	//c2.Wrapper_Damage(5);
//
//	//전략 패턴
//	//CContext context(Func_1);
//
//	//float f = context.Wrapper_Print(10.5f);
//
//	//cout << f << endl;
//
//	//context.Set_Print(Func_2);
//
//	//f = context.Wrapper_Print(10.5f);
//
//	//cout << f << endl;
//
//	//context.Set_Print(bind(&CContext::Member_Print, context, placeholders::_1));
//
//	//f = context.Wrapper_Print(10.5f);
//
//	//cout << f << endl;
//
//	//D d;
//
//	//d.f(10);
//	//d.f();
//
//	shared_ptr<B> pB(new B());
//
//	pB->fDefault();
//
//	pB.reset(new D());
//
//	pB->fDefault();
//
//	return 0;
//}