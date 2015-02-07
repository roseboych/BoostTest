#include "simpleComObj.h"


static const IID IID_IX = 
{ 0xa348fbdd, 0xe765, 0x4b41, { 0x84, 0x77, 0x6d, 0x8b, 0x70, 0x38, 0xfc, 0xc6 } };

// {10A90ED2-FCDE-4067-92DA-ABA38F5C1B12}
static const IID IID_IY = 
{ 0x10a90ed2, 0xfcde, 0x4067, { 0x92, 0xda, 0xab, 0xa3, 0x8f, 0x5c, 0x1b, 0x12 } };

class CA: public IX
{
//构造与析构
public:
	CA()
	{
		m_lCount = 0;

		//构造时，需要自增引用计数
		AddRef();
	}
	virtual ~CA()		//析构函数一般采用虚函数
	{
		std::cout << "我被释放啦！" << std::endl;
	}

//实现
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ppv)
	{
		//查看PPT中CA的内存结构讲解如下的转换过程

		if (iid == IID_IUnknown)
		{
			//即使CA继承了两个IUnknown接口，其中一个来自于IX，另一个来自于IY。我们一般返回第一个被继承的IX接口。
			*ppv = static_cast<IX*>(this);		
		}
		else if (iid == IID_IX)
		{
			//返回IX接口
			*ppv = static_cast<IX*>(this);		
		}
		else
		{
			//查询不到IID，*ppv返回NULL。
			*ppv = NULL;
			return E_NOINTERFACE;	//函数返回值返回E_NOINTERFACE，表示组件不支持iid的接口。
		}

		//查询成功时，需要自增引用计数
		AddRef();		

		return S_OK;	//返回S_OK
	}

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		//简单实现方法
		return ++m_lCount;

		//多线程编程采用如下方法，这种方法确保同一个时刻只会有一个线程来访问成员变量
		//return InterlockedIncrement(&m_lCount);
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		//简单实现方法
		if (--m_lCount == 0)
		{
			std::cout << "com ref count = 0,delete this\n";
			delete this;	//销毁自己
			return 0;
		}
		return m_lCount;

		////多线程编程采用如下方法，这种方法确保同一个时刻只会有一个线程来访问成员变量
		//if (InterlockedDecrement(&m_lCount) == 0)
		//{
		//	delete this;		//销毁自己
		//	return 0;
		//}
		//return m_lCount;
	}

	virtual void Fx1()
	{
		std::cout << "Fx1" << std::endl;
	}

	
//数据
private:
	long m_lCount;		//引用计数，该计数只被该类管理，外界不可访问，访问权限设置为private

};

void CreateIXComInterface(IX** ppIx)
{
	HRESULT hr;
	CA *pA = new CA();
	*ppIx = NULL;
	hr = pA->QueryInterface(IID_IX, (void**)ppIx);
	(*ppIx)->Release();
}