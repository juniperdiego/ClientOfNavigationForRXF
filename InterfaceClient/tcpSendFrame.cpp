#include "tcpSendFrame.h"

tcpSendFrame::tcpSendFrame()
	:m_frameStartTag(TCP_FRAME_START_TAG),
	m_reserveInt(0),
	m_frameEndTag(TCP_FRAME_END_TAG)
{
}

tcpSendFrame::~tcpSendFrame()
{
}

vector<int> tcpSendFrame::generateFrame()
{
	return vector<int> ();
}



remoteParamSendFrame::remoteParamSendFrame()
{
	m_frameLen = 0; //mark it is invalid 
}

void remoteParamSendFrame::setMode(bool mode)
{
	m_mode = mode;

	if(mode == false)
		m_frameLen = 4 * 6;
	else
		m_frameLen = 4 * 5;
}

void remoteParamSendFrame::setAntennaPattern(bool pattern)
{
	m_antennaPatern = pattern;
}

vector<int> remoteParamSendFrame::generateFrame()
{
	vector<int>  res;

	res.push_back(m_frameStartTag);
	res.push_back(m_frameLen);
	res.push_back(m_reserveInt);
	if(m_mode == false)
	{
		res.push_back(0);
		if(m_antennaPatern == false)
			res.push_back(0);
		else
			res.push_back(1);
	}
	else
		res.push_back(1);
	res.push_back(m_frameEndTag);

	return res;
}

