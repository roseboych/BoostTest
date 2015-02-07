#ifndef __BASE_H
#define __BASE_H
#include <windows.h>
#include <stdio.h>
#include <string>
#include <assert.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/smart_ptr.hpp>

#ifndef BOOST_MEM_FN_ENABLE_STDCALL
#define BOOST_MEM_FN_ENABLE_STDCALL
#endif
#include <boost/mem_fn.hpp>

class Foo
{
public:
	Foo(const std::string& strName) : m_strName(strName) {}
	~Foo() { std::cout << "Destructing a Foo with name = " << m_strName << std::endl; }
private:
	std::string m_strName;
};

typedef boost::shared_ptr<Foo> FooPtr;
//class  Foo
//{
//public:
//	Foo(const std::string& name);
//	~Foo();
//
//private:
//	std::string  m_strName;
//};
//
//Foo::Foo(const std::string& name)
//{
//	this->m_strName = name;
//}
//
//Foo::~Foo()
//{
//	std::cout << "Destruction the class with the name is" << m_strName << std::endl;
//}
//typedef boost::shared_ptr<Foo> FooPtr;

class RAIIClass
{
public:
    RAIIClass()
	{
		InitializeCriticalSection(&m_CriticalSection);
		EnterCriticalSection(&m_CriticalSection);
	}

	~RAIIClass()
	{
		LeaveCriticalSection(&m_CriticalSection);
		DeleteCriticalSection(&m_CriticalSection);
		std::cout << "Îö¹¹RAIIClass\n";
	}
private:
	CRITICAL_SECTION m_CriticalSection;
	
};


class Base
{
public:
	virtual void Print()
	{
		std::cout << "print from base class\n";
	}
};

class Derive : public Base
{
public:
	void Print()
	{
		std::cout << "print from derive class\n";
	}
};

class A;
class B;

class A
{

public:
	~A()
	{
		std::cout << "Îö¹¹class A\n";
	}
    B* b;
};

class B
{

public:
	~B()
	{
		std::cout << "Îö¹¹class B\n";
	}
    A* a;
};




#endif