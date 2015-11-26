#ifndef _AI_MASKMAN_DETECT_H_
#define _AI_MASKMAN_DETECT_H_

#include "algorithmInterface.h"

enum ForwardResult{
	BACKWARD = 0,  //����
	NORMAL,   //����
	FAST_FORWARD,  //���
	PAUSE,  //��ͣ
};

#define MAXSIZE 4096
class AI_Maskman_Detect: public AlgorithmInterface{
public:
	AI_Maskman_Detect();
	~AI_Maskman_Detect();
	virtual void init();
	virtual void destroy();

	float interval;  //֡�����������֡
	//ע��file ��Ҫ�򿪵���Ƶ�ļ���
	//	  folder ��������Ҫ������ݵ��ļ���·����  ���ڸ���algorithmInterface.h�ж���
	char eventInfo[MAXSIZE];  //��������Ϣ
	cv::Mat curFrame_out; //���⴫������֡
	uint forwardInfo;  //�Ƿ�������ͣ
};

#endif