
#include "import_dll_class.h"


ImportDllClass::ImportDllClass()
{

	typedef UIBase* (*UIBaseFun)();
	QLibrary *DealUIDll = new QLibrary("DealUI.dll");
	if (DealUIDll->load())
	{
		UIBaseFun uibaseFun = (UIBaseFun)DealUIDll->resolve("getUIBaseInstance");
		if (uibaseFun)
		{
			m_pUIBase = uibaseFun();
		}
	}

	typedef AlgorithmBase* (*AlgorithmBaseFun)();
	QLibrary *AlgorithmBaseDll = new QLibrary("ImageAlgorithm.dll");
	if (AlgorithmBaseDll->load())
	{
		AlgorithmBaseFun algorithmFun = (AlgorithmBaseFun)AlgorithmBaseDll->resolve("getAlgorithmBaseInstance");
		if (algorithmFun)
		{
			m_pAlgorithmBase = algorithmFun();
		}
	}
	

}
ImportDllClass::~ImportDllClass()
{
}

ImportDllClass* ImportDllClass::_instance = NULL;
ImportDllClass* ImportDllClass::GetInstance()
{
	if (NULL == ImportDllClass::_instance)
	{
		ImportDllClass::_instance = new ImportDllClass();
	}
	return ImportDllClass::_instance;
}
