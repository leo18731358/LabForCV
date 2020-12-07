
#include "imagealgorithm_global.h"
#include "algorithm_base.h"

AlgorithmBase::AlgorithmBase(QObject *parent) : QObject(parent)
{

}

AlgorithmBase::~AlgorithmBase()
{
}

std::shared_ptr<ImageFormatConvert> AlgorithmBase::getImageConvertInstance()
{
	m_ImageFormatConvertPtr = std::make_shared<ImageFormatConvert>();
	return m_ImageFormatConvertPtr;
}



AlgorithmBase* AlgorithmBase::instance = NULL;
IMAGEALGORITHM_EXPORT AlgorithmBase *getAlgorithmBaseInstance()
{
	if (NULL == AlgorithmBase::instance)
	{
		AlgorithmBase::instance = new AlgorithmBase();
	}
	return AlgorithmBase::instance;
}