#ifndef IMPORTDLLCLASS_H
#define IMPORTDLLCLASS_H

#include "..\DealUI\ui_base.h"
#include "..\ImageAlgorithm\algorithm_base.h"

#include <QObject>
#include <QLibrary>


class  ImportDllClass
{
public:
	 ImportDllClass();
	 ~ImportDllClass();


public:
	UIBase *m_pUIBase = NULL;
	AlgorithmBase *m_pAlgorithmBase = NULL;


	static ImportDllClass *_instance;
	static ImportDllClass *GetInstance();

};


#endif // !IMPORTDLLCLASS_H
