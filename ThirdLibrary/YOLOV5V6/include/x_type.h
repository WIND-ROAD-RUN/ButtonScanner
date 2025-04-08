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
#include <stdio.h>
#include <time.h>

#if defined(ANDROID)
#include <bits/types.h>
#endif

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
#include <winsock2.h>
#include <windows.h>
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
#ifdef ANDROID		/**< Android编译弘 */
#define TDBOOL int
#endif
typedef char int8;		/**<  */
typedef unsigned char uint8;		/**<  */
typedef short int16;		/**<  */
typedef unsigned short uint16;		/**<  */

#if (defined(_WIN64) || defined(__x86_64__))
typedef void* handle_td;
typedef int int32;
typedef unsigned int uint32;
#define INVALID_TD_HANDLE (void*)-1
#else
typedef int int32;
typedef unsigned int uint32;
typedef int handle_td;
#define INVALID_TD_HANDLE -1
typedef long long int int64;		/**<  */
typedef unsigned long long uint64;		/**<  */
#endif
#define IS_INVALID_TD_HANDLE(x) (x == INVALID_TD_HANDLE)

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
#define LOAD_TALBE_NAME		10
#define DEV_NAME_LEN		256

#define MAX_DRIVE 			3					/**< 最大后缀长度 */
#define MAX_DIR 			256					/**< 最大路径长度 */
#define MAX_FNAME 			256					/**< 最大文件名长度 */
#define MAX_EXT 			256					/**< 最大扩展名长度 */

// 常用通用宏定义
#define SAFE_FREE(x)			if ((x) != NULL) { free(x); (x) = NULL;}

#define GLOABL

#ifdef _WIN32
#define localtime_r(a, b) localtime_ss(b, a)
#endif


#ifdef WIN32
#define ACCESS(fileName,accessMode) _access(fileName,accessMode)
#else
#define ACCESS(fileName,accessMode) access(fileName,accessMode)
#endif

typedef struct _RecMaskResult {
	int left;								//左上角坐标x
	int top;								//左上角坐标y
	int right;								//右下角坐标x
	int bottom;								//右下角坐标y
	int classID;							//类别id
	int track_id;							//跟踪id
	int label_len;							//名称长度
	int mask_id;							//mask_id
	double score;							//得分
	char label_text[MAX_CHAR_LEN];			//名称
} RecMaskResult;

typedef struct _PyRecMaskResult {
	int left;								//左上角坐标x
	int top;								//左上角坐标y
	int right;								//右下角坐标x
	int bottom;								//右下角坐标y
	int classID;							//类别id
	int track_id;							//跟踪id
	int label_len;							//名称长度
	int mask_b;								//b分类值
	int mask_g;								//g分量值
	int mask_r;								//r分量值
	double score;							//得分
	double area;
	char label_text[MAX_CHAR_LEN];			//名称
} PyRecMaskResult;

#endif
