/*
 * Controller.cpp
 *
 * function: Control each part of the project and manage them
 *
 *  Created on: 2015-3-18
 *      Author: Bill Wang
 */

#include <Windows.h>
#include <fstream>
#include "Controller.h"
#include "StaticData.h"

using namespace std;
using namespace cv;

Controller* Controller::instance = NULL;

//constructor
Controller::Controller(){
}

//destructor
Controller::~Controller()
{
	if( capture.isOpened())
		capture.release();

	if( instance != NULL){
		delete instance;
		instance = NULL;
	}
}

//initialize the Controller class
//load the cascade classifier
bool Controller::init()
{
	//�㷨����init
	this->isDetect = false;
	this->isColor = false;
	this->cascadeCnt = 0;
	this->nestedCnt=0;
	this->fScale = 1.0;      //���ű���
	this->learningRate=0.5;    // ���Ʊ����ۻ�ѧϰ������
	this->area_threshold = 30;  //���������С��ֵ
	this->nThreshold=30; //��ֵ����ֵ
	this->lastRectHeight=0; //�洢��һ֡��������θ߶�

	StaticData staticdata;
	//��ָ�����ļ�Ŀ¼�м��ؼ���������
	//���������û���������أ�����
	if( !cascade.load( staticdata.cascadePath ) )
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return false;
	}

	if( !nestedCascade.load( staticdata.nestedCascadePath ) )
	{
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
		return false;
	}

	return true;
}

void Controller::setParam(AI_Maskman_Detect *pAI_da){
	this->pAI_id = pAI_da;
	this->videoPath = pAI_da->file;
	this->savePath = pAI_da->folder;
	this->interval = pAI_da->interval;
	this->pAI_id->forwardInfo = ForwardResult::NORMAL; //Ĭ������������
}

Controller* Controller::getInstance(){
	if( instance == NULL){
		instance = new Controller();
	}
	return instance;
}

