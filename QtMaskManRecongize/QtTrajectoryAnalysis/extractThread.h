#ifndef _H_EXTRACTTHREAD_
#define _H_EXTRACTTHREAD_
//#include <Qt/qthread.h>
#include <QThread>
#include "serviceDll.h"
#include "AlgorithmInterface/AI_Maskman_Detect.h"

class extractThread :public QThread{
	Q_OBJECT

public:
	void init(AI_Maskman_Detect* pAlInterface);
	bool getStatus() const;
	void setStatus(bool status);

	int getPercent() const;
	bool getImg(cv::Mat*&);
	std::string getEventInfo();
	extractThread(QObject *parent);
	~extractThread();

signals:
	void sendSliderVal(int);
	void threadStop();
	void threadEnd();
	void threadFail();

protected:
	void run();

private:
	ServiceDLL* serviceDll;
	AI_Maskman_Detect* pAI_md;
};

#endif