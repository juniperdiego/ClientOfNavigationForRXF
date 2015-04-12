#include "interfaceclient.h"

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
}

void InterfaceClient::onRFBroClick()
{
	QDir path;
	path.cd("DATA");
    QString fileName = QFileDialog::getOpenFileName(this, toString("选择数据文件"),
                           path.absolutePath(), tr("DAT (*.dat)"));
    if (!fileName.endsWith(".dat", Qt::CaseInsensitive)) return;
    ui.rffileLE->setText(fileName);
}

void InterfaceClient::onRFIntoClick()
{

}

void InterfaceClient::onRGBroClick()
{
	QDir path;
	path.cd("DATA");
    QString fileName = QFileDialog::getOpenFileName(this, toString("选择数据文件"),
                           path.absolutePath(), tr("DAT (*.dat)"));
    if (!fileName.endsWith(".dat", Qt::CaseInsensitive)) return;
    ui.rgfileLE->setText(fileName);
}

void InterfaceClient::onRGIntoClick()
{

}

void InterfaceClient::onRMIntoClick()
{

}

void InterfaceClient::onRZMIntoClick()
{

}

void InterfaceClient::onRXIntoClick()
{

}

void InterfaceClient::setRWorkState(bool state)
{
	ui.rstateL->setText(state ? toString("天线收发工作模式") : toString("天线单发工作模式"));
}