#include "interfaceclient.h"
#include <QBrush>


InterfaceClient::InterfaceClient(QWidget *parent)
	: QMainWindow(parent)
	, m_serverDialog(NULL)
	, m_genDataDialog(NULL)
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
	ui.logTW->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//init validator
	m_angleValid = new QDoubleValidator(0, 360, 3, this);
	m_doubleValid = new QDoubleValidator(this);
	m_doubleValid->setBottom(0);
		
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

	//init menu
	connect(ui.actionNetSet, SIGNAL(triggered()), this, SLOT(onServerSetting()));
	connect(ui.actionGenData, SIGNAL(triggered()), this, SLOT(onDataGen()));

	//init log 
	m_logMng = new LogMng("Client");

	//test
	addLog(LOG_TYPE_MESSAGE, "adsadadfadf");
	addLog(LOG_TYPE_WARNNING, "系统一切正常");
	addLog(LOG_TYPE_ERROR, "系统出错");
	addLog(LOG_TYPE_ERROR, "系统出错");
	addLog(LOG_TYPE_ERROR, "系统出错");
	addLog(LOG_TYPE_ERROR, "系统出错");
}

InterfaceClient::~InterfaceClient()
{
	delete m_logMng;
}

void InterfaceClient::onServerSetting()
{
	if (m_serverDialog == NULL)
		m_serverDialog = new ServerSetting(false, this);
	m_serverDialog->exec();
}

void InterfaceClient::onDataGen()
{
	if (m_genDataDialog == NULL)
		m_genDataDialog = new DataGenDialog(this);
	m_genDataDialog->show();
	m_genDataDialog->raise();
}

void InterfaceClient::addLog(LogTypeEnum type,const char* msg)
{
	int row = ui.logTW->rowCount();
	if (row >= MAX_LOG_LINE)
		ui.logTW->removeRow(0);

	row = ui.logTW->rowCount();
	ui.logTW->insertRow(row);

	QTableWidgetItem* item0 = new QTableWidgetItem(QString::number(m_logIndex));
	if (type != LOG_TYPE_MESSAGE) item0->setForeground(type == LOG_TYPE_ERROR ? QBrush(Qt::red) : QBrush(Qt::blue));
	item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.logTW->setItem(row, 0, item0);

	QTableWidgetItem* item1 = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
	if (type != LOG_TYPE_MESSAGE) item1->setForeground(type == LOG_TYPE_ERROR ? QBrush(Qt::red) : QBrush(Qt::blue));
	item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui.logTW->setItem(row, 1, item1);

	QTableWidgetItem* item2 = new QTableWidgetItem(toString(msg));
	if (type != LOG_TYPE_MESSAGE) item2->setForeground(type == LOG_TYPE_ERROR ? QBrush(Qt::red) : QBrush(Qt::blue));
	ui.logTW->setItem(row, 2, item2);

	ui.logTW->setCurrentItem(NULL);
	ui.logTW->scrollToBottom();
	
	++m_logIndex;

	if (ui.logCB->isChecked())
	{
		QString logStr = item0->text() + " \t" + item1->text() + " \t" + item2->text() + "\n";
		m_logMng->log(type, logStr);
	}
}

void InterfaceClient::clearLog()
{
	ui.logTW->clearContents();
	ui.logTW->setRowCount(0);
	m_logIndex = 0;
}


