#include "interfaceclient.h"

void InterfaceClient::initComR()
{
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(4);
	rCom = new PixelArray(6, 6, false);
	layout->addWidget(rCom);

	ui.tab3->setLayout(layout);
}