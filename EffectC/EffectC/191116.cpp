//#include <iostream>
//
//using namespace std;
//
//
////void* operator new (size_t size) throw(bad_alloc)
////{
////	if (0 == size)
////		size = 1;
////
////	cerr << "user operator new call \n";
////
////	while (true)
////	{
////		void* p = malloc(size);
////
////		if (nullptr != p)
////			return p;
////
////		new_handler glovalhandler = set_new_handler(nullptr);
////		set_new_handler(glovalhandler);
////
////		if (nullptr != glovalhandler)
////			(*glovalhandler)();
////		else
////			throw::bad_alloc();
////	}
////}
////
////void operator delete (void* rawMemory) throw()
////{
////	if (nullptr == rawMemory)
////		return;
////
////	cerr << "user operator delete call \n";
////
////	free(rawMemory);
////	rawMemory = nullptr;
////}
//
//class CAllocFree
//{
//public:
//	//표준
//	static void* operator new(size_t size) throw(bad_alloc)
//	{
//		return ::operator new(size);
//	}
//
//	static void operator delete(void* rawMemory) throw()
//	{
//		return ::operator delete(rawMemory);
//	}
//
//	//위치지정
//	static void* operator new(size_t size, void* where) throw()
//	{
//		return ::operator new(size, where);
//	}
//
//	static void operator delete(void* rawMemory, void* where) throw()
//	{
//		return ::operator delete(rawMemory, where);
//	}
//
//	//예외지정
//	static void* operator new(size_t size, nothrow_t& nt) throw()
//	{
//		return ::operator new(size, nt);
//	}
//
//	static void operator delete(void* rawMemory, nothrow_t& nt) throw()
//	{
//		return ::operator delete(rawMemory, nt);
//	}
//};
//
//class CWidget : public CAllocFree
//{
//public:
//	using CAllocFree::operator new;
//	using CAllocFree::operator delete;
//
//public:
//	CWidget() { cerr << "Widget default construct call \n"; }
//	CWidget(int p_i) { cerr << "Widget parameter construct call \n"; }
//
//	~CWidget() { cerr << "Widget defalut destruct call \n"; }
//
//	static void* operator new(size_t size, ostream& logstream) throw(bad_alloc)
//	{
//		if (0 == size)
//			size = 1;
//
//		void* p = malloc(size);
//
//		logstream << "log : CWidget alloc \n";
//
//		if (nullptr != p)
//			return p;
//
//		new_handler glovalhandler = set_new_handler(nullptr);
//		set_new_handler(glovalhandler);
//
//		if (nullptr != glovalhandler)
//			(*glovalhandler)();
//		else
//			throw::bad_alloc();
//	}
//
//	static void operator delete(void* rawMemory, ostream& logsteam) throw()
//	{
//		if (nullptr == rawMemory)
//			return;
//
//		logsteam << "log : CWidget free \n";
//
//		rawMemory = nullptr;
//	}
//};
//
//int main()
//{
//	CWidget* p = new(cout) CWidget(10);
//
//	delete p;
//
//	return 0;
//}