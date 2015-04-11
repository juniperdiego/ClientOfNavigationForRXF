#include "interfaceclient.h"

void InterfaceClient::initPara()
{
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
