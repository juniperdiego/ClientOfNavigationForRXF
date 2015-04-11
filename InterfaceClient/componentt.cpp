#include "interfaceclient.h"

void InterfaceClient::initComT()
{
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(4);
	m_tCom = new PixelArray(16, 16, false);
	layout->addWidget(m_tCom);

	ui.tab2->setLayout(layout);
}