#include "interfaceclient.h"
#include "tcpSendFrame.h"

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
	m_srCom = new PixelArray(6, 6, 2, false);
	rLayout->addWidget(m_srCom);
	ui.srW->setLayout(rLayout);

	//init T
	QHBoxLayout* tLayout = new QHBoxLayout;
	tLayout->setMargin(0);
	m_stCom = new PixelArray(16, 16, 2, false);
	tLayout->addWidget(m_stCom);
	ui.stW->setLayout(tLayout);

	connect(ui.szsendPB, SIGNAL(clicked()), this, SLOT(onSZSendClick()));
	connect(ui.sdsendPB, SIGNAL(clicked()), this, SLOT(onSDSendClick()));
	connect(ui.srsendPB, SIGNAL(clicked()), this, SLOT(onSRSendClick()));
	connect(ui.stsendPB, SIGNAL(clicked()), this, SLOT(onSRSendClick()));

	connect(ui.srfixCB, SIGNAL(toggled(bool)), this, SLOT(onSRToggled(bool)));
	connect(ui.srtestCB, SIGNAL(toggled(bool)), this, SLOT(onSRToggled(bool)));
	connect(ui.stfixCB, SIGNAL(toggled(bool)), this, SLOT(onSTToggled(bool)));
	connect(ui.sttestCB, SIGNAL(toggled(bool)), this, SLOT(onSTToggled(bool)));
}

void InterfaceClient::onSRToggled(bool state)
{
	if (state)
	{
		if (sender() == ui.srfixCB)
			ui.srtestCB->setChecked(false);
		else
			ui.srfixCB->setChecked(false);
	}
}

void InterfaceClient::onSTToggled(bool state)
{
	if (state)
	{
		if (sender() == ui.stfixCB)
			ui.sttestCB->setChecked(false);
		else
			ui.stfixCB->setChecked(false);
	}
}

void InterfaceClient::onSZSendClick()
{
	if (!checkInputValue(this, ui.saxLE, -180, 180, 3, 5.625) || 
		!checkInputValue(this, ui.sayLE, -180, 180, 3, 5.625) || 
		!checkInputValue(this, ui.sazLE, -180, 180, 3, 5.625))
		return;

	compRInstallErrorSendFrame crieSF;
	crieSF.set(ui.saxLE->text().toFloat(), ui.sayLE->text().toFloat(), ui.sazLE->text().toFloat()); 

	vector<int> frame = crieSF.generateFrame();

	int *packet = new int[frame.size()];

	htonlArray(packet, frame.size());

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	m_socketSR->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onSDSendClick()
{
	if (!checkInputValue(this, ui.sdxLE, -180, 180, 3, 5.625) || 
		!checkInputValue(this, ui.sdyLE, -180, 180, 3, 5.625))
		return;

	compRFixPointSendFrame crfpSF;
	crfpSF.set(ui.sdxLE->text().toFloat(), ui.sdyLE->text().toFloat()); 

	vector<int> frame = crfpSF.generateFrame();

	int *packet = new int[frame.size()];

	htonlArray(packet, frame.size());

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	m_socketSR->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onSRSendClick()
{
	if (!ui.srfixCB->isChecked() && !ui.srtestCB->isChecked())
		return;

	vector<vector<float>> angles;
	vector<vector<bool>> states;

	m_srCom->getAngleAndStates(angles, states);
	vector<int> frame;

	if (ui.srfixCB->isChecked())
	{
		compRCorrectionSendFrame crcSF;
		crcSF.setDegree(angles);
		crcSF.setEnable(states);
		frame = crcSF.generateFrame();
	}
	else
	{
		compRTestCodeSendFrame crtcSF;
		crtcSF.setEnable(states);
		frame = crtcSF.generateFrame();
	}

	int *packet = new int[frame.size()];

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	htonlArray(packet, frame.size());

	m_socketSR->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onSTSendClick()
{
	if (!ui.stfixCB->isChecked() && !ui.sttestCB->isChecked())
		return;

	vector<vector<float>> angles;
	vector<vector<bool>> states;

	m_stCom->getAngleAndStates(angles, states);
	vector<int> frame;

	if (ui.stfixCB->isChecked())
	{
		compTCorrectionSendFrame ctcSF;
		ctcSF.setDegree(angles);
		ctcSF.setEnable(states);
		frame = ctcSF.generateFrame();
	}
	else
	{
		compTTestCodeSendFrame cttcSF;
		cttcSF.setEnable(states);
		frame = cttcSF.generateFrame();
	}

	int *packet = new int[frame.size()];

	

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	htonlArray(packet, frame.size());
	m_socketST->write((char*)packet, frame.size() * sizeof(int));
}

