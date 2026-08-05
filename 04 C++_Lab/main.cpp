/***********************************************************/
// [1-1] C++ 표준 console 출력
/***********************************************************/

#if 0
#include <iostream>

int main()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << "i * i = " << i * i << " 입니다\n";
		std::cout << "i * i = " << i * i << " 입니다" << std::endl;
	}

	return 0;
}
#endif

/***********************************************************/
// [1-2] Namespace와 :: 연산자
/***********************************************************/

#if 0
#include <iostream>

int x, y;

namespace my
{
	int x, y;

	int func(int a, int b)
	{
		return a + b;
	}
}

namespace your
{
	int x, y;

	int func(int a, int b)
	{
		return a - b;
	}
}

int main()
{
	my::x = 10, my::y = 20;
	std::cout << my::func(my::x, my::y) << std::endl;

	x = 5, y = 10;
	your::x = 100, your::y = 200;
	std::cout << your::func(x, y) << std::endl;

	return 0;
}
#endif

/***********************************************************/
// [1-3-1] using directive를 이용한 namespace 사전 지정
/***********************************************************/

#if 0
#include <iostream>

namespace my
{
	int x, y;

	int func(int a, int b)
	{
		return a + b;
	}
}

namespace your
{
	int x, y;

	int func(int a, int b)
	{
		return a - b;
	}
}

int main()
{
	using namespace my;

	x = 10, y = 20;
	your::x = 100, your::y = 200;
	std::cout << func(x, y) << std::endl;

	return 0;
}
#endif

/***********************************************************/
// [1-3-2] using declarataion을 이용한 namespace 사전 지정
/***********************************************************/

#if 0
#include <iostream>

namespace my
{
	int x, y;

	int func(int a, int b)
	{
		return a + b;
	}
}

namespace your
{
	int x, y;

	int func(int a, int b)
	{
		return a - b;
	}
}

int main()
{
	using my::x;
	using my::y;

	my::x = 10, y = 20;
	std::cout << my::func(x, y) << std::endl;

	return 0;
}
#endif

/***********************************************************/
// [1-4] std를 생략하기 위한 using의 사용
/***********************************************************/

#if 0
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	std::cout << "Hello 1\n";
	cout << "Hello 2" << endl;
	printf("hello 3\n");
	std::printf("hello 4\n");

	return 0;
}
#endif

/***********************************************************/
// [1-5] in/out manipulator
/***********************************************************/

#if 0
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int a = 100;

	cout << hex << a << " " << dec << a << " " << oct << a << endl;
	cout << showbase << uppercase << hex << a << " " << dec << a << " " << oct << a << endl;
	cout << a << endl;
	cout << setw(8) << dec << a << endl;
	cout << setw(8) << -100 << " " << setfill('*') << left << setw(8) << dec << a << endl;
	cout << a << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-6] C++ 표준 console 입력
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int main()
{
	int x;

	cout << "정수 값 입력 ";
	cin >> x;
	cout << "입력은 " << x << " 입니다" << endl;

	cout << "16진수 값 입력 ";
	cin >> hex >> x;
	cout << "입력은 " << x << " 입니다" << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-7] C++ 표준 console 입력 : 여러 정수 값 받기
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int main()
{
	int x, y, z;

	cout << "정수 3개 입력 ";
	cin >> x >> y >> z;
	cout << " x = " << x << " y = " << y << " z = " << z << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-8-1] 문자열 입력 받기(공백 포함 받기)
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int main()
{
	double d;
	char s[20];
	 
	cout << "실수 값 입력 ";
	cin >> d;
	cout << d << endl;

	cout << "두 단어 입력(Hello World)" << endl;
	cin >> s;
	cout << s << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-8-2] cin.getline으로 문자열 입력 받기
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int main()
{
	double d;
	char s[20];

	cout << "실수 값 입력 ";
	cin >> d;
	cout << d << endl;

	cout << "두 단어 입력(Hello World)" << endl;
	cin.getline(s, 20);
	cout << s << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-8-3] cin.ignore()
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int main()
{
	double d;
	char s[20];

	cout << "실수 값 입력 ";
	cin >> d;
	cout << d << endl;
	
	cin.ignore();

	cout << "두 단어 입력(Hello World)" << endl;
	cin.getline(s, 20);
	cout << s << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-9] 상수 표현, 변수 초기화
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

struct st
{
	int a = -10;
	char b;
};

int main()
{
	int a = 0b1010;
	int b(20);
	int c{ 30 };

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;

	int d[2] = { 40,50 };
	int e[2]{ 60,70 };

	struct st f = { 80, 'A' };
	st g{ 90, 'B' };

	cout << d[1] << endl;
	cout << e[1] << endl;
	cout << f.a << endl;
	cout << g.b << endl;
}
#endif

/***********************************************************/
// [1-10] 함수의 Default Parameter
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int f1(int a, int b = 10, int c = 20)
{
	return a + b + c;
}

int f2(int x, int y = 10, int z = 20);

