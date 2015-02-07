#ifndef __SHARED_PTR_TECH_H
#define __SHARED_PTR_TECH_H
#include "base.h"
/*
ʹ��shared_ptr��Ŀ�ģ�
1 ��ֹ�ڴ�й¶
2 �����ÿͻ����ֶ����������������ڴ���յĺ���
3 ��shared_ptr���ܻ��Ľ����ڴ����
*/


/*
1 ʹ��shared_ptr����c���Ծ��ʽ������
*/
typedef boost::shared_ptr<FILE> FilePtr;

void     FileClose(FILE* file);

FilePtr FileOpen(char const* path,char const* mode);

void    FileRead(FilePtr& f, void * data, size_t size);



/*
2 ʹ��C++ "Pimpl"ģʽ��װincomplete class
*/
class FileSharedPtr
{
private:

    class impl;//����Ҫһ�㣬ǰ������ʵ���࣬����ʵ����.cpp�ļ��У�����ʵ��ϸ��
	boost::shared_ptr<impl> pimpl; //shared_ptr��Ϊ˽�г�Ա����

public:

    FileSharedPtr(char const * name, char const * mode);
    void Read(void * data, size_t size);
};


/*
3 ʹ������ӿڱ�̷�ʽ����ʵ��
*/

class IPrinter
{
   public:

    virtual void Print() = 0;

protected://�ܱ������������������±�����뱻�̳�,���ҿͻ��˲��ܵ���delete���������ڴ��ͷ���ȫ��shared_ptr������

    virtual ~IPrinter() 
	{
		printf("invoke IPrinter virtual ��������\n");
	}
};

typedef boost::shared_ptr<IPrinter> PrinterPtr;

PrinterPtr CreatePrinter();//��������������IPrinter����ָ��




/*
4 ��win32 �ں˶���(�������ü�����HANDLE)���а�װ
*/

typedef boost::shared_ptr<void> handle;
handle  createMutexHandle();



/*
5 �Ծ�̬��ȫ�ֶ�����а�װ
*/
static Foo staticFoo("test static object");

struct null_deleter//�º�������
{
	//���غ������ò�����()
	void operator()(void* const ) const  { std::cout << "null_deleter�º���\n";} //û���κδ���
};

boost::shared_ptr<Foo> CreateStaticObj();



/*
6 ʹ��shared_ptr<void> ����������������Ȩ
*/

boost::shared_ptr<void> CreateVoidPtrFromString();



#endif