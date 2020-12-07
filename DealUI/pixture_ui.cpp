#include "pixture_ui.h"
#include <QStyleOption>
#include <QPainter>

PixtureUI::PixtureUI(QWidget *parent): QWidget(parent)
{
	m_cBrush = QBrush(Qt::black);
	m_dScale = 1.0;
	m_nXPtInterval = 0;
	m_nYPtInterval = 0;
	m_bIsPressed = false;
}

PixtureUI::~PixtureUI()
{
}

void PixtureUI::showImage(QImage img)
{
	m_cImage = img;
	this->update();
}

void PixtureUI::wheelEvent(QWheelEvent *event)
{
	int value = event->delta();
	double origenScale = m_dScale;
	QPoint pos = event->pos();

	if (value > 0)
	{
		m_dScale *= 1.1;
	}
	if (value < 0)
	{
		m_dScale *= 0.9;
	}
	m_cOldPos = pos;
	this->update();
}

void PixtureUI::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_cOldPos = event->pos();
		m_bIsPressed = true;
	}
}

void PixtureUI::mouseMoveEvent(QMouseEvent *event)
{
	if (!m_bIsPressed)
	{
		return QWidget::mouseMoveEvent(event);
	}

	this->setCursor(Qt::SizeAllCursor);
	QPoint pos = event->pos();
	int xPtInterval = pos.x() - m_cOldPos.x();
	int yPtInterval = pos.y() - m_cOldPos.y();

	m_nXPtInterval += xPtInterval;
	m_nYPtInterval += yPtInterval;

	m_cOldPos = pos;
	this->update();
}

void PixtureUI::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bIsPressed = false;
		this->setCursor(Qt::ArrowCursor);
	}
}

void PixtureUI::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_dScale = 1.0;
		m_nXPtInterval = 0;
		m_nYPtInterval = 0;
		this->update();
	}
}
void PixtureUI::paintEvent(QPaintEvent *event)
{
	// 绘制样式
	Q_UNUSED(event);
	QStyleOption opt;
	opt.init(this);
	QPainter painter(this);
	painter.setBackground(m_cBrush);
	painter.eraseRect(rect());
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

	if (m_cImage.isNull())
		return QWidget::paintEvent(event);

	// 根据窗口计算应该显示的图片的大小
	int width = qMin(m_cImage.width(), this->width());
	int height = width * 1.0 / (m_cImage.width() * 1.0 / m_cImage.height());
	height = qMin(height, this->height());
	width = height * 1.0 * (m_cImage.width() * 1.0 / m_cImage.height());

	// 平移
	painter.translate(this->width() / 2 + m_nXPtInterval, this->height() / 2 + m_nYPtInterval);

	// 缩放
	painter.scale(m_dScale, m_dScale);

	// 绘制图像
	QRect picRect(-width / 2, -height / 2, width, height);
	painter.drawImage(picRect, m_cImage);

}