bool Controller::startDetect()
{
	//����Ƶ����
	capture.open(this->videoPath);
	if (!capture.isOpened())
		return false;
	if (!firstGrayFrame.empty())  //�������
		firstGrayFrame.release();

	string detectInfo = "";
	double fps = capture.get(CAP_PROP_FPS);
	double frameCount = capture.get(CAP_PROP_FRAME_COUNT); //����֡��
	int count = 1; //֡����
	int h,m,s;//ʱ����
	double ratio;
	strcpy(this->pAI_id->eventInfo,  "");
	this->pAI_id->curFrame_out.setTo(0);

	//���log��Ϣ�ļ���
	string filename;
	string videoName;
	int seq = 1;
	int startIndex = videoPath.find_last_of('/');  //�Ҳ�������-1
	int startIndex2 = videoPath.find_last_of('\\');
	startIndex = startIndex>startIndex2?startIndex:startIndex2;

	int endIndex = videoPath.find_last_of('.');
	videoName = videoPath.substr(startIndex+1,endIndex-startIndex-1);  //ֻ����Ƶ������
	string textName = savePath+"\\"+videoName+"_"+"events_log.txt";

	Mat firstFrame;
	if(!capture.read(firstFrame))
		return false;
	image_is_color(firstFrame,this->isColor);  //ȷ���Ƿ��ǲ�ɫ��Ƶ

	if(this->isColor == true)
	{
		detectInfo+="�������Ƶ�ǲ�ɫ��Ƶ��\n";
		strcpy(this->pAI_id->eventInfo , "�������Ƶ�ǲ�ɫ��Ƶ��\n");
	}
	else
	{
		detectInfo+="�������Ƶ�Ǻڰ���Ƶ��\n";
		strcpy(this->pAI_id->eventInfo , "�������Ƶ�Ǻڰ���Ƶ��\n");
	}

	while(1)
	{
// 		if (count == 500)
// 			this->pAI_id->forwardInfo = ForwardResult::FAST_FORWARD;
// 		waitKey( 1 );
// 		if( waitKey( 1 ) == 27 )
// 			waitKey();

		if( !this->pAI_id->isRun){//�˳���
			break;
		}

		if( this->pAI_id->forwardInfo == ForwardResult::PAUSE){//��ͣ
			Sleep(100);
			continue;
		}else if(this->pAI_id->forwardInfo == ForwardResult::BACKWARD){//����
			if ( count-(int)fps >0 ){
				count-=(int)fps;
			}else{
				count=0;
			}
			capture.set(CV_CAP_PROP_POS_FRAMES,count);
			this->pAI_id->forwardInfo = ForwardResult::NORMAL;
			continue;

		}else if(this->pAI_id->forwardInfo == ForwardResult::FAST_FORWARD){//���
			count+=(int)fps;
			if ( count>= frameCount-int(0.3*fps) )  //���������֡�����߶������ļ�
				break;
			capture.set(CV_CAP_PROP_POS_FRAMES,count);
			this->pAI_id->forwardInfo = ForwardResult::NORMAL;
			continue;
		}

		if(!capture.read(curFrame_ori))
			break;
		isDetect=false; //ÿ��while��isDetect��ʼ��

		//��֡
// 		if(lastMaskFrame!=0 && count < lastMaskFrame + interval*fps){
// 			count++;
// 			if ( count>=frameCount )
// 				break;
// 			continue;
// 		}

		cout<<"\n\n*****************New Frame******************"<<endl;
		cout<<"count == "<<count<<endl;

		//��ԭͼ������
		resize(curFrame_ori,curFrame_resize,Size(curFrame_ori.cols * fScale,curFrame_ori.rows * fScale),0,0,CV_INTER_LINEAR);
		//תΪ��ͨ���Ҷ�ͼ
		cvtColor(curFrame_resize, curFrame_gray, CV_BGR2GRAY);

		if(firstGrayFrame.empty())
		{
			//��¼��һ֡
			curFrame_gray.convertTo(firstGrayFrame,CV_32F);
		}
		firstGrayFrame.convertTo(firstGrayFrame_8U, CV_8U);

		//���
		absdiff(firstGrayFrame_8U, curFrame_gray, curFrame_diff);

		threshold(curFrame_diff, curFrame_diff_bin, nThreshold, 255, THRESH_BINARY);
		accumulateWeighted(curFrame_gray, firstGrayFrame,learningRate,curFrame_diff_bin);
		medianBlur(curFrame_diff_bin, curFrame_diff_bin,5);

		//��ʼ���߽缫ֵ������
		Point A,C;
		A.x=0x7fffffff; A.y=0x7fffffff;
		C.x=0; C.y=0;
		//�������
		vector<vector<Point>> _contours;//������������
		vector<Vec4i>hierarchy;
		cv::findContours( curFrame_diff_bin, _contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		for(size_t i = 0; i< _contours.size(); ++i){
			//������������
			//�����������
			double contArea =  fabs(contourArea(_contours[i]));
			//ȥ����С���������
			if( contArea < area_threshold)
				continue;
			//�����Ӿ���
			Rect r0 = boundingRect(Mat(_contours[i]));
			//�ҳ���߽�ĵ�
			findBoundary(r0,A,C);
			//ʵʱ����ÿ������
			//rectangle(img_diff_bi,r0,cvScalar(255,255,255),1,8,0);
		}

		biggerRect(A,C,curFrame_resize);
		int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

		if (c<=0 || d<=0){
			//���ο򲻴��ڣ���ⲻ��
		}else{
			if(d<lastRectHeight*0.7) //�Ŵ�����ο����
				hugeRect(A,C,curFrame_resize);

			//�õ�Ҫʶ��ľ��ο�
			Rect r=Rect(a,b,c,d);
			//��ȡcurFrame_rz�е�r���ο��С
			Mat sentToDetect=curFrame_resize(r);

			//��ȥ�������
			if(this->isColor == true)
				detectAndDrawColorful(sentToDetect,cascade, nestedCascade ,1.0);
			else
				detectAndDrawGray(sentToDetect,cascade, nestedCascade ,1.0);
			//imshow("frame", curFrame_resize);

			//����������ͼƬ����Ϣ
			if(this->isDetect==true){
				//�ļ���+ _ + h + _ + m + _ + s + _ +���.jpg
				stringstream temp;
				filename = "/" + videoName + "_";
				s = count / fps +1;
				h = s / 3600;
				m = (s % 3600)/60;
				s = s % 60;
				temp.str("");
				temp<<h;
				if(h/10 == 0)
					filename += "0";
				filename += temp.str() + "_";
				temp.str("");
				temp<<m;
				if(m/10 == 0)
					filename += "0" ;
				filename += temp.str()+ "_";
				temp.str("");
				temp<<s;
				if(s/10 == 0)
					filename += "0";
				filename += temp.str()+ "_";
				temp.str("");
				temp<<seq;
				filename += temp.str()+ ".jpg";

				imwrite(savePath+filename,sentToDetect); //����������ͼƬ
				//ʱ�� h:m:s ����������
				temp.str("");
				detectInfo += "����Ƶʱ�䣺";
				temp<<h;
				if(h/10 == 0)
					detectInfo += "0" ;
				detectInfo += temp.str() + ":";
				temp.str("");
				temp<<m;
				if(m/10 == 0)
					detectInfo += "0";
				detectInfo += temp.str()+ ":";
				temp.str("");
				temp<<s;
				if(s/10 == 0)
					detectInfo += "0";
				detectInfo += temp.str()+ "  ��⵽������!\n";
				seq++;
				lastMaskFrame = count;
			}

			lastRectHeight = d;
		}//else !(c<=0 || d<=0)

		count++; //֡����
		ratio = count/(double)capture.get(CAP_PROP_FRAME_COUNT);
		this->pAI_id->percent = ratio*100; //�ٷֱ�
		pAI_id->lock(pAI_id->mutex);
		this->pAI_id->curFrame_out = curFrame_resize.clone();
		pAI_id->unlock(pAI_id->mutex);

		if( this->isDetect )//д����������Ϣ
			strcpy(this->pAI_id->eventInfo , detectInfo.c_str());
	}//while
	//��eventд��text
	ofstream out(textName);
	if(out.is_open())
		out<<detectInfo;
	out.close();

	if( capture.isOpened())
		capture.release();
	this->pAI_id->curFrame_out.setTo(0);

	if(count < frameCount-int(0.3*fps))
	{
		ratio=100;
		return true;
		//return false;
	}
	return true;
}

//��һ֡�����о��εı߽��ĵ�
void Controller::findBoundary(Rect r,Point &a,Point &c){
	//a�Ǿ���ԭ��
	//c��ԭ��Խ��ߵ�
	//r.x����a.x�����
	if (r.x < a.x)
		a.x = r.x;
	//r.y ���� a.y ����
	if(r.y < a.y)
		a.y = r.y;
	//r.x+r.width ����c.x���ұ�
	if ((r.x+r.width) > c.x)
		c.x = r.x+r.width;

	//(r.y+r.height) ���� c.y ����
	if((r.y+r.height) > c.y)
		c.y = r.y+r.height;
}

void Controller::biggerRect(Point &a,Point &c,Mat img){
	if (c.x-a.x<0 || c.y-a.y<0)
		return;

	a.x -= 30;
	a.y -= 100;
	c.x += 30;
	c.y += 100;

	if(a.x<0)
		a.x=0;

	if(a.y<0)
		a.y=0;

	if(c.x>img.cols)
		c.x=img.cols;

	if(c.y>img.rows)
		c.y=img.rows;
}

void Controller::hugeRect(Point &a,Point &c,Mat img){
	a.y = 0;
	c.y = img.rows;
}

//��ɫ�����˼��
void Controller::detectAndDrawColorful( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale){
		Mat img_ori=img.clone();

		//ע�͵���һ������Ƕ�������ļ��
		//nestedCascade.~CascadeClassifier() ;

		int i = 0;
		double t = 0;
		vector<Rect> faces;
		const static Scalar colors[] =  { CV_RGB(0,0,255),
			CV_RGB(0,128,255),
			CV_RGB(0,255,255),
			CV_RGB(0,255,0),
			CV_RGB(255,128,0),
			CV_RGB(255,255,0),
			CV_RGB(255,0,0),
			CV_RGB(255,0,255)} ;//�ò�ͬ����ɫ��ʾ��ͬ������

		Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��ͼƬ��С���ӿ����ٶ�

		//	cvtColor( img, smallImg, CV_BGR2GRAY );
		cvtColor( img, gray, CV_BGR2GRAY );//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
		resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//���ߴ���С��1/scale,�����Բ�ֵ
		equalizeHist( smallImg, smallImg );//ֱ��ͼ����

		t = (double)cvGetTickCount();//���������㷨ִ��ʱ��

		//�������
		//detectMultiScale������smallImg��ʾ����Ҫ��������ͼ��ΪsmallImg��faces��ʾ��⵽������Ŀ�����У�1.1��ʾ
		//ÿ��ͼ��ߴ��С�ı���Ϊ1.1��2��ʾÿһ��Ŀ������Ҫ����⵽3�β��������Ŀ��(��Ϊ��Χ�����غͲ�ͬ�Ĵ��ڴ�
		//С�����Լ�⵽����),CV_HAAR_SCALE_IMAGE��ʾ�������ŷ���������⣬��������ͼ��Size(30, 30)ΪĿ���
		//��С���ߴ�
		cascade.detectMultiScale( smallImg, faces,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			|CV_HAAR_SCALE_IMAGE
			,
			Size(50, 50) );

		t = (double)cvGetTickCount() - t;//���Ϊ�㷨ִ�е�ʱ��
		printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

		for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
		{
			Mat smallImgROI;
			vector<Rect> nestedObjects;
			Point center;
			Scalar color = colors[i%8];
			int radius;
			center.x = cvRound((r->x + r->width*0.5)*scale);//��ԭ��ԭ���Ĵ�С
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			//circle( img, center, radius, color, 3, 8, 0 );

			this->cascadeCnt++;

			if( nestedCascade.empty() )
				continue;

			smallImgROI = img_ori(*r);

			//������ĺ�������һ��
			nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
				1.1, 2, 0
				//|CV_HAAR_FIND_BIGGEST_OBJECT
				//|CV_HAAR_DO_ROUGH_SEARCH
				//|CV_HAAR_DO_CANNY_PRUNING
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );  
			for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
			{
				Mat supSmallImg;
				Mat ssimgResult;

				center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
				center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
				radius = cvRound((nr->width + nr->height)*0.25*scale);
				//circle( img, center, radius, color, 1, 8, 0 );

				this->nestedCnt++;
				supSmallImg = smallImgROI(*nr);

				//imshow("supSmallImg",supSmallImg);
				cvSkinOtsu(supSmallImg, ssimgResult);
				//imshow("ssimgResult",ssimgResult);

				//imshow("��⵽����",img);
				//waitKey();

				if(findMaskMan(ssimgResult) == true)
				{
					isDetect=true;
					circle( img, center, radius, color, 3, 8, 0 );
// 					imshow("test",img);
// 					waitKey();
// 					destroyAllWindows();
				}
			}
		}

		cout<<"cnt == "<<this->cascadeCnt<<endl;
		cout<<"nestedCnt == "<<this->nestedCnt<<endl;
}

