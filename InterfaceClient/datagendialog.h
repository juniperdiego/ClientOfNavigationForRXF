#ifndef DATAGENDIALOG_H
#define DATAGENDIALOG_H

#include <QDialog>
#include <QDoubleValidator>
#include <QDir>
#include <QFileDialog>
#include "ui_datagendialog.h"
#include "comm.h"

class DataGenDialog : public QDialog
{
	Q_OBJECT

public:
	DataGenDialog(QWidget *parent = 0);
	~DataGenDialog();

private slots:
	void onFGenFileClick();
	void onGGenFileClick();

private:
	Ui::DataGenDialog ui;
};

#endif // DATAGEN_H
