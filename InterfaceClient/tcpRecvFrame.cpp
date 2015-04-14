#include "tcpRecvFrame.h"

tcpRecvFrame::tcpRecvFrame()
	:m_frameStartTag(TCP_FRAME_START_TAG),
	m_reserveInt(0),
	m_frameEndTag(TCP_FRAME_END_TAG)
{
}

tcpRecvFrame::~tcpRecvFrame()
{
}

bool tcpRecvFrame::parseRecvTcpFrame(int* frame, int frameLen)
{
	if(frame == NULL)
		return false;

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

compTStatus::compTStatus()
{
	//m_framlen == TBD TODO
}
bool compTStatus::parseRecvTcpData(int* data, int dataLen)
{
	//TODO
	return true;
}

compRStatus::compRStatus()
{
	//m_framlen == TBD TODO
}
bool compRStatus::parseRecvTcpData(int* data, int dataLen)
{
	//TODO
	return true;
}

remoteParam::remoteParam()
{
	m_frameLen = 4 * 14; 
}
bool remoteParam::parseRecvTcpData(int* data, int dataLen)
{
	float * p = (float*)data;
	m_paramVec.clear();

	for(int i = 0; i < dataLen; i++)
		m_paramVec.push_back(p[i]);
	return true;
}

returnedParamStatus::returnedParamStatus()
{
	m_frameLen = 4 * (4/*header+tail*/ + 1/*modeCode*/ + 11/*data*/); 
}
bool returnedParamStatus::parseRecvTcpData(int* data, int dataLen)
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