int main()
{
	cout << f1(10, 100, 200) << endl;
	cout << f1(10, 100) << endl;
	cout << f1(10) << endl;

	cout << f2(10, 100, 200) << endl;
	cout << f2(10, 100) << endl;
	cout << f2(10) << endl;

	return 0;
}

int f2(int xx, int yy, int zz)
{
	return xx + yy + zz;
}
#endif

/***********************************************************/
// [1-11] 함수 Overloading
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int f(int a)
{
	return a * a;
}

int f(int x, int y)
{
	return x * y;
}

void f(double x)
{
	cout << x << endl;
}

double f(double x, double y)
{
	return x + y;
}

int main()
{
	cout << f(10) << endl;
	cout << f(10, 20) << endl;
	f(3.14);
	cout << f(3.14, 5.5) << endl;
	cout << f(3, 5.5) << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-12] Parameter 타입의 Template 지정
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

template<typename T>
T f1(T x, T y)
{
	return x + y;
}

template<typename myT>
myT f2(myT x, int y)
{
	return x + y;
}

template<typename myT>
int f3(myT x, int y)
{
	return x + y;
}

template<typename T1, typename T2>
auto f4(T1 x, T2 y){
	return x*y;
}

int main()
{
	cout << f1(10, 20) << endl;
	cout << f1(3.14, 5.5) << endl;

	cout << f2<int>(10, 20) << endl;
	cout << f2<double>(3.14, 30) << endl;

	cout << f3<int>(10, 20) << endl;
	cout << f3<double>(3.14, 30) << endl;

	cout << f4<double, int>(3.14, 30) << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-13] 동적 메모리 할당(new, delete)
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

struct _st
{
	int a;
	char b;
};

int main()
{
	int * p = new int;
	char * q = new char[4];
	int (*r)[4] = new int[3][4];
	_st * x = new _st[2];

	p[0] = 10;
	q[3] = 'A';
	r[2][3] = 100;
	x[1].b = 'B';

	cout << p[0] << endl;
	cout << q[3] << endl;
	cout << r[2][3] << endl;
	cout << x[1].b << endl;

	delete p;
	delete[] q;
	delete[] r;
	delete[] x;

	return 0;
}
#endif

/***********************************************************/
// [1-14] inline 함수
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

inline int f(int x)
{
	return x * x;
}

int main()
{
	cout << f(3) << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-15] refernce &의 의미
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int main()
{
	int a = 10;
	int &b = a;
	int *p = &a;

	b = 20;
	cout << a << " " << b << endl;
	*p = 30;
	cout << a << " " << *p << endl;

	return 0;
}
#endif

/***********************************************************/
// [1-16] Call by reference와 & Modifier
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

void f1(int x)
{
	x = 10;
}

void f2(int *p)
{
	p[1] = 20;
}

void f3(int &r)
{
	r = 30;
}

void f4(const int &s)
{
	cout << s << endl;
}

int main()
{
	int a[4] = { 1,2,3,4 };

	f1(a[0]);
	f2(a);
	f3(a[2]);

	cout << a[0] << endl;
	cout << a[1] << endl;
	cout << a[2] << endl;

	f4(a[3]);

	return 0;
}
#endif

/***********************************************************/
// [1-17] ranged for
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int main()
{
	int a[4] = { 1,2,3,4 };

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		cout << a[i] << endl;
	}

	for (int x : a)
	{
		cout << x << endl;
	}

	return 0;
}
#endif

/***********************************************************/
// [1-18] auto 타입, bool 타입
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

char func() 
{
	return 'X';
}

int main()
{
	auto a = 100;
	auto b = 3.14;
	bool c = false;
	bool d = ((10 < 20) == true);
	auto e = func();
	int f[] = { 1,3,5, };

	cout << e << endl;
	cout << c << ":" << d << endl;

	for (const auto &x : f)
	{
		cout << x << endl;
	}

	return 0;
}
#endif

/***********************************************************/
// [2-1-1] Procedural Oriented Programming 방식
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int total = 0;

void mart_calc(int price)
{
	total += price;
}

int main(void)
{
	mart_calc(10);
	cout << "total=" << total << endl;

	mart_calc(20);
	cout << "total=" << total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-1-2] Procedural의 공동 사용시 고려할 점
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int total[4] = { 0,0,0,0 };

void mart_calc(int user, int price)
{
	total[user] += price;
}

int main(void)
{
	mart_calc(0, 10);
	mart_calc(0, 20);
	cout << "total[0]=" << total[0] << endl;

	mart_calc(1, 200);
	cout << "total[1]=" << total[1] << endl;

	mart_calc(0, 50);
	cout << "total[0]=" << total[0] << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-2] 구조체를 이용한 Object 생성
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

struct _st
{
private:
	double irate = 0.02;

	void disp_total(void)
	{
		cout << total << endl;
	}

public:
	double total = 0;

	double func(int x)
	{
		total += x * (1 + irate);
		disp_total();
		return total;
	}
};

