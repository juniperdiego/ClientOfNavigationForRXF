#include "interfaceclient.h"
#include "tcpSendFrame.h"
#include "tcpRecvFrame.h"

void InterfaceClient::initReturn()
{
	ui.rzbLE->setValidator(m_doubleValid);
	ui.rzpLE->setValidator(m_doubleValid);
	ui.rzqLE->setValidator(m_angleValid);
	ui.rzjLE->setValidator(m_angleValid);
	ui.rzfLE->setValidator(m_angleValid);
	ui.rzdLE->setValidator(m_angleValid);

	ui.rdhLE->setValidator(m_doubleValid);
	ui.rdjLE->setValidator(m_angleValid);
	ui.rdwLE->setValidator(m_angleValid);

	ui.rxfLE->setValidator(m_angleValid);
	ui.rxzLE->setValidator(m_angleValid);

	ui.ryfLE->setValidator(m_angleValid);
	ui.ryzLE->setValidator(m_angleValid);

	connect(ui.rfgenPB, SIGNAL(clicked()), this, SLOT(onDataGen()));
	connect(ui.rfinPB, SIGNAL(clicked()), this, SLOT(onRFIntoClick()));
	connect(ui.rffileTB, SIGNAL(clicked()), this, SLOT(onRFBroClick()));
	connect(ui.rggenPB, SIGNAL(clicked()), this, SLOT(onDataGen()));
	connect(ui.rginPB, SIGNAL(clicked()), this, SLOT(onRGIntoClick()));
	connect(ui.rgfileTB, SIGNAL(clicked()), this, SLOT(onRGBroClick()));
	connect(ui.rminPB, SIGNAL(clicked()), this, SLOT(onRMIntoClick()));
	connect(ui.rzminPB, SIGNAL(clicked()), this, SLOT(onRZMIntoClick()));
	connect(ui.rxinPB, SIGNAL(clicked()), this, SLOT(onRXIntoClick()));

	connect(ui.rz1useCB, SIGNAL(toggled(bool)), this, SLOT(onAvailToggled(bool)));
	connect(ui.rz2useCB, SIGNAL(toggled(bool)), this, SLOT(onAvailToggled(bool)));
	connect(ui.rz3useCB, SIGNAL(toggled(bool)), this, SLOT(onAvailToggled(bool)));
	connect(ui.rduseCB, SIGNAL(toggled(bool)), this, SLOT(onAvailToggled(bool)));
}

void InterfaceClient::onAvailToggled(bool state)
{
	if (state)
	{
		QList<QAbstractButton*> buttons = ui.availBG->buttons();
		for (int i = 0; i <buttons.count(); ++i)
		{
			if (buttons[i] != sender())
			{
				buttons[i]->setChecked(false);
			}
		}
	}
}

char InterfaceClient::getWhichAvail()
{
	if (ui.rz1useCB->isChecked())
		return 0x11;
	else if (ui.rz2useCB->isChecked())
		return 0x22;
	else if (ui.rz3useCB->isChecked())
		return 0x33;
	else if (ui.rduseCB->isChecked())
		return 0x44;
	else
		return 0x55;
}

void InterfaceClient::onRFBroClick()
{
	QDir path;
	path.cd("DATA");
    QString fileName = QFileDialog::getOpenFileName(this, toString("选择飞行器数据文件"),
                           path.absolutePath(), tr("DAT (*.dat)"));
    if (!fileName.endsWith(".dat", Qt::CaseInsensitive)) return;
    ui.rffileLE->setText(fileName);
}

