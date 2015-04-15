#ifndef TCP_SEND_FRAME_H
#define TCP_SEND_FRAME_H

#include "comm.h"

class tcpSendFrame
{
public:
	tcpSendFrame();
	~tcpSendFrame();
protected:
	virtual vector<int> generateFrame();
protected:
	int	m_frameStartTag;
	int	m_frameLen;
	int	m_reserveInt;
	int	m_frameEndTag;
};


// for tab 系统遥测遥控参数
class remoteParamSendFrame: public tcpSendFrame
{
private:
	bool 	m_mode;
	bool 	m_antennaPatern;
private:
public:
	remoteParamSendFrame();
	void setMode(bool);//  0- 工作模式发送指令, 1 - 复位控制指令
	void setAntennaPattern(bool);// 0- 天线收发同时工作, 1- 天线单发工作
	virtual vector<int> generateFrame();
};

// for tab 测控参数注入以及返回
class injectParamSendFrame: public tcpSendFrame
{
};


#endif // TCP_SEND_FRAME_H
