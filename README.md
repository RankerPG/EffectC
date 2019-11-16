# EffectC++

> 읽으면서 몰랐던 부분 정리

<pre>
현재 페이지 : 397 ( 11/16 )
끝 페이지 : 397
11월 17일 까지 다 읽기 목표

일일 필요 공부량
11.12 - ~ 250
11.13 - ~ 290
11.14 - ~ 320
11.15 - ~ 350
11.16 - ~ 397
11.17 - ~ 복습

다읽고 복습하면서 다시 한번 정리하는 시간 필요할 듯
</pre>

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
=> C++ 11에 적용된 기법으로 컴파일러가 함수의 리턴 값을 받은 객체가 있을 경우, 리턴 값을 반환 받는 대상의 메모리에 반환하는 방식
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

**다시 읽어봐야 될 듯**

<pre>
**찾아보기**
1. pimpl idiom
=> 컴파일 시간 최적화 기법으로, 필요한 변수들을 모은 구조체를 정의하여
포인터로 가지고 있어 헤더파일을 추가하지 않는다.
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

# 2019.11.11
<code> ~ page 217 </code>

## Chapter 5 - 구현

### Item 26 : 변수 정의는 늦출 수 있는 데까지 늦추는 근성을 발휘하자
*****

- 필요한 변수를 미리 선언하는 방식은 생성자와 더불어 복사 대입 연산자를 호출하는
비효율적인 코드가 되며, 사용하지 않을 가능성과 예외가 발생할 경우에 취약하다.

- for 문에서 객체를 정의할 때
1. 루프 바깥쪽에 정의할 때 : 생성자 1번 + 소멸자 1번 + 대입 n번
2. 루프 안쪽에 정의할 때 : 생성자 n번 + 소멸자 n번

- A 방법의 경우 객체를 볼 수 있는 유효범위가 B 방법보다 넓어지기 때문에
프로그램의 이해도와 유지보수성이 역으로 안 좋아질 수도 있다.

- '복사 대입 연산자 < 생성자 + 소멸자' 이거나 전체 코드에서 수행 성능에 민감한
부분이 아니라면 B 방법이 좋다.

<pre>
평소에 A 방법이 최적화하는 방법이라고 생각하고 사용했는데
B방법도 고려하면서 선택해야겠다.
</pre>

### Item 27 : 캐스팅은 절약, 또 절약! 잊지 말자
*****

- 함수 방식 캐스트

- dynamic_cast가 필요한 상황에 대한 대안
1. **타입 안정성을 갖춘 컨테이너 사용**
2. 함수를 부모 클래스로 올려 상속

- 폭포식 dynamic_cast (if로 비교하는 방식)은 최악의 방식이므로 피해야 함

<pre>
dynamic_cast를 대체할만한 방법을 생각해봤는데 컨테이너 사용 방식이 제일 맞는 것 같다.
</pre>

### Item 28 : 내부에서 사용하는 객체에 대한 '핸들'을 반환하는 코드는 되도록 피하자
*****

- 핸들 : 다른 객체에 손을 댈 수 있게 하는 매개자 ( 포인터, 반복자, 참조자 )

- 어떤 객체에서 호출한 상수 멤버 함수의 참조자 반환 값의 실제 데이터가
그 객체의 바깥에 저장되어 있다면, 이 함수의 호출부에서 그 데이터의 수정이 가능하다.

<pre>
여기서 말하는 문제를 발생시킬 수 있는 핸들을 getter로 반환한 경우가 생각보다 많다.
사실상 이런 점을 고려하지 않았기 때문에 내가 사용했던 getter는 취약할 것 같다.
고려할 점이 늘었다.
</pre>

### Item 29 : 예외 안전성이 확보되는 그날 위해 싸우고 또 싸우자!
*****

- 예외 안전성을 가진 함수의 조건
1. 자원이 새도록 만들지 않는다.
=> 자원 관리 클래스를 사용해 해결 가능
2. 자료구조가 더렵혀지는 것을 허용하지 않는다.

- 원자적인 동작 : 기능적으로 분할할 수 없거나 분할되지 않도록 보증된 조작.
원자와 같이 분할할 수 없다는 것을 비유하여 이렇게 부른다.
원자 조작은 끼어들기가 불가능하며, 만일 중지되면 동작 개시 직전의 상태로 시스템을
복귀시킬 것을 보증하는 복구(백업과 복원) 기능이 제공된다.

