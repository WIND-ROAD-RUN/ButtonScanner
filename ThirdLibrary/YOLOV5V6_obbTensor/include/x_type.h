/**
    @file		x_type.h
    @author  	lll
    @version 	1.0
    @brief 		工程通用头文件
 */

#ifndef X_TYPEH
#define X_TYPEH

#include <string.h>
#include <stdlib.h>
#include <string>

#if (defined(_WIN32) || defined(_WIN64)) && !defined(__WIN__)
#define __WIN__
#endif
#if !defined(__WIN__)
#define STDCALL		/**<  */
#define X_API		/**<  */
#define CALLBACK	/**<  */
#ifndef FALSE		
#define FALSE 0		/**<  */
#endif
#ifndef TRUE		
#define TRUE 1		/**<  */
#endif
#ifndef HWND		
#define HWND void*	/**<  */
#endif
#ifndef HDC
#define HDC void*	/**<  */
#endif
#else
#define NOMINMAX
#include <winsock2.h>
//#include <windows.h>
#define STDCALL __stdcall	/**<  */
#define X_API __declspec(dllexport)	/**<  */
#define CALLBACK __stdcall	/**<  */
#define _CRT_SECURE_NO_WARNINGS 1 /**<  */
#if defined(_MSC_VER)
#if _MSC_VER < 1900
#  define snprintf _snprintf
#endif
#endif

#endif

#ifndef OUT
#define OUT		/**<  */
#endif

#ifndef IN
#define IN		/**<  */
#endif

#ifndef NULL
#define NULL 0		/**<  */
#endif

/**    
    @name	通用基本数据类型
    @{
*/
//typedef int BOOL;		/**<  */
#define BOOL int
typedef char int8;		/**<  */
typedef unsigned char uint8;		/**<  */
typedef short int16;		/**<  */
typedef unsigned short uint16;		/**<  */
typedef long int32;		/**<  */
typedef unsigned long uint32;		/**<  */
//typedef long long int int64;		/**<  */
//typedef unsigned long long uint64;		/**<  */
/**    
    @}
*/

#define TRY_AGIAN_NUM	30	/**< 发送重发次数 */
#define MAX_IP_LEN 16	/**< 最大IP地址长度 */
#define MAX_MAC_LEN 60	/**< 最大MAC地址长度 */
#define MAX_USERNAME_LEN 60	/**< 最大用户名长度 */
#define MAX_PASSWORD_LEN 60	/**< 最大密码长度 */
#define MAX_MONTH 12	/**< 最大月份长度 */
#define MAX_WEEKDAY 7	/**< 最大星期长度 */
#define MAX_TIME_STRING_LEN 8	/**< 最大时间串长度 */
#define MAX_CHAR_LEN		64  //最大字符长度
#ifndef MAX_PATH
#define MAX_PATH 260	/**< 最大路径长度 */
#endif

#define DEF_BUF_SIZE		1024
#define IP_HEADER_SIZE		20
#define ICMP_HEADER_SIZE	12
#define MAX_DATA_LEN		256
#define MAX_ID_LEN			60
#define MAX_IMG_LEN			1920 * 1080 * 4 * 10

#ifndef MAX_DRIVE
#define MAX_DRIVE 			3					/**< 最大后缀长度 */
#endif
#ifndef MAX_DIR
#define MAX_DIR 			256					/**< 最大路径长度 */
#endif
#ifndef MAX_FNAME
#define MAX_FNAME 			256					/**< 最大文件名长度 */
#endif
#ifndef MAX_EXT
#define MAX_EXT 			256					/**< 最大扩展名长度 */
#endif

#define COLOR_GRAY				RGB(240, 240, 240)		//灰色
#define COLOR_GRAYISH			RGB(183, 183, 183)		//浅灰色
#define COLOR_WHITE				RGB(255, 255, 255)		//白色
#define COLOR_BLACK				RGB(0, 0, 0)			//黑色

#define COLOR_BLUE				RGB(0,0,255)			//蓝色

#define HeaderFontH	15		//表头的字高
#define HeaderFontW	0		//表头的字宽
#define RowHeigt	20		//行高

#define FONT_SIZE		700		//字体加粗

#define MAX_SQL_LEN 2048
#define MAX_SQL_LEN_QUERY 4092

#define DRAWER_ITEM_HEIGHT				28 
#define PREPOINT_NUM                    256


#define RECOG_TYPE_ZHENGYES		0
#define RECOG_TYPE_ZHENGNO		1
#define RECOG_TYPE_BEIYES		2
#define RECOG_TYPE_BEINO		3
#define RECOG_TYPE_ZHENGLOWXI	4
#define RECOG_TYPE_BEILOWXI		5

// 常用通用宏定义
#define SAFE_FREE(x)			if ((x) != NULL) { free(x); (x) = NULL;}
#define GLOABL

#ifdef _WIN32
#define localtime_r(a, b) localtime_s(b, a)
#endif

#ifdef __WIN__
typedef struct {
    HANDLE hthread;
} LThread;
#else
#include <pthread.h>
typedef struct {
    pthread_t thr;
} LThread;
#endif

/**
    @ingroup 底层开发包
    @brief 线程函数
    @param arg 线程参数
    @retval void* 线程返回值
 */
typedef void* (STDCALL* ThreadStartFunc)(void* arg);

typedef struct _CommTime {
	uint16 year;        
	uint16 month; 
	uint16 day;   
	uint16 hour;  
	uint16 minute; 
	uint16 second; 
}CommTime;

//定义一个时间对
typedef struct _PairTime { 
	CommTime start_time;
	CommTime end_time;
} PairTime;

typedef struct _RecTrackResult {
	int	index_No;							//编号
	int left;								//左上角坐标x
	int top;								//左上角坐标y
	int right;								//右下角坐标x
	int bottom;								//右下角坐标y
	int center_x;							//中心点横坐标
	int center_y;							//中心点纵坐标
	int classID;							//类别id
	int track_id;							//跟踪id
	int label_len;							//名称长度
    int alg_type;                           //算法类型
	double score;							//得分
	char label_text[MAX_CHAR_LEN];			//名称
} RecTrackResult;

typedef struct _Yolov5ObbXResult {
	float left;								//左上角坐标x
	float top;								//左上角坐标y
	float right;							//右下角坐标x
	float bottom;							//右下角坐标y
	int center_x;							//旋转矩形中心点坐标x
	int center_y;							//旋转矩形中心点坐标y
	int width;								//旋转矩形框宽度
	int height;								//旋转矩形框高度
	double angle;							//旋转矩形框角度
	int classID;							//类别id
	int label_len;							//名称长度
	double score;							//得分
	char label_text[MAX_CHAR_LEN];			//名称
} Yolov5ObbXResult;

#endif
