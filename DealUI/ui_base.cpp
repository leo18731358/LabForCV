
#include "ui_base.h"


UIBase::UIBase(QObject *parent) :QObject(parent)
{

}

UIBase::~UIBase()
{

}

std::shared_ptr<PixtureUI> UIBase::getPixtureUIInstance()
{
	m_pPictureUIPtr = std::make_shared<PixtureUI>();
	return m_pPictureUIPtr;
}

std::shared_ptr<PasswordForm> UIBase::getPasswordFormInstance(PassWordClassify pwc)
{
	m_pPasswrdFormPtr = std::make_shared<PasswordForm>(pwc);
	return m_pPasswrdFormPtr;

}

std::shared_ptr<OpencvImageUI> UIBase::getOpencvImageUIInstnce()
{
	m_pOpencvImageUIPtr = std::make_shared<OpencvImageUI>();
	return m_pOpencvImageUIPtr;
}


UIBase* UIBase::instance = NULL;
DEALUI_EXPORT UIBase* getUIBaseInstance()
{
	if (NULL == UIBase::instance)
	{
		UIBase::instance = new UIBase();
	}
	return UIBase::instance;
}
