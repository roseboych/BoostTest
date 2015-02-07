#include "shared_ptr_tech.h"
#include "simpleTest.h"
#include <assert.h>
#include "simpleTest.h"
#include "simpleComObj.h"
#include "shared_ptr_error_use.h"

void Test_RAII_Class()
{
	int i = 0;

	RAIIClass raii;
	i++;
}


void Test_Shared_Ptr_For_Virual_Function()
{

	boost::shared_ptr<Base> ptrBase(new Base());
	ptrBase->Print();

	boost::shared_ptr<Derive> ptrDerive(new Derive());
	ptrDerive->Print();
   
	boost::shared_ptr<Base> ptr(new Derive());
	ptr->Print(); 

	boost::shared_ptr<Base> ptr2 = ptr;
	ptr2->Print();

	boost::shared_ptr<Base> ptr3 = ptrDerive;
	ptr3->Print();

}

void Test_Boost_Shared_Ptr()
{
	FooPtr ptr1(new Foo("Foo1"));
	assert(ptr1.use_count() == 1);

	FooPtr ptr2 = ptr1;
	assert(ptr1.use_count() == ptr2.use_count());
	assert(ptr1 == ptr2);
	assert(ptr1.use_count() == 2);
	
	FooPtr ptr3 = ptr2;
	assert(ptr1.use_count() == ptr2.use_count() && ptr1.use_count()	== ptr3.use_count()); 
	assert(ptr1.use_count() == 3 && ptr2.use_count() == 3 && ptr3.use_count() == 3);
	assert(ptr1 == ptr2 && ptr1 == ptr3);
	


	//重置ptr3
	ptr3.reset();
	assert(ptr3.use_count() == 0);
	assert(ptr3.get() == NULL);
	std::cout << "ptr3引用计数为0,get() 指针指向NULL,但是不会调用析构函数,因为ptr1和ptr2都指向了原生指针" << std::endl;
	assert(ptr1.use_count() == ptr2.use_count() && ptr1.use_count() == 2);
	assert(ptr1 == ptr2 && ptr1 != ptr3);
	
	
    //前面ptr1和ptr2都指向同一个对象，因此他们的引用计数都为2
	//现在我们新建一个ptr4,让其指向ptr1
	FooPtr ptr4 = ptr1;
    assert(ptr1 == ptr2&& ptr1 == ptr4);
	assert(ptr4.use_count() == 3);

	//现在我们转移ptr2的所有权到另外一个Foo指针上去
	std::cout << "转移ptr2的拥有权到一个新的Foo指针上" << std::endl;
	ptr2.reset(new Foo("Foo2"));
	//在ptr2转移所有权后，ptr2计数器应该是1，并且ptr1和ptr4的计数器是2,并且ptr1 != ptr2
	assert(ptr2.use_count() == 1 && ptr1.use_count() == 2 && ptr4.use_count() == 2);
	assert(ptr1 != ptr2 && ptr1 == ptr4);

	//此时ptr3因为被重置为0,并且get() 为 NULL了，我们再使用一个ptr5来指向ptr3也应该引用计数为0而不是1，并且get()为NULL
	FooPtr ptr5 = ptr3;
	assert(ptr5.use_count() == 0&&ptr5.get() == NULL);
	

	//运行到此时，程序即将结束，在退出作用于前会调用析构函数
	//首先会打印出Destructing a Foo with name = Foo__2
	//ptr1 和 ptr4也会相继调用析构函数进行引用计数递减
	//最终会打印出Destructing a Foo with name = Foo__1
	//这样就没有任何内存泄露了哦

}


	

void Test_Boost_Shared_Ptr_Crash()
{
	//不能同时指向原始指针
	//必须要用智能指针赋值操作
	Foo*   foo = new Foo("error use");
	FooPtr fooPtr1(foo);
	FooPtr fooPtr2(foo);
	//程序崩溃
}

void Test_Parent_Child_Ref()
{
	ParentPtr father(new Parent());
	ChildPtr  son(new Child());
	father->child = son;
	son->parent = father;
}


void Test_C_File_Ptr()
{
	FilePtr ptr = FileOpen("memory.log","r");
	FilePtr ptr2 = ptr;
	char data[51];
	FileRead(ptr,data,50);
	data[50] = '\0';
	printf("%s\n",data);
}

void Test_CPP_File_Ptr()
{
	FileSharedPtr ptr("memory.log","r");
	FileSharedPtr ptr2 = ptr;
	char data[51];
	ptr.Read(data,50);
	data[50] = '\0';
	printf("%s\n",data);
}

void Test_Printer()
{
	PrinterPtr ptr = CreatePrinter();
	ptr->Print();
	PrinterPtr ptr2 = ptr;
	ptr2->Print();
}

void Test_Create_Mutex_Handle()
{
	handle hMutex = createMutexHandle();
	handle hMutex2  = hMutex;
}

void Test_Create_Static_Obj()
{
   boost::shared_ptr<Foo> staticPtr = CreateStaticObj();
   boost::shared_ptr<Foo> staticPtr2 = staticPtr;
} 

void Test_Create_Void_Ptr_From_String()
{
	boost::shared_ptr<void> ptr = CreateVoidPtrFromString();
	boost::shared_ptr<void> ptr2 = ptr;
	std::cout << ptr2.use_count() << std::endl;
	boost::shared_ptr<std::string> ptrStr = boost::static_pointer_cast<std::string>(ptr2);
	std::cout << ptrStr.use_count() << std::endl;
	std::cout << ptrStr->c_str() << std::endl;
	
}

void Test_Vector_Shared_Ptr()
{
	char name[32];
	std::vector<FooPtr> ptrs;
	for(int i = 0; i < 20; i++)
	{
        sprintf(name,"foo%d",i);
		ptrs.push_back(FooPtr(new Foo(name)));	
	}

	for(int i = 0; i < 20; i++)
	{
		FooPtr ptr = ptrs[i];
		assert(ptrs[i].use_count() == 2);
	}

	for(int i = 0; i < 20; i++)
		assert(ptrs[i].use_count() == 1);	
}

boost::shared_ptr<IX> Test_Shared_Ptr_From_Com_Obj()
{
    IX* ix = NULL;
	CreateIXComInterface(&ix);
	boost::shared_ptr<IX> ixPtr(ix,boost::mem_fn(&IX::Release));
	return ixPtr;
}


//
//void Test()
//{
//	A* a = new A;
//	B* b = new B;
//	a->b = b;
//	b->a = a;
//	delete a;
//	delete b;
//}

int main()
{ 
	//Test_RAII_Class();
	//Test_Shared_Ptr_For_Virual_Function();
	//Test_Boost_Shared_Ptr();
	//Test_Boost_Shared_Ptr_Crash();
	//Test_Parent_Child_Ref();
    //Test_Vector_Shared_Ptr();
	 Test_C_File_Ptr();
	//Test_CPP_File_Ptr();
	//Test_Printer();
	
	/*
	boost::shared_ptr<IX> comPtr = Test_Shared_Ptr_From_Com_Obj();
	boost::shared_ptr<IX> comPtr2 = comPtr;
	*/
	
	//Test_Create_Mutex_Handle();
	//Test_Create_Static_Obj();
	//Test_Create_Void_Ptr_From_String();

	//Test();
	
	getchar();
	return 0;
}
