#include "interfaceclient.h"

void InterfaceClient::initReturn()
{
	connect(ui.rfgenPB, SIGNAL(clicked()), this, SLOT(onRFGenClick()));
	connect(ui.rfinPB, SIGNAL(clicked()), this, SLOT(onRFIntoClick()));
	connect(ui.rffileTB, SIGNAL(clicked()), this, SLOT(onRFBroClick()));
	connect(ui.rggenPB, SIGNAL(clicked()), this, SLOT(onRGGenClick()));
	connect(ui.rginPB, SIGNAL(clicked()), this, SLOT(onRGIntoClick()));
	connect(ui.rgfileTB, SIGNAL(clicked()), this, SLOT(onRGBroClick()));
	connect(ui.rminPB, SIGNAL(clicked()), this, SLOT(onRMIntoClick()));
	connect(ui.rzminPB, SIGNAL(clicked()), this, SLOT(onRZMIntoClick()));
	connect(ui.rxinPB, SIGNAL(clicked()), this, SLOT(onRXIntoClick()));
}

void InterfaceClient::onRFGenClick()
{

}

void InterfaceClient::onRFBroClick()
{
	QDir path;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                           path.absolutePath(), tr("BIN (*.bin)"));
    if (!fileName.endsWith(".bin")) return;
    ui.rffileLE->setText(fileName);
}

void InterfaceClient::onRFIntoClick()
{

}

void InterfaceClient::onRGGenClick()
{

}

void InterfaceClient::onRGBroClick()
{
	QDir path;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                           path.absolutePath(), tr("BIN (*.bin)"));
    if (!fileName.endsWith(".bin")) return;
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