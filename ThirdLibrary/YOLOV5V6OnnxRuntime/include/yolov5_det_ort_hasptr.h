/*
====================================================================
Name			: yolov5_det_ort_hasptr.h
Author			: lll
qq				: 742721388
Wchart			: xinsuinizhuan
bilibili		: xinsuinizhuan
tiktok			: lllstandout
Version			: 0.1
Copyright		:
Description		: yolov5_det_ort_hasptr 接口头文件
====================================================================
*/
 
#ifndef YOLOV5_DET_ONNXRUNTIME_HASPTR_H
#define YOLOV5_DET_ONNXRUNTIME_HASPTR_H

#ifndef X_TYPEH
#include "x_type.h"
#endif

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/**
@brief yolov5_det_onnxtr_hasptr_cleanup 注销函数
@param void
@retval TRUE 成功
@retval FALSE 失败
@description
*/
X_API bool STDCALL yolov5_det_onnxtr_hasptr_cleanup(void);

/**
@brief yolov5_det_onnxtr_hasptr_create 创建识别任务,自动分配gpu
@param _engine文件，_classname objname文件
@param _conf_thres 置性度阈值，_nms_thres 非最大抑制阈值
@retval 任务索引，0创建失败，大于0则成功
@description
*/
X_API uint64_t STDCALL yolov5_det_onnxtr_hasptr_create(const char* _onnxfile, const char* _classname, double _conf_thres = 0.4, double _nms_thres = 0.4);

/**
@brief yolov5_det_onnxtr_hasptr_destroy 销毁指定任务
@param _taskindex 任务索引
@retval TRUE 成功
@retval FALSE 失败
@description
*/
X_API bool STDCALL yolov5_det_onnxtr_hasptr_destroy(uint64_t _taskindex);

/**
@brief yolov5_det_onnxtr_hasptr_set_conf_iou 设置检测置性度和iou值
@param _taskindex 任务索引
@param _conf_thres 置性度
@param _iou_thres IOU值
@description
*/
X_API void STDCALL yolov5_det_onnxtr_hasptr_set_conf_iou(uint64_t _taskindex, double _conf_thres = 0.4, double _nms_thres = 0.5);

/**
@brief yolov5_det_onnxtr_hasptr_process 图像处理
@param _taskindex 任务索引
@param _ImgSrc 图片数据
@param _ResultImg 结果图片
@param _objRec 目标数据
@description
*/
X_API bool STDCALL yolov5_det_onnxtr_hasptr_process(uint64_t _taskindex, cv::Mat _ImgSrc, OUT cv::Mat& _ResultImg, OUT std::vector<RecTrackResult>& _objRec);
#ifdef __cplusplus
}
#endif
#endif //YOLOV5_DET_ONNX_TENSORRT_HASPTR_H

