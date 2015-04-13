#ifndef DATAGENDIALOG_H
#define DATAGENDIALOG_H

#include <QDialog>
#include <QDoubleValidator>
#include <QDir>
#include <QFileDialog>
#include "ui_datagendialog.h"
#include "comm.h"
#include "sourcecodemodel.h"

const int LEN_DATA=104; 

class DataGenDialog : public QDialog
{
	Q_OBJECT

public:
	DataGenDialog(QWidget *parent = 0);
	~DataGenDialog();

public:
	void setIsOnTrack(bool isOnTrack);

private slots:
	void onFGenFileClick();
	void onGGenFileClick();

private:
	bool checkCraftParameter();

private:
	Ui::DataGenDialog ui;

	SourceCodeModel* m_craftModel;
};

#endif // DATAGEN_H
