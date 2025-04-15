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
//#define BOOL int
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
#define LOG_SAVE_TIME		3600*24*30    //30天

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

// 常用通用宏定义
#define SAFE_FREE(x)			if ((x) != NULL) { free(x); (x) = NULL;}
#define GLOABL

#ifdef _WIN32
#define localtime_r(a, b) localtime_s(b, a)
#endif

#define C_SHARP_MAX_OBJECTS				128

#ifdef __WIN__
typedef struct {
	HANDLE hthread;
} LThread;

typedef struct {
	CRITICAL_SECTION section;
} LMutex;
#else
#include <pthread.h>
typedef struct {
	pthread_t hthread;
} LThread;

typedef struct {
	pthread_mutex_t mutex;
} LMutex;
#endif


typedef struct _RecMaskResult {
	int left;								//左上角坐标x
	int top;								//左上角坐标y
	int right;								//右下角坐标x
	int bottom;								//右下角坐标y
	int classID;							//类别id
	int track_id;							//跟踪id
	int label_len;							//名称长度
	int mask_id;							//maskid
	double score;							//得分
	char label_text[MAX_CHAR_LEN];			//名称
} RecMaskResult;

struct mask_t_container {
	RecMaskResult candidates[C_SHARP_MAX_OBJECTS];
};

#endif
