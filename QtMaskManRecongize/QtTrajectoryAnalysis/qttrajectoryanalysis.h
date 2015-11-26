#ifndef QTTRAJECTORYANALYSIS_H
#define QTTRAJECTORYANALYSIS_H

//#include <QtGui/QDialog>
#include <QtWidgets/QDialog>
//#include <QtGui/QMainWindow>
#include "ui_qttrajectoryanalysis.h"
#include <string>
#include <opencv2/opencv.hpp>
#include "updateThread.h"
#include "waitingprogressbar.h"
#include "AlgorithmInterface/AI_Maskman_Detect.h"
#include <QMetaType>

class QtTrajectoryAnalysis : public QDialog
{
	Q_OBJECT

public:
	QtTrajectoryAnalysis(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~QtTrajectoryAnalysis();

	bool loadImage(std::string);
	void setFolder(QString);
	void setBatchInfo(QStringList&);
	bool loadData();

private:
	Ui::QtTrajectoryAnalysisClass ui;

	ServiceDLL* serviceDll;
	extractThread *m_extractThread;
	updateThread *m_updateThread;
	std::string outputFolder; //����ļ���
	std::string videoName;//�ļ�������
	bool isClicked;
	QGraphicsScene imgScene;

	///��������
	WaitingProgressBar waitingDlg;
	QStringList fileList;
	QString folder;
	bool isBatch;
	int batchCnt;

	AI_Maskman_Detect AI_md;

	QPoint move_point; //�ƶ��ľ���
	bool mouse_press; //��갴��
private:
	bool init();
	void destroy();
	void setImage(cv::Mat&);
	void setRun();
	void setStop();
	void batchFiles();
	void continueBatch();
	std::string getFileName(const QString&, QString, QString&);
	QString detectLog;

	QImage const copy_mat_to_qimage(cv::Mat const &mat, QImage::Format format);
	QImage const mat_to_qimage_cpy(cv::Mat &mat, int qimage_format);

protected:
	//��갴���¼�
	void mousePressEvent(QMouseEvent *event);
	//����ͷ��¼�
	void mouseReleaseEvent(QMouseEvent *event);
	//����ƶ��¼�
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void on_pBtn_Run_clicked();
	void on_pBtn_forward_clicked();
	void on_pBtn_backward_clicked();
	void on_pBtn_OutputFolder_clicked();
	void on_pBtn_exit_clicked();
	void on_pBtn_minimize_clicked();

	void updateProcessBar(int);

	void getThreadEnd();
	void getThreadStop();
	void getThreadFail();

	void updateImg(cv::Mat*);
	void updateEventInfo(std::string);

	void closeWaitDlg();
	void batchDone();
};
Q_DECLARE_METATYPE(cv::Mat);
Q_DECLARE_METATYPE(std::string);
#endif // QTTRAJECTORYANALYSIS_H
