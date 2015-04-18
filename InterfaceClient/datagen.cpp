#include "dataGen.h"
#include <algorithm>
#include <QtDebug>

dataGen::dataGen(char dataHeader, char cmd, char dataLen)
{
	m_dataHeader = dataHeader;
	m_cmd = cmd;
	m_dataLen = dataLen;
}

dataGen::~dataGen()
{
}

int dataGen::getBufSize()
{
	return m_dataLen + 4;
}

dataGenForAerocraft::dataGenForAerocraft()
	:dataGen(0x91, 0x55, 0x1f)
{
	
}

void dataGenForAerocraft::setMode(bool isOnTrack)
{
	m_isOnTrack = isOnTrack;
}

void dataGenForAerocraft::setPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

		
void dataGenForAerocraft::setVelocity(float vx, float vy, float vz)
{
	m_vx = vx;
	m_vy = vy;
	m_vz = vz;
}
void dataGenForAerocraft::setAngle(float a1, float a2, float a3)
{
	m_angle1 = a1;
	m_angle2 = a2;
	m_angle3 = a3;
}
void dataGenForAerocraft::setPalstance(float p1, float p2, float p3)
{
	m_p1 = p1;
	m_p2 = p2;
	m_p3 = p3;
}

void dataGenForAerocraft::generate(char *buf, int size)
{
	float precision = 0.0f;
	buf[0] = m_dataHeader;
	buf[1] = m_cmd;
	buf[2] = m_dataLen;

	if(m_isOnTrack)
		buf[3] = 0x3C;//在轨段数据
	else
		buf[3] = 0xC3;//再入段数据

	unsigned int x = qRound(abs(m_x)/0.001f);
	buf[4] = (x >> 16) & 0xFF;
	if(m_x < 0)
		buf[4] = buf[4] | 0x80;
	buf[5] = (x >> 8) & 0xFF;
	buf[6] = x  & 0xFF;

	unsigned int y = qRound(abs(m_y)/0.001f);
	buf[7] = (y >> 16) & 0xFF;
	if(m_y < 0)
		buf[7] = buf[7] | 0x80;
	buf[8] = (y >> 8) & 0xFF;
	buf[9] = y  & 0xFF;

	unsigned int z = qRound(abs(m_z)/0.001f);
	buf[10] = (z >> 16) & 0xFF;
	if(m_z < 0)
		buf[10] = buf[10] | 0x80;
	buf[11] = (z >> 8) & 0xFF;
	buf[12] = z  & 0xFF;

	unsigned int vx = qRound(abs(m_vx)/0.0015f);
	buf[13] = (vx >> 16) & 0xFF;
	if(m_vx < 0)
		buf[13] = buf[13] | 0x80;
	buf[14] = (vx >> 8) & 0xFF;
	buf[15] = vx  & 0xFF;

	unsigned int vy = qRound(abs(m_vy)/0.0015f);
	buf[16] = (vy >> 16) & 0xFF;
	if(m_vy < 0)
		buf[16] = buf[16] | 0x80;
	buf[17] = (vy>> 8) & 0xFF;
	buf[18] = vy  & 0xFF;

	unsigned int vz = qRound(abs(m_vz)/0.0015f);
	buf[19] = (vz >> 16) & 0xFF;
	if(m_vz < 0)
		buf[19] = buf[19] | 0x80;
	buf[20] = (vz>> 8) & 0xFF;
	buf[21] = vz  & 0xFF;


	if(m_isOnTrack)
		precision = 0.0256f;
	else
		precision = 0.006f;

	unsigned int a1 = qRound(abs(m_angle1)/precision);
	buf[22] = (a1>> 8) & 0xFF;
	if(m_angle1 < 0)
		buf[22] = buf[22] | 0x80;
	buf[23] = a1  & 0xFF;

	unsigned int a2 = qRound(abs(m_angle2)/precision);
	buf[24] = (a2>> 8) & 0xFF;
	if(m_angle2 < 0)
		buf[24] = buf[24] | 0x80;
	buf[25] = a2  & 0xFF;

	unsigned int a3 = qRound(abs(m_angle3)/precision);
	buf[26] = (a3>> 8) & 0xFF;
	if(m_angle3 < 0)
		buf[26] = buf[26] | 0x80;
	buf[27] = a3  & 0xFF;

	if(m_isOnTrack)
		precision = 0.00512f;
	else
		precision = 0.0035f;

	unsigned int p1 = qRound(abs(m_p1)/precision);
	buf[28] = (p1>> 8) & 0xFF;
	if(m_p1 < 0)
		buf[28] = buf[28] | 0x80;
	buf[29] = p1  & 0xFF;

	unsigned int p2 = qRound(abs(m_p2)/precision);
	buf[30] = (p2>> 8) & 0xFF;
	if(m_p2 < 0)
		buf[30] = buf[30] | 0x80;
	buf[31] = p2  & 0xFF;

	unsigned int p3 = qRound(abs(m_p3)/precision);
	buf[32] = (p3>> 8) & 0xFF;
	if(m_p3 < 0)
		buf[32] = buf[32] | 0x80;
	buf[33] = p3  & 0xFF;

	buf[34] = 0x00;

	for(int i = 3; i < getBufSize() -1 ;i++)
		buf[34] = buf[34] ^ buf[i];
}

dataGenForBroadcast::dataGenForBroadcast()
	:dataGen(0x91, 0xAA, 0x06)
{
}

void dataGenForBroadcast::setYMD(int y, int m, int d)
{
	m_year = y;
	m_month = m;
	m_day =d;
}

void dataGenForBroadcast::setHMS(int h, int m, int s, int ms)
{
	m_hour = h;
	m_min = m;
	m_sec = s;
	m_msec = ms;
}

void dataGenForBroadcast::generate(char *buf, int size)
{
	buf[0] = (m_year >> 4) & 0xff;
	buf[1] = ((m_year & 0xf) << 4) | m_month;
	buf[2] = ((m_day & 0x1f) << 3) | ((m_hour  & 0x1f) >> 2);
	buf[3] = ((m_hour& 0x3) << 6) | (m_min  & 0x3f) ;
	buf[4] = ((m_sec& 0x1f) << 2) | ((m_msec) >> 8 );
	buf[5] = m_msec & 0xff ;
}