int main()
{
	_st y;

	cout << y.func(50) << endl;
	cout << y.func(100) << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-3] 기본 Class, Object(Instance) 생성 및 사용
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class mart_calc
{
public:
	int total = 0;

	void buy(int price)
	{
		total += price;
	}
};

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.buy(10);
	calc1.buy(20);
	cout << calc1.total << endl;

	calc2.buy(200);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-4] Member Function을 외부에 정의
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class mart_calc
{
private:
	double tax = 0.01;
	void disp_total(void);

public:
	double total = 0;
	void buy(int price);
};

void mart_calc::disp_total(void)
{
	cout << "total=" << total << endl;
}

void mart_calc::buy(int price)
{
	total += price * (1 + tax);
	disp_total();
}

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.buy(10);
	calc1.buy(20);
	cout << calc1.total << endl;

	calc2.buy(200);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-5] change_tax method 구현
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class mart_calc
{
private:
	double tax = 0.01;

public:
	double total = 0;
	void buy(int price);
	void change_tax(double tax);
};

void mart_calc::buy(int price)
{
	total += price * (1 + tax);
}

void mart_calc::change_tax(double tax)
{
	// class의 private 변수 tax를 전달 받은 값으로 변경
	// mart_calc::tax = tax;
	this->tax = tax;
}

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.change_tax(0.02);

	calc1.buy(10);
	calc1.buy(20);
	cout << calc1.total << endl;

	calc2.buy(200);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-6] Parameter와 Member의 이름이 같을 경우 해결 방법
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class mart_calc
{
private:
	double tax = 0.01;

public:
	double total = 0;
	void buy(int price);
	void change_tax(double tax);
};

void mart_calc::buy(int price)
{
	total += price * (1 + tax);
}

void mart_calc::change_tax(double tax)
{
	mart_calc::tax = tax;
}

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.change_tax(0.02);

	calc1.buy(10);
	calc1.buy(20);
	cout << calc1.total << endl;

	calc2.buy(200);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-7] change_tax method 구현 : this 이용
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class mart_calc
{
private:
	double tax = 0.01;

public:
	double total = 0;
	void buy(int price);
	void change_tax(double tax);
};

void mart_calc::buy(int price)
{
	total += price * (1 + tax);
}

void mart_calc::change_tax(double tax)
{
	this->tax = tax;
}

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.change_tax(0.02);

	calc1.buy(10);
	calc1.buy(20);
	cout << calc1.total << endl;

	calc2.buy(200);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-8] buy method overloding
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class mart_calc
{
private:
	double tax = 0.01;

public:
	double total = 0;
	void buy(int price);
	void buy(int price, double tax);
};

void mart_calc::buy(int price)
{
	total += price * (1 + tax);
}

void mart_calc::buy(int price, double tax)
{
	total += price * (1 + tax);
}

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.buy(10);
	calc1.buy(20, 0.1);
	cout << calc1.total << endl;

	calc2.buy(200, 0.1);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-9] default parameter를 사용한 buy method
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class mart_calc
{
public:
	double total = 0;
	void buy(int price, double tax = 0.01);
};

// member function buy 설계
void mart_calc::buy(int price, double tax){
	this->total += price * (1 + tax);
	
}

int main(void)
{
	mart_calc calc1;
	mart_calc calc2;

	calc1.buy(10);
	calc1.buy(20, 0.1);
	cout << calc1.total << endl;

	calc2.buy(200, 0.1);
	cout << calc2.total << endl;

	calc1.buy(50);
	cout << calc1.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-10] 생성자에 의한 초기화
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int rent_count = 0;

class mart_calc
{
public:
	double total = 0;

	mart_calc(int price)
	{
		rent_count++;
		total += price;
	}

	void buy(int price);
};

void mart_calc::buy(int price)
{
	total += price;
}

int main(void)
{
	mart_calc calc1(10);
	mart_calc calc2(100);

	cout << "CNT=" << rent_count << endl;

	calc1.buy(10);
	calc1.buy(20);
	cout << calc1.total << endl;

	calc2.buy(200);
	cout << calc2.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-11] Constructor 실행 및 Overloading
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class buf
{
public:
	int * p;

	buf()
	{
		p = new int[4];
	}

	buf(int size)
	{
		p = new int[size];
	}

	void wr_buf(int i, int v)
	{
		p[i] = v;
	}
};

int main(void)
{
	buf x;
	// buf y();		// 이렇게 하면 문제
	buf z(10);

	x.wr_buf(3, 100);
	z.wr_buf(9, 200);

	cout << x.p[3] << " " << z.p[9] << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-12] 모든 parameter가 default인 constructor
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class buf
{
public:
	int * p;

	buf(int size = 4)
	{
		cout << "H" << endl;
		p = new int[size];
	}

	void wr_buf(int i, int v)
	{
		p[i] = v;
	}
};

int main(void)
{
	buf x;
	buf y;
	buf z(10);

	x.wr_buf(3, 100);
	y.wr_buf(3, 100);
	z.wr_buf(9, 200);

	cout << x.p[3] << endl;
	cout << y.p[3] << endl;
	cout << z.p[9] << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-13] 소멸자(destructor)에 의한 Object 삭제
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int rent_count = 0;

