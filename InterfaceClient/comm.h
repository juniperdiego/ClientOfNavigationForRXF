#ifndef COMMON_H
#define COMMON_H

#include <QTextCodec>
#include <QString>
#include <QDebug>

inline 
QString toString(const QByteArray& str)
{
	static QTextCodec* codec =QTextCodec::codecForName("GB18030");
	return codec->toUnicode(str);
}

#endif // COMMON_H
