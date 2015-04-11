#include "interfaceclient.h"

void InterfaceClient::initSetting()
{
	//init R
	QHBoxLayout* rLayout = new QHBoxLayout;
	rLayout->setMargin(0);
	srCom = new PixelArray(6, 6, true, false);
	rLayout->addWidget(srCom);
	ui.srW->setLayout(rLayout);

	//init T
	QHBoxLayout* tLayout = new QHBoxLayout;
	tLayout->setMargin(0);
	stCom = new PixelArray(16, 16, true, false);
	tLayout->addWidget(stCom);
	ui.stW->setLayout(tLayout);
}