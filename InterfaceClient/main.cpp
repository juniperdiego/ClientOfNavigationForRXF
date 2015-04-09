#include "interfaceclient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")) ;
	
	InterfaceClient w;
	w.show();
	return a.exec();
}
