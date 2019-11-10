# EffectC++

> 읽으면서 몰랐던 부분 정리

# 2019.11.04
<code> ~ page 51 </code>

# 2019.11.05
<code> ~ page 80 </code>

## Chapter 1
### Item 3 : 낌새만 보이면 const를 들이대보자.
*****
- const vector::iterator = 상수 반복자
- vector::const_iterator = 상수 데이터

- 물리적 상수성은 멤버 변수가 1비트라도 변경되면 안된다.
- 논리적 상수성은 내부적으로 바뀌어도 사용자가 모르면 상수성이 유지된다라고 말함.

- mutable 키워드 : 물리적 상수성을 무시한다.

### Item 4 : 객체를 사용하기 전에 반드시 그 객체를 초기화하자
*****
- 비지역 정적 객체는 함수에서 정의하지 않는 정적 객체로 초기화 순서를 지정할 수 없다.
그래서 함수 내부에 넣어 정의하여 비지역 정적 객체를 지역 정적 객체로 바꿔 사용해야 초기화되지 않은 객체에 접근하는 경우를 막을 수 있다.
이 방법을 이용한 패턴이 싱글턴 패턴이다.

- 멀티 쓰레드 환경에서 비상수 정적 변수는 시한폭탄과 같다. 그래서 다중쓰레드 시동전에 미리 초기화를 다 끝내 경쟁 상태(race condition)을 막을 수 있다.
- 경쟁 상태 : 전산학에서 경쟁 상태란 공유 자원에 대해 여러 개의 프로세스가 동시에 접근을 시도할 때 접근의 타이밍이나 순서 등이 결과값에 영향을 줄 수 있는 상태를 말한다. 동시에 접근할 때 자료의 일관성을 해치는 결과가 나타날 수 있다. 이를 방지하기 위해서는 프로세스 협력 기법이 필요하다.

# 2019.11.06
<code> ~ page 115 </code>

## Chapter 2 - 생성자 소멸자 및 대입 연산자

### Item 5 : C++가 은글슬쩍 만들어 호출해 버리는 함수들에 촉각을 세우자
*****

### Item 6 : 컴파일러가 만들어낸 함수가 필요 없으면 확실히 이들의 사용을 금해 버리자
*****
> 복사를 막을 클래스 구현
- 복사 생성자와 복사 대입 연산자를 private으로 하여 외부 복사 방지
- 복사 생성자와 복사 대입 연산자를 private으로 만든 클래스를 상속 받기 (부스트의 noncopyable 클래스를 상속받는 경우)
- 복사 생성자와 복사 대입 연산자를 delete 키워드로 삭제 ( 책에는 안나오지만 가장 좋은 방법 같음 )

### Item 7 : 다형성을 가진 기본 클래스에서는 소멸자를 반드시 가상 소멸자로 선언하자
*****
- vtbl : virtual table ( 가상 함수 테이블 )
- vptr : virtual table pointer ( 가상 함수 테이블 포인터 )
- 기본클래스로서 다형성을 가진다면 가상 소멸자를 사용한다.

### Item 8 : 예외가 소멸자를 떠나지 못하도록 붙들어 놓자
*****
- 소멸자에서 예외가 발생하면 프로그램을 종료하거나 예외를 삼키는 방법밖에 없어 예외가 발생할만한 요소를 함수로 빼서 사용자가
이용할 수 있게끔 하여 예외에 대한 대응을 할 수 있게 한다.

### Item 9 : 객체 생성 및 소멸 과정 중에는 절대로 가상 함수를 호출하지 말자
*****
- **초기화되지 않은 데이터 멤버는 정의되지 않은 상태에 있다**
- 생성자 혹은 소멸자에 가상 함수를 넣으면 미정의 행동이 발생할 수 있다.

```cpp
class parent
{
  parent()
  {
    func();
  }
  
  virtual func();
}

class child
{
  child()
  : parent()
  {
    func();
  }
  virtual func();
}
```

> 위의 상황의 경우 부모 생성자의 func은 부모 클래스의 함수가 호출된다.

- 가상 함수가 생성자에 필요할 경우
1. 가상 함수를 비가상 함수로 만듬 ( ex : 부모 생성자에서 함수 호출에 필요한 값을 받아 함수를 호출한다. ) <br>
2. 함수 호출 클래스를 명시하여 사용

