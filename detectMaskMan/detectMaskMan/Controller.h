/*
 * Controller.h
 *
 *  Created on: 2015-3-18
 *      Author: Bill Wang
 */

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cv.h"
#include "highgui.h"
#include "AI_Maskman_Detect.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <string>

class Controller
{
public:
	AI_Maskman_Detect* pAI_id;
	static Controller* instance;
	cv::CascadeClassifier cascade;
	cv::CascadeClassifier nestedCascade;
	cv::CascadeClassifier thirdCascade;
	cv::CascadeClassifier forthCascade;

	bool init();
	Controller();  //constructor
	~Controller(void); //destructor
	static Controller* getInstance();
	bool startDetect();
	void setParam(AI_Maskman_Detect *pAI_da);

private:
	double fScale;      //���ű���
	double learningRate;    // ���Ʊ����ۻ�ѧϰ������
	double area_threshold;  //���������С��ֵ
	int nThreshold; //��ֵ����ֵ

	cv::Mat curFrame_ori;		//ÿһ֡ԭͼ�񣬾�������
	cv::Mat curFrame_resize;
	cv::Mat curFrame_gray;
	cv::Mat firstGrayFrame;
	cv::Mat firstGrayFrame_8U;
	cv::Mat curFrame_diff;		//��ֺ�ͼ��
	cv::Mat curFrame_diff_bin;  //��ֲ���ֵ����
	int lastRectHeight; //�洢��һ֡��������θ߶�
	double lastMaskFrame; //��һ�������˳��ֵ�֡����������֡
	bool isDetect;   //�Ƿ��⵽������
	bool isColor;	 //������Ƶ�Ƿ�Ϊ��ɫ

private:
	int cascadeCnt;
	int nestedCnt;
	cv::VideoCapture capture;
	std::string videoPath;
	std::string savePath;
	float interval; //֡�����������֡���ӿ촦���ٶ�

	void findBoundary(cv::Rect r,cv::Point &a,cv::Point &c);
	void biggerRect(cv::Point &a,cv::Point &c,cv::Mat img);
	void hugeRect(cv::Point &a,cv::Point &c,cv::Mat img);
	//�ڰ������˼��
	void detectAndDrawGray( cv::Mat& src,
		cv::CascadeClassifier& cascade, cv::CascadeClassifier& nestedCascade,
		double scale);

	//��ɫ�����˼��
	void detectAndDrawColorful( cv::Mat& src,
		cv::CascadeClassifier& cascade, cv::CascadeClassifier& nestedCascade,
		double scale);
	void whThresholdOtsu(cv::Mat &src, cv::Mat &dst);
	void cvSkinOtsu(cv::Mat &src, cv::Mat &dst);
	bool findMaskMan(cv::Mat img);
	void con_num_detect(cv::Mat src,bool &isDetect);
	void cut_image_percent(cv::Mat &img,double left,double upper,double right,double bottom);
	double get_max_2_con_rate(cv::Mat &img);
	bool keepSomeMaxCon(cv::Mat &src, int n);
	bool image_is_color(cv::Mat image,bool& is_color);
};

#endif
