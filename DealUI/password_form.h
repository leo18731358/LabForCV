#pragma once

#include <QtWidgets>
#include <QLabel>
#include <QLineEdit>


enum PassWordClassify{ EXITMAINPROCESS, ENTRYCAMERASET };

class PasswordForm : public QWidget
{
	Q_OBJECT

public:
	PasswordForm(PassWordClassify pwc = PassWordClassify::EXITMAINPROCESS, QWidget *parent = Q_NULLPTR);
	~PasswordForm();

private:
	void __setupUI();
	void keyReleaseEvent(QKeyEvent *event);
	private slots:
	void __confirmPassword();
	void closeEvent(QCloseEvent *event);

signals:
	void confirmPassword();

private:
	QLabel *m_pPassInfo = NULL;
	QLineEdit *m_pPassEdit = NULL;
	PassWordClassify m_pwc;


};
