#include "interfaceclient.h"


InterfaceClient::InterfaceClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	//init log tw
	QStringList headers;
    headers << toString("���") << toString("ʱ��") << toString("����");
	ui.logTW->setColumnCount(3);
	ui.logTW->setHorizontalHeaderLabels(headers);
	ui.logTW->setColumnWidth(0, 40);
	ui.logTW->setColumnWidth(1, 140);
	
	ui.presetL->setText(toString("��λ"));

	//init component T
	initComT();

	//init component R
	initComR();

	//init Setting
	initSetting();
}

InterfaceClient::~InterfaceClient()
{

}