<pre>
**찾아보기**
1. unexpected 함수 ( set_unexpected )
2. shared_ptr reset 함수
</pre>

- 예외 안전성을 갖춘 함수의 보장 (guarantee) 종류
1. 기본적인 보장 : 함수 동작 중에 예외가 발생하면, 실행중인 프로그램에 관련된
모든 것들을 유효한 상태로 유지하겠다는 보장
2. 강력한 보장 : 함수 동작 중에 예외가 발생하면, 프로그램의 상태를 절대로
변경하지 않겠다는 보장
3. 예외불가 보장 : 예외를 절대로 던지지 않겠다는 보장, 약속된 동작은
언제나 끝까지 완수하는 함수

- 복사 후 맞바꾸기 ( copy and swap ) : 객체를 수정하고 싶을 때, 객체의 사본을 만들어 
사본을 수정한 후 성공적으로 완료되면 수정된 사본을 원본 객체와 맞바꾸는 방법

- 모든 함수를 강력한 보장을 제공하면 좋겠지만 현실적으로 효율이나 복잡성에서 생기는
비용으로 어렵다. 그러니 기본적인 보장을 우선적으로 하되 강력한 보장을 고려하는 방향으로
권함

- 어떤 함수가 제공하는 예외 안전성 보장의 강도는, 그 함수가 내부적으로 호출하는 함수들이
제공하는 가장 약한 보장을 넘지 않는다.

<pre>
지금까지 작성했던 코드들은 예외 안전성이 전혀 되지 않는 재래식 방식이었나라는 생각이 들었지만,
exception이나 throw를 안써봐서 그렇지 함수 내에서 발생할 수 있는 가능성은 체크했기에
나름 기본적인 예외 안전성은 제공하지 않나 싶다.
shared_ptr 대신 레퍼런스 카운트를 수동으로 체크하는 방식을 사용했는데 다음 프로젝트는
더 신경써서 개발해야겠다.
</pre>

### Item 30 : 인라인 함수는 미주알고주알 따져서 이해해 두자
*****

- 목적 파일 : 컴파일하거나 어셈블하여 생긴 파일 ( .obj 파일 )

- 인라인화 하지 않는 함수
1. 함수안에 루프가 있는 경우
2. 재귀 함수인 경우
3. 가상 함수인 경우
4. 함수의 주소를 취하는 함수가 있을 경우
5. 함수를 함수 포인터로 호출할 경우

- 인라인화는 작고, 자주 호출되는 함수만 하는 것을 권장.
이로 인해 디버깅 및 라이브러리의 바이너리 업그레이드가 용이해지고,
자칫 생길 수 있는 코드 비대화 현상을 최소화하며,
프로그램의 속력이 빨라질 수 있는 여지가 최고로 많아진다.

# 2019.11.12
<code> ~ page 256 </code>

### Item 31 : 파일 사이의 컴파일 의존성을 최대로 줄이자
*****

사전 컴파일 헤더

- 핸들 클래스 - pimpl 관용구를 사용하는 클래스

- 컴파일 의존성을 줄이는 방법은 정의와 선언을 분리하는 것이다. 핸들 클래스를 사용하는 방법이나 인터페이스 클래스를 사용하는 방법으로 가능하지만 그에 따르는 실행 시간 비용이나 메모리가 필요하다.

- 핸들 클래스의 비용
1. 구현부 객체에 접근하기 위한 간접화 연산
2. 구현부 객체의 포인터를 저장을 위한 포인터 공간
3. 구현부의 동적 할당 연산

- 인터페이스 클래스의 비용
1. 호출되는 함수가 전부 가상함수이기 때문에 가상 테이블 점프 비용
2. 자식 클래스의 가상 함수 테이블 포인터 저장 공간

- 핸들 클래스와 인터페이스 클래스는 인라인 함수를 사용할 수 없다.

<pre>
pimpl 방식은 써보지 않았지만,
애초에 원래 개발하던 방식이 상속에 의존하기 때문에 가상 함수 테이블 포인터가 없는 클래스가 없다.
인터페이스 방식을 사용한 것 같은데 의존성에 대해 깊게 생각하면서 개발하진 않았다.
게임이 성능을 중요시하지만 개발 편리성이나 개발 시간외의 시간 비용도 중요하게 생각할 것 같다.
오히려 후자를 더 중요시 할수도..
https://www.slideshare.net/devcatpublications/ndc2010-unity-build 읽어보기
</pre>

