#include "interfaceclient.h"


InterfaceClient::InterfaceClient(QWidget *parent)
	: QMainWindow(parent)
	, m_logIndex(1)
{
	ui.setupUi(this);


	//init log tw
	QStringList headers;
    headers << toString("序号") << toString("时间") << toString("动作");
	ui.logTW->setColumnCount(3);
	ui.logTW->setHorizontalHeaderLabels(headers);
	ui.logTW->setColumnWidth(0, 40);
	ui.logTW->setColumnWidth(1, 140);
	
	//init Parameter
	initPara();

	//init Return
	initReturn();

	//init component T
	initComT();

	//init component R
	initComR();

	//init Setting
	initSetting();

	//test
	addLog("adsadadfadf");
	addLog("adsadadfad111111111111111f");
}

InterfaceClient::~InterfaceClient()
{

}

void InterfaceClient::addLog(const QString& msg)
{
	int row = ui.logTW->rowCount();
	ui.logTW->insertRow(row);

	QTableWidgetItem* item0 = new QTableWidgetItem(QString::number(m_logIndex));
	item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.logTW->setItem(row, 0, item0);

	QTableWidgetItem* item1 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
	item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.logTW->setItem(row, 1, item1);

	QTableWidgetItem* item2 = new QTableWidgetItem(msg);
	ui.logTW->setItem(row, 2, item2);

	ui.logTW->setCurrentItem(NULL);

	++m_logIndex;
}

void InterfaceClient::clearLog()
{
	ui.logTW->clearContents();
	ui.logTW->setRowCount(0);
	m_logIndex = 0;
}


