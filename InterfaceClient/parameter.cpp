#include "interfaceclient.h"
#include "tcpSendFrame.h"


void InterfaceClient::initPara()
{
	ui.pv1LE->setValidator(m_doubleValid);
	ui.pa1LE->setValidator(m_doubleValid);
	ui.pa2LE->setValidator(m_doubleValid);
	ui.pa3LE->setValidator(m_doubleValid);
	ui.pa4LE->setValidator(m_doubleValid);
	ui.pa5LE->setValidator(m_doubleValid);
	ui.pc1LE->setValidator(m_doubleValid);
	ui.pc2LE->setValidator(m_doubleValid);
	ui.pc3LE->setValidator(m_doubleValid);
	ui.pc4LE->setValidator(m_doubleValid);

	connect(ui.pmodesendPB, SIGNAL(clicked()), this, SLOT(onPModeSendClick()));
	connect(ui.presetPB, SIGNAL(clicked()), this, SLOT(onPResetClick()));
	connect(ui.pmPB, SIGNAL(clicked()), this, SLOT(onPMeasureClick()));
}

void InterfaceClient::onPModeSendClick()
{
	remoteParamSendFrame rpSF;

	rpSF.setMode(ui.pmodeCO->currentIndex() == 0);

	vector<int> frame = rpSF.generateFrame();

	int *packet = new int[frame.size()];

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	m_socketP->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onPResetClick()
{

}

void InterfaceClient::onPMeasureClick()
{

}

void InterfaceClient::rcvPState()
{

}