## Chapter 6 - 상속, 그리고 객체 지향 설계

### Item 32 : public 상속 모형은 반드시 "is-a"를 따르도록 만들자.
*****

- public 상속의 의미는 "is-a"이기 때문에 기본 클래스에 적용되는 모든 것들이 파생 클래스에
그대로 적용되어야 한다. 모든 파생 클래스는 기본 클래스 객체의 일종이기 때문에
(ex: class Square : public Rectangle )

### Item 33 : 상속된 이름을 숨기는 일은 피하자
*****

- 컴파일러가 이름을 찾을 때, 안쪽에서 바깥쪽으로 찾기 때문에 가려지는 경우가 발생한다.

- 기본 클래스를 상속 받을 때, 오버로드 된 함수가 기본 클래스에 있고 이 함수들 중 몇개만
재정의하고 싶다면, 각 이름에 대해 using 선언을 붙여 줘야 한다. 

- 전달 함수 ( forwarding function ) - 파생 클래스에서 기본 클래스의 함수를 호출하는 함수
> ex : virtual void mf1() { Base::mf1(); }

### Item 34 : 인터페이스 상속과 구현 상속의 차이를 제대로 파악하고 구별하자
*****

- 순수 가상 함수도 정의할 수 있고, 접근하기 위해선 클래스 이름을 한정자로 붙여 줘야 한다.

- 상속되는 함수의 종류와 특징
1. 순수 가상 함수 : 인터페이스만 제공하며 파생 클래스에게 재정의를 유도(강제)한다.
2. 기본 가상 함수 : 인터페이스와 구현부를 제공한다. 사용자는 기본 클래스의 함수와 재정의 함수를
선택할 수 있다.
3. 비가상 함수 : 파생 클래스가 인터페이스와 더불어 '필수적인 구현'을 제공한다.

- 기본 가상 함수는 기본 동작을 원하지 않을 때에도 물려 받는 단점이 있다. 아래의 방법을 통해 
파생 클래스는 물려받거나 재정의할 수 있다.

1. 가상 함수의 구현부를 비가상 기본 함수로 제공하고 가상 함수를 순수 가상 함수로 바꾸는 방법
2. 가상 함수를 순수 가상 함수로 바꾸고 순수 가상 함수를 정의하는 방법

- **가상 함수는 비용이 필요하지만 전체 실행 시간의 80%가 소모되는 부분이 전체 코드의 20%밖에
되지 않는 다는 법칙처럼 가상 함수의 비용을 상쇄할만큼의 진짜 큰 차이를 만드는 20%의 코드를
만드는 데에 집중해보는 것**

<pre>
정리한 내용만 보면 기본 가상 함수보단 순수 가상 함수가 더 좋아보인다.
생각해보면 꼭 기본 가상 함수를 써야 하는 경우가 많은가? 라는 의문이 든다.
</pre>

# 2019.11.13
<code> ~ page 294 </code>

### Item 35 : 가상 함수 대신 쓸 것들도 생각해 두는 자세를 시시때때로 길러 두자
*****

<pre>
**찾아보기**
1. 템플릿 메서드 패턴
2. std::bind 더 찾아보기
</pre>

- 비가상 함수 인터페이스( non-virtual interface : NVI ) 

- **상속받은 private 가상 함수를 파생 클래스가 재정의 할 수 있다.**

- NVI 관용구는 가상 함수를 private으로 선언하고 이 가상 함수를 감싸는 랩퍼( wrapper )로 호출한다. NVI는 
가상함수를 호출할 때 사전 검사와 사후 검사를 할 수 있다.

- 컴파일러가 호출할 함수를 찾을 때 순서
1. 이름 조회 - 범위를 늘려가며 찾음
2. 오버로드 해소 - 매개변수가 가장 일치하는 함수
3. 접근성 점검 - 그 함수에 접근할 수 있는가?

- tr1::function을 사용하면 함수 포인터의 반환 값과 매개변수 타입에 암시적 변환이 가능한 타입까지 넣을 수 있어
좀 더 일반화된 함수 포인터를 가질 수 있다.

