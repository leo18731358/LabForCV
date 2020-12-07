
#include "lab_main_form.h"
#include "opencv2\opencv.hpp"
#include <opencv2/highgui.hpp>
#include <QVBoxLayout>

#include "..\ImageAlgorithm\image_format_convert.h"
#include "..\DealUI\opencv_image_ui.h"

using namespace cv;

LabMainForm::LabMainForm(QWidget *parent) : QWidget(parent)
{
	__setupUI();
}

LabMainForm::~LabMainForm()
{
	//m_pixtureUIPtr = ImportDllClass::GetInstance()->m_pUIBase->getPixtureUIInstance(); //在析构时必须新实例化一个，不然析构函数报错
	m_OpencvImageUIPtr = ImportDllClass::GetInstance()->m_pUIBase->getOpencvImageUIInstnce();
}

void LabMainForm::__setupUI()
{
	QFont m_cFont = this->font();
	m_cFont.setPixelSize(15);

	this->setMinimumSize(1200, 800);
	this->setFont(m_cFont);

	//m_pixtureUIPtr = ImportDllClass::GetInstance()->m_pUIBase->getPixtureUIInstance();
	m_OpencvImageUIPtr = ImportDllClass::GetInstance()->m_pUIBase->getOpencvImageUIInstnce();

	m_pConfirmBtn = new QPushButton();
	m_pConfirmBtn->setText(QStringLiteral("开始测试"));
	m_cFont.setBold(true);
	m_cFont.setPixelSize(28);
	m_pConfirmBtn->setFont(m_cFont);

	QVBoxLayout *m_pVBoxLayoutRight = new QVBoxLayout();
	m_pVBoxLayoutRight->addWidget(m_pConfirmBtn);

	QHBoxLayout *m_pHBoxLayout = new QHBoxLayout();
	m_pHBoxLayout->addWidget(m_OpencvImageUIPtr.get());
	m_pHBoxLayout->addLayout(m_pVBoxLayoutRight);
	m_pHBoxLayout->setStretchFactor(m_OpencvImageUIPtr.get(), 5);
	m_pHBoxLayout->setStretchFactor(m_pVBoxLayoutRight, 1);

	connect(m_pConfirmBtn, SIGNAL(clicked()), this, SLOT(comfirmClicked()));

	this->setLayout(m_pHBoxLayout);

}


void LabMainForm::comfirmClicked()
{

	Mat srcImage = imread("D:\\Desktop\\1.bmp");


	m_OpencvImageUIPtr->showMatImage(srcImage);

}


