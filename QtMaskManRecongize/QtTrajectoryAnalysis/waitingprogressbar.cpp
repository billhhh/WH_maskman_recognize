
#include "waitingprogressbar.h"

WaitingProgressBar::WaitingProgressBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//���ô�����������ز�����λ�ڶ���
	this->setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);
	//�ɻ�ȡ������Ч��
	this->setMouseTracking(true);
	mouse_press = false;

	fileCnt = 0;
	ui.progressBar->setRange(0, 100);

}

WaitingProgressBar::~WaitingProgressBar()
{

}

void WaitingProgressBar::setInfo(int i){
	fileCnt = i;
}

void WaitingProgressBar::on_cmdLinkBtn_clicked(){
	on_pBtn_exit_clicked();
}

void WaitingProgressBar::updateProgress(int i){
	ui.progressBar->setValue(i);
}

void WaitingProgressBar::updateLabel(int i){
	QString qstr = QString::number(i) + "/" + QString::number(fileCnt);
	ui.label_progress->setText(qstr);
}

void WaitingProgressBar::setBtnTip(QString qstr){
	ui.cmdLinkBtn->setText(qstr);
}

void WaitingProgressBar::setLabelFile(QString qstr){
	ui.label_file->setText(qstr);
}

void WaitingProgressBar::closeEvent(QCloseEvent *e){
	on_pBtn_exit_clicked();
}

void WaitingProgressBar::mousePressEvent(QMouseEvent *event){  
	if(event->button() == Qt::LeftButton){
		mouse_press = true;
		//�������ڴ����λ�ã�����ʹ��event->globalPos() - this->pos()��
		move_point = event->pos();;
	}
}
void WaitingProgressBar::mouseMoveEvent(QMouseEvent *event){
	//��������������
	if(mouse_press){
		//����������Ļ��λ��
		QPoint move_pos = event->globalPos();

		//�ƶ�������λ��
		this->move(move_pos - move_point);
	}
}

void WaitingProgressBar::mouseReleaseEvent(QMouseEvent *event){  
	//�������Ϊδ������
	mouse_press = false;
}

void WaitingProgressBar::on_pBtn_minimize_clicked(){
	this->showMinimized();
}

void WaitingProgressBar::on_pBtn_exit_clicked(){
	if( !procEnd)
		emit procStop();
	updateProgress(0);
	this->close();
}

void WaitingProgressBar::setProcStatus(bool val){
	procEnd = val;
}