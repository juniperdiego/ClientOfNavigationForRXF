#include "serversetting.h"

ServerSetting::ServerSetting(bool flag, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowTitle(toString("����������"));
	m_wnd = qobject_cast<InterfaceClient*>(parent);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(switchConnection()));

	if(flag) //������
	{
		ui.spinBox_ip1->setReadOnly(true);
		ui.spinBox_ip2->setReadOnly(true);
		ui.spinBox_ip3->setReadOnly(true);
		ui.spinBox_ip4->setReadOnly(true);

		ui.pushButton->setText(toString("�Ͽ�����"));                                                          
	}
	else //δ����
	{
		ui.spinBox_ip1->setReadOnly(false);
		ui.spinBox_ip2->setReadOnly(false);
		ui.spinBox_ip3->setReadOnly(false);
		ui.spinBox_ip4->setReadOnly(false);

		ui.pushButton->setText(toString("����"));                                                          
	}
	m_flag=flag;
}

ServerSetting::~ServerSetting()
{

}

void ServerSetting::switchConnection()
{
	if(m_flag) //������
	{
		disconnectServer();
	}
	else //δ����
	{
		connectServer();
	}
}

void ServerSetting::connectServer()
{
	m_ipAddress = ui.spinBox_ip1->text() + "." + ui.spinBox_ip2->text() + "." + ui.spinBox_ip3->text() + "." + ui.spinBox_ip4->text();
	//m_wnd->connectServer(m_ipAddress);
}

void ServerSetting::disconnectServer()
{
	//m_wnd->disconnectServer();

	ui.spinBox_ip1->setReadOnly(false);
	ui.spinBox_ip2->setReadOnly(false);
	ui.spinBox_ip3->setReadOnly(false);
	ui.spinBox_ip4->setReadOnly(false);
	ui.pushButton->setText(toString("����"));                                                          
	m_flag = false;
}