### Item 10 : 대입 연산자는 [*]this의 참조자를 반환하게 하자
*****

- 대입 연산자는 [*]this의 참조자를 반환하는 게 관례이다.

### Item 11 : operator=에서는 자기대입에 대한 처리가 빠지지 않도록 하자
*****

- 복사 대입 연산자를 만들 때, 자기대입에 대한 처리가 필요하다.
1. if로 this와 &rhs를 비교
2. rhs의 사본을 만들어 사본과 바꿈
3. 복사 대입 연산자의 매개변수를 참조가 아닌, 값의 의한 전달로 복사된 사본과 바꿈

<pre>
**찾아 보기**
항목 29에서 나온다는데 swap 함수를 만드는 법이 궁금하다.
함수 안에서 [*]this에 대입한다면 또 다시 복사 대입 연산자를 호출해 무한 루프에 빠지게 되는데
단순히 모든 멤버 변수를 일일이 대입해주는 방식인지 후에 찾아보기
</pre>

### Item 12 : 객체의 모든 부분을 빠짐없이 복사하자
*****

- 객체 복사 함수를 사용할 때 확인할 점
1. 해당 클래스의 데이터 멤버를 모두 복사했는지 확인
2. 이 클래스가 자식 클래스라면 부모 클래스의 복사 함수도 호출했는지 확인

- 복사 함수들이 겹치는 부분이 많다고 한쪽을 이용해 다른 쪽을 구현하는 시도는 좋지 않고 불가능하다.
가능하더라도 하면 안된다.

# 2019.11.07
<code> ~ page 154 </code>

## Chapter 3 - 자원 관리

### Item 13 : 자원 관리에는 객체가 그만!
*****

- 스마트 포인터인 auto_ptr와 같은 객체를 활용하여 자원 관리하자

- RAII ( Resource Acquisition is Initialization ) : 자원 획득 즉시 초기화

- RCSP ( Reference-Counting smart pointer) : 참조 카운팅 방식 스마트 포인터<br>
shared_ptr이 RCSP 클래스이며, 서로 참조하는 경우는 해결하지 못함

<pre>
**찾아 보기**
1. boost에 있는 scoped_array와 shared_array로 동적 배열도 자원 관리할 수 있다고 한다.
이미 표준화되있을 수 있으니 찾아보기
2. shared_ptr의 서로 참조하는 경우의 해결책 찾아보기
</pre>

### Item 14 : 자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자
*****

```cpp
class CBase
{
public:
	CBase() = default;
	~CBase() = default;

public:
	int		m_iNum;
};

class CDerived : private CBase
{
public:
	CDerived()
	{
		m_iNum = 10;
	}
};

class CDerived2 : public CDerived
{
public:
	CDerived2()
	{
      // private 멤버라 접근 불가하여 에러
		//m_iNum = 10;
	}
};
```

- CBase를 CDerived로 private으로 상속하면 CBase의 private 멤버는 접근 불가하고<br>
다른 멤버들은 Derived에서 private 멤버로 바뀐다. <br>
Derived를 Derived로 public으로 상속하면 CBase의 m_iNum에 Derived2는 접근하지 못한다.

- shared_ptr은 2번째 매개변수로 삭제자(Deleter)를 받아 카운트가 0이 되어 소멸할 때 호출할 함수를
받을 수 있다.

- RAII 객체를 복사할 때
1. 복사를 금지한다.
2. **관리하고 있는 자원에 대해 참조 카운팅을 수행한다. (shared_ptr & deleter 설정)**
3. 관리하고 있는 자원을 진짜로 복사
4. 관리하고 있는 자원의 소유권을 옮김

### Item 15 : 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자
*****

```cpp
// 명시적 변환
Resource get() const { return resource; }

// 암시적 변환
Resource operator Resource() const { return resource; }
```

- 자원 관리 객체가 관리하는 자원이 필요한 경우 자원 관리 객체는 자원을 얻을 수 있는 방법을 제공해야 된다.
shared_ptr과 같은 경우 명시적 변환을 통한 get() 함수를 제공하지만 암시적 변환도 가능하다.
안정적인 명시적 변환이 더 좋아보임

