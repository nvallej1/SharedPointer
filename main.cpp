#include "SharedPtr.hpp"

struct A {
	int x;
	int y;
	int z;
	A();
	A(int x, int y, int z);
    virtual void foo() { std::cout << "A" << std::endl; }
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

struct B : A {
    void foo() { std::cout << "B" << std::endl; }
};

int main() {
	{
		double pi = 3.14;
		double * p = &pi;

		cs540::SharedPtr <double> sp_d(&pi);
		cs540::SharedPtr <double> sp_d2(p);
        //cs540::SharedPtr <double> sp_cpy(new cs540::SharedPtr<double>()); // copy constructor with rvalue parameter non existent
        A * a = new A;
        a->foo();
        B * b = new B;
        a = b;
        a->foo();
        b->foo();
	}
}