class mart_calc
{
public:
	double total = 0;

	mart_calc(int price)
	{
		rent_count++;
		total += price;
	}

	~mart_calc()
	{
		rent_count--;
	}

	void buy(int price)
	{
		total += price;
	}
};

// 만약 이렇게 calc0를 전역에서 선언 했다면? 어떻게 될까?
// mart_calc calc0(10);

int main(void)
{
	{
		mart_calc calc1(10);
		{
			mart_calc calc2(100);

			cout << "CNT=" << rent_count << endl;

			calc1.buy(10);
			calc1.buy(20);
			cout << calc1.total << endl;

			calc2.buy(200);
			cout << calc2.total << endl;
		}
		cout << "CNT=" << rent_count << endl;
	}

	cout << "CNT=" << rent_count << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-14] Instance 배열, 포인터 생성
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class buf
{
public:
	int p[4];

	void wr_buf(int i, int v)
	{
		p[i] = v;
	}
};

int main(void)
{
	buf x;
	buf y[2];
	buf *z = new buf;

	x.wr_buf(3, 100);
	y[1].wr_buf(3, 200);
	z->wr_buf(2, 300);
	(*z).wr_buf(3, 400);

	cout << x.p[3] << endl;
	cout << y[1].p[3] << endl;
	cout << z->p[2] << endl;
	cout << (*z).p[3] << endl;

	delete z;

	cout << x.p[3] << endl;
	cout << y[1].p[3] << endl;
	cout << z->p[2] << endl;
	cout << (*z).p[3] << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-15] 정적 멤버 => static member data(class 변수)
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class mart_calc
{
public:
	static int rent_count;
	static int sales_total;
	double total = 0;

	mart_calc(int price)
	{
		rent_count++;
		total += price;
		sales_total += price;
	}

	void buy(int price)
	{
		total += price;
		sales_total += price;
	}
};

int mart_calc::rent_count = 0;
int mart_calc::sales_total = 0;

int main(void)
{
	mart_calc calc1(10);
	mart_calc calc2(100);

	cout << "CNT=" << mart_calc::rent_count << endl;
	cout << "CNT=" << calc1.rent_count << endl;

	calc1.buy(10);
	calc1.buy(20);
	cout << calc1.total << endl;

	calc2.buy(200);
	cout << calc2.total << endl;

	cout << "CNT=" << mart_calc::sales_total << endl;
	
	return 0;
}
#endif

/***********************************************************/
// [2-16] 정적 멤버 => static member function(class 함수)
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

void prt(void)
{
	cout << "Static Function" << endl;
}

class mart_calc
{
public:
	double total = 0;
	static int rent_count;

	mart_calc(int price)
	{
		rent_count++;
		total += price;
	}

	void buy(int price)
	{
		total += price;
	}

	static double get_total(void)
	{
		prt();
		return rent_count;
	}
};

int mart_calc::rent_count = 0;

int main(void)
{
	mart_calc calc1(10);
	mart_calc calc2(100);

	cout << calc1.total << endl;
	cout << calc2.total << endl;

	cout << "CNT=" << mart_calc::get_total() << endl;
	cout << "CNT=" << calc1.get_total() << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-17] 변수 종류 정리
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

int g = 10;

class A 
{
public:
	static int s;
	int i;

	A(int n): i(n) {}

	void fi(int p)
	{
		int l = 10;
		cout << "fi = " << g + s + i + p + l << endl;		
	}

	static void fc(int p)
	{
		int l = 20;
		cout << "fs = " << g + s + p + l << endl;
	}
};

int A::s = 50;

int main(void)
{
	A b(5);
	A c(-5);
	
	b.fi(100);
	c.fi(100);

	b.fc(200);
	c.fc(200);
	A::fc(200);

	cout << b.i << endl;
	cout << c.i << endl;	
	cout << b.s << endl;
	cout << c.s << endl;	
	cout << A::s << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-18] Instance 생성의 실체
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	int x, y;

	A(int xx = 3, int yx = 10): x(xx + 1), y(yx + 2) 
	{
		cout << "xx=" << xx << " A::x=" << A::x << endl;
	}
};

int main(void)
{
	int a;
	int b = 100;
	int c(200);

	A d;
	A e(500);
	A f = A(1000);

	cout << b << endl;
	cout << c << endl;
	cout << d.x << endl;
	cout << e.x << endl;
	cout << f.x << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-19] Constructor를 초기화 List로 사용하는 경우
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class student
{
public:
	const int age;
	const char * name;

	student(int a, const char * n): age(a), name(n)
	{
	}
};

int main(void)
{
	student x(10, "KIM");

	cout << x.age << endl;
	cout << x.name << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-20] 상수 멤버 함수(Const Member Function)
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class student
{
public:
	int age;

	student(int a) : age(a) {}

	int func(int inc) const
	{
		int r;

		inc++;
		r = age + inc;
		
		age = r;

		cout << age << " " << r << endl;
		return inc;
	}
};

