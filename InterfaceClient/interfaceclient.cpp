#include "interfaceclient.h"


InterfaceClient::InterfaceClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	//init log tw
	QStringList headers;
    headers << toString("序号") << toString("时间") << toString("动作");
	ui.logTW->setColumnCount(3);
	ui.logTW->setHorizontalHeaderLabels(headers);
	ui.logTW->setColumnWidth(0, 40);
	ui.logTW->setColumnWidth(1, 140);
	
	ui.presetL->setText(toString("复位"));

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
