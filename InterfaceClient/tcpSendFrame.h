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


// for tab ϵͳң��ң�ز���
class remoteParamSendFrame: public tcpSendFrame
{
private:
	bool 	m_mode;
	bool 	m_antennaPatern;
private:
public:
	remoteParamSendFrame();
	void setMode(bool);//  0- ����ģʽ����ָ��, 1 - ��λ����ָ��
	void setAntennaPattern(bool);// 0- �����շ�ͬʱ����, 1- ���ߵ�������
	virtual vector<int> generateFrame();
};

// for tab ��ز���ע���Լ�����
class injectParamSendFrame: public tcpSendFrame
{
};


#endif // TCP_SEND_FRAME_H