int main(void)
{
	student x(10);

	cout << x.func(2) << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-21] const instnace의 제약 사항
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class student
{
public:
	int age;

	student(int a) : age(a) {}

	int func()	// 여기에 const를 붙이면 문법적으로 가능하도록 허용
	{
		cout << age << endl;
		return age;
	}
};

int main(void)
{
	const student x(10);

	x.age = 20;
	int r = x.func();

	cout << r << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-22] Const Member Function의 필요성
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class student
{
public:
	int age;

	student(int a) : age(a) {}

	int func() const
	{
		cout << age << endl;
		return age;
	}
};

int main(void)
{
	const student x(10);

	int r = x.func();

	cout << r << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-23] Class에서 Type Template 사용
/***********************************************************/

#if 00
#include <iostream>
using namespace std;

template <typename T> 
class mart_calc
{
public:
	double total = 0;

	mart_calc(T price)
	{
		total += price;
	}

	void buy(T price)
	{
		total += price;
	}
};

int main(void)
{
	mart_calc<int> a(10);
	mart_calc<double> b(3.5);

	a.buy(20.5);
	b.buy(10);

	cout << a.total << endl;
	cout << b.total << endl;

	return 0;
}
#endif

/***********************************************************/
// [2-24-1] class member pointer 및 member pointer 연산자
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A 
{
public:
	int p;
};

int main(void)
{
	A a;
	a.p = 10;

	int A::* pp = &A::p;

	cout << a.*pp << endl;
	a.p = 20;
	cout << a.*pp << endl;
	
	return 0;
}
#endif

/***********************************************************/
// [2-24-2] class member pointer 활용 예
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A {
public:
	int price = 10;
	int amount = 20;
};

void f(A &p, int A::* dst)
{
	cout << p.*dst << endl;
}

int main(void)
{
	A a;

	f(a, &A::price);
	f(a, &A::amount);

	return 0;
}
#endif

/***********************************************************/
// [3-1] Class 상속의 기본
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;
	const char * mission;
	int price;

	void set_car(const char * x, const char * y, int z)
	{
		model = x;
		mission = y;
		price = z;
	}
};

class truck : public car
{
public:
	double load;

	void set_info(double v)
	{
		load = v;
	}
};

class van : public car
{
public:
	int passenger;

	void set_info(int v)
	{
		passenger = v;
	}
};

int main(void)
{
	car a;
	truck b;
	van c;

	a.set_car("Sonata", "Auto", 1200);
	b.set_car("Bongo", "Manual", 900);
	b.set_info(2.5);
	c.set_car("Carnival", "Auto", 2400);
	c.set_info(11);
	
	cout << a.model << endl;
	cout << b.model << endl;
	cout << b.load << endl;
	cout << c.model << endl;
	cout << c.passenger << endl;

	return 0;
}
#endif

/***********************************************************/
// [3-2] 상속의 대상과 Access Modifier
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	int a = 10;
protected:
	int b = 20;
private:
	int c = 30;
};

class B : public A
{
public:
	int d = 40;

	void f(void)
	{
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
		cout << d << endl;
	}
};

int main(void)
{
	A aa;
	B bb;

	cout << aa.a << endl;
	cout << aa.b << endl;
	cout << aa.c << endl;

	cout << bb.a << endl;
	cout << bb.b << endl;
	cout << bb.c << endl;
	cout << bb.d << endl;

	bb.f();

	return 0;
}
#endif

/***********************************************************/
// [3-3] Derived Class의 상속 대상 접근성 지정
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public: 
	int a = 10;
protected: 
	int b = 20;
private: 
	int c = 30;
};

class B : public A 
{ 
public:
	void f()
	{
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
	}
};

class C : protected A
{
public:
	void f()
	{
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
	}
};

class D : private A
{
public:
	void f()
	{
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
	}
};

int main()
{
	B x;
	cout << x.a << endl;	// public
	cout << x.b << endl;	// protected
	cout << x.c << endl;	// private
	x.f();

	C y;
	cout << y.a << endl;	// protected
	cout << y.b << endl;	// protected
	cout << y.c << endl;	// private
	y.f();

	D z;
	cout << z.a << endl;	// private
	cout << z.b << endl;	// private
	cout << z.c << endl;	// private
	z.f();

	return 0;
}
#endif

/***********************************************************/
// [3-4] friend class, friend function 지정
/***********************************************************/

#if 0
#include <iostream>
using namespace std;	

class A
{
private:
	int a;

protected:

	void f()
	{
		cout << a << endl;
	}

	friend class B;
	friend void h();
};

class B
{
public:

	void g()
	{	
		A x;
		x.a = 40;
		x.f();
	}
};

void h()
{
	A x;
	x.a = 50;
	x.f();
}

int main()
{
	B y;
	y.g();
	h();

	return 0;
}
#endif

/***********************************************************/
// [3-5] 상속 Class의 constructor, destructor 동작 순서
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A" << endl;
	}
	~A()
	{
		cout << "~A" << endl;
	}
};