### Item 16 : new 및 delete를 사용할 때는 형태를 반드시 맞추자
*****

- 동적할당 시 메모리 구조

|단일 객체|배열 객체|
|--------|----------------|
|object | n object object|

- 객체가 1개인지 배열인지에 따라 구성되는 메모리 구조가 다르기 때문에 해제할 때 []로 구분해야된다.

### Item 17 : new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자
*****

```cpp
void priority(shared_ptr<Widget> p_pw, int p_priority);

int iPriority;

priority(shared_ptr<Widget>(new Widget), iPriority);
// 위 상황에서 일어나는 일들
// 1. priority 호출
// 2. new Widget
// 3. shared_ptr 생성자
// 컴파일러에 따라 호출 순서가 다르기 때문에 원치 않는 순서로 진행해 예외가 발생할 수 있다.

shared_ptr<Widget> pWidget(new Widget);

priority(pWidget, iPriority);

// 스마트 포인터 생성을 따로 처리한 후 매개변수로 넣어 예외가 발생할 수 있는 가능성을 없앤다.
```

## Chapter 4 - 설계 및 선언

<code> ' 제대로 쓰기엔 쉽게, 엉터리로 쓰기엔 어렵게' </code>

### Item 18 : 인터페이스 설계는 제대로 쓰기엔 쉽게, 엉터리로 쓰기엔 어렵게 하자
*****

- 인터페이스의 올바른 사용을 이끄는 방법
1. 인터페이스 사이의 일관성 잡아주기
2. 기본제공 타입과의 동작 호환성 유지하기

- 사용자의 실수를 방지하는 방법
1. 새로운 타입 만들기
2. 타입에 대한 연산을 제한하기
3. 객체의 값에 대해 제약 걸기
4. **자원 관리 작업을 사용자 책임으로 놓지 않기**
> 4번을 제외하고는 엔진을 개발할 때 해볼만한 방법인 것 같다.<br>
> 4번의 경우 팩토리 패턴에서 반환하는 값을 스마트 포인터로 바꿔 삭제자를 등록할 수 있고,<br>
> 삭제에 대한 책임을 사용자에게 묻지 않을 수 있다.

### Item 19 : 클래스 설계는 타입 설계와 똑같이 취급하자
*****

- 좋은 클래스는 문법이 자연스럽고, 의미구조가 직관적이며, 효율적인 구현이 한 가지 이상 가능해야 한다.

- 효과적인 클래스를 설계할 때 고려할 점들
1. 객체 생성 및 소멸은 어떻게 이루어지는가?
2. 객체 초기화는 객체 대입과 어떻게 달라야 하는가?
3. 객체가 '값에 의한 전달'인 경우, 즉 복사 생성자에 어떤 의미를 줄 것인가?
4. 객체가 가질 수 있는 적법한 값에 대한 제약은 무엇으로 잡을 것인가?
> 클래스의 불변속성(invariant)는 멤버로서 유효한 값이다.<br>
> 생성자, 대입 연산자, setter 함수에서 불변속성을 고려하여 예외 방지
5. 기존의 클래스 상속 계통망에 맞출 것인가?
6. 어떤 종류의 타입 변환을 허용할 것인가?
7. 어떤 연산자와 함수를 두어야 의미가 있을까?
8. 표준 함수들 중 어떤 것을 허용하지 말 것인가? (private 선언 고려)
9. 멤버의 접근권한을 어느 쪽에 줄 것인가?
10. 수행 성능, 예외 안전성, 자원 사용과 같은 보장 중 어떤 것을 보장할 수 있는가?
11. 새로 만드는 타입이 얼마나 일반적인가?
12. 정말로 꼭 필요한 타입인가?

### Item 20 : '값에 의한 전달'보다는 '상수객체 참조자에 의한 전달'방식을 택하는 편이 대게 낫다
*****

- 기본 제공 타입, STL 반복자, 함수 객체 타입은 '값에 의한 전달'을 해도 되지만,
그 외의 타입들(사용자 정의 타입 등)은 '상수 객체 참조자의 의한 전달'을 해야 한다.
1. 복사 손실 문제(Slicing problem)를 막아준다.
2. '값의 의한 전달'은 복사 생성자 호출로 인해 무겁다. ( 부모 생성자 호출, 멤버 변수 생성자 호출 )

