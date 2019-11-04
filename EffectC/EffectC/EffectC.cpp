#include <iostream>

using namespace std;

class A
{
public:
	A() = default;
	~A() = default;
	explicit A(int p_num)
		: m_iNum(p_num) {}

public:
	inline const int& Get_Num() { return m_iNum; }

private:
	int m_iNum;
};

void ShowClassA(A p_a)
{
	cout << p_a.Get_Num() << endl;
}

int main()
{
	// 암시적 형변환의 예
	//ShowClassA(5);
}