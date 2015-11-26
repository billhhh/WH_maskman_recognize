#ifndef _H_ALGORITHMINTERFACE_H_
#define _H_ALGORITHMINTERFACE_H_
#include <string>
#include <opencv2/opencv.hpp>

enum AlgorithmResult{
	AR_DONE = 0,//�㷨�ɹ�ִ�����
	AR_BREAK,//�㷨������ж�
	AR_INTERNAL,//�㷨���ڲ������ж�
	AR_EXTERNAL,//�㷨���ⲿ�����ж�
	AR_END//�㷨ִ��ʧ��
};

#define MAXPATH 256
class AlgorithmInterface{
public:
	char file[MAXPATH];//�����ļ���ȫ·����
	char folder[MAXPATH];//������Ҫ������ݵ��ļ���·����

	cv::Mat image;//ͼ�����
	cv::Mat* pImg;//ָ��ͼ������ָ�롣

	uint percent;//�㷨����Ľ��ȣ���ΧΪ��0-100����
	bool isRun;//�㷨���ⲿ���Ʊ����������㷨�Ƿ����ִ�С�

	int mutex;//�ź�������ֹͬһ���ݵĶ�д��ͻ��
public:
	AlgorithmInterface();
	~AlgorithmInterface();
	virtual void init() = 0;
	virtual void destroy() = 0;
	void lock(int &);//���ź���������s
	void unlock(int &);//���ź��������� 
};

#endif