class B : public A
{
public:
	B()  // B() : A() => 이렇게 설계해도 무방(기본적으로 해 줌)
	{
		cout << "B" << endl;
	}
	~B()
	{
		cout << "~B" << endl;
	}
};

int main()
{
	B x;

	return 0;
}
#endif

/***********************************************************/
// [3-6-1] Base Class가 default constructor일 경우
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A" << endl;
	}
};

class B : public A
{
public:
	B(int x)
	{
		cout << "B:" << x << endl;
	}
};

int main()
{

	B b(3);

	return 0;
}
#endif

/***********************************************************/
// [3-6-2] Base Class가 default constructor가 아닐 경우
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	A(int n)
	{
		cout << "A" << n << endl;
	}
};

class B : public A
{
public:
	B(int x) : A(x + 1)
	{
		cout << "B:" << x << endl;
	}
};

int main()
{
	B x(3);
	B y(10);

	return 0;
}
#endif

/***********************************************************/
// [3-7] Derived Class에서 Base Constructor 사용 예
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;
	int price;

	car(const char * x, int z)
	{
		model = x;	
		price = z;
	}
};

class truck : public car
{
public:
	double load;

	truck(const char * x, int z, int v) : car(x, z)
	{
		load = v;
	}
};

class van : public car
{
public:
	int passenger;

	van(const char * x, int z, int v) : car(x, z)
	{
		passenger = v;
	}
};

int main(void)
{
	car a("Sonata", 1200);
	truck b("Bongo", 900, 2.5);
	van c("Carnival", 2400, 11);

	cout << a.model << endl;
	cout << b.model << endl;
	cout << b.load << endl;
	cout << c.model << endl;
	cout << c.passenger << endl;

	return 0;
}
#endif

/***********************************************************/
// [3-8] Class 포인터를 전달 받는 함수의 문제점
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;
	const char * mission;
	int price;
};

class truck : public car
{
public:
	double load;
};

class van : public car
{
public:
	int passenger;
};

void prt_price(truck *p)
{
	cout << p->price << endl;
}

int main(void)
{
	truck x;
	van y;

	x.price = 1200;
	y.price = 2400;

	prt_price(&x);
	prt_price(&y);

	return 0;
}
#endif

/***********************************************************/
// [3-9] derived class 포인터의 upcasting
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;
	const char * mission;
	int price;
};

class truck : public car
{
public:
	double load;
};

class van : public car
{
public:
	int passenger;
};

void prt_price(car *p)
{
	cout << p->price << endl;
}

int main(void)
{
	truck x; 
	van y;

	x.price = 1200;
	y.price = 2400;

	prt_price(&x);
	prt_price(&y);

	return 0;
}
#endif

/***********************************************************/
// [3-10-1] base class 포인터의 downcasting => 에러
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;
	const char * mission;
	int price;
};

class truck : public car
{
public:
	double load;
};

int main(void)
{
	truck x;
	car * p = &x;

	x.price = 1200;
	x.load = 2.5;

	cout << p->price << endl;
	cout << p->load << endl;

	return 0;
}
#endif

/***********************************************************/
// [3-10-2] base class 포인터의 downcasting => 정상
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;
	const char * mission;
	int price;
};

class truck : public car
{
public:
	double load;
};

int main(void)
{
	truck x;
	car * p = &x;

	x.price = 1200;
	x.load = 2.5;

	cout << p->price << endl;
	cout << ((truck *)p)->load << endl;

	return 0;
}
#endif

/***********************************************************/
// [3-11-1] 다중 상속 constructor, destructor 동작 순서
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		cout << "A" << endl;
	}
	~A()
	{
		cout << "~A" << endl;
	}
};

class B
{
public:
	B()
	{
		cout << "B" << endl;
	}
	~B()
	{
		cout << "~B" << endl;
	}
};

class C : public A, public B
{
public:
	C() // C() : A(), B() => 이렇게 설계해도 무방(기본적으로 해 줌)
	{
		cout << "C" << endl;
	}
	~C()
	{
		cout << "~C" << endl;
	}
};

int main()
{
	C x;
}
#endif

/***********************************************************/
// [3-11-2] 다중 상속 : default constructor가 아닌 경우
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	A(int x)
	{
		cout << "A:" << x << endl;
	}
	~A()
	{
		cout << "~A" << endl;
	}
};

class B
{
public:
	B(int x, int y)
	{
		cout << "B:" << x + y << endl;
	}
	~B()
	{
		cout << "~B" << endl;
	}
};

class C : public A, public B
{
public:
	C() : A(3), B(10, 20)
	{
		cout << "C" << endl;
	}
	~C()
	{
		cout << "~C" << endl;
	}
};

int main()
{
	C x;
}
#endif

/***********************************************************/
// [3-12] 다중 상속된 class에서 Base class의 함수 사용
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	void func()
	{
		cout << "A" << endl;
	}
};

class B
{
public:
	void func()
	{
		cout << "B" << endl;
	}
};

