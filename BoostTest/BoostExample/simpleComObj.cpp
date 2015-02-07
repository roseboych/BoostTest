#include "simpleComObj.h"


static const IID IID_IX = 
{ 0xa348fbdd, 0xe765, 0x4b41, { 0x84, 0x77, 0x6d, 0x8b, 0x70, 0x38, 0xfc, 0xc6 } };

// {10A90ED2-FCDE-4067-92DA-ABA38F5C1B12}
static const IID IID_IY = 
{ 0x10a90ed2, 0xfcde, 0x4067, { 0x92, 0xda, 0xab, 0xa3, 0x8f, 0x5c, 0x1b, 0x12 } };

class CA: public IX
{
//����������
public:
	CA()
	{
		m_lCount = 0;

		//����ʱ����Ҫ�������ü���
		AddRef();
	}
	virtual ~CA()		//��������һ������麯��
	{
		std::cout << "�ұ��ͷ�����" << std::endl;
	}

//ʵ��
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ppv)
	{
		//�鿴PPT��CA���ڴ�ṹ�������µ�ת������

		if (iid == IID_IUnknown)
		{
			//��ʹCA�̳�������IUnknown�ӿڣ�����һ��������IX����һ��������IY������һ�㷵�ص�һ�����̳е�IX�ӿڡ�
			*ppv = static_cast<IX*>(this);		
		}
		else if (iid == IID_IX)
		{
			//����IX�ӿ�
			*ppv = static_cast<IX*>(this);		
		}
		else
		{
			//��ѯ����IID��*ppv����NULL��
			*ppv = NULL;
			return E_NOINTERFACE;	//��������ֵ����E_NOINTERFACE����ʾ�����֧��iid�Ľӿڡ�
		}

		//��ѯ�ɹ�ʱ����Ҫ�������ü���
		AddRef();		

		return S_OK;	//����S_OK
	}

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		//��ʵ�ַ���
		return ++m_lCount;

		//���̱߳�̲������·��������ַ���ȷ��ͬһ��ʱ��ֻ����һ���߳������ʳ�Ա����
		//return InterlockedIncrement(&m_lCount);
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		//��ʵ�ַ���
		if (--m_lCount == 0)
		{
			std::cout << "com ref count = 0,delete this\n";
			delete this;	//�����Լ�
			return 0;
		}
		return m_lCount;

		////���̱߳�̲������·��������ַ���ȷ��ͬһ��ʱ��ֻ����һ���߳������ʳ�Ա����
		//if (InterlockedDecrement(&m_lCount) == 0)
		//{
		//	delete this;		//�����Լ�
		//	return 0;
		//}
		//return m_lCount;
	}

	virtual void Fx1()
	{
		std::cout << "Fx1" << std::endl;
	}

	
//����
private:
	long m_lCount;		//���ü������ü���ֻ�����������粻�ɷ��ʣ�����Ȩ������Ϊprivate

};

void CreateIXComInterface(IX** ppIx)
{
	HRESULT hr;
	CA *pA = new CA();
	*ppIx = NULL;
	hr = pA->QueryInterface(IID_IX, (void**)ppIx);
	(*ppIx)->Release();
}