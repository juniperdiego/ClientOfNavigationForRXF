#include "logmng.h"

LogMng::LogMng(const QString& prefix)
	: m_prefix(prefix)
	, m_fileSize(0)
	, m_sizeOfSingleFile(500000000)
{
	QDir curPath;
	curPath.mkdir("LOG");
	curPath.cd("LOG");
	m_path = curPath.absolutePath();


	m_file.setFileName(getNewFileName());
	qDebug()<<m_file.fileName();
}

LogMng::~LogMng()
{
	if (m_file.isOpen())
		m_file.close();
}

QString LogMng::getNewFileName()
{
	QString timeStr = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	return m_path + "\\" + m_prefix + "_" + timeStr + ".log"; 
}

void LogMng::log(LogTypeEnum type, const QString& msg)
{
	if (!m_file.isOpen())
	{
		if (!m_file.open(QIODevice::Append | QIODevice::Text))
			return;
	}

	if((m_fileSize+msg.length()) >= m_sizeOfSingleFile)
	{
		m_file.close();
		m_file.setFileName(getNewFileName());
		if(!m_file.open(QIODevice::Append | QIODevice::Text)) 
			return;

		m_fileSize = 0;
	}

	m_fileSize += m_file.write((qPrintable(msg)));
	m_file.flush();
}