class C : public A, public B { };

int main()
{
	C x;
	x.func();
	x.A::func();
	x.B::func();

	return 0;
}
#endif

/***********************************************************/
// [3-13] 다중 상속된 class에서 발생할 수 있는 모호성 문제
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	int a;
};

class B1 : public A
{
public:
	int b;
};

class B2 : public A
{
public:
	int b;
};

class C : public B1, public B2
{
public:
	int c;
};

int main()
{
	C x;
	x.c = 10;
	x.B1::b = 20;
	x.B2::b = 30;
	
	// x.a = -10;	// x.{B1 / B2}::a 로 호출해야함. >> 현재는 B1의 a인지 B2의 a인지 불명확해서 에러

	x.B1::a = 40;
	x.B2::a = 50;

	cout << x.B1::a << endl;
	cout << x.B2::a << endl;

	return 0;
}
#endif

/***********************************************************/
// [3-14] Virtual Inheritance
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	int a;
};

class B1 : virtual public A
{
public:
	int b;
};

class B2 : virtual public A
{
public:
	int b;
};

class C : public B1, public B2
{
public:
	int c;
};

int main()
{
	C x;
	x.c = 10;
	x.B1::b = 20;
	x.B2::b = 30;

	x.a = -10;

	x.B1::a = 40;
	x.B2::a = 50;

	cout << x.B1::a << endl;
	cout << x.a << endl;

	B1 y;
	y.a = 100;

	cout << y.a << endl;

	return 0;
}
#endif

/***********************************************************/
// [4-1] Overloading에 의한 각 instance의 멤버 함수 호출 예
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;

	void prt_car()
	{
		cout << model << endl;
	}
};

class truck : public car
{
public:
	double load;

	void prt_car()
	{
		cout << load << endl;
	}
};

void func(car * y)
{
	y->prt_car();
}

void func(truck * y)
{
	y->prt_car();
}

int main(void)
{
	car c;
	truck x;

	c.model = "Sonata";
	x.load = 2.5;

	x.prt_car();
	x.car::model = "Bongo";
	x.car::prt_car();

	func(&c);
	func(&x);

	return 0;
}
#endif

/***********************************************************/
// [4-2] Derived Class의 Function Override(함수 재정의)
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;
	int price;

	void prt_car()
	{
		cout << model << endl;
	}
};

class truck : public car
{
public:
	double load;

	void prt_car()
	{
		cout << load << endl;
	}
};

int main(void)
{
	car c;
	truck x;

	c.model = "Sonata";
	x.load = 2.5;

	c.prt_car();
	x.prt_car();

	return 0;
}
#endif

/***********************************************************/
// [4-3] upcasting될 때 재정의 함수가 문제되는 경우
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;

	void prt_car()
	{
		cout << model << endl;
	}
};

class truck : public car
{
public:
	double load;

	void prt_car()
	{
		cout << load << endl;
	}
};

class van : public car
{
public:
	int passenger;

	void prt_car()
	{
		cout << passenger << endl;
	}
};

void print_info(car *p)
{
	p->prt_car();
}

int main(void)
{
	truck x;
	van	y;

	x.model = "Bongo";
	x.load = 2.5;
	y.model = "Carnival";
	y.passenger = 11;

	print_info(&x);
	print_info(&y);

	return 0;
}
#endif

/***********************************************************/
// [4-4] 가상 멤버 함수로 문제점 해결
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class car
{
public:
	const char * model;
	int price;

	virtual void prt_car()
	{
		cout << model << endl;
	}
};

class truck : public car
{
public:
	double load;

	virtual void prt_car() override
	{
		cout << load << endl;
	}
};

class van : public car
{
public:
	int passenger;

	virtual void prt_car() override
	{
		cout << passenger << endl;
	}
};

void print_info(car *p)
{
	p->prt_car();
}

int main(void)
{
	truck x;
	van	y;

	x.model = "Bongo";
	x.load = 2.5;
	y.model = "Carnival";
	y.passenger = 11;

	print_info(&x);
	print_info(&y);

	return 0;
}
#endif

/***********************************************************/
// [4-5-1] Function Overloading으로 새 함수 추가
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	void prt()
	{
		cout << "A" << endl;
	}
};

class B : public A
{
public:
	void prt() 
	{
		cout << "B" << endl;
	}
};

class C : public A
{
public:
	void prt() 
	{
		cout << "C" << endl;
	}
};

void print_info(A *p)
{
	p->prt();
}

void print_info(B *p)
{
	p->prt();
}

void print_info(C *p)
{
	p->prt();
}

int main(void)
{
	A x;
	B y;
	C z;

	print_info(&x);
	print_info(&y);
	print_info(&z);

	return 0;
}
#endif

/***********************************************************/
// [4-5-2] 가상 멤버 함수로 새 함수 추가
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	virtual void prt()
	{
		cout << "A" << endl;
	}
};

class B : public A
{
public:
	virtual void prt() override
	{
		cout << "B" << endl;
	}
};