- 가상 함수를 대체하는 방법
1. NVI 관용구 사용
2. 함수 포인터 멤버 변수
3. function 멤버 변수
4. 한쪽 클래스 계통에 속해 있는 가상 함수를 다른 쪽 계통에 속해 있는 가상 함수로 대체

### Item 36 : 상속받은 비가상 함수를 파생 클래스에서 재정의하는 것은 절대 금물!
*****

- 비가상 함수를 재정의하여 가려지는 현상을 방지하자는 내용

### Item 37 : 어떤 함수에 대해서도 상속받은 기본 매개변수 값은 절대로 재정의하지 말자
*****

- 기본 매개변수를 갖는 가상 함수를 상속받은 파생 클래스가 기본 매개변수 값을 재정의해서 사용할 경우,
기본 매개변수는 정적 바인딩으로 정해지기 때문에 동적 타입과 상관 없이 정적 타입에 해당하는 기본 매개변수를 가지는
함수가 호출된다.

### Item 38 : "has-a" 혹은 "is-implemented-in-terms-ㅐf"를 모형화할 때는 객체 합성을 사용하자
*****

- 소프트웨어의 응용 영역 : 일상생활에서의 사물
- 소프트웨어의 구현 영역 : 응용 영역 외의 나머지 ( 버퍼, 뮤텍스, 탐색 등 )

- 응용 영역에서의 객체 함성은 "has-a"이고 구현 영역에서의 객체 합성은 "is-implemented-in-terms-of"이다.

### Item 39 : private 상속은 심사숙고해서 구사하자
*****

- EBO ( empty base optimization ) : 공백 기본 클래스 최적화

- private 상속은 거의 사용되지 않지만 생각해볼 수 있는 조건은 있다.
1. protected 멤버에 접근해야 할 경우
2. 상속받은 가상 함수를 재정의해야 할 경우 ( 굳이?? private 가상 함수가 아니라면 필요없을 거 같다. )
3. EBO를 활성화하고자 할 때

### Item 40 : 다중 상속은 심사숙고해서 사용하자
*****

- 상속할 때 가상 상속도 가능한데, 크기, 속도, 복잡도가 커져서 웬만해서는 쓰지 않는 게 좋지만 멤버 변수가 없는
자바의 인터페이스에서는 나름 실용적일 수 있다.

- 다중 상속을 쓸만한 경우는 인터페이스 클래스를 public으로 구현 클래스를 private으로 상속받는 경우가 있다.

# 2019.11.14
<code> ~ page 320 </code>

## Chapter 7 - 템플릿과 일반화 프로그래밍

- 일반화 프로그래밍 : 조작할 객체의 타입과 상관없이 코드를 작성하도록 하는 개념

- 튜링 완전성 (turing-complete) : 범용 튜링 기계와 동등한 계산 능력을 갖고 있는 어떤 추상 기계 혹은
프로그래밍 언어의 성질

### Item 41 : 템플릿 프로그래밍의 천릿길로 암시적 인터페이스와 컴파일 타임 다형성부터
*****

- 함수 시그니처 : 함수 이름, 매개변수, 반환 값

- 클래스를 객체화할 때, 인터페이스는 명시적이며 함수의 시그니처를 중심으로 구성되어 있고,
다형성은 프로그램 실행 중에 가상 함수를 통해 나타난다.

- 템플릿 매개변수의 경우, 인터페이스는 암시적이며 **유효 표현식**에 기반을 두어 구성되며,
다형성은 컴파일 중에 템플릿 인스턴스화와 함수 오버로딩 모호성 해결을 통해 나타난다.

<pre>
지금까지 템플릿을 사용하면서 템플릿을 위해 연산자 오버로딩한다던지 반환 값을 맞춰준 적이 없었는데
템플릿이 암시적 인터페이스를 사용해서 그런거였군
</pre>

### Item 42 : typename의 두 가지 의미를 제대로 파악하자
*****

- 의존 이름 ( dependent name ) : 템플릿 매개변수에 종속된 것

- 중첩 의존 이름은 구문분석기에 의해 처리될 때 타입이라고 알려 주지 않는 한 그 이름이
타입이 아니라고 가정한다.

- 중첩 의존 타입을 식별하는 용도에는 반드시 typename을 사용하여야 한다. 단, 중첩 의존 이름이
기본 클래스 리스트에 있거나 멤버 초기화 리스트 내의 기본 클래스 식별자로 있는 경우는 예외

