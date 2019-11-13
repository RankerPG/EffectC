#pragma once
#include <memory>

using namespace std;

class CData
{
public:
	CData()
		: m_iNum(0)
	{
	}

	~CData() = default;

public:
	inline const int& Get_Num() { return m_iNum; }

	inline void Set_Num(int p_num) { m_iNum = p_num; }

private:
	int m_iNum;
};

class CCapsule
{
public:
	CCapsule()
		: m_data(new CData) {}

	~CCapsule()
	{
		if (nullptr != m_data)
			delete m_data;
	}

	CCapsule(const CCapsule& rhs)
		: m_data(new CData)
	{
		*m_data = *rhs.m_data;
	}

	CCapsule& operator=(const CCapsule& rhs)
	{
		*m_data = *rhs.m_data;

		return *this;
	}

public:
	inline const int& Get_Num() { return m_data->Get_Num(); }

	inline void Set_Num(int p_num) { m_data->Set_Num(p_num); }

public:
	void swap(CCapsule& p_other)
	{
		using std::swap;

		swap(m_data, p_other.m_data);
	}

private:
	CData* m_data;
};

//namespace std
//{
//	template<>
//	void swap<CCapsule>(CCapsule& p_lhs, CCapsule& p_rhs)
//		_NOEXCEPT_COND(is_nothrow_move_constructible_v<CCapsule>&&
//		is_nothrow_move_assignable_v<CCapsule>)
//	{
//		p_lhs.swap(p_rhs);
//	}
//}