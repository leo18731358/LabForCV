#pragma once

#include "dealui_global.h"
#include <QObject>
#include <QMap>
#include <iostream>
#include <memory>
#include "pixture_ui.h"
#include "password_form.h"
#include "opencv_image_ui.h"



class DEALUI_EXPORT UIBase : QObject
{
	Q_OBJECT
public:
	UIBase(QObject *parent=Q_NULLPTR);
	~UIBase();

public:

	virtual std::shared_ptr<PixtureUI> getPixtureUIInstance();
	virtual std::shared_ptr<OpencvImageUI> getOpencvImageUIInstnce();
	virtual std::shared_ptr<PasswordForm> getPasswordFormInstance(PassWordClassify pwc = PassWordClassify::EXITMAINPROCESS);

public:
	std::shared_ptr<PixtureUI> m_pPictureUIPtr = NULL;                      //最后一次创建的实例
	std::shared_ptr<PasswordForm> m_pPasswrdFormPtr = NULL;                 //最后一次创建的实例
	std::shared_ptr<OpencvImageUI> m_pOpencvImageUIPtr = NULL;              //最后一次创建的实例

	static UIBase* instance;
};

extern "C"
{
	DEALUI_EXPORT UIBase* getUIBaseInstance();
}