void Controller::whThresholdOtsu(Mat &src, Mat &dst){
	int height=src.rows;
	int width=src.cols;
	//histogram
	float histogram[256]={0};
	for(int i=0;i<height;i++) {
		unsigned char* p=(unsigned char*)src.data+src.step*i;
		for(int j=0;j<width;j++) {
			histogram[*p++]++;
		}
	}
	//normalize histogram
	int size=height*width;
	for(int i=0;i<256;i++) {
		histogram[i]=histogram[i]/size;
	}

	//average pixel value
	float avgValue=0;
	for(int i=0;i<256;i++) {
		avgValue+=i*histogram[i];
	}

	int threshold;	
	float maxVariance=0;
	float w=0,u=0;
	for(int i=0;i<256;i++) {
		w+=histogram[i];
		u+=i*histogram[i];

		float t=avgValue*w-u;
		float variance=t*t/(w*(1-w));
		if(variance>maxVariance) {
			maxVariance=variance;
			threshold=i;
		}
	}

	cv::threshold( src, dst, threshold, 255, THRESH_BINARY);
}

void Controller::cvSkinOtsu(Mat &src, Mat &dst){
	Mat ycrcb;
	Mat cr;
	cvtColor(src,ycrcb,COLOR_BGR2YCrCb);

	vector<Mat> mv;
	split(ycrcb,mv);
	whThresholdOtsu(mv[1],cr);

	dst = cr.clone();
}

