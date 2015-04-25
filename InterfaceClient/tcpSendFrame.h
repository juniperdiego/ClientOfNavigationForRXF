#ifndef TCP_SEND_FRAME_H
#define TCP_SEND_FRAME_H

#include "comm.h"
#include "tcpData.h"

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
//1.飞行器自身参数
class aerocraftSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame(char* buf, int len);
};

//2.广播时间信息
class broadcastSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame(char* buf, int len);
};

//3.地面注入参数
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
	// 地面站
	float	m_groundParam1;
	float	m_groundParam2;
	int		m_groundParam3;
	//中继星、地面站可用内容
	char	m_whichAvail; // 0x11-卫星1 可用； 0x22-卫星2 可用；0x33-卫星三可用；0x44-地面站可用; 0x55-不可用
};

// 4.相控阵指向参数注入
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
// 5.飞行器指向方式
class aerocraftDirectionSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame();
	void set(bool isTrackCalc);
private:
	bool	m_isTrackCalc;
};

#endif // TCP_SEND_FRAME_H

// for测试参数设置

//1.T组件修正码
class compTCorrectionSendFrame: public tcpSendFrame
{
public:
	bool setDegree(vector<vector<float> > degreeMatrix);
	bool setEnable(vector<vector<bool> > enableMatrix);
	vector<int> generateFrame();
private:
	compTCorrection m_ctc;
};

//2.T组件修正码
class compTTestCodeSendFrame: public tcpSendFrame
{
public:
	bool setEnable(vector<vector<bool> > enableMatrix);
	vector<int> generateFrame();
private:
	compTTestCode m_ctt;
};

//3.R组件修正码
class compRCorrectionSendFrame: public tcpSendFrame
{
public:
	bool setDegree(vector<vector<float> > degreeMatrix);
	bool setEnable(vector<vector<bool> > enableMatrix);
	vector<int> generateFrame();
private:
	compRCorrection m_crc;
};

//4.R组件修正码
class compRTestCodeSendFrame: public tcpSendFrame
{
public:
	bool setEnable(vector<vector<bool> > enableMatrix);
	vector<int> generateFrame();
private:
	compRTestCode m_crt;
};

//5.R组件安装误差
class compRInstallErrorSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame();
	void set(float x, float y, float z);
private:
	float 	m_x;
	float 	m_y;
	float 	m_z;
};

//6.R组件定点命令格式
class compRFixPointSendFrame: public tcpSendFrame
{
public:
	vector<int> generateFrame();
	void set(float x, float y);
private:
	float 	m_x;
	float 	m_y;
};
