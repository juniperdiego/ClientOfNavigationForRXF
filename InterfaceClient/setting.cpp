#include "interfaceclient.h"

void InterfaceClient::initSetting()
{
	ui.saxLE->setValidator(m_angleValid);
	ui.sayLE->setValidator(m_angleValid);
	ui.sazLE->setValidator(m_angleValid);

	ui.sdxLE->setValidator(m_angleValid);
	ui.sdyLE->setValidator(m_angleValid);

	//init R
	QHBoxLayout* rLayout = new QHBoxLayout;
	rLayout->setMargin(0);
	m_srCom = new PixelArray(6, 6, true, false);
	rLayout->addWidget(m_srCom);
	ui.srW->setLayout(rLayout);

	//init T
	QHBoxLayout* tLayout = new QHBoxLayout;
	tLayout->setMargin(0);
	m_stCom = new PixelArray(16, 16, true, false);
	tLayout->addWidget(m_stCom);
	ui.stW->setLayout(tLayout);

	connect(ui.szsendPB, SIGNAL(clicked()), this, SLOT(onSZSendClick()));
	connect(ui.sdsendPB, SIGNAL(clicked()), this, SLOT(onSDSendClick()));
	connect(ui.srsendPB, SIGNAL(clicked()), this, SLOT(onSRSendClick()));
	connect(ui.stsendPB, SIGNAL(clicked()), this, SLOT(onSRSendClick()));
}

void InterfaceClient::onSZSendClick()
{
}

void InterfaceClient::onSDSendClick()
{
}

void InterfaceClient::onSRSendClick()
{
}

void InterfaceClient::onSTSendClick()
{
}