void InterfaceClient::onRFIntoClick()
{
	QString fileName = ui.rffileLE->text();
	if (fileName.isEmpty())	return;

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return;
    QByteArray fData = file.readAll();

	aerocraftSendFrame aeSF;
	vector<int> frame = aeSF.generateFrame(fData.data(), fData.size());

	int *packet = new int[frame.size()];

	htonlArray(packet, frame.size());

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	m_socketS->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onRGBroClick()
{
	QDir path;
	path.cd("DATA");
    QString fileName = QFileDialog::getOpenFileName(this, toString("选择广播数据文件"),
                           path.absolutePath(), tr("DAT (*.dat)"));
    if (!fileName.endsWith(".dat", Qt::CaseInsensitive)) return;
    ui.rgfileLE->setText(fileName);
}

void InterfaceClient::onRGIntoClick()
{
	QString fileName = ui.rgfileLE->text();
	if (fileName.isEmpty())	return;

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return;
    QByteArray fData = file.readAll();

	broadcastSendFrame bcSF;
	vector<int> frame = bcSF.generateFrame(fData.data(), fData.size());

	int *packet = new int[frame.size()];

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	htonlArray(packet, frame.size());

	m_socketS->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onRMIntoClick()
{
	groundInjectParamSendFrame gipSF;
	gipSF.setYMD(ui.tySB->value(), ui.tmSB->value(), ui.tdSB->value());
	gipSF.setHMS(ui.thSB->value(), ui.tmmSB->value(), ui.tsSB->value(), ui.tmsSB->value());
	gipSF.setSatelliteParam(ui.rzbLE->text().toFloat(), ui.rzpLE->text().toFloat(), ui.rzqLE->text().toFloat(), 
		ui.rzjLE->text().toFloat(), ui.rzfLE->text().toFloat(), ui.rzdLE->text().toFloat());
	gipSF.setGroundParam(ui.rdhLE->text().toFloat(), ui.rdjLE->text().toFloat(), ui.rdwLE->text().toFloat());
	gipSF.setWhichAvail(getWhichAvail());

	vector<int> frame = gipSF.generateFrame();

	int *packet = new int[frame.size()];

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	htonlArray(packet, frame.size());

	m_socketS->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onRZMIntoClick()
{
	aerocraftDirectionSendFrame adSF;
	adSF.set(ui.rzmCO->currentIndex() == 0);

	vector<int> frame = adSF.generateFrame();

	int *packet = new int[frame.size()];

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	htonlArray(packet, frame.size());

	m_socketS->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::onRXIntoClick()
{
	phasedArrayRadaSendFrame parSF;
	parSF.setDirectionDegree(ui.rxfLE->text().toFloat());
	parSF.setCenterDegree(ui.rxzLE->text().toFloat());

	vector<int> frame = parSF.generateFrame();

	int *packet = new int[frame.size()];

	for(int i = 0; i < frame.size(); i++)
		packet[i] = frame[i];

	htonlArray(packet, frame.size());

	m_socketS->write((char*)packet, frame.size() * sizeof(int));
}

void InterfaceClient::setRWorkState(char avilable, bool status1, bool status2)
{
	switch (avilable)
	{
	case 0x0: ui.avilableL->setText(toString("地面站")); break;
	case 0x1: ui.avilableL->setText(toString("中继星1#")); break;
	case 0x2: ui.avilableL->setText(toString("中继星2#")); break;
	case 0x3: ui.avilableL->setText(toString("中继星3#")); break;
	default: break;
	}

	ui.status1L->setText(status1 ? toString("注入角度") : toString("星上计算"));
	ui.status2L->setText(status2 ? toString("再入轨道") : toString("在轨运行"));
}

void InterfaceClient::rcvSState()
{
	injectParamRecvFrame ipRF;

	int bufSize = ipRF.getFrameLen();
	char* buf = new char[bufSize];
	if (m_socketP->read(buf, bufSize) != bufSize)
		goto ERROR;

	if (!ipRF.parseRecvTcpFrame((int*)buf, bufSize))
		goto ERROR;

	ui.ryfLE->setText(QString::number(ipRF.getDirectionDegree()));
	ui.ryzLE->setText(QString::number(ipRF.getCenterDegree()));
	ui.rynLE->setText(QString::number(ipRF.getTotalCmdNum()));
	ui.rysLE->setText(QString::number(ipRF.getSuccessCmdNum()));
	setRWorkState(ipRF.getWhichAvilable(), ipRF.getWorkingStatus1(), ipRF.getWorkingStatus2());

ERROR:
	logError(toString("测控参数接收错误"));
	return;
}