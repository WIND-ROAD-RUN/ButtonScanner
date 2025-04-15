/*
 ====================================================================
 Name         : device_types.h
 Author       : lll
 Version      : 0.1
 Copyright    : 
 Description  : 视频设备管理头文件
 ====================================================================
 */

#ifndef DEVICE_TYPESH
#define DEVICE_TYPESH

#include <time.h>
#include <string>

#ifndef X_TYPEH
#include "x_type.h"
#endif

typedef struct _VideoDeviceInfo VideoDeviceInfo;

#define STREAM_CONNECT_TYPE_RTSP	0
#define STREAM_CONNECT_TYPE_USB		1
#define STREAM_CONNECT_TYPE_SDK		2


/**
@ingroup 设备管理模块
@param  devicefd句柄
@param  data 结果图像数据
@param  width 结果图像宽度
@param  height 结果图像高度
@param  channele 结果图像通道
@param  result 识别结果数字指针
@param  resultsize 识别结果个数
@param  udata 用户数据
 */
typedef void (CALLBACK* DeviceVideoProcssCallBack)(VideoDeviceInfo* devicefd, 
	unsigned char* data, int width, int height,
	int channele, 
	RecTrackResult* result, 
	int resultsize,
	void* udata);


/**
	@struct CameraHostFunc
*/
typedef struct _VideoDeviceFunc{
	bool(*device_stop_helmet)(VideoDeviceInfo* pdevice);
	bool(*device_start_helmet)(VideoDeviceInfo* pdevice);
	bool(*device_restart_helmet)(VideoDeviceInfo* pdevice, const char* _onnxfile, const char* _classname, int _threadnum);
	bool(*device_set_helmet_conf_iou)(VideoDeviceInfo* pdevice, double _conf_thres, double _nms_thres);
	bool(*device_stop_firesmoking)(VideoDeviceInfo* pdevice);
	bool(*device_start_firesmoking)(VideoDeviceInfo* pdevice);
	bool(*device_restart_firesmoking)(VideoDeviceInfo* pdevice, const char* _onnxfile, const char* _classname, int _threadnum);
	bool(*device_set_firesmoking_conf_iou)(VideoDeviceInfo* pdevice, double _conf_thres, double _nms_thres);
} VideoDeviceFunc;

//安全帽检测
typedef struct _HelmetDetInfo{
    int                                         fd;                         //任务索引
	char										m_helmetmodel[MAX_PATH];	//模型
	char										m_helmetnames[MAX_PATH];	//模型name文件路径
	int											m_threadnum;				//线程数
	double										m_conf_thres;				//Confidence threshold
	double										m_nms_thres;				//Non-maximum suppression threshold
} HelmetDetInfo;

//烟火检测
typedef struct _FireSmokingDetInfo {
    int                                         fd;								//任务索引
	char										m_firesmokingmodel[MAX_PATH];	//模型
	char										m_firesmokingnames[MAX_PATH];	//模型name文件路径
	int											m_threadnum;					//线程数
	double										m_conf_thres;					//Confidence threshold
	double										m_nms_thres;					//Non-maximum suppression threshold
} FireSmokingDetInfo;

struct _VideoDeviceInfo {
	VideoDeviceFunc*				profuncs;								//操作
    int                             fd;										//任务索引
    bool							status;                                 //任务状态，false销毁不可用，true可用
	int								device_id;								//设备id
	char							device_name[MAX_CHAR_LEN];				//设备名称
	char							device_addre[MAX_CHAR_LEN];				//设备位置
	char							device_usename[MAX_CHAR_LEN];			//设备用户名
	char							device_passwd[MAX_CHAR_LEN];			//设备密码
	char 							device_ip[MAX_IP_LEN];		    	    //设备ip
    int								device_port;							//设备端口	
    int32 							device_status;							//设备状态			
	int								device_connect_type;					//设备连接类型，0 rtsp流，1 usb, 2 SDK tcp连接
	int								device_usbindex;						//连接USB设备时，设备编号
	char							device_rtsp_addre[MAX_PATH];			//设备流地址
	bool							b_det_helmet;							//是否开启安全帽检测
	HelmetDetInfo					det_helmet_info;						//安全帽检测任务信息
	bool							b_det_firesmoking;						//是否开启烟火减
	FireSmokingDetInfo				det_firesmoking_info;					//烟火检测任务指针
	DeviceVideoProcssCallBack 		video_func;	        					//视频处理回调
    void*							video_udata;				    		//视频处理用户数据
	LThread							video_pro_thr;							//视频处理线程
	bool							video_pro_thr_active;					//频处理线程状态
};

#endif
