#include "interfaceclient.h"
#include <QtWidgets/QApplication>

#if 1
#include "dataGen.h"

void test_dataGenForAerocraft()
{
	//just for test
	dataGenForAerocraft d;
	d.setMode(true);
	d.setPos(7000, -7000, 7000);
	d.setVelocity(0.0015*100, -0.0015*100, 0.0015*100);
	d.setAngle(0.0256*2, -0.0256*2, 0.0256*2);
	d.setPalstance(0.00512*2, -0.00512*2, 0.00512*100);

	char *p = new char[d.getBufSize()];

	d.generate(p, d.getBufSize());
	qDebug() << d.getBufSize() ;

	for(int i = 0; i < d.getBufSize();i ++)
	{
		//std::cout <<std::hex << p[i] << "\t" ;
		qDebug() << i<<hex  <<(p[i]&0xff) << "\t";
		//printf("%2x ", p[i]&0xff);
	}
	
	delete p;
}

#endif

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")) ;

	test_dataGenForAerocraft();
	return 0;

	InterfaceClient w;
	w.show();
	return a.exec();
}
