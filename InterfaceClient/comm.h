#ifndef COMMON_H
#define COMMON_H

#include <QTextCodec>
#include <QString>
#include <QDebug>
#include <QMessageBox>


#include <vector>
using std::vector;

const int TCP_FRAME_START_TAG = 1234567890;
const int TCP_FRAME_END_TAG = -1234567890;

const int MAX_LOG_LINE=1000;

const int T_PORT=7000;
const int R_PORT=7001;
const int P_PORT=9000;
const int S_PORT=9001;
const int ST_PORT=8000;
const int SR_PORT=8002; 

inline 
QString toString(const QByteArray& str)
{
	static QTextCodec* codec =QTextCodec::codecForName("GB18030");
	return codec->toUnicode(str);
}

#endif // COMMON_H
