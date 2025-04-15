/*
 ====================================================================
 Name         : tensorrt_yolo_onnx_multask.h
 Author       : lll(wchart:xinsuinizhuan)
 Version      : 0.1
 Copyright    : 
 Description  : tensorrt_yolo_onnx_multask 接口头文件
 ====================================================================
 */
 
#ifndef TENSORRT_YOLO_ONNX_MULTITASK_H
#define TENSORRT_YOLO_ONNX_MULTITASK_H

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
@brief tensorrt_yolo_onnx_multask_create 创建识别任务
@param _trtmodelfile文件，_classname objname文件
@param _modeltype 0：V5; 1:X;2::V5OBB,
@param confidence_threshold 置性度阈值，nms_threshold 非最大抑制阈值
@param _gpu id
@retval >=0任务索引号
@retval -1模型或类别名称路径不对，-2最大模型加载数超限100，-3模型类型不正确，-4模型初始化失败
@description
*/
X_API int STDCALL tensorrt_yolo_onnx_multask_create(const char* _trtmodelfile, const char* _classname, int _modeltype = 0, float confidence_threshold = 0.25, float nms_threshold =  0.4, int _gpuid = 0);

/**
@brief tensorrt_yolo_onnx_multask_onnx2trt 模型onnx导出成trt
@param _onnxmodelfile 模型onnx的路径
@param _enginesavefile 生成的engine的文件全路径，最后不带反斜杠，比如“E:\\Item\\xxx.engine”;或者为空，则默认同目录下生成xxx.engine
@param _modeltype model type  转换类型，0 UES_FP32;1 UES_FP16,咱不支持8位
@param _converttype  0：V5; 1:X;2::V5OBB,
@param _gpu_id gpu编号
@param _batch_size 尺度
@retval -1 onnx路径为空，-2为非onnx后缀文件; -3表示gpu id不正确； -4表示模型类型id不正确； -5表示转换类型不正确；-6 engine路径打开失败，0 成功
@description
*/
X_API int STDCALL tensorrt_yolo_onnx_multask_onnx2trt(const char* _onnxmodelfile, const char* _enginesavefile = "",
    int _modeltype = 0,
    int _converttype = 0,
    int _gpu_id = 0,
    int _batch_size = 1);


/**
@brief tensorrt_yolo_onnx_multask_destroy 销毁任务
@param taskindex 任务索引
@retval TRUE 成功
@retval FALSE 失败
@description
*/
X_API bool STDCALL tensorrt_yolo_onnx_multask_destroy(int taskindex);

/**
@brief tensorrt_yolo_onnx_multask_clear 销毁所有任务
@description
*/
X_API void STDCALL tensorrt_yolo_onnx_multask_clear();

/**
@brief tensorrt_yolo_onnx_multask_process opencv格式图像处理
@param taskindex 任务索引
@param _ImgSrc 图片数据
@param _ResultImg 结果图片
@param _objRec 目标数据
@description
*/
X_API bool STDCALL tensorrt_yolo_onnx_multask_process(int taskindex,cv::Mat _ImgSrc, OUT cv::Mat& _ResultImg, OUT std::vector<Yolov5ObbXResult>& _objRec);

#ifdef __cplusplus
}
#endif
#endif //YOLOV5_OBB_X_TENSORRT_DET_H

