#include "qttrajectoryanalysis.h"
//#include <QtGui/QApplication>
#include <QtWidgets/QApplication>
#include <QTextCodec>
//#include <QMessageBox>
#include <QtWidgets/QMessageBox>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
// 	QTextCodec::setCodecForTr(codec);
// 	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
// 	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	qRegisterMetaType<cv::Mat>("Mat");
	qRegisterMetaType<cv::Mat>("cv::Mat&");
	qRegisterMetaType<std::string>("string");

	QtTrajectoryAnalysis w;	
	if( !w.loadData()){
		QMessageBox::information(0, QString::fromLocal8Bit("��ʾ"), 
			QString::fromLocal8Bit("�����ʼ��ʧ�ܣ�"));
		a.quit();
		return -1;
	}

	QString qpath(argv[1]);
	std::string file = std::string((const char *)qpath.toLocal8Bit());
	if (!w.loadImage(file)){
		QMessageBox::information(0, QString::fromLocal8Bit("��ʾ"), 
			QString::fromLocal8Bit("����ȷ�򿪳���"));
		a.quit();
		return -1;
	}
	////////��������
	if( argc > 3){
		QStringList files;
		for( int i = 1; i < argc -1; ++i){
			files << QString::fromLocal8Bit(argv[i]);
		}
		w.setBatchInfo(files);
	}
	if( argc >2 ){
		QString folder = QString::fromLocal8Bit(argv[argc-1]);
		w.setFolder(folder);
	}

	w.show();
	return a.exec();
}