# 2019.11.10
<code> ~ page 182 </code>

### Item 21 : 함수에서 객체를 반환해야 할 경우에 참조자를 반환하려고 들지 말자
*****

<pre>
**찾아 보기**
반환 값 최적화 (RVO : return value optimization)
</pre>

### Item 22 : 데이터 멤버가 선언될 곳은 private 영역임을 명심하자
*****

- 멤버 변수를 private으로 선언함으로써 캡슐화를 통해 불변속성인 객체를 만들 수 있다.

- 불변속성 : 어떤 객체의 상태가 프로그래머의 의도에 맞게 잘 정의되어 있다고 판단할 수 있는 
기준을 제공하는 속성

- 어떤 것이 바뀌면 깨질 가능성을 가진 코드가 늘어날 때, 캡슐화의 정도는 그에 반비례한다.

- 캡슐화 관점에서 멤버 변수의 접근 제어자가 private이 아닌 public, protected는 쓸모 없다.

- protected는 public보다 더 많이 보호받고 있는 것이 아니다.

- **인터페이스를 제공하는 입장에서 멤버 변수를 제거하거나 변경했을 때, 접근 제어자가 public이였을 경우를
생각해보자**

### Item 23 : 멤버 함수보다는 비멤버 비프렌드 함수와 더 가까워지자
*****

- 캡슐화의 정도는 어떤 데이터를 접근하는 함수의 개수로 알 수 있다.

- 비멤버 비프렌드 함수는 private에 접근할 수 없기 때문에 캡슐화를 높일 수 있다.

- 비멤버 비프렌드 함수를 기능마다 헤더로 나눠 관리하여 컴파일 의존성을 줄일 수 있다.

- **멤버 함수대신 비멤버 비프렌드 함수를 사용항으로써 캡슐화의 정도는 높아지고, 패키징 유연성도 커지며,
기능적인 확장성도 늘어난다.**

### Item 24 : 타입 변환이 모든 매개변수에 대해 적용되어야 한다면 비멤버 함수를 선언하자
*****

```cpp

class Rational
{
 public:
	Rational(int numerator = 0, int denominator = 1);
	
	int numerator() const;
	int denominator() const;
	
	const Rational operator* (const Rational& rhs);
}

Rational oneHalf(1, 2);

Rational result = oneHalf * 2;

result = 2 * oneHalf; // 에러 !

const Rational operator* (const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.numerator() * rhs.numerator()
	, lhs.denominator() * rhs.denominator());
}

result = 2 * oneHalf; // 성공 !
```

- int는 클래스와 연관되어 있지 않고, operator[*] 멤버 함수도 없다. 또한 비멤버 버전의 operator[*]도
없기 때문에 컴파일 에러가 발생한다.

- 멤버 연산자 함수를 호출할 때는 this가 되는 객체에 대해서는 암시적 변환이 되지 않는다.
비멤버 연산자 함수는 모든 인자에 대해 암시적 타입 변환이 가능하다.

### Item 25 : 예외를 던지지 않는 swap에 대한 지원도 생각해 보자
*****

<pre>
**찾아보기**
1. pimpl idiom
=> 컴파일 시간 최적화 기법으로, 필요한 변수들을 모은 구조체를 정의하여 포인터로 가지고 있어 헤더파일을 추가하지 않는다.
</pre>

- 클래스 템플릿의 부분 특수화는 함수 템플릿에 대해서는 허용하지 않는다.

- swap 함수 사용할 때 순서 (클래스 내부에 using std::swap 썼을 경우)
1. swap 함수 템플릿 특수화
2. 객체 내의 swap 함수
3. swap 일반 함수

- std::swap이 클래스에 대해 느리게 동작할 때
1. swap 멤버 함수를 제공한다.
단, 이 멤버 swap은 예외를 던지면 안된다.
2. 멤버 swap을 호출하는 비멤버 swap도 제공한다.
클래스에 대해 std::swap 특수화도 해둔다.
3. 사용자 입장에서 swap을 호출할 때는, std::swap에 대한 using 선언을 넣어 준 후에,
네임스페이스 한정자 없이 swap을 호출한다.
4. std 템플릿의 완전한 특수화가 가능하지만, std에 어떤 것도 추가하려하면 안된다.




