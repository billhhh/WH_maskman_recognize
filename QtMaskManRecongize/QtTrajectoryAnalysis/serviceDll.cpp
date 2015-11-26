#include "serviceDll.h"

ServiceDLL* ServiceDLL::instance = NULL;

ServiceDLL* ServiceDLL::getInstance(){
	if( instance == NULL)
		instance = new ServiceDLL();
	return instance;
}

ServiceDLL::ServiceDLL(){
}

ServiceDLL::~ServiceDLL(){
	releaseDLL();
}

bool ServiceDLL::execServiceExtract(AI_Maskman_Detect*& pMd){
	if ( maskManRec((void*)pMd, sizeof(*pMd))){
		return false;
	}
	return true;
}

/////�ͷ�DLL
void ServiceDLL::releaseDLL(){
	qLib.unload();
	maskManRec = NULL;
}

////����DLL
bool ServiceDLL::loadDLL(std::string path){
	////�ͷ�dll
	releaseDLL();

	qLib.setFileName(QString::fromStdString(path));
	if (!qLib.load()){
		printf("qLibrary ����ʧ�ܣ�\n");
		return false;
	}

	sayHello = (SayHello) qLib.resolve("sayHello");
	sayHello();
	maskManRec = (DetectMaskMan) qLib.resolve("maskman_detect");
	if( maskManRec == NULL){
		releaseDLL();
		return false;
	}
	return true;
}
