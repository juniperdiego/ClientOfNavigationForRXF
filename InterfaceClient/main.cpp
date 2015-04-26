#include "interfaceclient.h"
#include <QtWidgets/QApplication>
#include <QDesktopWidget>

#ifdef UT
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
	QApplication app(argc, argv);

	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")) ;

#ifdef UT
	test_dataGenForAerocraft();
	return 0;	
	
	
	int aaa = 0xC1480000;//12.5
	float *fp = (float*) (&aaa);

	qDebug() << *fp ;
	return 0;
#endif


	InterfaceClient* win = new InterfaceClient;
	InterfaceClient::s_wnd = win;
	win->resize(800, 600);
	win->move((app.desktop()->width() - win->width()) / 2, (app.desktop()->height() - win->height()) / 2);
	win->show();
	return app.exec();
}
