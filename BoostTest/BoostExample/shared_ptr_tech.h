#ifndef __SHARED_PTR_TECH_H
#define __SHARED_PTR_TECH_H
#include "base.h"
/*
使用shared_ptr的目的：
1 防止内存泄露
2 避免让客户端手动调用析构函数或内存回收的函数
3 让shared_ptr智能化的进行内存回收
*/


/*
1 使用shared_ptr隐藏c语言句柄式样函数
*/
typedef boost::shared_ptr<FILE> FilePtr;

void     FileClose(FILE* file);

FilePtr FileOpen(char const* path,char const* mode);

void    FileRead(FilePtr& f, void * data, size_t size);



/*
2 使用C++ "Pimpl"模式封装incomplete class
*/
class FileSharedPtr
{
private:

    class impl;//很重要一点，前向申明实现类，具体实现在.cpp文件中，隐藏实现细节
	boost::shared_ptr<impl> pimpl; //shared_ptr作为私有成员变量

public:

    FileSharedPtr(char const * name, char const * mode);
    void Read(void * data, size_t size);
};


/*
3 使用面向接口编程方式隐藏实现
*/

class IPrinter
{
   public:

    virtual void Print() = 0;

protected://受保护的析构函数，导致本类必须被继承,并且客户端不能调用delete操作符，内存释放完全被shared_ptr来管理

    virtual ~IPrinter() 
	{
		printf("invoke IPrinter virtual 析构函数\n");
	}
};

typedef boost::shared_ptr<IPrinter> PrinterPtr;

PrinterPtr CreatePrinter();//工厂方法，创建IPrinter智能指针




/*
4 对win32 内核对象(具有引用计数的HANDLE)进行包装
*/

typedef boost::shared_ptr<void> handle;
handle  createMutexHandle();



/*
5 对静态或全局对象进行包装
*/
static Foo staticFoo("test static object");

struct null_deleter//仿函数对象
{
	//重载函数调用操作符()
	void operator()(void* const ) const  { std::cout << "null_deleter仿函数\n";} //没有任何代码
};

boost::shared_ptr<Foo> CreateStaticObj();



/*
6 使用shared_ptr<void> 持有任意对象的所有权
*/

boost::shared_ptr<void> CreateVoidPtrFromString();



#endif