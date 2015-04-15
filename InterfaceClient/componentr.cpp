#include "interfaceclient.h"

void InterfaceClient::initComR()
{
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(4);
	m_rCom = new PixelArray(6, 6, false);
	layout->addWidget(m_rCom);

	ui.tab3->setLayout(layout);
}

void InterfaceClient::rcvRState()
{

}