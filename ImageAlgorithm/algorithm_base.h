
#pragma once

#include "imagealgorithm_global.h"
#include <QObject>
#include <iostream>
#include <memory>
#include "opencv2\opencv.hpp"
#include "image_format_convert.h"

class IMAGEALGORITHM_EXPORT AlgorithmBase : public QObject
{
	Q_OBJECT

public:
	AlgorithmBase(QObject *parent=Q_NULLPTR);
	~AlgorithmBase();

public:
	virtual std::shared_ptr<ImageFormatConvert> getImageConvertInstance();


private:
	std::shared_ptr<ImageFormatConvert> m_ImageFormatConvertPtr = NULL;


public:
	static AlgorithmBase *instance;


};

extern "C"
{
	IMAGEALGORITHM_EXPORT AlgorithmBase *getAlgorithmBaseInstance();
}