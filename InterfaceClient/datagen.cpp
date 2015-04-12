#include "datagen.h"

DataGen::DataGen(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QDoubleValidator* dValidator = new QDoubleValidator(this);
	dValidator->setBottom(0);
	ui.zxLE->setValidator(dValidator);
	ui.zyLE->setValidator(dValidator);
	ui.zzLE->setValidator(dValidator);
	ui.zxsLE->setValidator(dValidator);
	ui.zysLE->setValidator(dValidator);
	ui.zzsLE->setValidator(dValidator);

	ui.gjLE->setValidator(dValidator);
	ui.fjLE->setValidator(dValidator);
	ui.pjLE->setValidator(dValidator);
	ui.gjsLE->setValidator(dValidator);
	ui.fjsLE->setValidator(dValidator);
	ui.pjsLE->setValidator(dValidator);

	connect(ui.fgenfilePB, SIGNAL(clicked()), this, SLOT(onFGenFileClick()));
	connect(ui.ggenfilePB, SIGNAL(clicked()), this, SLOT(onGGenFileClick()));
}

DataGen::~DataGen()
{

}

void DataGen::onFGenFileClick()
{
	QDir curPath;
	curPath.mkdir("DATA");
	curPath.cd("DATA");
    QString fileName = QFileDialog::getSaveFileName(this, toString("保存数据文件"),
                           curPath.absolutePath(), tr("DAT (*.dat)"));
	if (!fileName.endsWith(".dat", Qt::CaseInsensitive)) return;
    
	qDebug()<<fileName;

}

void DataGen::onGGenFileClick()
{
	QDir curPath;
	curPath.mkdir("DATA");
	curPath.cd("DATA");
    QString fileName = QFileDialog::getSaveFileName(this, toString("保存数据文件"),
                           curPath.absolutePath(), tr("DAT (*.dat)"));
	if (!fileName.endsWith(".dat", Qt::CaseInsensitive)) return;
    
	qDebug()<<fileName;
}