#pragma once

#include <QtWidgets>
#include <QHBoxLayout>
#include <QPushButton>
#include "import_dll_class.h"
#include "..\DealUI\ui_base.h"
#include "..\DealUI\pixture_ui.h"

#include <QLabel>


class LabMainForm : public QWidget
{
	Q_OBJECT

public:
	LabMainForm(QWidget *parent=Q_NULLPTR);
	~LabMainForm();

	private slots:
	void comfirmClicked();

private:
	void __setupUI();

private:
	std::shared_ptr<PixtureUI> m_pixtureUIPtr = NULL;
	std::shared_ptr<OpencvImageUI> m_OpencvImageUIPtr = NULL;

	QPushButton *m_pConfirmBtn = NULL;

	QImage m_QImg;

};
