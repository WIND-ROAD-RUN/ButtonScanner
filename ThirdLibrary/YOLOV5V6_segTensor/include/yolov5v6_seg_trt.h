/*
 ====================================================================
 Name			: yolov5v6_seg_trt.h
Author			: lll
qq				: 742721388
Wchart			: xinsuinizhuan
bilibili		: xinsuinizhuan
tiktok			: lllstandout
Version			: 0.1
Copyright		:
Description		: yolov5v6_seg_trt 接口头文件
====================================================================
*/
 
#ifndef YOLOV5V6_2_ONNX_TENSORRT_SEG_MULTI_TASK_H
#define YOLOV5V6_2_ONNX_TENSORRT_SEG_MULTI_TASK_H

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
@brief yolov5v6_seg_trt_create 创建识别任务
@param _engine文件，_classname objname文件
@param _boxthres 目标位置阈值，_clasthres目标类别阈值，_nms_thres 非最大抑制阈值,_mask_thres掩膜阈值
@param _gpu_id指定运行gpu编号
@param _batch_size批量尺寸
@retval >=0任务索引号
@retval -1模型或类别名称路径不对，-2最大模型加载数超限100，-3模型初始化失败
@description
*/
X_API int STDCALL yolov5v6_seg_trt_create(const char* _enginefile, const char* _classname, 
	double _boxthres = 0.25, double _clasthres = 0.25, double _nms_thres = 0.4, double _mask_thres = 0.5,int _gpu_id = 0, int _batch_size = 1);

/**
@brief yolov5v6_seg_trt_destroy 销毁指定任务
@param taskindex 任务索引
@retval TRUE 成功
@retval FALSE 失败
@description
*/
X_API bool STDCALL yolov5v6_seg_trt_destroy(int taskindex);

/**
@brief yolov5v6_seg_trt_clear 销毁所有任务
@description
*/
X_API void STDCALL yolov5v6_seg_trt_clear();

/**
@brief yolov5v6_seg_trt_set_conf_iou 设置检测置性度和iou值
@param taskindex 任务索引
@param _box_thres 置性度
@param _cls_thres 置性度
@param _iou_thres IOU值
@param _mask_thres掩膜阈值
@description
*/
X_API void STDCALL yolov5v6_seg_trt_set_conf_iou(int taskindex, double _box_thres = 0.25, double _cls_thres = 0.25, double _nms_thres = 0.5, double _mask_thres = 0.5);

/**
@brief yolov5v6_seg_trt_process 图像处理
@param taskindex 任务索引
@param _ImgSrc 图片数据
@param _ResultImg 结果图片
@param _maskImg 掩膜图片
@param _objRec 目标数据
@description
*/
X_API bool STDCALL yolov5v6_seg_trt_process(int taskindex, cv::Mat _ImgSrc, OUT cv::Mat& _ResultImg, OUT cv::Mat& _maskImg, OUT std::vector<RecMaskResult>& _objRec);


/**
@brief yolov5v6_seg_trt_process_mask 指定类别
@param taskindex 任务索引
@param _ImgSrc 图片数据
@param _vecobjindex 检测目标索引
@param contourAreas 检测目标roi区域
@param _ResultImg 结果图片
@param _maskImg 掩膜图片
@param _objRec 目标数据
@description
*/
X_API bool STDCALL yolov5v6_seg_trt_process_mask(int taskindex, cv::Mat _ImgSrc, OUT cv::Mat& _ResultImg, OUT cv::Mat& _maskImg, OUT std::vector<PyRecMaskResult>& _objRec);

#ifdef __cplusplus
}
#endif
#endif //YOLOV5V6_2_ONNX_TENSORRT_SEG_MULTI_TASK_H