### Item 43 : 템플릿으로 만들어진 기본 클래스 안의 이름에 접근하는 방법을 알아 두자
*****

- 컴파일러는 템플릿으로 만들어진 기본 클래스를 탐색해 상속된 이름을 찾는 것을 거부한다.
컴파일러에게 템플릿화된 기본 클래스의 유효범위를 탐색하라고 알려줘야 찾음.

- 템플릿화된 기본 클래스에 접근하는 방법
1. **this->를 사용한 접근**
2. using으로 접근할 함수를 선언
3. --호출할 함수가 기본 클래스 함수라는 점을 명시적으로 지정-- ( 가상 함수일 경우 가상 함수 바인딩이 무시되기 때문에
추천하지 않음 )

- 파생 클래스가 템플릿으로부터 객체화될 때 컴파일러는 '이른 진단'에서 기본 클래스 멤버에 대한  참조가
무효한지 진단하기 때문에 기본 클래스의 내용에 대해 모르는 것으로 가정한다.

### Item 44 : 매개변수에 독립적인 코드는 템플릿으로부터 분리시키자
*****

- 코드 비대화 ( cnode bloat )

- 공통성 및 가변성 분석 ( commonality and variability analysis )

- 작업 세트 : 한 프로세스에서 자주 참조하는 페이지 집합. 한 프로세스에서 주 메모리에 올라갈 수 있는 페이지의 양을 나타낸다.

- 여러 버전으로 만들어지는 템플릿은 상수 전파 등의 최적화를, 한 가지 버전으로 만들어지는 템플릿은 작업 세트가 작아져
참조 지역성이 향상되는 장점을 가지고 있다.

# 2019.11.15
<code> ~ page 358 </code>

### Item 45 : "호환되는 모든 타입"을 받아들이는 데는 멤버 함수 템플릿이 직방!
*****

- 일반화 복사 생성자 ( generalized copy constructor ) : 같은 템플릿으로 객체화되지만 타입이 다른 타입의 객체로
부터 원하는 객체를 만들어주는 생성자

- 일반화된 복사 생성자와 대입 연산을 위해 멤버 템플릿을 선언해도, 기본 복사 생상자와 대입 연산자는 직접
선언해야 한다.

<pre>
템플릿 객체 생성시 기본 생성자여도 ()를 붙이면 안된다.
객체 생성조차 안되서 이거때문에 실습하다가 많이 헤맸다.
</pre>

### Item 46 : 타입 변환이 바람직할 경우에는 비멤버 함수를 클래스 템플릿안에 정의해 두자
*****

- 템플릿 인자 추론 과정에서 암시적 타입 변환이 고려되지 않는다.

- 함수 템플릿의 템플릿 인자 추론을 객체의 프렌드 함수로 두면 피할 수 있다.

### Item 47 : 타입의 대한 정보가 필요하다면 특성정보 클래스를 사용하자
*****

- 반복자 종류
1. 입력 반복자 ( istream_iterator ) : 한번에 한칸씩 전진만 가능, 같은 위치에 대해 읽기만 1번 가능
2. 출력 반복자 ( ostream_iterator ) : 한번에 한칸씩 전진만 가능, 같은 위치에 대해 쓰기만 1번 가능
3. 순방향 반복자 ( forward_iterator ) : 입출력 반복자 + 여러번 가능
4. 양방향 반복자 ( bidirectional iterator ) : 순방향 반복자 + 뒤로 가기 가능
5. 임의 접근 반복자 ( random access iterator ) : 양방향 반복자 + 산술 연산 가능

- 특성정보 ( traits ) : 컴파일 도중에 어떤 주어진 타입의 정보를 얻을 수 있게 하는 객체를 지칭하는 개념.
특성정보는 구조체로 구현하는 것이 관례이며 특성 정보를 다루는 표준적인 방법은 해당 특성정보를 템플릿 및
그 템플릿의 1개 이상의 특수화 버전에 넣는 것이다.

- 함수 오버로딩 기법과 결합하여 특성정보 클래스를 사용하면 컴파일 타임에 결정디는 타입별 if else 점검문을
구사할 수 있다.

### Item 48 : 템플릿 메타프로그래밍, 하지 않겠는가?
*****

