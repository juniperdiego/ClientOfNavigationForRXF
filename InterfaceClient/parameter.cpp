#include "interfaceclient.h"
#include "tcpSendFrame.h"
#include "tcpRecvFrame.h"
#include <QProcess>

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

void InterfaceClient::setPState(const vector<float>& states)
{
	ui.pv1LE->setText(QString::number(states[0]));
	ui.pa1LE->setText(QString::number(states[1]));
	ui.pa2LE->setText(QString::number(states[2]));
	ui.pa3LE->setText(QString::number(states[3]));
	ui.pa4LE->setText(QString::number(states[4]));
	ui.pa5LE->setText(QString::number(states[5]));
	ui.pc1LE->setText(QString::number(states[6]));
	ui.pc2LE->setText(QString::number(states[7]));
	ui.pc3LE->setText(QString::number(states[8]));
	ui.pc4LE->setText(QString::number(states[9]));
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
	remoteParamSendFrame rpSF;

	rpSF.setAntennaPattern(true);

	vector<int> frame = rpSF.generateFrame();

	int *packet = new int[frame.size()];

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	m_socketP->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onPMeasureClick()
{
	QProcess::startDetached("InterfaceServer.exe");
}

void InterfaceClient::rcvPState()
{
	remoteParamRecvFrame rpRF;
	vector<float> params;
	int bufSize = rpRF.getFrameLen();
	char* buf = new char[bufSize];
	if (m_socketP->read(buf, bufSize) != bufSize)
		goto ERROR;

	if (!rpRF.parseRecvTcpFrame((int*)buf, bufSize))
		goto ERROR;

	params = rpRF.getParamVec();

	if (params.size() != 10)
		goto ERROR;

	setPState(params);

	return;

ERROR:
	logError(toString("状态参数接收错误"));
	return;
}