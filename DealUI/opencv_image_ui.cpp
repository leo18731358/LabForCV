#include "opencv_image_ui.h"
#include <QFont>
#include <QStatusBar>
#include <QVBoxLayout>
#include <Windows.h>


OpencvImageUI::OpencvImageUI(QWidget *parent) : QWidget(parent)
{
	__setupUI();
	__initialConnection();
}

OpencvImageUI::~OpencvImageUI()
{

}


void onMouseCallback(int event, int x, int y, int flags, void* param)
{

	OpencvImageUI *m_pMyUI = (OpencvImageUI *)param;
	if (m_pMyUI->m_srcImage.data)
	{
		QString strPosition = QString("( %1, %2 )").arg(y).arg(x);
		m_pMyUI->m_pPositionLabel->setText(strPosition);
		QString strGrayValue = m_pMyUI->getPixelGrayValue(x, y);
		m_pMyUI->m_pGrayValueLabel->setText(strGrayValue);
		int nIndex = 0;
		if (m_pMyUI->m_bIsAllowDrawPoint)
		{
			switch (event)
			{
			case cv::EVENT_LBUTTONDOWN:
				m_pMyUI->drawedPoint.push_back(cv::Point(x, y));
				cv::circle(m_pMyUI->m_interactiveImage, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
				nIndex = m_pMyUI->drawedPoint.size();
				if (nIndex > 1)
				{
					cv::line(m_pMyUI->m_interactiveImage, m_pMyUI->drawedPoint[nIndex - 2], m_pMyUI->drawedPoint[nIndex - 1], cv::Scalar(0, 0, 255), 2);
				}			
				cv::imshow(m_pMyUI->m_strWindowName.toStdString(), m_pMyUI->m_interactiveImage);
				break;
			case cv::EVENT_RBUTTONDOWN:
				m_pMyUI->m_bIsAllowDrawPoint = false;
				break;
			}
		}

		
	}

}

void OpencvImageUI::__setupUI()
{
	QFont m_Font = this->font();
	m_Font.setPixelSize(15);
	this->setFont(m_Font);

	this->setMinimumSize(800, 600);

	QStatusBar *m_pQstatusBar = new QStatusBar();
	QLabel *m_Position = new QLabel();
	m_Position->setText(QStringLiteral("当前坐标："));
	QLabel *m_GrayValue = new QLabel();
	QLabel *m_SpacingLabel = new QLabel();
	m_GrayValue->setText(QStringLiteral("灰度值："));
	m_pPositionLabel = new QLabel();
	m_pGrayValueLabel = new QLabel();
	m_pPositionLabel->setMinimumWidth(100);
	m_pGrayValueLabel->setMinimumWidth(100);
	m_pQstatusBar->addPermanentWidget(m_Position);
	m_pQstatusBar->addPermanentWidget(m_pPositionLabel);
	m_pQstatusBar->addPermanentWidget(m_GrayValue);
	m_pQstatusBar->addPermanentWidget(m_pGrayValueLabel);

	QVBoxLayout *m_pVBoxLayoutMain = new QVBoxLayout();

	m_pToolBar = new QToolBar();
	m_pDrawPointAction = new QAction(QIcon(":/image/dot.ico"), QStringLiteral("获取点"));
	m_pClearDataAction = new QAction(QIcon(":/image/clear.ico"), QStringLiteral("清除数据"));
	m_pClearDataAction->setToolTip(QStringLiteral("清除数据"));
	m_pToolBar->addAction(m_pDrawPointAction);
	m_pToolBar->addAction(m_pClearDataAction);
	m_pVBoxLayoutMain->addWidget(m_pToolBar);

	m_pWidgetMain = new QWidget();
	m_pWidgetMain->setStyleSheet("QWidget{background:black}");
	m_pVBoxLayoutMain->addWidget(m_pWidgetMain);
	m_pVBoxLayoutMain->addWidget(m_pQstatusBar, Qt::AlignLeft);
	m_pVBoxLayoutMain->setStretchFactor(m_pToolBar, 1);
	m_pVBoxLayoutMain->setStretchFactor(m_pWidgetMain, 1000);
	m_pVBoxLayoutMain->setStretchFactor(m_pQstatusBar, 1);
	m_pVBoxLayoutMain->setContentsMargins(0, 0, 0, 0);
	this->setLayout(m_pVBoxLayoutMain);

	cv::namedWindow(m_strWindowName.toStdString(), CV_WINDOW_NORMAL); // CV_WINDOW_NORMAL); // 0;
	cv::resizeWindow(m_strWindowName.toStdString(), m_pWidgetMain->width(), m_pWidgetMain->height()); //设置窗口大小
																									  //moveWindow(m_strWindowName, 100, 100);		//移动窗口到指定位置
	HWND hwnd = (HWND)cvGetWindowHandle(m_strWindowName.toLatin1().data()); //toLatinl()转char*
																			//取m_strWindowName窗体的父窗体句柄
	HWND hparent = ::GetParent(hwnd);
	//改变某个子窗体的父窗口(子窗口句柄,新的父窗口句柄)
	::SetParent(hwnd, (HWND)m_pWidgetMain->winId());  //winId()取win32api要用的窗口句柄
													  //显示窗体SW_SHOW  隐藏窗体SW_HIDE
	::ShowWindow(hparent, SW_HIDE);
	cv::setMouseCallback(m_strWindowName.toStdString(), onMouseCallback, (void *)this);
	cv::Mat matdata(600, 800, CV_8UC1, cv::Scalar(0));
	showMatImage(matdata);
}

void OpencvImageUI::resizeEvent(QResizeEvent *event)
{
	cv::resizeWindow(m_strWindowName.toStdString(), m_pWidgetMain->width(), m_pWidgetMain->height()); //设置窗口大小
}

void OpencvImageUI::showMatImage(cv::Mat matData)
{
	cv::imshow(m_strWindowName.toStdString(), matData);
	matData.copyTo(m_srcImage);
}

QString OpencvImageUI::getPixelGrayValue(int x, int y)
{
	int w = m_srcImage.cols;
	int h = m_srcImage.rows;
	int channels = m_srcImage.channels();
	if (1 == channels)
	{
		cv::Mat_<uchar>::iterator it = m_srcImage.begin<uchar>();
		int pixelValue = *(it + y*w + x);
		return QString::number(pixelValue);

	}
	else
	{
		cv::Mat_<cv::Vec3b>::iterator it = m_srcImage.begin<cv::Vec3b>();
		it = it + y*w + x;
		QString strGrayValue = "BGR: " + QString::number((*it)[0]) + "," + QString::number((*it)[1]) + "," + QString::number((*it)[2]);
		return strGrayValue;

	}
}

void OpencvImageUI::__initialConnection()
{
	connect(m_pDrawPointAction, SIGNAL(triggered()), this, SLOT(getDrawPoint()));
	connect(m_pClearDataAction, SIGNAL(triggered()), this, SLOT(clearAllDrawData()));
}

void OpencvImageUI::getDrawPoint()
{
	clearAllDrawData();
	m_bIsAllowDrawPoint = true;
	m_srcImage.copyTo(m_interactiveImage);

}

void OpencvImageUI::clearAllDrawData()
{
	m_bIsAllowDrawPoint = false;
	m_interactiveImage.release();
	drawedPoint.clear();
	QVector<cv::Point>().swap(drawedPoint);
	showMatImage(m_srcImage);
}


