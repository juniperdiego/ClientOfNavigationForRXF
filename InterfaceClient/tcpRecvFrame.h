#ifndef TCP_RECV_FRAME_H
#define TCP_RECV_FRAME_H

#include "comm.h"

class tcpRecvFrame
{
public:
	tcpRecvFrame();
	~tcpRecvFrame();
	bool parseRecvTcpFrame(int* frame, int frameLen);// frameLen based on bytes
protected:
	virtual bool parseRecvTcpData(int* data, int dataLen);//dataLen based on int
protected:
	int	m_frameStartTag;
	int	m_frameLen;
	int	m_reserveInt;
	int	m_frameEndTag;
};

// for tab T���״̬
class compTStatus : public tcpRecvFrame
{
private:
	bool parseRecvTcpData(int* data, int dataLen);
public:
	compTStatus();
};

// for tab R���״̬
class compRStatus : public tcpRecvFrame
{
private:
	bool parseRecvTcpData(int* data, int dataLen);
public:
	compRStatus();
};

// for tab ϵͳң��ң�ز���
class remoteParam: public tcpRecvFrame
{
private:
	vector<float> m_paramVec;
private:
	bool parseRecvTcpData(int* data, int dataLen);
public:
	vector<float> getParamVec();
	remoteParam();
};

// for tab ��ز���ע���Լ�����
class returnedParamStatus: public tcpRecvFrame
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
	returnedParamStatus();
	float getCenterDegree();
	float getDirectionDegree();
};


#endif // TCP_RECV_FRAME_H