- TMP ( template metaprogramming ) 템플릿 메타 프로그래밍 : 컴파일 도중에 실행되는 템플릿 기반의 
프로그램을 작성하는 일. TMP의 강점은 까다롭거나 불가능한 일을 굉장히 쉽게 만들 수 있고, 컴파일 타임에 실행되기
때문에 기존 작업을 런타임 영역에서 컴파일 타임 영역으로 전환할 수 있다.

- traits는 TMP이고 typeid에 비해 컴파일 타임에 실행되서 빠르다.

- TMP는 재귀 함수 호출을 만들지 않고 재귀식 템플릿 인스턴스화를 한다.

- 치수 단위 ( dimensional unit )의 정확성 확인 : 치수 단위의 조합이 똑바로 되어야 하는 것이 최우선.
모든 치수 단위의 조합이 제대로 됐는지 컴파일 동안에 볼 수 있다.

- 행렬 연산의 최적화 : 표현식 템플릿 ( expression template )을 사용해 덩치 큰 임시 객체를 없애고 루프도 합칠 수 있다.

- 맞춤식 디자인 패턴 구현의 생성 : 전략 패턴, 감시자 패턴, 방문자 패턴 등 구현 방법이 다양하지만 
정책 기반 설계 ( policy-based design)를 사용하면 따로따로 마련된 설계상의 선택(정책)을 나타내는 템플릿을 만들 수 있고,
생성식 프로그래밍 ( generative programming )의 기초 기술로 사용된다.

## Chapter 8 - new와 delete를 내 맘대로

- new-handler ( new 처리자 ) : 사용자의 메모리 요구를 operator new가 맞추어 주지못했을 때 호출되는 함수
( typedef void (*new-handler)() )

### Item 49 : new 처리자의 동작 원리를 제대로 이해하자
*****

- new 연산자는 메모리가 부족할 때 new 처리자를 호출하는데, 이 new 처리자를 사용자 정의할 수 있고,
객체마다 정의할 수도 있다.

- CRTP ( curiously recurring template pattern ) 신기하게 반복되는 템플릿 패턴

- new 처리자가 할 수 있는 동작이자 꼭 한가지는 해야하는 동작
1. 사용할 수 있는 메모리를 더 많이 확보합니다.
2. 다른 new 처리자를 설치합니다.
3. new 처리자의 설치를 제거합니다.
4. 예외를 던집니다.
5. 복귀하지 않습니다.

<pre>
메모리가 부족했던 경험이 없기도 하고 64비트 기반으로 넘어오면서 더 힘들긴 하다.
하지만 게임의 사양을 고려했을 때 정해둔 메모리가 있다면 그 메모리를 넘어섰을 경우를 대비해 new 연산자를
재정의하는 것이 필요할 것이다.
</pre>

# 2019.11.16
<code> ~ page 397 </code>

### Item 50 : new 및 delete를 언제 바꿔야 좋은 소리를 들을지를 파악해 두자
*****

- new 와 delete를 재정의하는 이유
1. 잘못된 힙 사용을 탐지하기 위해 : 오버런과 언더런을 탐지할 메모리를 양쪽 끝에 추가로 할당하고 바꿔었는지
확인하는 방식
2. 효율 향상을 위해 : 힙 단편화이나 속도, 메모리 차원에서 빠르게 설계할 수 있다.
3. 동적 할당 메모리의 실제 사용에 관한 통계 정보를 수집하기 위해
4. 할당 및 해제 속력을 높이기 위해
5. 기본 메모리 관리자의 공간 오버헤드를 줄이기 위해
6. 적당히 타협한 기본 할당자의 바이트 정렬 동작을 보장하기 위해
7. 임의의 관계를 맺고 있는 객체들을 한 군데에 나란히 모아 놓기 위해 : 메모리 군집화는 위치 지정 new 와 delete로
구현할 수 있다.
8. 상황에 따라 원하는 동작을 수행하기 위해

- 부스트의 풀 ( pool ) 라이브러리

- 사용자 정의 new와 delete를 작성하는 데는 수행 성능을 향샹시키려는 목적, 힙 사용 시의 에러를 디버깅하려는 목적,
힙 사용 정보를 수집하려는 목적 등이 포함된다.

### Item 51 : new 및 delete를 작성할 때 따라야 할 기존의 관례를 잘 알아 두자
*****

