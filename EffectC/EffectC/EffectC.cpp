#include <iostream>
#include <chrono>
#include <numeric>

#include "dynamiccast.h"

using namespace std;

class CPoint
{
public:
	CPoint() 
	: x(0)
	, y(0) {}

	CPoint(int p_x, int p_y)
		: x(p_x)
		, y(p_y) {}

	~CPoint() = default;

public:
	const int& GetX() const { return x; }
	const int& GetY() const { return y; }

	void SetX(int p_x) { x = p_x; }
	void SetY(int p_y) { y = p_y; }

private:
	int x, y;
};

struct RectPoint
{
	CPoint rlt;
	CPoint rrb;
};

class CRect
{
public:
	CRect(const CPoint& p_lt, const CPoint& p_rb)
		: m_RectPoint(new RectPoint)
	{
		m_RectPoint->rlt = p_lt;
		m_RectPoint->rrb = p_rb;
	}
	~CRect() = default;

public:
	CPoint GETLeftTop() const { return m_RectPoint->rlt; }

private:
	shared_ptr<RectPoint> m_RectPoint;
};

int main()
{
	CPoint lt(0, 0), rb(100, 100);

	CRect rect(lt, rb);

	// CPoint& GETLeftTop() const { return m_RectPoint->rlt; }
	// rect.GETLeftTop().SetX(10); // 물리적 상수성 한계로 값 변경이 가능

	// const CPoint& GETLeftTop() const { return m_RectPoint->rlt; }
	// rect.GETLeftTop().SetX(10); // 실패

	// 	CPoint GETLeftTop() const { return m_RectPoint->rlt; }
	// rect.GETLeftTop().SetX(10); // 실패 - 핸들을 반환하지 않는다.

	return 0;
}