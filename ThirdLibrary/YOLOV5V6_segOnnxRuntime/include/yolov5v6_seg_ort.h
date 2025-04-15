/*
 ====================================================================
 Name         : yolov5v6_seg_ort.h
 Author       : lll
 Version      : 0.1
 Copyright    : 
 Description  : yolov5v6_seg_ort 接口头文件
 ====================================================================
 */
 
#ifndef YOLOV5V62_ONNXRUNTIME_SEG_H
#define YOLOV5V62_ONNXRUNTIME_SEG_H

#ifndef X_TYPEH
#include "x_type.h"
#endif

#include "opencv2\opencv.hpp"
#include <iostream>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/**
@brief yolov5v6_seg_ort_create 创建识别任务
@param _modelfile模型文件，_classname objname文件
@param boxThreshold 检测框得分，classThreshold类别得分,_nmsThresholdiou阈值，maskThreshold 非最大抑制阈值，
@param _isgpu是否gpu,0否，1是
@param m_threadnum线程个数
@retval >=0任务索引号
@retval -1模型或类别名称路径不对，-2最大模型加载数超限100，-3模型类型不正确，-4模型初始化失败
@description
*/
X_API int STDCALL yolov5v6_seg_ort_create(const char* _modelfile, const char* _classname, 
	double boxThreshold = 0.25, double classThreshold = 0.25, double _nmsThreshold = 0.45, double maskThreshold = 0.5,
	int _threadnum = 4, bool _isgpu = false);

/**
@brief yolov5v6_seg_ort_destroy 销毁任务
@param taskindex 任务索引
@retval TRUE 成功
@retval FALSE 失败
@description
*/
X_API bool STDCALL yolov5v6_seg_ort_destroy(int taskindex);

/**
@brief yolov5v6_seg_ort_clear 销毁所有任务
@description
*/
X_API void STDCALL yolov5v6_seg_ort_clear();

/**
@brief yolov5v6_seg_ort_set_conf_iou 设置检测置性度和iou值
@param taskindex 任务索引
@param boxThreshold 置性度阈值， classThreshold类别阈值,nmsThreshold 非最大抑制阈值,maskThreshold掩抹阈值
@description
*/
X_API void STDCALL yolov5v6_seg_ort_set_conf_iou(int taskindex, double boxThreshold = 0.25, double classThreshold = 0.25, double nmsThreshold = 0.45, double maskThreshold = 0.5);

/**
@brief yolov5v6_seg_ort_process opencv格式图像处理
@param taskindex 任务索引
@param _ImgSrc 图片数据
@param _ResultImg 结果图片
@param _maskImg 掩膜图片
@param _objRec 目标数据
@description
*/
X_API bool STDCALL yolov5v6_seg_ort_process(int taskindex, cv::Mat _ImgSrc, OUT cv::Mat& _ResultImg, OUT cv::Mat& _maskImg, OUT std::vector<RecMaskResult>& _objRec);

/**
@brief yolov5v6_seg_ort_process_csharp 图像处理c#
@param taskindex    任务索引
@param src			图像数据
@param w			图像宽
@param h			图像高
@param channel		图像通道数
@param resultimg	结果图像
@param resultimglen	结果图像数据长度
@param container	结果容器数组，最多128个目标
@retval int			识别到目标个数
@description
*/
X_API int STDCALL yolov5v6_seg_ort_process_csharp(int taskindex, void* src, int w, int h, int imgstride, int channel,
	uchar* resultimg, size_t& resultimglen,
	mask_t_container& container);
#ifdef __cplusplus
}
#endif
#endif //YOLOV7_OPENVNO_DET_H

