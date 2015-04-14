#include "serversetting.h"

ServerSetting::ServerSetting(bool flag, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowTitle(toString("服务器设置"));
	m_wnd = qobject_cast<InterfaceClient*>(parent);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(switchConnection()));

	if(flag) //已连接
	{
		ui.spinBox_ip1->setReadOnly(true);
		ui.spinBox_ip2->setReadOnly(true);
		ui.spinBox_ip3->setReadOnly(true);
		ui.spinBox_ip4->setReadOnly(true);

		ui.pushButton->setText(toString("断开连接"));                                                          
	}
	else //未连接
	{
		ui.spinBox_ip1->setReadOnly(false);
		ui.spinBox_ip2->setReadOnly(false);
		ui.spinBox_ip3->setReadOnly(false);
		ui.spinBox_ip4->setReadOnly(false);

		ui.pushButton->setText(toString("连接"));                                                          
	}
	m_flag=flag;
}

ServerSetting::~ServerSetting()
{

}

void ServerSetting::setFlag(bool flag)
{
	m_flag = flag;
	if(flag) //已连接
	{
		ui.spinBox_ip1->setReadOnly(true);
		ui.spinBox_ip2->setReadOnly(true);
		ui.spinBox_ip3->setReadOnly(true);
		ui.spinBox_ip4->setReadOnly(true);

		ui.pushButton->setText(toString("断开连接"));                                                          
	}
	else //未连接
	{
		ui.spinBox_ip1->setReadOnly(false);
		ui.spinBox_ip2->setReadOnly(false);
		ui.spinBox_ip3->setReadOnly(false);
		ui.spinBox_ip4->setReadOnly(false);

		ui.pushButton->setText(toString("连接"));                                                          
	}
}
void ServerSetting::switchConnection()
{
	if(m_flag) //已连接
	{
		disconnectServer();
	}
	else //未连接
	{
		connectServer();
	}
}

void ServerSetting::connectServer()
{
	m_ipAddress = ui.spinBox_ip1->text() + "." + ui.spinBox_ip2->text() + "." + ui.spinBox_ip3->text() + "." + ui.spinBox_ip4->text();
	m_wnd->connectServer(m_ipAddress);
}

void ServerSetting::disconnectServer()
{
	m_wnd->disconnectServer();

	ui.spinBox_ip1->setReadOnly(false);
	ui.spinBox_ip2->setReadOnly(false);
	ui.spinBox_ip3->setReadOnly(false);
	ui.spinBox_ip4->setReadOnly(false);
	ui.pushButton->setText(toString("连接"));                                                          
	m_flag = false;
}
