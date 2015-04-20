#ifndef TCP_RECV_FRAME_H
#define TCP_RECV_FRAME_H

#include "comm.h"

class tcpRecvFrame
{
public:
	tcpRecvFrame();
	virtual ~tcpRecvFrame();
	bool	parseRecvTcpFrame(int* frame, int frameLen);// frameLen based on bytes
	int		getFrameLen();
protected:
	virtual bool parseRecvTcpData(int* data, int dataLen);//dataLen based on int
protected:
	int	m_frameStartTag;
	int	m_frameLen;
	int	m_reserveInt;
	int	m_frameEndTag;
};

// for tab T���״̬
class compTStatusRecvFrame : public tcpRecvFrame
{
private:
	bool parseRecvTcpData(int* data, int dataLen);
public:
	compTStatusRecvFrame();
};

// for tab R���״̬
class compRStatusRecvFrame : public tcpRecvFrame
{
private:
	bool parseRecvTcpData(int* data, int dataLen);
public:
	compRStatusRecvFrame();
};

// for tab ϵͳң��ң�ز���
class remoteParamRecvFrame: public tcpRecvFrame
{
private:
	vector<float> m_paramVec;
private:
	bool parseRecvTcpData(int* data, int dataLen);
public:
	vector<float> getParamVec();
	remoteParamRecvFrame();
};

// for tab ��ز���ע���Լ�����
class injectParamRecvFrame: public tcpRecvFrame
{
private:
	float 	m_centerDegree;
	float 	m_directionDegree;
	char	m_totalCmdNum;
	char	m_sucCmdNum;
	char	m_whichAvilable;
	char	m_workingStatus1;
	char	m_workingStatus2;
private:
	bool parseRecvTcpData(int* data, int dataLen);
public:
	injectParamRecvFrame();
	float getCenterDegree();
	float getDirectionDegree();
};


#endif // TCP_RECV_FRAME_H
