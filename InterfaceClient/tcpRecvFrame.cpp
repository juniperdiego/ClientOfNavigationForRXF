#include "tcpRecvFrame.h"
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")

void htonlArray(int *p, int size)
{
	for(int i = 0; i < size; i++)
	{
		p[i] = htonl(p[i]);
	}
}

tcpRecvFrame::tcpRecvFrame()
	:m_frameStartTag(TCP_FRAME_START_TAG),
	m_reserveInt(0),
	m_frameEndTag(TCP_FRAME_END_TAG)
{
}

tcpRecvFrame::~tcpRecvFrame()
{
}

int tcpRecvFrame::getFrameLen()
{
	return m_frameLen;
}

bool tcpRecvFrame::parseRecvTcpFrame(int* frame, int frameLen)
{
	if(frame == NULL)
		return false;

		//network byte order to host byte order
	for(int i = 0; i < frameLen/sizeof(int); i++)
	{
		frame[i] = ntohl(frame[i]);
#if 0
		if(i < 3 || i == (frameLen/sizeof(int) -1) )
			qDebug() << frame[i];
		else
			qDebug() << *(float*)&(frame[i]);
#endif
	}

	if(frame[0] != m_frameStartTag)
		return false;

	if(frame[1] != frameLen || frameLen != m_frameLen)
		return false;

	if(frame[2] != 0)
		return false;

	if(frame[frameLen/sizeof(int) -1] != m_frameEndTag)
		return false;

	// parseRecvTcpData 's data is based on int, not byte
	return parseRecvTcpData(frame + 3, frameLen/sizeof(int) - 4);
}

bool tcpRecvFrame::parseRecvTcpData(int* frame, int frameLen)
{
	return true;
}

compTStatusRecvFrame::compTStatusRecvFrame()
{
	//m_framlen == TBD TODO
}
bool compTStatusRecvFrame::parseRecvTcpData(int* data, int dataLen)
{
	//TODO
	return true;
}

compRStatusRecvFrame::compRStatusRecvFrame()
{
	//m_framlen == TBD TODO
}
bool compRStatusRecvFrame::parseRecvTcpData(int* data, int dataLen)
{
	//TODO
	return true;
}

remoteParamRecvFrame::remoteParamRecvFrame()
{
	m_frameLen = 4 * 14; 
}
bool remoteParamRecvFrame::parseRecvTcpData(int* data, int dataLen)
{
	float * p = (float*)data;
	m_paramVec.clear();

	for(int i = 0; i < dataLen; i++)
	{
		m_paramVec.push_back(p[i]);
		//qDebug() << "p[i]" << p[i];
	}
	return true;
}

vector<float> remoteParamRecvFrame::getParamVec()
{
	return m_paramVec;
}

injectParamRecvFrame::injectParamRecvFrame()
{
	m_frameLen = 4 * (4/*header+tail*/ + 1/*modeCode*/ + 11/*data*/); 
}
bool injectParamRecvFrame::parseRecvTcpData(int* data, int dataLen)
{
	if(data == NULL)
		return false;

	if(data[0] & 0xff != 0xEB)
		return false;

	if(data[1] & 0xff != 0x90)
		return false;

	if(data[2] & 0xff != 0x55)
		return false;

	if(data[3] & 0xff != 0x06)
		return false;

	//do the check
	char check = 0;
	for(int i = 4; i < (data[3] & 0xff) ; i++)
	{
		check = check ^ data[i];
	}
	if(check != (data[dataLen - 1] & 0xff))
		return false;

	//begin to parse 
	int centerDegree = (data[4] << 4) | (data[5] >> 4);
	m_centerDegree = ((float)centerDegree)/10;

	int dirctionDegree = ((data[5] & 0xff) << 8) | data[6] ;
	m_directionDegree = ((float)dirctionDegree)/10;

	m_totalCmdNum = data[7];
	m_sucCmdNum = data[8];

	//working status
	m_whichAvilable = (data[9] >> 4) & 0x3;
	m_workingStatus1 = (data[9] >>2) & 0x3;
	m_workingStatus2 = (data[9] >>0) & 0x3;

	return true;
}

float injectParamRecvFrame::getCenterDegree()
{
	return m_centerDegree;
}

float injectParamRecvFrame::getDirectionDegree()
{
	return m_directionDegree;
}

int injectParamRecvFrame::getTotalCmdNum()
{
	return m_totalCmdNum;
}

int injectParamRecvFrame::getSuccessCmdNum()
{
	return m_sucCmdNum;
}

char injectParamRecvFrame::getWhichAvilable()
{
	return m_whichAvilable;
}

bool injectParamRecvFrame::getWorkingStatus1()
{
	return m_workingStatus1 == 0x0;
}

bool injectParamRecvFrame::getWorkingStatus2()
{
	return m_workingStatus2 == 0x0;
}


