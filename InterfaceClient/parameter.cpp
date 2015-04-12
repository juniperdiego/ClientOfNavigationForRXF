#include "interfaceclient.h"

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

}

void InterfaceClient::onPResetClick()
{

}

void InterfaceClient::onPMeasureClick()
{

}
