#ifndef COMMON_H
#define COMMON_H

#include <QTextCodec>
#include <QString>
#include <QDebug>

#define MAX_LOG_LINE 1000

inline 
QString toString(const QByteArray& str)
{
	static QTextCodec* codec =QTextCodec::codecForName("GB18030");
	return codec->toUnicode(str);
}

#endif // COMMON_H
