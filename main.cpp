#include "SharedPtr.hpp"

struct A {
	int x;
	int y;
	int z;
	A();
	A(int x, int y, int z);
};

A::A() {
	x=0;
	y=0;
	z=0;
}

A::A(int x, int y, int z) {
	x = x;
	y = y;
	z = z;
}

int main() {
	{
		cs540::SharedPtr <int> sharedptr;

		double pi = 3.14;
		double * p = &pi;

		cs540::SharedPtr <double> sp_d(&pi);
		cs540::SharedPtr <double> sp_d2(p);
	}
}
