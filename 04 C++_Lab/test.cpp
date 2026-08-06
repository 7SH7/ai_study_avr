#if 0

#include <iostream>
using namespace std;

class figure
{
public:
	int color_index;

	figure(int c) : color_index(c) {};
};

class square : public figure
{
public:
	int width;

	square(int c, int w) : figure(c), width(w) {};
};

class rectagle : public square
{
public:
	int height;

	rectagle(int c, int w, int h) : square(c, w), height(h) {}
};

template <typename T>
void prt_info(T * p)
{
     // --> 컴파일 때, line by line으로 다 읽는데, 그때 square가 들어오면, rectagle 조건문 부분에서 height가 없으니까 에러가 남.
	if(typeid(*p).name() == typeid(square).name()) cout << p->color_index << endl << p->width << endl;
	else if(typeid(*p).name() == typeid(rectagle).name()) cout << p->color_index << endl << p->width << endl << p->height << endl;
}

int main()
{
	square s(1, 10);
	rectagle r(2, 20, 30);

	prt_info(&s);
	prt_info(&r);

	return 0;
}

#else

#include <iostream>
using namespace std;

class figure
{
public:
	int color_index;

	figure(int c) : color_index(c) {};
};

class square : public figure
{
public:
	int width;

	square(int c, int w) : figure(c), width(w) {};
};

class rectagle : public square
{
public:
	int height;

	rectagle(int c, int w, int h) : square(c, w), height(h) {}
};

template <typename T>
void prt_info(T * p)
{
     // 코드 설계
	cout << p->color_index << endl << p->width << endl;
	if(typeid(*p) == typeid(rectagle)) {
		rectagle* rect_ptr = (rectagle*)p; 
		cout << rect_ptr->height << endl;
	}
}

int main()
{
	square s(1, 10);
	rectagle r(2, 20, 30);

	prt_info(&s);
	prt_info(&r);

	return 0;
}

#endif