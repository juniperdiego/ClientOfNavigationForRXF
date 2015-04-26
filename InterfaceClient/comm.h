#ifndef COMMON_H
#define COMMON_H

#include <QTextCodec>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>


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

extern void htonlArray(int *p, int size);

extern bool checkInputValue(QWidget* parent, QLineEdit* inputLE, float bottom, float top, int prec, float lsb);

inline 
QString toString(const QByteArray& str)
{
	static QTextCodec* codec =QTextCodec::codecForName("GB18030");
	return codec->toUnicode(str);
}

inline
bool isZero(float value)
{
	if(value > -1E6 && value < 1E6)
		return true;

	return false;
}

inline
uchar revChar(uchar c)
{
    c = (c & 0xaa) >> 1 | (c & 0x55) << 1;
    c = (c & 0xcc) >> 2 | (c & 0x33) << 2;
    c = (c & 0xf0) >> 4 | (c & 0x0f) << 4;

    return c;
}

inline
void revBuf(char* buf, int size)
{
	for (int i = 0; i < size; ++i)
	{
		buf[i] = revChar(buf[i]);
	}
}

#endif // COMMON_H
