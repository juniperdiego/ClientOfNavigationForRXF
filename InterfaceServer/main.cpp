#include "interfaceserver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	InterfaceServer w;
	w.show();
	return a.exec();
}
