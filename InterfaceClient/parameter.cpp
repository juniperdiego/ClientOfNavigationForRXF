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
	QProcess::startDetached("InterfaceServer.exe");
#if 0
	QByteArray sendBytes;
	QDataStream out(sendBytes);
	out<<TCP_FRAME_START_TAG;
	out<<2;
	out<<3.5;
	out<<4.6;
	out<<TCP_FRAME_END_TAG;

	m_socketP->write(sendBytes);
#endif
}

void InterfaceClient::rcvPState()
{
	remoteParamRecvFrame rpRF;
	int bufSize = rpRF.getFrameLen();
	char* buf = new char[bufSize];
	if (m_socketP->read(buf, bufSize) != bufSize)
	{
		logError(toString("数据接收错误"));
		return;
	}

	QByteArray rcvBytes(buf, bufSize);
	qDebug()<<rcvBytes.toHex();
	QDataStream in(&rcvBytes, QIODevice::ReadOnly);

	int header;
	in>>header;
	qDebug()<<header;

	//下面这个函数有问题，头parse的就不对，你看一下
	if (!rpRF.parseRecvTcpFrame((int*)buf, bufSize))
	{
		logError(toString("数据接收错误"));
		return;
	}

	vector<float> params = rpRF.getParamVec();
	qDebug()<<params[0];
}