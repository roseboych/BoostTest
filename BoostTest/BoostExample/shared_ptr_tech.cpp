#include "shared_ptr_tech.h"
#include <windows.h>
void  FileClose(FILE* file)
{
	//本函数只是为了打印是否调用了fclose函数以及fclose调用后是否成功
	int result = fclose(file);
	printf("invoke fclose result = %d\n",result);
	//return result;
}

FilePtr FileOpen(char const* path,char const* mode)
{
	//typedef boost::shared_ptr<FILE> FilePtr;
	FilePtr fptr(fopen(path,mode),FileClose);
	//FilePtr fptr(fopen(path,mode),fclose);
	return fptr;

}

void FileRead(FilePtr& f, void * data, size_t size)
{
	printf("the usercount = %d\n",f.use_count());
	fread(data,1,size,f.get());
}

class FileSharedPtr::impl
{
private:

    impl(impl const &)
	{
	}
    impl & operator=(impl const &)
	{
	}
    FILE* f;

public:

    impl(char const * name, char const * mode)
	{ 
		f = fopen(name,mode);
	}

    ~impl()
	{
       int result = fclose(f);
	   printf("invoke FileSharedPtr::impl 析构函数 result = %d\n",result);
	}

    void read(void * data, size_t size)
	{
		fread(data,1,size,f);
	}
};

FileSharedPtr::FileSharedPtr(const char *name, const char *mode) :
pimpl(new FileSharedPtr::impl(name,mode))
{
}

void FileSharedPtr::Read(void* data,size_t size)
{
	pimpl->read(data,size);
}



class Printer : public IPrinter
{
private:
	FILE* f;
public:
	Printer(const char* path,const char* mode)
	{
		f = fopen(path,mode);		
	}

	~Printer()
	{
	   int result = fclose(f);
	   printf("invoke Printer 析构函数 result = %d\n",result);
	}

	void Print()
	{
		char data[51];
		fread(data,1,50,f);
		data[50] = '\0';
		printf("%s\n",data);
		rewind(f);
	}
};

PrinterPtr CreatePrinter()
{
	PrinterPtr ptr(new Printer("memory.log","r"));
	return ptr;
}



void MyCloseHandleWrap(HANDLE h)
{
	std::cout << "调用win32 CloseHandle API\n";
    CloseHandle(h);
}

handle  createMutexHandle()
{
	boost::shared_ptr<void> ptr(CreateMutex(NULL,FALSE,NULL),MyCloseHandleWrap);
	return ptr;
}

boost::shared_ptr<Foo> CreateStaticObj()
{
	boost::shared_ptr<Foo> pFoo(&staticFoo,null_deleter());
	return pFoo;
}

boost::shared_ptr<void> CreateVoidPtrFromString()
{
	boost::shared_ptr<void> voidPtr(new std::string("CreateVoidPtrFromString"));
	return voidPtr;
}