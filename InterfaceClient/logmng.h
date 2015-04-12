#ifndef LOGMNG_H
#define LOGMNG_H

#include "comm.h"
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QTableWidget>

enum LogTypeEnum
{
	LOG_TYPE_MESSAGE,
	LOG_TYPE_WARNNING,
	LOG_TYPE_ERROR
};

class LogMng
{
public:
	LogMng(const QString& prefix);
	~LogMng();

public:
	void log(LogTypeEnum type, const QString& msg);

private:
	QString getNewFileName();

private:
	QFile	m_file;
	QString	m_prefix;


	int m_fileSize;
	int m_sizeOfSingleFile;
	QString	m_path;
};

#endif // LOGMNG_H
