#include "interfaceclient.h"

void InterfaceClient::initComT()
{
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(4);
	m_tCom = new PixelArray(16, 16, false);
	layout->addWidget(m_tCom);

	ui.tab2->setLayout(layout);
}

void InterfaceClient::rcvTState()
{
	/*QTextCodec * codec =QTextCodec::codecForName("GB18030");
	QString info;

	int data[PACKAGE_LEN_TM/sizeof(int)];
	memset(data, 0, PACKAGE_LEN_TM);
	qint64 len = m_s1553Tm->read((char*)data, PACKAGE_LEN_TM);
	if(len!=PACKAGE_LEN_TM) 
	{
		info=codec->toUnicode("收到遥测数据，长度错误！");
		LogError(info);
		return;
	}

	if(data[0] != PACKAGE_HEADER)
	{
		info=codec->toUnicode("收到遥测数据，帧头错误！");
		LogError(info);
		return;
	}
	else if(data[PACKAGE_LEN_TM/sizeof(int)-1] != PACKAGE_TAIL)
	{
		info=codec->toUnicode("收到遥测数据，帧尾错误！");
		LogError(info);
		return;
	}

	quint16 dataTm[LEN_TM_W];
	memset(dataTm, 0, LEN_TM_W*sizeof(quint16));
	for(int i=0; i<LEN_TM_W; i++)
	{
		dataTm[i]=(quint16)data[i+PACKAGE_HEADER_LEN/sizeof(int)];
	}

	m_uiTmSys->RefreshTM((char*)dataTm);*/
}