#ifndef TCP_SEND_FRAME_H
#define TCP_SEND_FRAME_H

#include "comm.h"

class tcpSendFrame
{
public:
	tcpSendFrame();
	virtual ~tcpSendFrame();
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
//1.�������������
class aerocraftSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame(char* buf, int len);
};

//2.�㲥ʱ����Ϣ
class broadcastSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame(char* buf, int len);
};

//3.����ע�����
class groundInjectParamSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame();
	void setYMD(int y, int m, int d);
	void setHMS(int h, int m, int s, int ms);
	void setSatelliteParam(float p1, float p2, float p3, 
			float p4, float p5, float p6);
	void setGroundParam(float p1, float p2, float p3); 
	void setWhichAvail(char which);
private:
	vector<int> generateSatelliteInfo();
	vector<int> generateGroundInfo();
private:
	//time
	int		m_year;
	int		m_month;
	int		m_day;
	int		m_hour;
	int		m_min;
	int		m_sec;
	int		m_msec;
	// satellite
	float	m_satelliteParam1;
	float	m_satelliteParam2;
	float	m_satelliteParam3;
	float	m_satelliteParam4;
	float	m_satelliteParam5;
	float	m_satelliteParam6;
	// ����վ
	float	m_groundParam1;
	float	m_groundParam2;
	int		m_groundParam3;
	//�м��ǡ�����վ��������
	char	m_whichAvail; // 0x11-����1 ���ã� 0x22-����2 ���ã�0x33-���������ã�0x44-����վ����; 0x55-������
};

// 4.�����ָ�����ע��
class phasedArrayRadaSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame();
	void setCenterDegree(float c);
	void setDirectionDegree(float c);
private:
	float 	m_centerDegree;
	float 	m_directionDegree;

};
// 5.������ָ��ʽ
class aerocraftDirectionSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame();
	void set(bool isTrackCalc);
private:
	bool	m_isTrackCalc;
};

#endif // TCP_SEND_FRAME_H
