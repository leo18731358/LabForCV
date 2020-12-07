#pragma once

#include <QtWidgets>
#include <QLabel>
#include <QToolBar>
#include <QVector>
#include <QPoint>
#include "opencv2\opencv.hpp"

class OpencvImageUI : public QWidget
{
	Q_OBJECT

public:
	OpencvImageUI(QWidget *parent=Q_NULLPTR);
	~OpencvImageUI();

	QString getPixelGrayValue(int x, int y);

	virtual void showMatImage(cv::Mat matData);

private:
	void __setupUI();
	void resizeEvent(QResizeEvent *event);
	void __initialConnection();

	private slots:
	void getDrawPoint();
	void clearAllDrawData();

public:
	QString m_strWindowName = "imageWindow";
	QLabel *m_pPositionLabel = NULL;
	QLabel *m_pGrayValueLabel = NULL;
	cv::Mat m_srcImage;
	cv::Mat m_interactiveImage;

	bool m_bIsAllowDrawPoint = false;
	QVector<cv::Point> drawedPoint;

private:
	
	QWidget *m_pWidgetMain = NULL;
	QToolBar *m_pToolBar = NULL;
	QAction *m_pDrawPointAction = NULL;
	QAction *m_pClearDataAction = NULL;


};
