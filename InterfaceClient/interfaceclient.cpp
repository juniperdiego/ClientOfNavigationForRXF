#include "interfaceclient.h"

InterfaceClient::InterfaceClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//init code
	codec =QTextCodec::codecForName("GB18030");

	//init log tw
	QStringList headers;
    headers << codec->toUnicode("���") << codec->toUnicode("ʱ��") << codec->toUnicode("����");
	ui.logTW->setColumnCount(3);
	ui.logTW->setHorizontalHeaderLabels(headers);
	ui.logTW->setColumnWidth(0, 40);
	ui.logTW->setColumnWidth(1, 140);
	
	ui.presetL->setText(codec->toUnicode("��λ"));
}

InterfaceClient::~InterfaceClient()
{

}