class C : public A
{
public:
	virtual void prt() override
	{
		cout << "C" << endl;
	}
};

void print_info(A *p)
{
	p->prt();
}

int main(void)
{
	A x;
	B y;
	C z;

	print_info(&x);
	print_info(&y);
	print_info(&z);

	return 0;
}
#endif

/***********************************************************/
// [4-6-1] Upcasting에 의한 Destructor 동작 문제점
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	A() { cout << "A" << endl; }
	~A() { cout << "~A" << endl; }
};

class B : public A
{
public:
	B() { cout << "B" << endl; }
	~B() { cout << "~B" << endl; }
};

void f(A * p)
{
	delete p;
}

int main()
{
	B * p = new B;
	f(p);

	return 0;
}
#endif

/***********************************************************/
// [4-6-2] Virtual Destructor를 이용하여 해결
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	A() { cout << "A" << endl; }
	virtual ~A() { cout << "~A" << endl; }
};

class B : public A
{
public:
	B() { cout << "B" << endl; }
	~B() { cout << "~B" << endl; }
};

void f(A * p)
{
	delete p;
}

int main()
{
	B * p = new B;
	f(p);

	return 0;
}
#endif

/***********************************************************/
// [4-7] Pure Virtual Function & Abstract Class
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public :
	virtual void f() = 0;
};

class B : public A
{
public:
	virtual void f() override
	{
		cout << "Hello" << endl;
	}
};

int main()
{
	A x;
	B y;

	y.f();

	return 0;
}
#endif

/***********************************************************/
// [4-8] Abstract Class를 활용한 인터페이스
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class items
{
public:
	virtual void move_pos() = 0;
	virtual void check_crash() = 0;
};

class enemy
{
public:
	items * obj;
	int color;
	int speed;
};

class ufo : public items
{
public:
	int posx, posy;

	virtual void move_pos() override
	{ 
		cout << "ufo: move" << endl; 
	}

	virtual void check_crash() override
	{ 
		cout << "ufo: check crash" << endl; 
	}
};

class missile : public items
{
public:
	int pos;
	int direction;

	virtual void move_pos() override
	{
		cout << "missile: move" << endl;
	}

	virtual void check_crash() override
	{
		cout << "missile: check crash" << endl;
	}
};

int main()
{
	enemy x;
	ufo ufo1;
	missile missile1;

	x.obj = &ufo1;
	x.speed = 2;
	x.obj->move_pos();
	x.obj->check_crash();

	x.obj = &missile1;
	x.speed = 3;
	x.obj->move_pos();
	x.obj->check_crash();

	return 0;
}
#endif

/***********************************************************/
// [4-9] 가상 함수로 인하여 발생하는 동적 바인딩
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	virtual void f() { cout << "A" << endl; }
};

class B : public A
{
public:
	virtual void f() override { cout << "B" << endl; }
};

class C : public B
{
public:
	virtual void f() override { cout << "C" << endl; }
};

void f(A * p)
{
	p->f();
}

int main()
{
	A a;
	B b;
	C c;

	f(&a);
	f(&b);
	f(&c);

	return 0;
}
#endif

/***********************************************************/
// [4-10] RTTI를 활용한 정적 바인딩
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	virtual void f() { cout << "A" << endl; }
};

class B : public A
{
public:
	virtual void f() override { cout << "B" << endl; }
};

class C : public B
{
public:
	virtual void f() override { cout << "C" << endl; }
};

void f(A * p)
{
	const type_info & t = typeid(*p);
	cout << t.name() << endl;

	if(typeid(*p) == typeid(A))	p->A::f();
	else p->f();
	
	((C *)p)->C::f();
}

int main()
{
	A a;
	B b;
	C c;

	f(&a);
	f(&b);
	f(&c);

	return 0;
}
#endif

/***********************************************************/
// [4-11] 멤버 함수에 의한 Operator Overloading
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class A
{
public:
	int a;

	A(int x = 0) : a(x) {};

	int operator+(A y)
	{
		return this->a - y.a;
	}
};

int main()
{
	A x(10);
	A y(20);
	A z = x + y;

	cout << x.a << " " << y.a << " " << z.a << endl;

	return 0;
}
#endif

/***********************************************************/
// [4-12] friend 외부 함수에 의한 Operator Overloading
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class B
{
public:
	int a;

	friend B operator*(const B& x, int y);
};

B operator*(const B &x, int y)
{
	B r;
	r.a = x.a + (y * 2);
	return r;
}

int main()
{
	B m;
	B n;
	m.a = 20;
	n = m * 5;

	cout << n.a << endl;

	return 0;
}
#endif

/***********************************************************/
// [4-13] 재정의한 연산자의 Cascading 연산
/***********************************************************/

#if 0
#include <iostream>
using namespace std;

class myout
{
public:
	int n;

	myout(int in = 0) : n(in) {}

	myout operator<<(int m)
	{
		this->n += m;
		return *this;
	}
};

int main()
{
	myout x;
	
	cout << (x << 10 << 20 << 30).n << endl;

	return 0;
}
#endif