- new 연산자는 메모리 부족시 new 처리자 함수를 호출해야 되고, 크기가 없는 메모리 요청에 대한 대비책을 갖추어야 한다.
또한 기본 new 연산자가 가려지지 않도록 해야한다.

- 기본 new 연산자는 루프를 가지고 있어 메모리 할당에 성공하거나 new 처리자가 다양한 방법 중 하나를 해주어야 루프에서
나올 수 있다.

- new[] 연산자는 원시 메모리 덩어리를 할당하는 것 밖엔 해줄 일이 없다. 객체가 얼마나 큰지 확정할 수 없고, 배열의
갯수를 저장할 메모리도 추가적으로 들어가기 때문에 요구한 메모리와 다르기 때문이다.

- delete 연산자는 nullptr 확인만 해주면 되고 클래스 버전이라면 클래스 크기와 비교해서 실행한다. 이때 기본 클래스의
소멸자가 가상 소멸자가 아니라면 delete 연산자가 정상적으로 동작하지 않을 수 있다.

### Item 52 : 위치지정 new를 작성했다면 위치지정 delete도 같이 준비하자
*****

- 위치지정 ( placement ) new : 추가 매개변수를 받는 new이며, 객체를 생성시킬 메모리 위치를 나타내는 포인터를 매개변수로 
받는 형태가 유용하다. std::vector가 원조임.

- new 연산자 실행 중 생성자 호출과정에서 예외가 발생하면 컴파일러는 new 연산자와 짝을 이루는 delete 연산자를 찾게 된다.
찾게 되면 delete 연산자를 호출해 할당한 메모리를 해제하지만 찾지 못하면 메모리 누수가 발생한다. 위치지정 delete 연산자는
new 연산자 실행 중 예외가 발생할 때만 호출되며 기본적인 delete 호출에서는 절대 호출되지 않음.

- **클래스에 new 연산자를 선언하면 표준 new 연산자가 가려진다. 그래서 기본 클래스에서 표준 new 연산자를 호출하도록 만들고
파생 클래스에서 using을 통해 가려지는 현상을 막는다.**

## Chapter 9 - 그 밖의 이야기들

### Item 53 : 컴파일러 경고를 지나치지 말자
*****

- 컴파일러 경고를 쉽게 지나치지말고 컴파일러가 지원하는 최고 경고 수준에도 경고 메세지를 내지 않고 컴파일되는 코드를
만드는 방향이 좋다. 다만 경고에 너무 기대면 컴파일러마다 경고하는 부분이 다르기 때문에 주의해야 한다.

### Item 54 : TR1을 포함한 표준 라이브러리 구성요소와 편안한 친구가 되자
*****

- tr1 라이브러리
1. 스마트 포인터
2. function<>
3. bind
4. hash table ( unordered_map ... )
5. 정규 표현식 ( regular expression )
6. 튜플 ( tuple )
7. array : begin, end를 지원하는 배열로 컴파일 과정에서 고정되어 동적 메모리를 사용하지 않음.
8. mem_fn
9. reference_wrapper
10. 난수 발생
11. 특수 용도의 수학 함수
12. 타입 특성정보 ( type traits ) : 컴파일 타임 정보를 제공하며 T가 기본제공 타입인지, 가상 소멸자를 지원하는지,
공백 클래스인지, 다른 U 타입으로 암시적 변환이 가능한지, 타입의 적절한 바이트 정렬 확인 등의 정보를 확인할 수 있다.
13. result_of : 어떤 함수 호출의 반환 타입을 추론해 주는 템플릿

- namespace tr1 = ::boost; 는 tr1을 boost 네임스페이스의 별칭으로 설정하는 방법이다.

### Item 55 : 부스트를 늘 여러분 가까이에
*****

- 컨버전 ( Conversion ) : numeric_cast, lexical_cast

- 규모가 큰 라이브러리로 부스트 그래프 라이브러리와 부스트 MPL 라이브러리가 있다.

- 타입리스트 ( typelist )

- 타 언어와의 연동 지원

<pre>
항목 54, 55는 찾아보는 형식으로 해야 될 것 같다.
책을 다 읽었지만 기억에 남는 것은 사실 많지 않다.
복습하고 다시 읽고 해야겠지만 정리 해둔 내용으로 복습하고
후에 필요한 내용에 대해 기억이 안난다면 정리 내용을 보고
이해가 부족하다면 책을 다시 읽는 방법이 맞는 것 같다.
</pre>





















