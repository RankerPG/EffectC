//#include <iostream>
//#include <vector>
//#include <list>
//
//using namespace std;
//
//class CTop
//{
//public:
//	CTop()
//		: m_iNum(0) {}
//
//	CTop(int p_n)
//		: m_iNum(p_n) {}
//
//public:
//	const int& Get_Num() { return m_iNum; }
//
//	void Set_Num(const int& p_n) { m_iNum = p_n; }
//
//private:
//	int m_iNum;
//};
//
//class CMid : public CTop
//{
//public:
//	CMid()
//		: CTop(100) {}
//};
//
//template <typename T>
//class CMemberTemplate
//{
//public:
//	CMemberTemplate()
//		: m_pData(new T)
//	{
//		memset(m_pData, 0, sizeof(T));
//	}
//
//	~CMemberTemplate()
//	{
//		if (nullptr != m_pData)
//			delete m_pData;
//	}
//
//	CMemberTemplate(const CMemberTemplate<T>& rhs)
//		: m_pData(rhs.m_pData)
//	{
//
//	}
//
//	template <typename U>
//	CMemberTemplate(const CMemberTemplate<U>& rhs)
//		: m_pData(new T)
//	{
//		//m_pData->Set_Num(rhs.Get_Data()->Get_Num());
//		*m_pData = *rhs.Get_Data();
//	}
//
//	template <typename U>
//	CMemberTemplate<T> operator= (const CMemberTemplate<U>& rhs)
//	{
//		//if (nullptr == m_pData)
//		//	m_pData = new T;
//
//		//m_pData->Set_Num(m_pData->Get_Num());
//	}
//
//public:
//	T* Get_Data() const { return m_pData; }
//	void Set_Data(T p_data) { *m_pData = p_data; }
//private:
//	T* m_pData;
//};
//
//class A
//{
//public:
//	template <typename T>
//	void PrintTemplate(T p_t) { cout << p_t << endl; }
//};
//
//template <typename T> class CMultiple;
//
//template <typename T>
//const CMultiple<T> doMultiple(const CMultiple<T>& lhs, const CMultiple<T>& rhs)
//{
//	return CMultiple<T>(lhs.Get_Data() * rhs.Get_Data());
//}
//
//template <typename T>
//class CMultiple
//{
//public:
//	CMultiple(const T& p_data)
//		: m_Data(p_data) {}
//
//public:
//	const T& Get_Data() const { return m_Data; }
//
//public:
//	friend const CMultiple operator* (const CMultiple& lhs, const CMultiple& rhs)
//	{
//		return doMultiple(lhs, rhs);
//	}
//
//private:
//	T m_Data;
//};
//
//
//template <typename func>
//void printTemplate(const func& p_f)
//{
//	p_f();
//}
//
//void f()
//{
//	cout << "call f" << endl;
//}
//
//template <typename IterT, typename DistT>
//void iterator_advance(IterT& p_iter, DistT p_d, bidirectional_iterator_tag)
//{
//	while (p_d)
//	{
//		if (p_d > 0)
//			++p_iter;
//		else
//			--p_iter;
//
//		--p_d;
//	}
//}
//
//template <typename IterT, typename DistT>
//void iterator_advance(IterT& p_iter, DistT p_d, random_access_iterator_tag)
//{
//	p_iter += p_d;
//}
//
//namespace stdFunc
//{
//	template <typename IterT, typename DistT>
//	void advance(IterT& p_iter, DistT p_d)
//	{
//		iterator_advance(p_iter, p_d, typename iterator_traits<IterT>::iterator_category());
//	}
//}
//
//template <unsigned n>
//struct Factorial
//{
//	enum { value = n * Factorial<n - 1>::value };
//};
//
//template <>
//struct Factorial<0>
//{
//	enum { value = 1 };
//};
//
//class CNewHandlerHolder
//{
//public:
//	CNewHandlerHolder(new_handler& p_handler)
//		: m_handler(p_handler) {}
//
//	~CNewHandlerHolder()
//	{
//		set_new_handler(m_handler);
//	}
//
//	CNewHandlerHolder(const CNewHandlerHolder& rhs) = delete;
//	CNewHandlerHolder& operator= (const CNewHandlerHolder& rhs) = delete;
//
//private:
//	new_handler m_handler;
//};
//
//template <typename T>
//class CNewHandlerSupport
//{
//public:
//	static new_handler set_new_handler(new_handler p_handler) noexcept;
//	static void* operator new(size_t size) throw(bad_alloc);
//
//private:
//	static new_handler m_currentHandler;
//};
//
//template <typename T>
//new_handler CNewHandlerSupport<T>::set_new_handler(new_handler p_handler) noexcept
//{
//	new_handler oldHandler = m_currentHandler;
//	m_currentHandler = p_handler;
//	return oldHandler;
//}
//
//template<typename T>
//void* CNewHandlerSupport<T>::operator new(size_t size) throw(bad_alloc)
//{
//	CNewHandlerHolder h(std::set_new_handler(m_currentHandler));
//	return ::operator new(size);
//}
//
//template <typename T>
//new_handler CNewHandlerSupport<T>::m_currentHandler = nullptr;
//
//class CWidget : public CNewHandlerSupport<CWidget>
//{
//private:
//	int m_i;
//	float m_f;
//};
//
//void OutofMemory()
//{
//	cerr << "Out of Memory ! < CWidget > \n";
//	system("pause");
//	abort();
//}
//
//new_handler CNewHandlerSupport<CWidget>::m_currentHandler = OutofMemory;
//
//int main()
//{
//	std::set_new_handler(OutofMemory);
//
//	CWidget* w = new CWidget[250000000L];
//
//	delete[] w;
//
//	//////////////////////////////////////////////////////////
//	//cout << Factorial<5>::value << endl;
//	//cout << Factorial<10>::value << endl;
//	//cout << Factorial<20>::value << endl; // int로 인자가 들어가서 오버플로우로 인해 음수가 되서 에러
//
//	//////////////////////////////////////////////////////////
//	//vector<int> v({ 1, 2, 3 });
//	//list<int> l({ 1, 2, 3 });
//
//	//vector<int>::iterator iter = v.begin();
//	//list<int>::iterator iter_list = l.begin();
//
//	//stdFunc::advance(iter, 2);
//	//cout << *iter << endl;
//
//	//stdFunc::advance(iter_list, 2);
//	//cout << *iter_list << endl;
//
//	//////////////////////////////////////////////////////////
//	//printTemplate(f);
//
//	//////////////////////////////////////////////////////////
//	//CMultiple<int> m(10), m2(20);
//
//	//m2 = 5 * m;
//
//	//cout << m2.Get_Data() << endl;
//
//	//////////////////////////////////////////////////////////
//	//CMemberTemplate<CTop> mt1;
//	//CMemberTemplate<CMid> mt2(mt1);
//
//	//CMemberTemplate<CMid> mt3;
//
//	//mt2 = mt3;
//
//	//CMemberTemplate<int> mt1;
//	//mt1.Set_Data(10);
//	//CMemberTemplate<float> mt2(mt1);
//
//	//CMemberTemplate<double> mt3;
//
//	//mt3.Set_Data(*mt1.Get_Data());
//
//	////CMemberTemplate<int> mt4();
//
//	////cout << mt4.Get_Data() << endl;
//
//	//cout << *mt1.Get_Data() << *mt2.Get_Data() << *mt3.Get_Data() << endl;
//
//	return 0;
//}