/*
 * lib_maskman_detect.h
 *
 * funtion:These functions can be external invoked
 *
 *    Author: Bill Wang
 */

#ifndef _LIB_MASKMAN_DETECT_H_
#define _LIB_MASKMAN_DETECT_H_


#include "AI_Maskman_Detect.h"


extern "C" __declspec(dllexport) uint maskman_detect(void*, int);	//�㷨�ⲿ�ӿں���

extern "C"__declspec(dllexport) void sayHello();	//Hello����

#endif
