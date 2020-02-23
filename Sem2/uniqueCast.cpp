#include <iostream>
#include <memory>
#include "Sem2/uniqueCasts.h"

struct Base
{
	int a;
	virtual void f() const { std::cout << "I am base!\n"; }
	virtual ~Base() {}
};

struct Derived : Base
{
	void f() const override
	{
		std::cout << "I am derived!\n";
	}
	~Derived() {}
};

int main() {
	auto basePtr = std::make_unique<Base>();
	std::cout << "Base pointer says: ";
	basePtr->f();

	auto derivedPtr = std::make_unique<Derived>();
	std::cout << "Derived pointer says: ";
	derivedPtr->f();

	// static_pointer_cast to go up class hierarchy
	basePtr = static_pointer_cast<Base>(derivedPtr);
	std::cout << "Base pointer to derived says: ";
	basePtr->f();

	// dynamic_pointer_cast to go down/across class hierarchy
	auto downcastedPtr = dynamic_pointer_cast<Derived>(basePtr);
	if (downcastedPtr)
	{
		std::cout << "Downcasted pointer says: ";
		downcastedPtr->f();
	}
}