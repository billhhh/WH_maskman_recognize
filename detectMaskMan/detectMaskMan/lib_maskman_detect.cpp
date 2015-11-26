#include "lib_maskman_detect.h"
#include "Controller.h"

using namespace std;

//�㷨�ⲿ�ӿں���
uint maskman_detect(void* pVoid, int size){
	AI_Maskman_Detect* pAI_id = (AI_Maskman_Detect*)pVoid;
	Controller* ctrl;
	if( !ctrl->getInstance()->init() ){ //δ��ʼ��ʧ��
		cout<<"Controller init error...\n";
		return AlgorithmResult::AR_END;
	}
	ctrl->getInstance()->setParam(pAI_id);
	if(!ctrl->getInstance()->startDetect())
		return AlgorithmResult::AR_INTERNAL;

	return AlgorithmResult::AR_DONE;
}

//Hello����
void sayHello(){
	printf("say Hello!\n");
}
