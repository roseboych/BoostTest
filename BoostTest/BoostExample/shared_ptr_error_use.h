#ifndef __SHARED_PTR_ERROR_USE_H
#define __SHARED_PTR_ERROR_USE_H
#include "base.h"
//前向声明类
class Parent;
class Child;

typedef boost::shared_ptr<Parent> ParentPtr;
typedef boost::shared_ptr<Child>  ChildPtr;
typedef boost::weak_ptr<Parent> ParentWeakPtr;
typedef boost::weak_ptr<Child>  ChildWeakPtr;

class Parent
{
public:
	~Parent()
	{
		std::cout << "调用parent的析构函数\n";
	}
public:
	ChildPtr child;
	//ChildWeakPtr child;
};

class Child
{
public:
	~Child()
	{
		std::cout << "调用child的析构函数\n";
	}
public:
	ParentPtr parent;
	//ParentWeakPtr parent;
};


#endif