bool Controller::findMaskMan(Mat img){
	//cout<<"����findMaskMan"<<endl;

	double scale=0.3;

	int width = img.cols;
	int height = img.rows;

	//�����ο�λ���°벿��
	Rect r=Rect(0,height*(1-scale),width,height*scale);
	img=img(r);

	int count=countNonZero(img);
	int area=width*height*scale;
	double rate=(double)count/area;

	if(rate<0.3){
		//rectangle(img,r0,cvScalar(255,255,255),1,8,0);
		//cvWaitKey(0);
		return true;
	}
	return false;
}

//�ڰ������˼��
void Controller::detectAndDrawGray( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale)
{
	bool flag=false;
	Mat faceImg;
	Mat img_ori=img.clone();

	vector<Rect> faces;

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��ͼƬ��С���ӿ����ٶ�

	cvtColor( img, gray, CV_BGR2GRAY );//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//���ߴ���С��1/scale,�����Բ�ֵ
	equalizeHist( smallImg, smallImg );//ֱ��ͼ����


	//detectMultiScale������smallImg��ʾ����Ҫ��������ͼ��ΪsmallImg��faces��ʾ��⵽������Ŀ�����У�1.1��ʾ
	//ÿ��ͼ��ߴ��С�ı���Ϊ1.1��2��ʾÿһ��Ŀ������Ҫ����⵽3�β��������Ŀ��(��Ϊ��Χ�����غͲ�ͬ�Ĵ��ڴ�
	//С�����Լ�⵽����),CV_HAAR_SCALE_IMAGE��ʾ�������ŷ���������⣬��������ͼ��Size(30, 30)ΪĿ���
	//��С���ߴ�
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT	//ֻ�����������
		//|CV_HAAR_DO_ROUGH_SEARCH	//ֻ�����Լ��
		|CV_HAAR_SCALE_IMAGE	//�������������
		,
		Size(50, 50) );

	//��ͷ����ɫ��
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++)
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//��ԭ��ԭ���Ĵ�С
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		//circle( img, center, radius, CV_RGB(255,0,0), 1, 8, 0 );

		//imshow("head",img);
		this->cascadeCnt++;
		//waitKey(1);

		if( nestedCascade.empty() )//��2�������û�е����
			continue;

		smallImgROI = img_ori(*r);
		Mat smallImgROI_clone = smallImgROI.clone();
		Mat smallImgROI_clone2 = smallImgROI.clone();

		//������ĺ�������һ��
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			|CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30) );

		//����������ɫ��ʶ
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
		{
			this->isDetect=false;

			//Mat supSmallImg;
			vector<Rect> thirdNestedObjects;
			vector<Rect> mouthNestedObjects;

			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			//circle( img, center, radius, CV_RGB(0,0,255), 1, 8, 0 );

			faceImg = smallImgROI(*nr);
			//�����������
			Rect re=Rect(faceImg.cols*0.25,faceImg.rows*0.65,faceImg.cols*0.5,faceImg.rows*0.35-1);
			Mat face2MouthRoi=faceImg(re);
			//imshow("face",faceImg);
			//imshow("mouth_area",face2MouthRoi);

			//��������ͼ��ж�������
			con_num_detect(face2MouthRoi,this->isDetect);

			this->nestedCnt++;
			//waitKey(1);

			if (this->isDetect == true)
			{
				flag=true;
				circle( img, center, radius, CV_RGB(0,0,255), 3, 8, 0 );
// 				imshow("�����˳���",faceImg);
// 				waitKey();
			}
		}
	}//��ͷ

	if(flag == true)
		this->isDetect=true;
}

