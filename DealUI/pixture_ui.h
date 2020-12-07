#pragma once

#include <QtWidgets>
#include <QImage>  
#include <QPixmap>  

class  PixtureUI : public QWidget
{
	Q_OBJECT

public:
	PixtureUI(QWidget *parent=Q_NULLPTR);
	~PixtureUI();

	 virtual void showImage(QImage image);

private:
	double m_dScale;
	QBrush m_cBrush;
	QImage m_cImage;
	int m_nXPtInterval;
	int m_nYPtInterval;
	QPoint m_cOldPos;
	bool m_bIsPressed;


protected:
	void paintEvent(QPaintEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	
};