void Controller::con_num_detect(Mat src,bool &isDet)
{
	//��ͨ��������ж�
	Mat src_ori = src.clone();
	//�и�ͼƬ
	cut_image_percent(src,0.2,0,0.8,1);

	Mat src_gray;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	int con_size_threshold=4;
	double nor_max_2_con_threshold = 0.13;

	if( !src.data ){
		return ;
	}

	GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

	//ת�ɻҶ�ͼ
	cvtColor( src, src_gray, CV_RGB2GRAY );

	Mat grad_y;
	Mat abs_grad_y;

	Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );

	abs_grad_y *=1.5;
	threshold(abs_grad_y,abs_grad_y,30,255,THRESH_OTSU | THRESH_BINARY);
	//threshold(abs_grad_y,abs_grad_y,30,255,THRESH_BINARY);

	Mat before_contours = abs_grad_y.clone();
	Mat before_contours2 = abs_grad_y.clone();

	//�������
	vector<vector<Point>> _contours;//������������
	vector<Vec4i>hierarchy;
	cv::findContours( abs_grad_y, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	double nonZeroRate = get_max_2_con_rate(before_contours);
	if (_contours.size() <= con_size_threshold)
	{
		//�����ж�Ϊ������
		if(nonZeroRate < nor_max_2_con_threshold) //�����ɫ��ɫ���֣�����������
			isDet = true;
	}

	else{
		//�ѳ����ж�Ϊ������
		if(nonZeroRate > nor_max_2_con_threshold); //����������������
		else
			isDet=true;
	}
}

//���ٷֱȽ�ȡͼƬ
void Controller::cut_image_percent(Mat &img,double left,double upper,double right,double bottom)
{
	Point a,c;
	a.x = img.cols * left;
	a.y = img.rows * upper;
	c.x = img.cols * right;
	c.y = img.rows * bottom;
	Rect r = Rect(a,c);
	img = img(r);
}

double Controller::get_max_2_con_rate(Mat &img)
{
	keepSomeMaxCon(img,2);
	int count=countNonZero(img);
	double rate = (double)count / (img.rows*img.cols);
	return rate;
}

//src�Ǵ����ֵͼ��n�Ǳ���ǰN����ͨ��
bool Controller::keepSomeMaxCon(Mat &src, int n){
	///////// !!!findcontours���ܲ���λ��ͼ���Ե�ĵ㣬���±�Ե�ĵ�û�����
	for(int i=0;i<src.cols;i++)
		src.at<uchar>(0,i) = src.at<uchar>(src.rows -1,i) = 0;
	for(int j=0;j<src.rows;j++)
		src.at<uchar>(j,0) = src.at<uchar>(j,src.cols -1) = 0;

	//��ͨ��ȥ�룬ֻʣ��n��
	Mat temp = src.clone();
	vector<vector<Point> > contours;
	findContours(temp,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); //����,������ı�temp

	//ԭͼ��ͨ������������Ҫ��������ͨ������
	if(contours.size() < n)	
		return false;

	Mat srt(Size(contours.size(),1),CV_32SC1);
	for(int c=0;c<(int)contours.size();c++)
		srt.at<int>(0,c) = (int)contourArea(contours[c]);

	cv::sortIdx(srt,srt,CV_SORT_EVERY_ROW + CV_SORT_DESCENDING);
	for(int i=n; i<(int)contours.size(); i++){ //ֻ����ǰn����ͨ��
		int idx = srt.at<int>(i);
		vector<Point> tmp = contours[idx];
		const Point* elementPoints[1] = { &tmp[0] };
		int numberOfPoints = (int)contours[idx].size();	
		fillPoly(src,elementPoints, &numberOfPoints ,1,Scalar(0,0,0));//��䵥����ͨ��		
	}

	return true;
}

//�ж�һ��ͼ���Ƿ��ǲ�ɫͼ��
bool Controller::image_is_color(Mat image,bool& is_color)
{
	if(!image.data)
		return false;

	int row = image.rows;
	int col = image.cols;
	isColor = false;
	for(int i = 0; i < row;i++)
		for(int j = 0; j< col;j++)
			if (  ((int)(image.at<Vec3b>(i,j)[0]) != (int)(image.at<Vec3b>(i,j)[1]))
				||((int)(image.at<Vec3b>(i,j)[1]) != (int)(image.at<Vec3b>(i,j)[2]))
				||((int)(image.at<Vec3b>(i,j)[2]) != (int)(image.at<Vec3b>(i,j)[0]))
			   )
			{
				//�ǲ�ɫ��Ƶ
				is_color=true;
				return true;
			}

	return true;
}