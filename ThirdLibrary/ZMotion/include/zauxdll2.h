/********************************** ZMCϵ�п�����  ************************************************
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**�ļ���: zmcaux.h
**������: ֣Т��
**ʱ��: 20130621
**����: ZMCDLL ��������

**------------�޶���ʷ��¼----------------------------------------------------------------------------
		
** �޸���: zxy
** ��  ��: 1.1
** �ա���: 2014.5.11
** �衡��: ZMC_ExecuteNoAck �滻Ϊ ZMC_Execute
		  
			
** �޸���: zxy
** ��  ��: 1.3
** �ա���: 2014.7.21
** �衡��: ZMC_Execute ZMC_DirectCommand �滻ΪZAux_Execute ZAux_DirectCommand
			  
���� ZAux_SetParam  ZAux_GetParam  ZAux_Direct_SetParam  ZAux_Direct_GetParam
				
���� ZAux_WriteUFile  ZAux_ReadUFile
				  
** �޸���: wy
** ��  ��: 1.5
** �ա���: 2016.6.6
** �衡��: ������BASICָ����з�װ������ZMC�⵽AUX��


  ** �޸���: wy
** ��  ��: 2.1
** �ա���: 2018.8.24
** ��  �������PCI���Ӻ���
**		   ������BASICָ���˶�ָ����з�װ����װ���б�����
**		   ���Ӳ�������ָ��
**		   ���Ӳ���MOVE_PARAָ��
		   ����λ�ñȽ����ָ��
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/




#ifndef _ZMOTION_DLL_AUX_H
#define _ZMOTION_DLL_AUX_H


//ZAUX֧�ֵ����������
#define MAX_AXIS_AUX   128  
#define MAX_CARD_AUX   32

#ifdef __cplusplus  
extern "C" {
#endif 





/*********************************************************
�������Ͷ���
**********************************************************/

typedef unsigned __int64   uint64;  
typedef __int64   int64;  


//#define BYTE           INT8U
//#define WORD           INT16U
//#define DWORD          INT32U
typedef unsigned char  BYTE;
typedef unsigned short  WORD;
//typedef unsigned int  DWORD;
//#define __stdcall 
typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable     �޷���8λ���ͱ���  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable        �з���8λ���ͱ���  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable     �޷���16λ���ͱ��� */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable         �з���16λ���ͱ��� */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable     �޷���32λ���ͱ��� */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable         �з���32λ���ͱ��� */
typedef float          fp32;                    /* single precision floating point variable (32bits) �����ȸ�������32λ���ȣ� */
typedef double         fp64;                    /* double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ� */
typedef unsigned int   uint;                  /* defined for unsigned 32-bits integer variable     �޷���32λ���ͱ��� */

typedef  void* ZMC_HANDLE;


/************************************************/
//������ 
/************************************************/
#define ERR_OK  0
#define ERROR_OK 0
#define ERR_SUCCESS  0

#define ERR_AUX_OFFSET       30000

#define ERR_NOACK               ERR_AUX_OFFSET      //��Ӧ��
#define ERR_ACKERROR            (ERR_AUX_OFFSET+1)  //Ӧ�����
#define ERR_AUX_PARAERR         (ERR_AUX_OFFSET+2)  //��������
#define ERR_AUX_NOTSUPPORT      (ERR_AUX_OFFSET+3)  //��֧��

#define ERR_AUX_FILE_ERROR      (ERR_AUX_OFFSET+4)  //��������
#define ERR_AUX_OS_ERR      (ERR_AUX_OFFSET+5)  //

#if 0
    //�����������
#endif


//#define  ZAUX_DEBUG //����Ҫ���ʱע�͵�����
//#define  ZAUX_DEBUG_FILE "d:\\zauxout.txt"

#define ZAUX_COMMAND_SUM  100		//д������������ʱʹ��

#ifdef  ZAUX_DEBUG

#define ZAUX_TRACE(cText,a)     ZAux_TraceOut("%s,L:%u,"cText"\r\n",__FILE__,(unsigned int)__LINE__,a)
#define ZAUX_WARN(cText,a)      ZAux_TraceOut("%s,L:%u,"cText"\r\n",__FILE__,(unsigned int)__LINE__,a)
#define ZAUX_ERROR(cText,a)     ZAux_TraceOut("Error:%s,L:%u,"cText"\r\n",__FILE__,(unsigned int)__LINE__,a)
#define ZAUX_ERROR2(cText,a,b)     ZAux_TraceOut("Error:%s,L:%u,"cText"\r\n",__FILE__,(unsigned int)__LINE__,a,b)

#else

#define  ZAUX_TRACE(cText,a)
#define  ZAUX_WARN(cText,a)
#define  ZAUX_ERROR(cText,a)
#define  ZAUX_ERROR2(cText,a,b)

#endif

void  ZAux_TraceOut(const char * cText, ...);



/*********************************************************
��������
**********************************************************/


/*************************************************************
Description:    //��װ Excute ����, �Ա���մ���
Input:          //������			handle
Input:          //�ַ�������		pszCommand
Input:			//���ص��ַ�����	uiResponseLength 
Output:         //���ص��ַ���		psResponse
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Execute(ZMC_HANDLE handle, const char* pszCommand, char* psResponse, uint32 uiResponseLength);


/*************************************************************
Description:    //��װ DirectCommand ����, �Ա���մ���
Input:          //������			handle
Input:          //�ַ�������		pszCommand
Input:			//���ص��ַ�����	uiResponseLength 
Output:         //���ص��ַ���		psResponse
Return:         //������
*************************************************************/
int32 __stdcall ZAux_DirectCommand(ZMC_HANDLE handle, const char* pszCommand, char* psResponse, uint32 uiResponseLength);

/*************************************************************
Description:    //�����������.
Input:          //������handle 
bifTofile		0 �ر�  1-ֻ�����������  2-ֻ����˶�����������  3���ȫ������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_SetTraceFile(int bifTofile, const char *pFilePathName);

/*************************************************************
Description:    //��ȡ�����������.
Input:          //������handle 
bifTofile		0 �ر�  1-ֻ�����������  2-ֻ����˶�����������  3���ȫ������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetTraceFile(int *bifTofile);


/*************************************************************
Description:    //��������������ӣ� ���ڷ�ʽ.
Input:          //���ں�COMId 
Output:         //������phandle
Return:         //������
*************************************************************/
int32 __stdcall ZAux_OpenCom(uint32 comid, ZMC_HANDLE * phandle);

/*************************************************************
Description:    //���ٿ�������������
Input:          //��С���ں�uimincomidfind
Input:          //��󴮿ں�uimaxcomidfind
Input:          //����ʱ��uims
Output:         //��ЧCOM pcomid
Output:         //������handle
Return:         //������
*************************************************************/
int32 __stdcall ZAux_SearchAndOpenCom(uint32 uimincomidfind, uint32 uimaxcomidfind,uint* pcomid, uint32 uims, ZMC_HANDLE * phandle);

/*************************************************************
Description:    //�����޸�ȱʡ�Ĳ����ʵ�����
Input:          //dwBaudRate ������
				dwByteSize   ����λ 
				dwParity = NOPARITY,У��λ 
				dwStopBits = ONESTOPBITֹͣλ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_SetComDefaultBaud(uint32 dwBaudRate, uint32 dwByteSize, uint32 dwParity, uint32 dwStopBits);

/*************************************************************
Description:    //�޸Ŀ�����IP��ַ
Input:          //������handle 
Input:          //IP��ַ  
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_SetIp(ZMC_HANDLE handle, char * ipaddress);

/*************************************************************
Description:    //���������������
Input:          //IP��ַ���ַ����ķ�ʽ����
Output:         //������handle
Return:         //������
*************************************************************/
int32  __stdcall ZAux_OpenEth(char *ipaddr, ZMC_HANDLE * phandle);


/*************************************************************
Description:    //���ټ���IP�б�
Input:          //uims ��Ӧʱ��
Input:          //addrbufflength		��󳤶�
output:			//ipaddrlist		��ǰ���IP�б�
Return:         //������, ERR_OK��ʾ��������.
*************************************************************/
int32 __stdcall ZAux_SearchEthlist(char *ipaddrlist, uint32 addrbufflength, uint32 uims);


/*************************************************************
Description:    //���ټ���������
Input:          //������IP��ַ
Input:          //��Ӧʱ��
Output:         //
Return:         //������, ERR_OK��ʾ��������.
*************************************************************/
int32 __stdcall ZAux_SearchEth(const char *ipaddress,  uint32 uims);

/*************************************************************
Description:    //�رտ���������
Input:          //������handle
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Close(ZMC_HANDLE  handle);

/*************************************************************
Description:    //��ͣ��������BAS��Ŀ
Input:          //������handle
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Resume(ZMC_HANDLE handle);

/*************************************************************
Description:    //��ͣ��������BAS����
Input:          //������handle
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Pause(ZMC_HANDLE handle);

/*************************************************************
Description:    //����BAS�ļ�����ZAR�������ص�����������
Input:          //������handle
Input:          //Filename BAS�ļ�·��
Input:          //RAM-ROM  0-RAM  1-ROM
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BasDown(ZMC_HANDLE handle,const char *Filename,uint32 run_mode);




#if 0
    //IOָ��
    // ����ʹ�� ZMC_GetIn ZMC_GetOutput ��
#endif
/*************************************************************
Description:    //��ȡ�����ź�
Input:          //������handle
				ionum IN���
Output:         //piValue �����״̬
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetIn(ZMC_HANDLE handle, int ionum , uint32 *piValue);


/*************************************************************
Description:    //������ź�
Input:          //������handle 
				ionum ����ڱ��
				iValue	�����״̬
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetOp(ZMC_HANDLE handle, int ionum, uint32 iValue);

/*************************************************************
Description:    //��ȡ�����״̬
Input:          //������handle  
				ionum ����ڱ��
Output:         //piValue �����״̬
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetOp(ZMC_HANDLE handle, int ionum, uint32 *piValue);


/*************************************************************
Description:    //��ȡģ���������ź�
Input:          //������handle 
				ionum AIN�ڱ��			
Output:         //pfValue ���ص�ģ����ֵ 4ϵ������0-4095
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAD(ZMC_HANDLE handle, int ionum , float *pfValue);

/*************************************************************
Description:    //��ģ��������ź�
Input:          //������handle  
				ionum DA����ڱ��
				fValue �趨��ģ����ֵ4ϵ������0-4095
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetDA(ZMC_HANDLE handle, int ionum, float fValue);


/*************************************************************
Description:    //��ȡģ�������״̬
Input:          //������handle  
				ionum ģ��������ڱ��
Output:         //pfValue ��ȡ�ĵ�ģ����ֵ 4ϵ������0-4095
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetDA(ZMC_HANDLE handle, int ionum, float *pfValue);

/*************************************************************
Description:    //��������ڷ�ת
Input:          //������handle  
				 ionum ����ڱ��
				 bifInvert ��ת״̬ 0/1
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetInvertIn(ZMC_HANDLE handle, int ionum, int bifInvert);

/*************************************************************
Description:    //��ȡ����ڷ�ת״̬
Input:          //������handle  
				ionum ����ڱ��
Output:         //piValue ��ת״̬
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetInvertIn(ZMC_HANDLE handle, int ionum, int *piValue);

/*************************************************************
Description:    //����pwmƵ��
Input:          //������handle  
				ionum PWM��ſ�
				fValue Ƶ�� Ӳ��PWM1M ��PWM 2K
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetPwmFreq(ZMC_HANDLE handle, int ionum, float fValue);

/*************************************************************
Description:    //��ȡpwmƵ��
Input:          //������handle  
				ionum PWM�ڱ��
Output:         //pfValue ���ص�Ƶ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetPwmFreq(ZMC_HANDLE handle, int ionum, float *pfValue);

/*************************************************************
Description:    //����pwmռ�ձ�
Input:          //������handle  
				ionum PWM�ڱ��
				fValue ռ�ձ�	0-1  0��ʾ�ر�PWM��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetPwmDuty(ZMC_HANDLE handle, int ionum, float fValue);

/*************************************************************
Description:    //��ȡpwmռ�ձ�
Input:          //������handle  
				ionum PWM�ڱ��
Output:         //pfValue ��ȡ��ռ�ձ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetPwmDuty(ZMC_HANDLE handle, int ionum, float *pfValue);

#if 0
    //ͨ��modbus���ٶ�ȡ����Ĵ���
#endif

/*************************************************************
Description:    //���� ���ٶ�ȡ�������
Input:          //������handle  
				ionumfirst IN��ʼ���
				ionumend	IN�������
Output:         //pValueList λ״̬ ��λ�洢
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetModbusIn(ZMC_HANDLE handle, int ionumfirst, int ionumend, uint8 *pValueList);


/*************************************************************
Description:    //���� ���ٶ�ȡ�����ǰ�����״̬
Input:          //������handle  
				ionumfirst IN��ʼ���
				ionumend	IN�������
Output:         //pValueList λ״̬ ��λ�洢
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetModbusOut(ZMC_HANDLE handle, int ionumfirst, int ionumend, uint8 *pValueList);


/*************************************************************
Description:    //���� ���ٶ�ȡ�����ǰ��DPOS
Input:          //������handle  
				imaxaxises ������
Output:         //pValueList ��ȡ������ֵ ����0��ʼ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetModbusDpos(ZMC_HANDLE handle, int imaxaxises, float *pValueList);


/*************************************************************
Description:    //���� ���ٶ�ȡ�����ǰ��MPOS
Input:          //������handle 
				imaxaxises ������
Output:         //pValueList ��ȡ�ķ�������ֵ ����0��ʼ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetModbusMpos(ZMC_HANDLE handle, int imaxaxises, float *pValueList);


/*************************************************************
Description:    //���� ���ٶ�ȡ�����ǰ���ٶ�
Input:          //������handle  
				imaxaxises ������
Output:         //pValueList ��ȡ�ĵ�ǰ�ٶ� ����0��ʼ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetModbusCurSpeed(ZMC_HANDLE handle, int imaxaxises, float *pValueList);



#if 0
    //����ZMC_DirectCommand �����ٻ�ȡһЩ״̬, ZMC_DirectCommand��ִ�б�ZMC_ExecuteҪ��
	// ֻ�в���������������Ԫ�ص���ʹ��ZMC_DirectCommand
	// 20130901�Ժ�İ汾��һЩ�˶�����Ҳ���Ե���ZMC_DirectCommand�����˶������������ʱ�򣬻����̷���ʧ�ܡ�
	// ZMC_DirectCommand�����˶�����ʱ�����������Ǿ������ֵ�������Ǳ������ʽ��
#endif

/*************************************************************
Description:    //ͨ�õĲ����޸ĺ��� sParam: ��д��������
Input:          //������handle 
				sParam ��������� "DPOS" ...
				iaxis ���
				fset �趨ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetParam(ZMC_HANDLE handle,const char *sParam,int iaxis, float fset);

/*************************************************************
Description:    //���� ͨ�õĲ�����ȡ����, sParam:��д��������
Input:          //������handle  
				sParam ��������� "DPOS" ...
				iaxis ���
Output:         //pfValue  ��ȡ�ķ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetParam(ZMC_HANDLE handle,const char *sParam, int iaxis, float *pfValue);

/*************************************************************
Description:    //���ü��ٶ�
Input:          //������handle  
				iaxis ���
				fValue  �趨ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetAccel(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���ٶ�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ٶȷ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAccel(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ������
Input:          //������handle  
				iaxis ���
Output:         //��ȡ����������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAddax(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //������澯�ź�
Input:          //������handle  
				iaxis ���
				iValue �����ź�����ڱ�ţ�ȡ��ʱ�趨-1
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetAlmIn(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ�澯�ź�
Input:          //������handle  
				iaxis ���
Output:         //piValue �����ź�����ڷ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAlmIn(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //����������
Input:          //������handle 
				iaxis ���
				iValue ������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetAtype(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ������
Input:          //������handle 
				iaxis ���
Output:         //iValue �����ͷ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAtype(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��ȡ��״̬
Input:          //������handle  
				iaxis ���
Output:         //��״̬����ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAxisStatus(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //�������ַ
Input:          //������handle  
				iaxis ���
				iValue ���ַ�趨ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetAxisAddress(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ���ַ
Input:          //������handle  
				iaxis ��� 
Output:         //piValue ���ַ����ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAxisAddress(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //������ʹ�� ��ֻ������߿�������ʹ����Ч��
Input:          //������handle  
				iaxis ���
				iValue ״̬ 0-�ر� 1- ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetAxisEnable(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ��ʹ��״̬
Input:          //������handle 
				iaxis ���
Output:         //piValue ���ص�ʹ��״̬
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAxisEnable(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //������������
Input:          //������handle 
				iaxis ���
				fValue ͬ����������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetClutchRate(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ��������
Input:          //������handle  
				iaxis ���
Output:         //pfValue �������ʷ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetClutchRate(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //�������津���Ľ������귶Χ��
Input:          //������handle  
				iaxis ���
				fValue �趨�ķ�Χֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetCloseWin(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���津���Ľ������귶Χ��
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���صķ�Χֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetCloseWin(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���ùսǼ���
Input:          //������handle 
				iaxis ���
				iValue �սǼ���ģʽ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetCornerMode(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ�սǼ���
Input:          //������handle  
				iaxis ���
Output:         //piValue ���صĹս�ģʽ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetCornerMode(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���û��������ٶ�
Input:          //������handle  
				iaxis ���
				fValue���õ��ٶ�ֵ
Output:         //	
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetCreep(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���������ٶ�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص������ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetCreep(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //����ԭ���ź�   �趨-1Ϊȡ��ԭ������
Input:          //������handle 
				iaxis ���
				iValue ���õ�ԭ���ź�����ڱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetDatumIn(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡԭ���ź�
Input:          //������handle  
				iaxis 
Output:         //piValue ����ԭ������ڱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetDatumIn(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���ü��ٶ�
Input:          //������handle
				iaxis ���
				fValue ���õļ��ٶ�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetDecel(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���ٶ�
Input:          //������handle 
				iaxis ���
Output:         //pfValue �趨�ļ��ٶȷ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetDecel(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���ùսǼ��ٽǶȣ���ʼ���ٽǶȣ���λΪ����
Input:          //������handle  
				iaxis ���
				fValue ���õĹսǼ��ٽǶ�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetDecelAngle(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ�սǿ�ʼ���ٽǶȣ���λΪ����
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���صĹսǼ��ٽǶ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetDecelAngle(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //������λ��
Input:          //������handle
				iaxis ���
				fValue ���õ�����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetDpos(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ��λ��
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص�����λ������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetDpos(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ�ڲ�������ֵ  �����߾���ֵ�ŷ�ʱΪ����ֵλ�ã�
Input:          //������handle  
				iaxis ���		
Output:         //pfValue ���ص��ڲ�������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetEncoder(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ��ǰ�˶�������λ��
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص�����λ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetEndMove(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ��ǰ�ͻ������˶�������λ�ã�����������Ծ���ת��
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص�����λ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetEndMoveBuffer(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //����SP�˶��Ľ����ٶ�
Input:          //������handle  
				iaxis ���
Output:         //fValue �趨���ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetEndMoveSpeed(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡSP�˶��Ľ����ٶ�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص��ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetEndMoveSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���ô����ǣ���AXISSTATUS����������������Щ������Ҫ�ر�WDOG��
Input:          //������handle 
				iaxis ���
				iValue ����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetErrormask(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ�����ǣ���AXISSTATUS����������������Щ������Ҫ�ر�WDOG��
Input:          //������handle 
				iaxis ���
Output:         //piValue ���صı��ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetErrormask(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���ÿ���JOG����
Input:          //������handle  
				iaxis ���
				iValue ����JOG����ڱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFastJog(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ����JOG����
Input:          //������handle  
				iaxis ���
Output:         //���ص�JOG����ڱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFastJog(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���ÿ��ټ��ٶ�
Input:          //������handle  
				iaxis ���
				fValue �趨�Ŀ��ټ��ٶ�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFastDec(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���ټ��ٶ�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���صĿ��ټ��ٶ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFastDec(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ�涯���
Input:          //������handle 
				iaxis ���
Output:         //pfValue ���ص��涯���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFe(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //�������������涯���ֵ
Input:          //������handle  
				iaxis ���
				fValue ���õ�������ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFeLimit(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���������涯���ֵ
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص�����������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFeLimit(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���ñ���ʱ�涯���ֵ
Input:          //������handle  
				iaxis ���
				fValue ���õ����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFRange(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ����ʱ���涯���ֵ
Input:          //������handle
				iaxis ���
Output:         //pfValue ���صı������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFeRange(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���ñ�������
Input:          //������handle  
				iaxis ���
				iValue ���õ�����ڱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFholdIn(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ��������
Input:          //������handle 
				iaxis ���
Output:         //piValue ��������HOLDIN����ڱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFholdIn(ZMC_HANDLE handle, int iaxis, int *piValue);


/*************************************************************
Description:    //�����ᱣ���ٶ�
Input:          //������handle  
				iaxis ���
				fValue ���õ��ٶ�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFhspeed(ZMC_HANDLE handle, int iaxis, float pfValue);

/*************************************************************
Description:    //��ȡ�ᱣ���ٶ�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���صı����ٶ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFhspeed(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //����SP�˶��������ٶ�
Input:          //������handle  
				iaxis ���
				fValue ���õ��ٶ�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetForceSpeed(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡSP�˶��������ٶ�
Input:          //������handle
				iaxis ���
Output:         //pfValue ����SP�˶��ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetForceSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //������������λ		ȡ��ʱ����һ���ϴ�ֵ����
Input:          //������handle  
				iaxis ���
				fValue �趨����λֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFsLimit(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ��������λ
Input:          //������handle
				iaxis ���
Output:         //pfValue ���ص�������λ����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFsLimit(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //����СԲ������С�뾶
Input:          //������handle  
				iaxis ���
				fValue ���õ���С�뾶
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFullSpRadius(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡСԲ������С�뾶
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص����ٰ뾶
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFullSpRadius(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��������Ӳ��λ����  ���ó�-1ʱ��ʾ��������λ
Input:          //������handle  
				iaxis ���
				iValue ���õ���λ����ڱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFwdIn(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ����Ӳ��λ����
Input:          //������handle  
				iaxis ���
Output:         //piValue ����������λ����ڱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFwdIn(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��������JOG����
Input:          //������handle  
				iaxis ���
				iValue ���õ�JOG����ڱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetFwdJog(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ����JOG����
Input:          //������handle  
				iaxis ���
Output:         //piValue ���ص�JOG����ڱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetFwdJog(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��ȡ���Ƿ��˶�����
Input:          //������handle  
				iaxis ���
Output:         //piValue ��������״̬ 0-�˶��� -1 ֹͣ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetIfIdle(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //�����������ģʽ
Input:          //������handle  
				iaxis ���
				iValue �趨���������ģʽ ����+����/˫����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetInvertStep(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ�������ģʽ
Input:          //������handle  
				iaxis ���
Output:         //piValue ���ص�����ģʽ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetInvertStep(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���ò岹ʱ���Ƿ�����ٶȼ��㣬ȱʡ���루1�����˲���ֻ��ֱ�ߺ������ĵ�������������
Input:          //������handle  
				iaxis	���
				iValue ģʽ 0-������ 1-����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetInterpFactor(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ�岹ʱ���Ƿ�����ٶȼ��㣬ȱʡ���루1�����˲���ֻ��ֱ�ߺ������ĵ�������������
Input:          //������handle  
				iaxis ���
Output:         //piValue ���ص��ٶȼ���ģʽ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetInterpFactor(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //����JOGʱ�ٶ�
Input:          //������handle  
				iaxis ���
Output:         //fValue �趨���ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetJogSpeed(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡJOGʱ�ٶ�
Input:          //������handle  
				iaxis	���
Output:         //pfValue ���ص�JOG�ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetJogSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ��ǰ�����˶��Ĳο����
Input:          //������handle  
				iaxis ���
Output:         //piValue �������ӵĲο����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetLinkax(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��ȡ��ǰ���˵�ǰ�˶��Ƿ��л��� 
Input:          //������handle
				iaxis ���
Output:         //piValue ����״ֵ̬  -1 û��ʣ�ຯ�� 0-����ʣ���˶�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetLoaded(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��������ʼ�ٶ�
Input:          //������handle  
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetLspeed(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ����ʼ�ٶ�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص���ʼ�ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetLspeed(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���û��㷴�ҵȴ�ʱ��
Input:          //������handle 
				iaxis ���
				iValue ���㷴�ҵȴ�ʱ�� MS
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetHomeWait(ZMC_HANDLE handle, int iaxis, int fValue);

/*************************************************************
Description:    //��ȡ���㷴�ҵȴ�ʱ��
Input:          //������handle  
				iaxis ���
Output:         //piValue ���صķ��ҵȴ�ʱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetHomeWait(ZMC_HANDLE handle, int iaxis, int *pfValue);


/*************************************************************
Description:    //��ȡ����������ʾ�̷���״̬
Input:          //������handle  
				iaxis ���
Output:         //piValue  ���ص����津��״̬ -1-���津�� 0-δ����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMark(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��ȡ����������b����״̬
Input:          //������handle  
iaxis ���
Output:         //piValue  ���ص����津��״̬ -1-���津�� 0-δ����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMarkB(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��������������Ƶ��
Input:          //������handle  
				iaxis ���
				iValue ���õ��������Ƶ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetMaxSpeed(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ����������Ƶ��
Input:          //������handle  
				iaxis ���
Output:         //piValue ���ص�����Ƶ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMaxSpeed(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���������岹
Input:          //������handle  
				iaxis ���
				iValue	�����岹���� 0-�ر������岹 1-�������岹
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetMerge(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ�����岹״̬
Input:          //������handle  
				iaxis ���
Output:         //piValue ���ص������岹����״̬
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMerge(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��ȡ��ǰ�������������˶�����
Input:          //������handle  
				iaxis ����
Output:         //piValue �����˶���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMovesBuffered(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��ȡ��ǰ�����˶�ָ���MOVE_MARK���
Input:          //������handle  
				iaxis ���
Output:         //piValue ��ǰMARK���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMoveCurmark(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //�����˶�ָ���MOVE_MARK��� ÿ�����˶��������˶�����ʱMARK�Զ�+1
Input:          //������handle  
				iaxis ���
				iValue �趨��MARKֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetMovemark(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //���÷���λ��
Input:          //������handle  
				iaxis ���
				fValue ���õķ���λ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetMpos(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ����λ��
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص��ᷴ��λ������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMpos(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ�����ٶ�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���صı����������ٶ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMspeed(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ��ǰ�����˶�ָ������
Input:          //������handle  
				iaxis ���
Output:         //piValue ���ص�ǰ���˶�����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetMtype(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //��ȡ��ǰ���ڽ��е��˶�ָ�����ĵ�һ��ָ�����ͣ����岹����ʱ���Դ������Ƿ���������˶�ָ������
Input:          //������handle  
				iaxis  ���
Output:         //piValue ������һ��ָ����˶�����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetNtype(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //�����޸�ƫ��λ��
Input:          //������handle 
				iaxis ���
				fValue ���õ�ƫ��ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetOffpos(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ�޸�ƫ��λ��
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص�ƫ������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetOffpos(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //�������津���Ľ������귶Χ�㡣
Input:          //������handle  
				iaxis ���
				fValue ���õ�����ֵ
Output:         // 
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetOpenWin(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���津���Ľ������귶Χ�㡣
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���صĽ�������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetOpenWin(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ��������Ĳ�������λ��(MPOS)
Input:          //������handle 
				iaxis ���
Output:         //pfValue ���������λ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRegPos(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ��������Ĳ�������λ��(MPOS)
Input:          //������handle 
iaxis ���
Output:         //pfValue ���������λ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRegPosB(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ�����ᵱǰ�˶���δ��ɵľ���
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص�ʣ�����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRemain(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //����  ��ʣ��Ļ���, ��ֱ�߶�������
REMAIN_BUFFERΪΨһһ�����Լ�AXIS����ZAux_DirectCommand��ȡ��.
Input:          //������handle  
				iaxis ���
Output:         //piValue ʣ���ֱ�߻�������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRemain_LineBuffer(ZMC_HANDLE handle, int iaxis,int * piValue);

/*************************************************************
Description:    //����  ��ʣ��Ļ���, ����ӵĿռ�Բ��������
REMAIN_BUFFERΪΨһһ�����Լ�AXIS����ZAux_DirectCommand��ȡ��.
Input:          //������handle  
				iaxis ���
Output:         //piValue ʣ��Ļ�������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRemain_Buffer(ZMC_HANDLE handle, int iaxis, int *piValue);


/*************************************************************
Description:    //���ø���REP_OPTION�������Զ�ѭ����DPOS��MPOS���ꡣ
Input:          //������handle  
				iaxis ���
				fValue	���õ�����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetRepDist(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ����REP_OPTION�������Զ�ѭ����DPOS��MPOS���ꡣ
Input:          //������handle 
				iaxis	���
Output:         //pfValue ���ص�ѭ������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRepDist(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���������ظ�����
Input:          //������handle  
				iaxis ���
				iValue ģʽ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetRepOption(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ�����ظ�����
Input:          //������handle
				iaxis ���
Output:         //piValue ���ص�ģʽ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRepOption(ZMC_HANDLE handle, int iaxis, int *piValue);


/*************************************************************
Description:    //���ø���Ӳ����λ���ض�Ӧ��������ţ�-1��Ч��
Input:          //������handle  
				iaxis  ���
				iValue ���õ�����ڱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetRevIn(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ����Ӳ����λ���ض�Ӧ��������ţ�-1��Ч��
Input:          //������handle  
				iaxis ���
Output:         //piValue ���صĸ�����λ����ڱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRevIn(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���ø���JOG�����Ӧ��������ţ�-1��Ч��
Input:          //������handle  
				iaxis ���
				iValue ���õ�����ڱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetRevJog(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //��ȡ����JOG�����Ӧ��������ţ�-1��Ч��
Input:          //������handle  
				iaxis ���
Output:         //piValue ���ص�����ڱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRevJog(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���ø�������λλ�á�  ����һ���ϴ��ֵʱ��Ϊȡ����λ
Input:          //������handle  
				iaxis	���
				fValue  ������λֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetRsLimit(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ��������λλ�á�
Input:          //������handle  
				iaxis	���
Output:         //pfValue �趨����λֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetRsLimit(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //�������ٶȣ���λΪunits/s���������˶�ʱ����Ϊ�岹�˶����ٶ�
Input:          //������handle  
				iaxis ���
				fValue ���õ��ٶ�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetSpeed(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���ٶȣ���λΪunits/s���������˶�ʱ����Ϊ�岹�˶����ٶ�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���ص��ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���� S�������á� 0-���μӼ���
Input:          //������handle  
				iaxis ���
				fValue S����ƽ��ʱ��MS
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetSramp(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ S�������á�
Input:          //������handle  
				iaxis ���
Output:         //pfValue ƽ��ʱ��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetSramp(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���� �Զ����ٶȵ�SP�˶�����ʼ�ٶ�
Input:          //������handle 
				iaxis ���
				fValue ���õ��ٶ�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetStartMoveSpeed(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ�Զ����ٶȵ�SP�˶�����ʼ�ٶ�
Input:          //������handle  
				iaxis	���
Output:         //pfValue ���ص�SP�˶���ʼ�ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetStartMoveSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���� ���ٵ���͵���С�ս� ������
Input:          //������handle  
				iaxis ���
				fValue ���õĽǶ�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetStopAngle(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���ٵ���͵���С�ս� ������
Input:          //������handle  
				iaxis ���
Output:         //pfValue ���صĹս�ֹͣ�Ƕ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetStopAngle(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���� ���ٵ��ǰ뾶
Input:          //������handle  
				iaxis	���
				fValue	���ǰ뾶
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetZsmooth(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���ǰ뾶
Input:          //������handle  
				iaxis	���
Output:         //pfValue	���صĵ��ǰ뾶ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetZsmooth(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //���� ���嵱��
Input:          //������handle  
				iaxis ���
				fValue ���õĵ���ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetUnits(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ���嵱��
Input:          //������handle
				iaxis	���
Output:         //pfValue ���ص����嵱��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetUnits(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ�����ᵱǰ��ǰ�˶��ͻ����˶���δ��ɵľ���
Input:          //������handle
				iaxis ���
Output:         //pfValue ���ص��������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetVectorBuffered(ZMC_HANDLE handle, int iaxis, float *pfValue);

/*************************************************************
Description:    //��ȡ��ǰ�����е������ٶ�
Input:          //������handle  
				iaxis	���
Output:         //pfValue	���صĵ�ǰ�ٶ�ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetVpSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue);




/*************************************************************
Description:    //ȫ�ֱ�����ȡ, Ҳ�����ǲ����ȵ�
Input:          //������handle  
				pname ȫ�ֱ�������/����ָ����ŵ����������DPOS(0)
Output:         //pfValue ����ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetVariablef(ZMC_HANDLE handle, const char *pname, float *pfValue);


/*************************************************************
Description:    //ȫ�ֱ�����ȡ, Ҳ�����ǲ����ȵ�
Input:          //������handle  
				pname ȫ�ֱ�������/����ָ����ŵ����������DPOS(0)
Output:         //piValue ����ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetVariableInt(ZMC_HANDLE handle, const char *pname, int *piValue);

///////////////////////  ֻ��������˶�����֧��ֱ�ӵ��ã����������е�ָ�֧��
///////////////////////  ���� 20130901 �Ժ�Ŀ������汾֧��

/*************************************************************
Description:    //BASEָ�����
�����޸����������BASE�б����Կ����������������BASE�����޸�.
�޸ĺ󣬺���������MOVE��ָ��������BASEΪ����  
Input:          //������handle
				imaxaxises ��������
				piAxislist	���б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Base(ZMC_HANDLE handle, int imaxaxises, int *piAxislist);

/*************************************************************
Description:    //����DPOS,������ʹ�ã�����ֱ�ӵ���SETDPOS�ﵽͬ��Ч��
Input:          //������handle
				iaxis	���
				pfDpos ���õ�����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Defpos(ZMC_HANDLE handle, int iaxis, float pfDpos);

/*************************************************************
Description:    //�������ֱ�߲岹  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Move(ZMC_HANDLE handle, int imaxaxises, int *piAxislist,float *pfDisancelist);


/*************************************************************
Description:    //��Զ���ֱ�߲岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float *pfDisancelist);



/*************************************************************
Description:    //���Զ���ֱ�߲岹  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveAbs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float *pfDisancelist);


/*************************************************************
Description:    //���Զ���ֱ�߲岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveAbsSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float *pfDisancelist);



/*************************************************************
//Description:    //�˶����޸Ľ���λ��  20130901 �Ժ�Ŀ������汾֧��
//Input:          //������handle
					��� iaxis
					���Ծ��� pfDisance
//Output:         //
//Return:         //������
/*************************************************************/
int32 __stdcall ZAux_Direct_MoveModify(ZMC_HANDLE handle, int iaxis, float pfDisance);


/*************************************************************
Description:    //���Բ�Ķ�Բ���岹�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��һ�����˶�����
				end2              �ڶ������˶�����
				centre1    ��һ�����˶�Բ�ģ��������ʼ�㡣
				centre2    �ڶ������˶�Բ�ģ��������ʼ�㡣
				direction  0-��ʱ�룬1-˳ʱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection);


/*************************************************************
Description:    //���Բ�Ķ�Բ���岹�˶� �岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��һ�����˶�����
				end2              �ڶ������˶�����
				centre1    ��һ�����˶�Բ�ģ��������ʼ�㡣
				centre2    �ڶ������˶�Բ�ģ��������ʼ�㡣
				direction  0-��ʱ�룬1-˳ʱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCircSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection);



/*************************************************************
Description:    //����Բ��Բ���岹�˶�  20130901 �Ժ�Ŀ������汾֧��  �޷�����Բ
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��һ�����˶����꣬����λ��
				end2              �ڶ������˶����꣬����λ��
				centre1    ��һ�����˶�Բ�ģ�����λ��
				centre2    �ڶ������˶�Բ�ģ�����λ��
				direction  0-��ʱ�룬1-˳ʱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCircAbs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection);


/*************************************************************
Description:    //����Բ��Բ���岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��  �޷�����Բ
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��һ�����˶����꣬����λ��
				end2              �ڶ������˶����꣬����λ��
				centre1    ��һ�����˶�Բ�ģ�����λ��
				centre2    �ڶ������˶�Բ�ģ�����λ��
				direction  0-��ʱ�룬1-˳ʱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCircAbsSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection);




/*************************************************************
Description:    //���3�㶨Բ���岹�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				mid1       ��һ�����м�㣬�����ʼ�����
				mid2       �ڶ������м�㣬�����ʼ�����
				end1              ��һ��������㣬�����ʼ�����
				end2              �ڶ���������㣬�����ʼ�����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc2(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fmid1, float fmid2, float fend1, float fend2);



/*************************************************************
Description:    //����3�㶨Բ���岹�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				mid1       ��һ�����м�㣬����λ��
				mid2       �ڶ������м�㣬����λ��
				end1              ��һ��������㣬����λ��
				end2              �ڶ���������㣬����λ�� 
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc2Abs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fmid1, float fmid2, float fend1, float fend2);


/*************************************************************
Description:    //���3�㶨Բ���岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				mid1       ��һ�����м�㣬�����ʼ�����
				mid2       �ڶ������м�㣬�����ʼ�����
				end1              ��һ��������㣬�����ʼ�����
				end2              �ڶ���������㣬�����ʼ�����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc2Sp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fmid1, float fmid2, float fend1, float fend2);



/*************************************************************
Description:    //����3�㶨Բ���岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				mid1       ��һ�����м�㣬����λ��
				mid2       �ڶ������м�㣬����λ��
				end1              ��һ��������㣬����λ��
				end2              �ڶ���������㣬����λ�� 
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCirc2AbsSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fmid1, float fmid2, float fend1, float fend2);


/*************************************************************
Description:    //���3��Բ�������岹�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��һ�����˶�����
				end2              �ڶ������˶�����
				centre1    ��һ�����˶�Բ�ģ��������ʼ��
				centre2    �ڶ������˶�Բ�ģ��������ʼ��		
				direction  0-��ʱ�룬1-˳ʱ��
				distance3���������˶����롣
				mode      ��������ٶȼ���:0(ȱʡ)����������ٶȼ��㡣1�����᲻�����ٶȼ��㡣
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MHelical(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fDistance3, int imode);


/*************************************************************
Description:    //����3��Բ�������岹�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��һ�����˶�����
				end2              �ڶ������˶�����
				centre1    ��һ�����˶�Բ������
				centre2    �ڶ������˶�Բ������
				direction  0-��ʱ�룬1-˳ʱ��
				distance3���������˶����롣
				mode      ��������ٶȼ���:0(ȱʡ) ����������ٶȼ��㡣1�����᲻�����ٶȼ��㡣
Output:         //
 Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MHelicalAbs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fDistance3, int imode);


/*************************************************************
Description:    //���3��Բ�������岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��һ�����˶�����
				end2              �ڶ������˶�����
				centre1    ��һ�����˶�Բ�ģ��������ʼ��	  
				centre2    �ڶ������˶�Բ�ģ��������ʼ��		
				direction  0-��ʱ�룬1-˳ʱ��  
				distance3���������˶����롣
			  mode      ��������ٶȼ���: 0(ȱʡ)����������ٶȼ��㡣 1�����᲻�����ٶȼ��㡣
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MHelicalSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fDistance3, int imode);


/*************************************************************
Description:    //����3��Բ�������岹�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��һ�����˶�����
				end2              �ڶ������˶�����
				centre1    ��һ�����˶�Բ������
				centre2    �ڶ������˶�Բ������
				direction  0-��ʱ�룬1-˳ʱ��
				distance3���������˶����롣
				mode      ��������ٶȼ���:0(ȱʡ) ����������ٶȼ��㡣1�����᲻�����ٶȼ��㡣
Output:         //
 Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MHelicalAbsSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fDistance3, int imode);



/*************************************************************
Description:    //���3�� 3�㻭�����岹�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				mid1       ��һ�����м��  
				mid2       �ڶ������м��	
				end1              ��һ���������	  
				end2              �ڶ����������		
				distance3���������˶�����		  
				mode      ��������ٶȼ���:			
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MHelical2(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fmid1, float fmid2, float fend1, float fend2, float fDistance3, int imode);


/*************************************************************
Description:    //����3�� 3�㻭�����岹�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
			imaxaxises			�����˶�������
			piAxislist			����б�
			mid1       ��һ�����м��
			mid2       �ڶ������м��
			end1              ��һ���������
			end2              �ڶ����������
			distance3   ���������˶�������
			mode      ��������ٶȼ���:
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MHelical2Abs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fmid1, float fmid2, float fend1, float fend2, float fDistance3, int imode);


/*************************************************************
Description:    //���3�� 3�㻭�����岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				mid1       ��һ�����м��  
				mid2       �ڶ������м��	
				end1              ��һ���������	  
				end2              �ڶ����������		
				distance3���������˶�����		  
				mode      ��������ٶȼ���:			
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MHelical2Sp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fmid1, float fmid2, float fend1, float fend2, float fDistance3, int imode);


/*************************************************************
Description:    //����3�� 3�㻭�����岹SP�˶�  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
			imaxaxises			�����˶�������
			piAxislist			����б�
			mid1       ��һ�����м��
			mid2       �ڶ������м��
			end1              ��һ���������
			end2              �ڶ����������
			distance3   ���������˶�������
			mode      ��������ٶȼ���:
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MHelical2AbsSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fmid1, float fmid2, float fend1, float fend2, float fDistance3, int imode);




/*************************************************************
Description:    //�����Բ�岹 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
			imaxaxises			�����˶�������
			piAxislist			����б�
			fend1              �յ��һ�����˶����꣬�������ʼ�㡣
			fend2              �յ�ڶ������˶����꣬�������ʼ�㡣
			fcenter1    ���ĵ�һ�����˶����꣬�������ʼ�㡣
			fcenter2    ���ĵڶ������˶����꣬�������ʼ�㡣
			idirection  0-��ʱ�룬1-˳ʱ��
			fADis         ��һ�����Բ�뾶���볤����߰���ᶼ�ɡ�
			fBDis        �ڶ������Բ�뾶���볤����߰���ᶼ�ɣ�AB���ʱ�Զ�ΪԲ����������
			fend        ����������˶����룬��Ҫ����ʱ����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MEclipse(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis,float fend);


/*************************************************************
Description:    //������Բ�岹 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				fend1              �յ��һ�����˶�����
				fend2              �յ�ڶ������˶�����
				fcenter1    ���ĵ�һ�����˶����ꡣ
				fcenter2    ���ĵڶ������˶����ꡣ
				idirection  0-��ʱ�룬1-˳ʱ��
				fADis         ��һ�����Բ�뾶���볤����߰���ᶼ�ɡ�
				fBDis        �ڶ������Բ�뾶���볤����߰���ᶼ�ɣ�AB���ʱ�Զ�ΪԲ����������
				fend         ����������˶����꣬��Ҫ����ʱ����
  Output:         //
  Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MEclipseAbs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis,float fend);


/*************************************************************
Description:    //�����Բ�岹SP�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
			imaxaxises			�����˶�������
			piAxislist			����б�
			fend1              �յ��һ�����˶����꣬�������ʼ�㡣
			fend2              �յ�ڶ������˶����꣬�������ʼ�㡣
			fcenter1    ���ĵ�һ�����˶����꣬�������ʼ�㡣
			fcenter2    ���ĵڶ������˶����꣬�������ʼ�㡣
			idirection  0-��ʱ�룬1-˳ʱ��
			fADis         ��һ�����Բ�뾶���볤����߰���ᶼ�ɡ�
			fBDis        �ڶ������Բ�뾶���볤����߰���ᶼ�ɣ�AB���ʱ�Զ�ΪԲ����������
			fend         ����������˶����꣬��Ҫ����ʱ����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MEclipseSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis,float fend);


/*************************************************************
Description:    //������Բ�岹SP�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				fend1              �յ��һ�����˶�����
				fend2              �յ�ڶ������˶�����
				fcenter1    ���ĵ�һ�����˶����ꡣ
				fcenter2    ���ĵڶ������˶����ꡣ
				idirection  0-��ʱ�룬1-˳ʱ��
				fADis         ��һ�����Բ�뾶���볤����߰���ᶼ�ɡ�
				fBDis        �ڶ������Բ�뾶���볤����߰���ᶼ�ɣ�AB���ʱ�Զ�ΪԲ����������
				fend         ����������˶����꣬��Ҫ����ʱ����
  Output:         //
  Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MEclipseAbsSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis,float fend);



/*************************************************************
Description:    //��� ��Բ + �����岹�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				fend1              �յ��һ�����˶����꣬�������ʼ�㡣
				fend2              �յ�ڶ������˶����꣬�������ʼ�㡣
				fcenter1    ���ĵ�һ�����˶����꣬�������ʼ�㡣
				fcenter2    ���ĵڶ������˶����꣬�������ʼ�㡣
				idirection  0-��ʱ�룬1-˳ʱ��
				fADis         ��һ�����Բ�뾶���볤����߰���ᶼ�ɡ�
				fBDis        �ڶ������Բ�뾶���볤����߰���ᶼ�ɣ�AB���ʱ�Զ�ΪԲ����������
				fDistance3	����������˶�����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MEclipseHelical(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis, float fDistance3);


/*************************************************************
Description:    //������Բ + �����岹�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				fend1              �յ��һ�����˶�����
				fend2              �յ�ڶ������˶�����
				fcenter1    ���ĵ�һ�����˶����ꡣ
				fcenter2    ���ĵڶ������˶����ꡣ
				idirection  0-��ʱ�룬1-˳ʱ��
				fADis         ��һ�����Բ�뾶���볤����߰���ᶼ�ɡ�
				fBDis        �ڶ������Բ�뾶���볤����߰���ᶼ�ɣ�AB���ʱ�Զ�ΪԲ����������
				fDistance3	����������˶�����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MEclipseHelicalAbs(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis,float fDistance3);


/*************************************************************
Description:    //��� ��Բ + �����岹SP�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				fend1              �յ��һ�����˶����꣬�������ʼ�㡣
				fend2              �յ�ڶ������˶����꣬�������ʼ�㡣
				fcenter1    ���ĵ�һ�����˶����꣬�������ʼ�㡣
				fcenter2    ���ĵڶ������˶����꣬�������ʼ�㡣
				idirection  0-��ʱ�룬1-˳ʱ��
				fADis         ��һ�����Բ�뾶���볤����߰���ᶼ�ɡ�
				fBDis        �ڶ������Բ�뾶���볤����߰���ᶼ�ɣ�AB���ʱ�Զ�ΪԲ����������
				fDistance3	����������˶�����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MEclipseHelicalSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis, float fDistance3);


/*************************************************************
Description:    //������Բ + �����岹SP�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				fend1              �յ��һ�����˶�����
				fend2              �յ�ڶ������˶�����
				fcenter1    ���ĵ�һ�����˶����ꡣ
				fcenter2    ���ĵڶ������˶����ꡣ
				idirection  0-��ʱ�룬1-˳ʱ��
				fADis         ��һ�����Բ�뾶���볤����߰���ᶼ�ɡ�
				fBDis        �ڶ������Բ�뾶���볤����߰���ᶼ�ɣ�AB���ʱ�Զ�ΪԲ����������
				fDistance3	����������˶�����
  Output:         //
  Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MEclipseHelicalAbsSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fcenter1, float fcenter2, int idirection, float fADis, float fBDis,float fDistance3);


/*************************************************************
Description:    //�ռ�Բ�� + �����岹�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��1�����˶��������1	��������
				end2              ��2�����˶��������1	��������  
				end3              ��3�����˶��������1	��������
				centre1    ��1�����˶��������2	��������
				centre2    ��2�����˶��������2	��������
				centre3    ��3�����˶��������2 ��������
				mode      ָ��ǰ�����������
					0 ��ǰ�㣬�м�㣬�յ����㶨Բ�����������1Ϊ�յ���룬�������2Ϊ�м����롣
					1 ����С��Բ�����������1Ϊ�յ���룬�������2ΪԲ�ĵľ��롣
					2 ��ǰ�㣬�м�㣬�յ����㶨Բ���������1Ϊ�յ���룬�������2Ϊ�м����롣
					3 ������С��Բ�����ټ���������Բ���������1Ϊ�յ���룬�������2ΪԲ�ĵľ��롣
				fcenter4	��4�����˶�������� 
				fcenter5	��5�����˶��������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MSpherical(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fend3, float fcenter1, float fcenter2, float fcenter3, int imode, float fcenter4, float fcenter5);


/*************************************************************
Description:    //�ռ�Բ�� + ���� �岹SP�˶� 20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��1�����˶��������1	��������
				end2              ��2�����˶��������1	��������  
				end3              ��3�����˶��������1	��������
				centre1    ��1�����˶��������2	��������
				centre2    ��2�����˶��������2	��������
				centre3    ��3�����˶��������2 ��������
				mode      ָ��ǰ�����������
					0 ��ǰ�㣬�м�㣬�յ����㶨Բ�����������1Ϊ�յ���룬�������2Ϊ�м����롣
					1 ����С��Բ�����������1Ϊ�յ���룬�������2ΪԲ�ĵľ��롣
					2 ��ǰ�㣬�м�㣬�յ����㶨Բ���������1Ϊ�յ���룬�������2Ϊ�м����롣
					3 ������С��Բ�����ټ���������Բ���������1Ϊ�յ���룬�������2ΪԲ�ĵľ��롣
				fcenter4	��4�����˶�������� 
				fcenter5	��5�����˶��������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MSphericalSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float fend1, float fend2, float fend3, float fcenter1, float fcenter2, float fcenter3, int imode, float fcenter4, float fcenter5);



/*************************************************************
Description:    //������Բ���岹�˶�������ƶ���ʽ������ʼ�뾶0ֱ����ɢʱ��0�Ƕȿ�ʼ
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				centre1: ��1��Բ�ĵ���Ծ���
				centre2: ��2��Բ�ĵ���Ծ���
				circles:  Ҫ��ת��Ȧ��������ΪС��Ȧ��������ʾ˳ʱ��.
				pitch:   ÿȦ����ɢ���룬����Ϊ����
				distance3        ��3�������Ĺ��ܣ�ָ����3�����Ծ��룬���᲻�����ٶȼ��㡣
				distance4        ��4�������Ĺ��ܣ�ָ����4�����Ծ��룬���᲻�����ٶȼ��㡣
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveSpiral(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float centre1, float centre2, float circles, float pitch, float distance3, float distance4);

/*************************************************************
Description:    //������Բ���岹SP�˶�������ƶ���ʽ������ʼ�뾶0ֱ����ɢʱ��0�Ƕȿ�ʼ
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				centre1: ��1��Բ�ĵ���Ծ���
				centre2: ��2��Բ�ĵ���Ծ���
				circles:  Ҫ��ת��Ȧ��������ΪС��Ȧ��������ʾ˳ʱ��.
				pitch:   ÿȦ����ɢ���룬����Ϊ����
				distance3        ��3�������Ĺ��ܣ�ָ����3�����Ծ��룬���᲻�����ٶȼ��㡣
				distance4        ��4�������Ĺ��ܣ�ָ����4�����Ծ��룬���᲻�����ٶȼ��㡣
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveSpiralSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float centre1, float centre2, float circles, float pitch, float distance3, float distance4);

/*************************************************************
Description:    //�ռ�ֱ���˶���������һ��ֱ���˶��ľ��������ڹս��Զ�����Բ��������Բ�����ʹ���˶����յ���ֱ�ߵ��յ㲻һ�£��սǹ���ʱ�������Բ���������벻��ʱ���Զ���С�뾶
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��1�����˶���������
				end2              ��2�����˶���������
				end3              ��3�����˶���������
				next1      ��1������һ��ֱ���˶���������
				next2      ��2������һ��ֱ���˶���������
				next3      ��3������һ��ֱ���˶���������
				radius      ����Բ���İ뾶���������ʱ���Զ���С��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveSmooth(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float end1, float end2, float end3, float next1, float next2, float next3, float radius);

/*************************************************************
Description:    //�ռ�ֱ�߲岹SP�˶���������һ��ֱ���˶��ľ��������ڹս��Զ�����Բ��������Բ�����ʹ���˶����յ���ֱ�ߵ��յ㲻һ�£��սǹ���ʱ�������Բ���������벻��ʱ���Զ���С�뾶
Input:          //������handle
				imaxaxises			�����˶�������
				piAxislist			����б�
				end1              ��1�����˶���������
				end2              ��2�����˶���������
				end3              ��3�����˶���������
				next1      ��1������һ��ֱ���˶���������
				next2      ��2������һ��ֱ���˶���������
				next3      ��3������һ��ֱ���˶���������
				radius      ����Բ���İ뾶���������ʱ���Զ���С��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveSmoothSp(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, float end1, float end2, float end3, float next1, float next2, float next3, float radius);


/*************************************************************
Description:    //�˶���ͣ		���岹�˶���ͣ���ᡣ���б����һ����
Input:          //������handle  
				��� iaxis
				ģʽ imode	0��ȱʡ�� ��ͣ��ǰ�˶��� 
							1 �ڵ�ǰ�˶���ɺ���׼��ִ����һ���˶�ָ��ʱ��ͣ�� 
							2 �ڵ�ǰ�˶���ɺ���׼��ִ����һ���˶�ָ��ʱ����������ָ���MARK��ʶ��һ��ʱ��ͣ�����ģʽ��������һ�������ɶ��ָ����ʵ��ʱ��������һ����������ɺ���ͣ�� 
  
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MovePause(ZMC_HANDLE handle,int iaxis, int imode);


/*************************************************************
Description:    //ȡ���˶���ͣ
Input:          //������handle  
					��� iaxis
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveResume(ZMC_HANDLE handle,int iaxis);

/*************************************************************
Description:    //�ڵ�ǰ���˶�ĩβλ�������ٶ����ƣ�����ǿ�ƹսǼ���
Input:          //������handle  
				 ��� iaxis
Output:         //
 Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveLimit(ZMC_HANDLE handle, int iaxis,float limitspeed);

/*************************************************************
Description:    //���˶������м������ָ��
Input:          //������handle  
				��� iaxis
				����ڱ�� ioutnum
				�����״̬	ivalue
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveOp(ZMC_HANDLE handle, int iaxis,int ioutnum, int ivalue);

/*************************************************************
Description:    //���˶������м���������������ָ��
Input:          //������handle  
				��� iaxis
				�������ʼ��� ioutnumfirst
				����ڽ������ ioutnumend
				��Ӧ�����״̬���������ֵ	ivalue
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveOpMulti(ZMC_HANDLE handle, int iaxis, int ioutnumfirst, int ioutnumend, int ivalue);

/*************************************************************
Description:    //���˶������м������ָ�� ,ָ��ʱ������״̬��ת
Input:          //������handle  
				��� iaxis
				����ڱ�� ioutnum
				�����״̬	ivalue
				״̬��תʱ�� iofftimems
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveOp2(ZMC_HANDLE handle, int iaxis, int ioutnum, int ivalue, int iofftimems);

/*************************************************************
Description:    //���˶������м���AOUT���ָ��
Input:          //������handle  
				��� iaxis
				DA�ڱ�� ioutnum
				ģ����ֵ fvalue ��4ϵ������ 12λ0-4095��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveAout(ZMC_HANDLE handle, int iaxis, int ioutnum, float fvalue);

/*************************************************************
Description:    //���˶������м�����ʱָ��
Input:          //������handle  
				��� iaxis
				��ʱʱ�� itimems ����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveDelay(ZMC_HANDLE handle, int iaxis, int itimems);

/*************************************************************
Description:    //��תֱ̨�߲岹�˶���  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				tablenum			�洢��ת̨������table��� 
				imaxaxises			�����˶�������
				piAxislist			����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveTurnabs(ZMC_HANDLE handle, int tablenum ,int imaxaxises,int *piAxislist, float *pfDisancelist);

/*************************************************************
Description:    //��ת̨Բ��+�����岹�˶���  20130901 �Ժ�Ŀ������汾֧��
Input:          //������handle
				tablenum       �洢��ת������table���
				refpos1    ��һ����ο��㣬����λ��
				refpos2    �ڶ�����ο��㣬����λ��
				mode      1-�ο����ǵ�ǰ��ǰ�棬2-�ο����ǽ�������棬3-�ο������м䣬�������㶨Բ�ķ�ʽ��
				end1              ��һ��������㣬����λ��
				end2              �ڶ���������㣬����λ��
				imaxaxises        �����˶�������
				piAxislist		  ���б�
				pfDisancelistNumber      �����������Ч������  ������Ϊ2��ʾ��0���͵�2������Ҫ��Ч�Ľ���λ�ã����������᲻����
				pfDisancelist	����������б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_McircTurnabs(ZMC_HANDLE handle, int tablenum ,float refpos1,float refpos2,int mode,float end1,float end2,int imaxaxises,int *piAxislist , uint pfDisancelistNumber,float *pfDisancelist);

/*************************************************************
Description:    //����͹�� ͬ���˶�
Input:          //������handle  
				iaxis			���
				istartpoint		��ʼ��TABLE���
				iendpoint		������TABLE���
				ftablemulti		λ�ñ�����һ����Ϊ���嵱��ֵ
				fDistance		�ο��˶��ľ��룬�����������˶�ʱ��
 Output:         //
 Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Cam(ZMC_HANDLE handle,int iaxis, int istartpoint, int iendpoint, float ftablemulti, float fDistance);

/*************************************************************
Description:    //����͹�� ͬ���˶�
Input:          //������handle
				iaxis			���
				istartpoint		��ʼ��TABLE���
				iendpoint		������TABLE���
				ftablemulti		λ�ñ�����һ����Ϊ���嵱��ֵ
				fDistance		�ο��˶��ľ���
				ilinkaxis		�ο�����
				ioption			�ο�������ӷ�ʽ,����������μ�ZBASIC����ֲ��PC�����ֲ�
				flinkstartpos	��ioption��������Ϊ2ʱ���ò�����ʾ���ӿ�ʼ�����ľ���λ��
				linkoffpos:     ��ioption����bit4��Ϊ1ʱ���ò�����ʾ�����Ѿ�����������λ��
 Output:         //
 Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Cambox(ZMC_HANDLE handle, int iaxis,int istartpoint, int iendpoint, float ftablemulti, float fDistance, int ilinkaxis, int ioption, float flinkstartpos,float linkoffpos);



/*************************************************************
Description:    //����͹�� ͬ���˶�
Input:          //������handle
				iaxis			�����˶������(������)
				fDistance		ͬ�����̸������˶�����
				fLinkDis		ͬ�����̲ο���(����)�˶����Ծ���
				fLinkAcc		��������ٽ׶Σ��ο����ƶ��ľ��Ծ���
				fLinkDec		��������ٽ׶Σ��ο����ƶ��ľ��Ծ���
				iLinkaxis		�ο�������
				ioption			����ģʽѡ��,����������μ�ZBASIC����ֲ��PC�����ֲ�
				link_pos	    ��ioption��������Ϊ2ʱ���ò�����ʾ���ӿ�ʼ�����ľ���λ��
				link_offpos     ��ioption����bit4��Ϊ1ʱ���ò�����ʾ�����Ѿ�����������λ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Movelink(ZMC_HANDLE handle, int iaxis, float fDistance, float fLinkDis, float fLinkAcc, float fLinkDec, int iLinkaxis, int ioption, float link_pos, float link_offpos);

/*************************************************************
Description:    //����͹�� ͬ���˶�
Input:          //������handle  
				iaxis			�����˶������(������)
				fDistance		ͬ�����̸������˶�����
				fLinkDis		ͬ�����̲ο���(����)�˶����Ծ���
				startsp			����ʱ������Ͳο�����ٶȱ�����units/units��λ��������ʾ�����Ḻ���˶�
				endsp			����ʱ������Ͳο�����ٶȱ�����units/units��λ, ������ʾ�����Ḻ���˶���
				iLinkaxis		�ο�������
				ioption			����ģʽѡ��,����������μ�ZBASIC����ֲ��PC�����ֲ�
				link_pos	��ioption��������Ϊ2ʱ���ò�����ʾ�ο����ڸþ���λ��ֵʱ�����ӿ�ʼ 
				link_offpos  ��ioption����bit4��Ϊ1ʱ���ò�����ʾ�����Ѿ�����������λ�á�20170428���Ϲ̼�֧�֡�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Moveslink(ZMC_HANDLE handle, int iaxis,float fDistance, float fLinkDis, float startsp, float endsp,int iLinkaxis, int ioption,float link_pos,float link_offpos);

/*************************************************************
Description:    //���� ͬ���˶�ָ�� ���ӳ���
Input:          //������handle  
				ratio		���ʣ������ɸ���ע������������ı�����	
				link_axis	���������ţ�����ʱΪ��������
				move_axis	�涯���
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Connect(ZMC_HANDLE handle, float ratio, int link_axis, int move_axis);

/*************************************************************
Description:    //���� ͬ���˶�ָ�� ���ӳ��� ����ǰ���Ŀ��λ����link_axis��Ĳ岹ʸ������ͨ�����ӳ�������
Input:          //������handle  
				ratio		���ʣ������ɸ���ע������������ı�����	
				link_axis	���������ţ�����ʱΪ��������
				move_axis	�涯���
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Connpath(ZMC_HANDLE handle, float ratio, int link_axis, int move_axis);


/*************************************************************
Description:    //λ������ָ��
Input:          //������handle  
				iaxis	���
				imode	����ģʽ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Regist(ZMC_HANDLE handle,int iaxis, int imode);

/*************************************************************
Description:    //������������ֱȣ�ȱʡ(1,1)
Input:          //������handle  
				iaxis		���
				mpos_count	���ӣ���Ҫ����65535
				input_count	 ��ĸ����Ҫ����65535
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_EncoderRatio(ZMC_HANDLE handle, int iaxis,int output_count,int input_count);

/*************************************************************
Description:    //���ò���������ֱȣ�ȱʡ(1,1)
Input:          //������handle  
				iaxis		���
				mpos_count	���ӣ�1-65535
				input_count	 ��ĸ��1-65535
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_StepRatio(ZMC_HANDLE handle, int iaxis, int output_count,int input_count);


/*************************************************************
Description:    //����������ֹͣ
Input:          //������handle 
				imode ֹͣģʽ
				0��ȱʡ��ȡ����ǰ�˶�
				1	ȡ��������˶�
				2	ȡ����ǰ�˶��ͻ����˶���
				3	�����ж����巢�͡�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Rapidstop(ZMC_HANDLE handle, int imode);

/*************************************************************
Description:    //������˶�ֹͣ
Input:          //������handle  ��ţ� ����
				imaxaxises		����
				piAxislist		���б�
				imode	ģʽ
					0��ȱʡ��ȡ����ǰ�˶�
					1	ȡ��������˶�
					2	ȡ����ǰ�˶��ͻ����˶���
					3	�����ж����巢�͡�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_CancelAxisList(ZMC_HANDLE handle, int imaxaxises, int *piAxislist, int imode);

/*************************************************************
Description:    //CONNFRAME��е�����ָ��	2ϵ�����Ͽ�����֧��
Input:          //������handle
				Jogmaxaxises	�ؽ�������
				JogAxislist		�ؽ����б�
				frame			��е������
				tablenum		��е�ֲ���TABLE��ʼ���
				Virmaxaxises	�������������
				VirAxislist		�������б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Connframe(ZMC_HANDLE handle,int Jogmaxaxises,int *JogAxislist, int frame, int tablenum , int Virmaxaxises , int *VirAxislist);

/*************************************************************
Description:    //CONNREFRAME��е������ָ��	2ϵ�����Ͽ�����֧��
Input:          //������handle
				Virmaxaxises	�������������
				VirAxislist		�������б�
				frame			��е������
				tablenum		��е�ֲ���TABLE��ʼ���
				Jogmaxaxises	�ؽ�������
				JogAxislist		�ؽ����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Connreframe(ZMC_HANDLE handle,int Virmaxaxises , int *VirAxislist, int frame, int tablenum , int Jogmaxaxises,int *JogAxislist);


#if 0
    //���ắ��
#endif

/*************************************************************
Description:    //������˶�	iaddaxis�˶����ӵ�iaxis�� ��ADDAXָ����ӵ����������
Input:          //������handle  
				 iaxis		��������
				 iaddaxis	������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Single_Addax(ZMC_HANDLE handle, int iaxis, int iaddaxis);

/*************************************************************
Description:    //�����˶�ֹͣ
Input:          //������handle  
				iaxis ���
				imode ģʽ
					0��ȱʡ��ȡ����ǰ�˶�
					1	ȡ��������˶�
					2	ȡ����ǰ�˶��ͻ����˶���
					3	�����ж����巢�͡�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Single_Cancel(ZMC_HANDLE handle, int iaxis, int imode);


/*************************************************************
Description:    //���������˶�
Input:          //������handle  
				iaxis ���
				idir ���� 1���� -1����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Single_Vmove(ZMC_HANDLE handle, int iaxis, int idir);

/*************************************************************
Description:    //��������ʽ����
Input:          //������handle  
				iaxis	���
				imode	ģʽ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Single_Datum(ZMC_HANDLE handle, int iaxis, int imode);

/*************************************************************
Description:    //�������״̬
Input:          //������handle  
				iaxis ���
Output:         //homestatus ������ɱ�־ 0-�����쳣 1����ɹ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetHomeStatus(ZMC_HANDLE handle,uint32 iaxis,uint32 * homestatus);


/*************************************************************
Description:    //��������˶�
Input:          //������handle  
				iaxis ���
				fdistance ����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Single_Move(ZMC_HANDLE handle, int iaxis, float fdistance);


/*************************************************************
Description:    //��������˶�
Input:          //������handle  
				iaxis ���
				fdistance ����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Single_MoveAbs(ZMC_HANDLE handle, int iaxis, float fdistance);


#if 0
    //��������
#endif

/*********************�ڴ����

/*********************�ڴ����
/*************************************************************
Description:    //дVR, 
Input:          //������handle 
				vrstartnum		VR��ʼ���
				numes			д�������
				pfValue			д��������б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetVrf(ZMC_HANDLE handle,int vrstartnum, int numes, float *pfValue);

/*************************************************************
Description:    //VR��ȡ, ����һ�ζ�ȡ���
Input:          //������handle  
				vrstartnum	��ȡ��VR��ʼ��ַ
				numes		��ȡ������
Output:         //pfValue  ���صĶ�ȡֵ�����ʱ�������ռ�.
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetVrf(ZMC_HANDLE handle, int vrstartnum, int numes, float *pfValue);


/*************************************************************
Description:    //VRINT��ȡ�� ����150401���ϰ汾��֧��VRINT��DIRECTCOMMAND��ȡ
Input:          //������handle  
				vrstartnum	��ȡ��VR��ʼ��ַ
				numes		��ȡ������
				Output:         //piValue  ���صĶ�ȡֵ�����ʱ�������ռ�.
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetVrInt(ZMC_HANDLE handle, int vrstartnum, int numes, int *piValue);

/*************************************************************
Description:    //дtable 
Input:          //������handle 
				tabstart	д���TABLE��ʼ���
				numes		д�������
				pfValue		д�������ֵ
Output:         //	
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetTable(ZMC_HANDLE handle,int tabstart, int numes, float *pfValue);

/*************************************************************
Description:    //table��ȡ, ����һ�ζ�ȡ���
Input:          //������handle  
				tabstart	��ȡTABLE��ʼ��ַ
				numes		��ȡ������
Output:         //pfValue  ���ʱ�������ռ�.
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetTable(ZMC_HANDLE handle, int tabstart, int numes, float *pfValue);

/*************************************************************
Description:    //�ַ���תΪfloat
Input:          //������handle 
				pstringin ���ݵ��ַ���
				inumes   ת�����ݸ���
Output:         //pfvlaue ת��������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_TransStringtoFloat(const char* pstringin, int inumes,  float* pfvlaue);


/*************************************************************
Description:    //�ַ���תΪint
Input:          //������handle 
				pstringin ���ݵ��ַ���
				inumes   ת�����ݸ���
Output:         //pivlaue ת��������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_TransStringtoInt(const char* pstringin, int inumes,  int* pivlaue);

/*************************************************************
Description:    //��float��ʽ�ı����б�洢���ļ��� ���������U���ļ���ʽһ��.
Input:          //sFilename �ļ�����·��
				pVarlist	д��������б�
				inum		���ݵĳ���
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_WriteUFile(const char *sFilename, float *pVarlist, int inum);

/*************************************************************
Description:    //��ȡfloat��ʽ�ı����б� ���������U���ļ���ʽһ��.
Input:          //sFilename �ļ�����·��
				inum		���ݵĳ���	
Output:         //pVarlist	��ȡ�������б�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_ReadUFile(const char *sFilename, float *pVarlist, int* pinum);


/*************************************************************
Description:    //modbus�Ĵ������� modbus_bit
Input:          //������handle �Ĵ�����ַ
				start	��ʼ���
				inum	����
				pdata ���õ�λ״̬  ��λ�洢
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Set0x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint8* pdata);

/*************************************************************
Description:    //modbus�Ĵ������� modbus_bit
Input:          //������handle �Ĵ�����ַ
				start	��ʼ���
				inum	����
Output:         //pdata ���ص�λ״̬  ��λ�洢
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Get0x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint8* pdata);

/*************************************************************
Description:    //modbus�Ĵ������� MODBUS_REG
Input:          //������handle �Ĵ�����ַ
				start	��ʼ���
				inum	����
Output:         //pdata	��ȡ��REG�Ĵ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Set4x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint16* pdata);

/*************************************************************
Description:    //modbus�Ĵ������� MODBUS_REG
Input:          //������handle �Ĵ�����ַ
				start	��ʼ���
				inum	����
Output:         //pdata	��ȡ��REG�Ĵ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Get4x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint16* pdata);

/*************************************************************
Description:    //modbus�Ĵ�������		MODBUS_IEEE
Input:          //������handle �Ĵ�����ַ
				start	��ʼ���
				inum	����
				pfdata	����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Get4x_Float(ZMC_HANDLE handle, uint16 start, uint16 inum, float* pfdata);

/*************************************************************
Description:    //modbus�Ĵ�������		MODBUS_IEEE
Input:          //������handle �Ĵ�����ַ
				start	��ʼ���
				inum	����
				pfdata	����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Set4x_Float(ZMC_HANDLE handle, uint16 start, uint16 inum, float* pfdata);

/*************************************************************
Description:    //modbus�Ĵ�������		MODBUS_LONG
Input:          //������handle �Ĵ�����ַ
				start	��ʼ���
				inum	����
				pidata	����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Get4x_Long(ZMC_HANDLE handle, uint16 start, uint16 inum, int32* pidata);

/*************************************************************
Description:    //modbus�Ĵ������� MODBUS_LONG
Input:          //������handle �Ĵ�����ַ
				start	��ʼ���
				inum	����
Output:         //pidata	��ȡ��REG�Ĵ���ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Set4x_Long(ZMC_HANDLE handle, uint16 start, uint16 inum, int32* pidata);

/*************************************************************
Description:    //��ȡmodbus_string
Input:          //������handle
				start	modbus��ʼ��ַ
				inum	����			
Output:         pidata	��ȡ���ص��ַ���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Get4x_String(ZMC_HANDLE handle, uint16 start, uint16 inum, char * pidata);

/*************************************************************
Description:    //����modbus_string
Input:          //������handle
				start	modbus��ʼ��ַ
				inum	����
				pidata	д����ַ���
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Modbus_Set4x_String(ZMC_HANDLE handle, uint16 start, uint16 inum, char * pidata);

/*************************************************************
Description:    //д�û�flash��, float����
Input:          //������handle
					uiflashid 	flash���
					uinumes		��������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_FlashWritef(ZMC_HANDLE handle, uint16 uiflashid, uint32 uinumes, float *pfvlue);

/*************************************************************
Description:    //��ȡ�û�flash��, float����
Input:          //������handle
					uiflashid 	flash���
					uibuffnum	�����������
Output:         //
					puinumesread ��ȡ���ı�������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_FlashReadf(ZMC_HANDLE handle, uint16 uiflashid, uint32 uibuffnum, float *pfvlue, uint32* puinumesread);



/*****************************************************************************************************2018-08-24 V2.1�������**************************
/*************************************************************
Description:    //ʾ������������ 150723�Ժ�̼��汾֧��
Input:          //������handle  
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Trigger(ZMC_HANDLE handle);


//MOVE_PARA,MOVE_PWM, MOVE_SYNMOVE,MOVE_ASYNMOVE
/*************************************************************
Description:    //�˶����޸Ĳ���. 20170503���Ϲ̼�֧��
Input:          //������handle  PARANAME, INDEX, VALUE
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MovePara(ZMC_HANDLE handle,uint32 base_axis,char *  paraname,uint32 iaxis,float fvalue);

/*************************************************************
Description:    //�˶����޸�PWM 20170503���Ϲ̼�֧��
Input:          //������handle  PARANAME, INDEX, VALUE
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MovePwm(ZMC_HANDLE handle,uint32 base_axis,uint32 pwm_num,float pwm_duty,float pwm_freq);

/*************************************************************
Description:    //�˶���ͬ����������˶�,. 20170503���Ϲ̼�֧��
Input:          //������handle  PARANAME, INDEX, VALUE
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveSynmove(ZMC_HANDLE handle,uint32 base_axis,uint32 iaxis,float fdist,uint32 ifsp);

/*************************************************************
Description:    //�˶��д�����������˶�. 20170503���Ϲ̼�֧��
Input:          //������handle  PARANAME, INDEX, VALUE
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveASynmove(ZMC_HANDLE handle,uint32 base_axis,uint32 iaxis,float fdist,uint32 ifsp);

/*************************************************************
Description:    //�˶����޸�TABLE
Input:          //������handle  
				base_axis	�岹������
				table_num	TABLE���
				fvalue		�޸�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveTable(ZMC_HANDLE handle,uint32 base_axis,uint32 table_num,float fvalue);


/*************************************************************
Description:    //BASE���˶��������һ���ɱ����ʱ  �̼�150802���ϰ汾�� ��XPLC160405���ϰ汾֧�֡�
Input:          //������handle  
				base_axis	�岹������
				paraname	�������ַ��� DPOS MPOS IN AIN VPSPEED MSPEED MODBUS_REG MODBUS_IEEE MODBUS_BIT NVRAM VECT_BUFFED  REMAIN 
				inum		������Ż����
				Cmp_mode	�Ƚ����� 1 >=   0=  -1<=  ��IN��BIT���Ͳ�����Ч��
				fvalue		�Ƚ�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveWait(ZMC_HANDLE handle,uint32 base_axis,char * paraname,int inum,int Cmp_mode,float fvalue);

/*************************************************************
Description:    //BASE���˶��������һ��TASK���� �������Ѿ�����ʱ���ᱨ������Ӱ�����ִ�С�
Input:          //������handle			
				base_axis	�岹������
				tasknum   	������ 
				labelname		BAS��ȫ�ֺ��������߱��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveTask(ZMC_HANDLE handle,uint32 base_axis,uint32 tasknum,char * labelname);

/*************************************************************
Description:    //λ�ñȽ�PSWITCH
Input:          //������handle
				//�Ƚ������ num 0-15
				//�Ƚ���ʹ�� enable 0/1
				//�Ƚϵ���� axisnum
				//����ڱ�� outnum
				//���״̬	outstate 0/1
				//�Ƚ���ʼλ��	setpos
				//�����λλ��	resetpos
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Pswitch(ZMC_HANDLE handle, int num, int enable, int axisnum, int outnum, int  outstate, float setpos,float resetpos);

/*************************************************************
Description:    //Ӳ��λ�ñȽ���� 4ϵ�в�Ʒ���������������֧��Ӳ���Ƚ����
Input:          //������handle
				//ģʽ	 mode 1-�����Ƚ���, 2- ֹͣ��ɾ��û��ɵıȽϵ�.
				//���� direction 0-���긺��,  1- ��������  
				//Ԥ�� Reserve   Ԥ��
				//TABLE��ʼ�� Tablestart  ��һ���Ƚϵ���������TABLE���
				//TABLE������ tableend ���һ���Ƚϵ���������TABLE���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_HwPswitch(ZMC_HANDLE handle,int Axisnum,int Mode, int Direction, int Reserve, int Tablestart, int  Tableend);

/*************************************************************
Description:    //Ӳ��λ�ñȽ����ʣ�໺���ȡ 4ϵ�в�Ʒ���������������֧��Ӳ���Ƚ����
Input:          //������handle
				//ģʽ	 axisnum				���
output:			//λ�ñȽ����ʣ�໺����		buff
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetHwPswitchBuff(ZMC_HANDLE handle,int axisnum,int * buff);

/*************************************************************
Description:    //Ӳ����ʱ������Ӳ���Ƚ������һ��ʱ���ԭ��ƽ 4ϵ�в�Ʒ֧��
Input:          //������	handle  
				//ģʽ			mode		0ֹͣ,  2-����			
				//����ʱ��	   cyclonetime  us��λ
				//��Чʱ��	   optime		us��λ
				//�ظ�����	   reptimes
				//���ȱʡ״̬ opstate		����ڱ�Ϊ�Ǵ�״̬��ʼ��ʱ
				// ����ڱ��  opnum		������Ӳ���Ƚ�����Ŀ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_HwTimer(ZMC_HANDLE handle,int mode,int cyclonetime,int optime,int reptimes,int opstate,int  opnum );

/*************************************************************
Description:    //��ȡ��ֹͣԭ��
Input:          //������handle  
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAxisStopReason(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //�����Ͷ�ȫ�������״̬
Input:          //������handle 
Input:          //
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAllAxisPara(ZMC_HANDLE handle,const char *sParam,int imaxaxis,float * pfValue);

/*************************************************************
Description:    //�����Ͷ�ȫ�������״̬
Input:          //������handle 
Input:          //
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetAllAxisInfo(ZMC_HANDLE handle,int imaxaxis,int * IdleStatus,float * DposStatus,float * MposStatus,int * AxisStatus);

/*************************************************************
Description:    //����BASIC�Զ���ȫ������  
Input:          //������handle  
				arrayname ��������
				arraystart ������ʼԪ��
				numes		Ԫ������
				pfValue     ����ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetUserArray(ZMC_HANDLE handle,char * arrayname ,int arraystart, int numes, float *pfValue);

/*************************************************************
Description:    //��ȡ����BASIC�Զ���ȫ������ , ����һ�ζ�ȡ���
Input:          //������handle  
				arrayname ��������
				arraystart ������ʼԪ��
				numes		Ԫ������
Output:         //pfValue  ���ʱ�������ռ�.
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetUserArray(ZMC_HANDLE handle,char * arrayname ,int arraystart, int numes, float *pfValue);

/*************************************************************
Description:    //�����Զ������, 
Input:          //������handle  
				varname ���������ַ���
				pfValue	�趨ֵ
Output:         //  
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetUserVar(ZMC_HANDLE handle,char * varname , float pfValue);

/*************************************************************
Description:    //��ȡ�Զ���ȫ�ֱ���, 
Input:          //������handle  
				varname ���������ַ���
Output:         //pfValue  ����ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetUserVar(ZMC_HANDLE handle,char * varname , float *pfValue);

/*************************************************************
Description:    //��ȡPCI�Ŀ��ƿ�����
Input:          //
Output:         //������handle
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetMaxPciCards();

/*************************************************************
Description:    //���������������
Input:          //PCI���ţ�
Output:         //������handle
Return:         //������
*************************************************************/
int32 __stdcall ZAux_OpenPci(uint32 cardnum, ZMC_HANDLE * phandle);

/*************************************************************
Description:    //��ȡ����������Ϣ
Input:          //������handle  
Output:         SoftType �������ͺ�����
				SoftVersion ����������汾���̼��汾��
				ControllerId	������ΨһID
Return:         //������
uint32 __stdcall ZMC_GetSoftVersion(ZMC_HANDLE handle,float *pVersion, char *pVerString, uint32 *pVerDate);
*************************************************************/
int32 __stdcall ZAux_GetControllerInfo(ZMC_HANDLE handle ,char * SoftType ,char * SoftVersion ,char *  ControllerId);

/*************************************************************
Description:    //��ȡ�����Ͻڵ�����
Input:          //������handle 
:				 //slot ��λ��ȱʡ0
Output:         //piValue ����ɨ��ɹ��ڵ�����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_GetNodeNum(ZMC_HANDLE handle,int slot,int *piValue);

/*************************************************************
Description:    //��ȡ�ڵ��ϵ���Ϣ
Input:          //������handle 
				slot	��λ��
				node	�ڵ���
				sel		��Ϣ���	0-���̱��1-�豸��� 2-�豸�汾 3-���� 10-IN���� 11-OUT���� 
Output:         //piValue ������Ϣ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_GetNodeInfo(ZMC_HANDLE handle,int slot,int node,int sel ,int *piValue);

/*************************************************************
Description:    //��ȡ�ڵ�����״̬
Input:          //������handle  
				slot ��λ��ȱʡ0
				node �ڵ���
Output:         //nodestatus ��λ���� bit0-�ڵ��Ƿ����  bit1-ͨѶ״̬   bit2-�ڵ�״̬
ֵΪ1ʱ��bit0Ϊ1��bit1��bit2Ϊ0���豸ͨѶ����
ֵΪ3ʱ��bit0��bit1Ϊ1��bit2Ϊ0���豸ͨѶ����
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_GetNodeStatus(ZMC_HANDLE handle,uint32 slot,uint32 node,uint32 * nodestatus);

/*************************************************************
Description:    //��ȡ�ڵ�SDO������Ϣ
Input:          //������handle  
				slot	��λ�� ȱʡ0
				node	�ڵ���
				index	�����ֵ��ţ�ע�⺯��Ϊ10�������ݣ�
				subindex	�ӱ��	��ע�⺯��Ϊ10�������ݣ�
				type	��������  1-bool 2-int8 3-int16 4-int32 5-uint8 6-uint16 7-uint32
Output:         //value ��ȡ������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_SDORead(ZMC_HANDLE handle,uint32 slot,uint32 node,uint32 index,uint32 subindex ,uint32 type ,int32 * value, uint32 tableNumber = 0);

/*************************************************************
Description:    //д�ڵ�SDO������Ϣ
Input:          //������handle  
				slot	��λ�� ȱʡ0
				node	�ڵ���
				index	�����ֵ��ţ�ע�⺯��Ϊ10�������ݣ�
				subindex	�ӱ��	��ע�⺯��Ϊ10�������ݣ�
				type	��������  1-bool 2-int8 3-int16 4-int32 5-uint8 6-uint16 7-uint32
				value	�趨������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_SDOWrite(ZMC_HANDLE handle,uint32 slot,uint32 node,uint32 index,uint32 subindex ,uint32 type ,int32  value);

/*************************************************************
Description:    //��ȡ��SDO������Ϣ
Input:          //������handle  
				slot	��λ�� ȱʡ0
				node	�ڵ���
				index	�����ֵ��ţ�ע�⺯��Ϊ10�������ݣ�
				subindex	�ӱ��	��ע�⺯��Ϊ10�������ݣ�
				type	��������  1-bool 2-int8 3-int16 4-int32 5-uint8 6-uint16 7-uint32
Output:         //value ��ȡ������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_SDOReadAxis(ZMC_HANDLE handle,uint32 iaxis,uint32 index,uint32 subindex ,uint32 type ,int32 * value, uint32 tableNumber=0);

/*************************************************************
Description:    //д��SDO������Ϣ
Input:          //������handle  
				slot	��λ�� ȱʡ0
				node	�ڵ���
				index	�����ֵ��ţ�ע�⺯��Ϊ10�������ݣ�
				subindex	�ӱ��	��ע�⺯��Ϊ10�������ݣ�
				type	��������  1-bool 2-int8 3-int16 4-int32 5-uint8 6-uint16 7-uint32
				value	�趨������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_SDOWriteAxis(ZMC_HANDLE handle,uint32 iaxis,uint32 index,uint32 subindex ,uint32 type ,int32  value);

/*************************************************************
Description:    //Rtex��ȡ������Ϣ
Input:          //������handle  
				iaxis	���
				ipara	��������*256 + �������  Pr7.11-ipara = 7*256+11
Output:         //value ��ȡ������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_RtexRead(ZMC_HANDLE handle,uint32 iaxis ,uint32 ipara ,float * value);

/*************************************************************
Description:    //Rtexд������Ϣ
Input:          //������handle  
				iaxis	���
				ipara	��������*256 + �������  Pr7.11-ipara = 7*256+11
				value	�趨������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_RtexWrite(ZMC_HANDLE handle,uint32 iaxis ,uint32 ipara,float  value);


/*************************************************************
Description:    //���û���ƫ�ƾ���
Input:          //������handle  
				iaxis ���
				fValue ƫ�ƾ���
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_SetDatumOffpos(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡ����ƫ�ƾ���
Input:          //������handle  
				iaxis ���
Output:         //fValue ������ƫ�ƾ���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_GetDatumOffpos(ZMC_HANDLE handle, int iaxis, float * fValue);

/*************************************************************
Description:    //��������������
Input:          //������handle  
				homemode ����ģʽ���鿴�������ֲ�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_Datum(ZMC_HANDLE handle,uint32 iaxis,uint32  homemode);

/*************************************************************
Description:    //�������������״̬
Input:          //������handle  
				iaxis ���
Output:         //homestatus ������ɱ�־ 0-�����쳣 1����ɹ�
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_GetHomeStatus(ZMC_HANDLE handle,uint32 iaxis,uint32 * homestatus);

/*************************************************************
Description:    //������������ŷ�����
Input:          //������handle 
				iaxis ���
				mode ģʽ 0-�����ǰ�澯  1-�����ʷ�澯  2-����ⲿ����澯
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_DriveClear(ZMC_HANDLE handle,uint32 iaxis,uint32  mode);

/*************************************************************
Description:    //��ȡ��ǰ����������ǰ����	��Ҫ���ö�Ӧ��DRIVE_PROFILE����
Input:          //������handle  
				iaxis ���
Output:         //piValue ��ǰת��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_GetDriveTorque(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //���õ�ǰ�����������ת��  ��Ҫ���ö�Ӧ��DRIVE_PROFILE����
Input:          //������handle		
				iaxis ���
				piValue ���ת������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_SetMaxDriveTorque(ZMC_HANDLE handle, int iaxis, int piValue);

/*************************************************************
Description:    //��ȡ��ǰ�����������ת��  ��Ҫ���ö�Ӧ��DRIVE_PROFILE����
Input:          //������handle  
				iaxis ���
Output:         //piValue ���ص����ת��
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_GetMaxDriveTorque(ZMC_HANDLE handle, int iaxis, int *piValue);

/*************************************************************
Description:    //����ģ������� ���ء��ٶ�ģʽ�¿���  ����������Ҫ���ö�ӦDRIVE_PROFILE���� ��ATYPE
Input:          //������handle  
				iaxis ���
				ģ���� ���ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetDAC(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //��ȡģ������� ���ء��ٶ�ģʽ�¿���  ����������Ҫ���ö�ӦDRIVE_PROFILE���� ��ATYPE
Input:          //������handle  
				iaxis ���
Output:         //fValue ģ��������ֵ
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetDAC(ZMC_HANDLE handle, int iaxis, float *fValue);

/*************************************************************
Description:    //���߳�ʼ��  �����Zmotion tools ����������ù����߲���������ʹ����Ч��
Input:          //������handle  
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_InitBus(ZMC_HANDLE handle);

/*************************************************************
Description:    //��ȡ���߳�ʼ�����״̬  �����Zmotion tools ����������ù����߲���������ʹ����Ч��
Input:          //������handle  
Output:         //
Return:         //������piValue 0-��ʼ��ʧ�� 1�ɹ�
*************************************************************/
int32 __stdcall ZAux_BusCmd_GetInitStatus(ZMC_HANDLE handle,int *piValue);

/*************************************************************
Description:    //��ȡ��������ź�
Input:          //������handle  
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetInMulti(ZMC_HANDLE handle, int startio , int endio, int32 *piValue);

/*************************************************************
Description:    //�������ʱ�ȴ�ʱ��
Input:          //������handle ����ʱ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_SetTimeOut(ZMC_HANDLE  handle, uint32 timems);

/*************************************************************2017-12-14���
Description:    //Ӳ��λ�ñȽ����2 4ϵ�в�Ʒ, 20170513���ϰ汾֧��.  ZMC306E/306N֧��
Input:          //������					handle
				//ģʽ						mode		
				//����ڱ��				Opnum		4ϵ�� out 0-3ΪӲ��λ�ñȽ����
				//��һ���Ƚϵ�����״̬	Opstate		0-�ر� 1��										
				//�๦�ܲ���				ModePara1	 
				//�๦�ܲ���				ModePara2
				//�๦�ܲ���				ModePara3
				//�๦�ܲ���				ModePara4

mode 1-�����Ƚ���, 
		ModePara1 =  ��һ���Ƚϵ���������TABLE���
		ModePara2 =	 ���һ���Ƚϵ���������TABLE���
		ModePara3 =  ��һ�����жϷ���,  0-���긺��,  1- ��������,  -1-��ʹ�÷���
		ModePara4 =	 Ԥ��
		ModePara5=	 Ԥ��
		ModePara6=   Ԥ��
mode 2- ֹͣ��ɾ��û��ɵıȽϵ�. 
		ModePara1 =  Ԥ��
		ModePara2 =	 Ԥ��
		ModePara3 =  Ԥ��
		ModePara4 =	 Ԥ��
		ModePara5=	 Ԥ��
		ModePara6=   Ԥ��
//ʹ��ʸ������Ƚ�ʱ����VECTOR_MOVED���бȽϣ����������˶�ǰ����VECTOR_MOVED��ʼֵ
mode 3- ʸ���ȽϷ�ʽ   
		ModePara1 =  ��һ���Ƚϵ���������TABLE���
		ModePara2 =	 ���һ���Ƚϵ���������TABLE���
		ModePara3 =  Ԥ��
		ModePara4 =	 Ԥ��
		ModePara5=	 Ԥ��
		ModePara6=   Ԥ��
Mode=4 :ʸ���ȽϷ�ʽ, �����Ƚϵ�
		ModePara1 =  �Ƚϵ�����
		ModePara2 =	 Ԥ��
		ModePara3 =  Ԥ��
		ModePara4 =	 Ԥ��
		ModePara5=	 Ԥ��
		ModePara6=   Ԥ��
Mode=5 :ʸ���ȽϷ�ʽ, ��������ģʽ
		ModePara1 =  �Ƚϵ�����  VECTOR_MOVED��ǰ�˶�����
		ModePara2 =	 �ظ�����, һ�������ڱȽ�����, �������Ч״̬,�������Ч״̬.
		ModePara3 =  ���ھ���, ÿ������������Opstate, �����Ч״̬�ľ��루ModePara4����ԭΪ��Ч״̬.
		ModePara4 =	 �����Ч״̬�ľ���,  (ModePara3- ModePara4) Ϊ��Ч״̬����
		ModePara5=	 Ԥ��
		ModePara6=   Ԥ��
Mode=6 :ʸ���ȽϷ�ʽ, ����ģʽ, ����ģʽһ����HW_TIMERһ��ʹ��.
		ModePara1 =  �Ƚϵ�����  �Ƚϵ�VECTOR_MOVED��ǰ�˶�����
		ModePara2 =	 �ظ�����, һ������ֻ�Ƚ�һ��
		ModePara3 =  ���ھ���, ÿ������������һ��
		ModePara4 =	 Ԥ��
		ModePara5=	 Ԥ��
		ModePara6=   Ԥ��
Mode=7����HW_TIMERһ��ʹ��
	  ModePara1 = ��һ���Ƚϵ�VECTOR_MOVED��������TABLE���
	  ModePara2 = ���һ���Ƚϵ�VECTOR_MOVED��������TABLE���
	  [��hwtimer����ʱ�����Զ�̬����hwtimer����]
	  ModePara3 =  ��̬����HW_TIMER����Чʱ��
	  ModePara4 =  ��̬����HW_TIMER�Ĵ�����������0-�����
	  ModePara5=   ��̬����HW_TIMER����������ʱ��
	  ModePara6=   Ԥ��
Mode=25, 26, 35,36, ��ά�ıȽ�ģʽ     25,26  2D�Ƚ�ģʽ      35,36 3D�Ƚ�ģʽ
	  ModePara1 = �Ƚ�λ��ÿ�������ҵ�����ƫ�����ƫ�Χ��ʼ�Ƚ�
	  ModePara2 = table����洢�ıȽϵ����
	  ModePara3 = ��һ���Ƚϵ���������table���
	  [��hwtimer����ʱ�����Զ�̬����hwtimer����]
	  ModePara4 =  ����ʱ��
	  ModePara5=   �������
	  ModePara6=   ��������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_HwPswitch2(ZMC_HANDLE handle,int Axisnum,int Mode, int Opnum , int Opstate, float ModePara1, float ModePara2,float ModePara3,float ModePara4, float ModePara5,float ModePara6);

/*************************************************************
Description:    //��ȡ�������������
Input:          //������handle 
Output:         //Max_VirtuAxises	 �����������
Output:         //Max_motor			 ���������
Output:         //Max_io			 ���IN,OUT,AD,DA����				
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetSysSpecification(ZMC_HANDLE  handle, uint16 * Max_VirtuAxises,uint8 * Max_motor,uint8 *Max_io);

/*************************************************************
Description:    ////�����ϱ��Ļص�������ʽ
Input:          //������handle
				itypecode: �ϴ�������
				idatalength: ���ݳ���
				pdata: ����ָ��
Output:         //
Return:         //������
*************************************************************/
typedef void (*PZMCAutoUpCallBack)(ZMC_HANDLE handle, int32 itypecode, int32 idatalength, uint8 *pdata); 

/*************************************************************
Description:    //�������Զ��ϱ�
Input:          //������	handle 
Input:         //�ص�����   pcallback			
Return:         //������
*************************************************************/
int32 __stdcall ZAux_SetAutoUpCallBack(ZMC_HANDLE handle, PZMCAutoUpCallBack pcallback);

/*************************************************************
Description:    //IO�ӿ� �������
Input:          //������handle
Input:          //IO����ʼ���  iofirst
Input:          //IO�ڽ������  ioend
Input:          //�����״̬    istate��λ�洢��һ��UINT�洢32�������״̬
Output:         //״̬
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetOutMulti(ZMC_HANDLE handle, uint16 iofirst,uint16 ioend, uint32 * istate);

/*************************************************************
Description:    //IO�ӿ� ���ö�·���
Input:          //������handle
Input:          //IO����ʼ���  iofirst
Input:          //IO�ڽ������  ioend
Input:          //�����״̬    istate��λ�洢��һ��UINT�洢32�������״̬
Output:         //״̬
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetOutMulti(ZMC_HANDLE handle, uint16 iofirst,uint16 ioend, uint32 * istate);

/*************************************************************
Description:    //������Զ���ֱ�߲岹 
Input:          //������handle
				iMoveLen			��д���˶�����
				imaxaxises			�����˶�������
				piAxislist			����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MultiMove(ZMC_HANDLE handle,int iMoveLen, int imaxaxises, int *piAxislist, float *pfDisancelist);

/*************************************************************
Description:    //������Զ���ֱ�߲岹 
Input:          //������handle
				iMoveLen			��д���˶�����
				imaxaxises			�����˶�������
				piAxislist			����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MultiMoveAbs(ZMC_HANDLE handle,int iMoveLen, int imaxaxises, int *piAxislist, float *pfDisancelist);

/*************************************************************
Description:    //��е������ϵ��ת
Input:          //������handle
				iaxis					��� �ؽ���/������
				pfRotatePara			ƽ����ת����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_FrameRotate(ZMC_HANDLE handle,int iaxis, float *pfRotatePara);

/*************************************************************
Description:    //��ȡCAN��չ��Դ���
Input:          //������handle 
Output:         //CanNum			 ��ǰ���ӵ�CAN��վ����
Output:         //CanId_List		 ��ǰ���ӵ�CAN��վID�б�
Output:         //CanIn_List		 �ڵ����������
Output:         //CanOut_List		 �ڵ����������
Output:         //CanAin_List		 �ڵ�AD����	
Output:         //CanAOut_List		 �ڵ�DA����	
Output:         //CanAxis_List		 �ڵ�������				
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetCanInfo(ZMC_HANDLE  handle, uint8 * CanNum,uint16 * CanId_List,uint8 *CanIn_List,uint8 *CanOut_List,uint8 *CanAin_List,uint8 *CanAOut_List,uint8 *CanAxis_List);

/*************************************************************
Description:    //�������PT�˶�
Input:          //������handle
				iMoveLen			��д���˶�����
				imaxaxises			�����˶�������
				piAxislist			����б�
				pTickslist			�����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MultiMovePt(ZMC_HANDLE handle,int iMoveLen, int imaxaxises, int *piAxislist, uint32 *pTickslist, float *pfDisancelist);

/*************************************************************
Description:    //��������PT�˶�
Input:          //������handle
				iMoveLen			��д���˶�����
				imaxaxises			�����˶�������
				piAxislist			����б�
				pTickslist			�����б�
				pfDisancelist		�����б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MultiMovePtAbs(ZMC_HANDLE handle,int iMoveLen, int imaxaxises, int *piAxislist, uint32 *pTickslist, float *pfDisancelist);

/*************************************************************
Description:    //����ZAR�ļ�������
Input:          //������handle
Input:          //Filename �ļ�·��
Input:          //���ص�RAM-ROM  0-RAM  1-ROM
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_ZarDown(ZMC_HANDLE handle,const char *Filename,uint32 run_mode);

/*************************************************************
Description:    //��ȡRTCʱ��
Input:          //������handle
Input:          //ϵͳ���� ��ʽYYMMDD
Input:          //ϵͳʱ�� ��ʽHHMMSS
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_GetRtcTime(ZMC_HANDLE handle,char * RtcDate,char * RtcTime);

/*************************************************************
Description:    //����RTCʱ��
Input:          //������handle
Input:          //ϵͳ���� ��ʽYYMMDD
Input:          //ϵͳʱ�� ��ʽHHMMSS
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_SetRtcTime(ZMC_HANDLE handle,char * RtcDate,char * RtcTime);

/*************************************************************
Description:    //���������������, ����ָ�����ӵĵȴ�ʱ��
Input:          //��������	type			 1-COM 2-ETH 3-Ԥ��USB 4-PCI
Input:          //�����ַ��� pconnectstring  COM�ں�/IP��ַ
Input:          //���ӳ�ʱʱ�� uims				
Output:         //������handle
Return:         //������
*************************************************************/
int32 __stdcall ZAux_FastOpen(int type, char *pconnectstring, uint32 uims ,ZMC_HANDLE * phandle);

/*************************************************************
Description:    //�Զ�����λ���
Input:          //������handle 	
Input:          //���iaxis 	
Input:          //����ģʽimode 	
Input:          //�������HighSpeed	
Input:          //�������HighSpeed	
Input:          //���λ���ƫ�ƾ���DatumOffset	
Output:         //
Return:         //
*************************************************************/
int32 __stdcall ZAux_Direct_UserDatum(ZMC_HANDLE handle, int iaxis, int imode,float HighSpeed,float LowSpeed,float DatumOffset);

/*************************************************************
Description:    //��������ݾಹ������չ����Ч��
Input:          //handle �������
Input:          //iaxis	  ���
Input:          //iEnable  �Ƿ����ò���
Input:          //StartPos  ��ʼ����MPOSλ��
Input:          //maxpoint  ���������ܵ���
Input:          //DisOne   ÿ����������
Input:          //TablNum   ��������ֵ����TABLEϵͳ������ʼ������ַ
Input:          //pfDisancelist  ���䲹��ֵ�б�
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Pitchset(ZMC_HANDLE handle,int iaxis,int iEnable,float StartPos,uint32 maxpoint,float DisOne ,uint32 TablNum,float * pfDisancelist);

/*************************************************************
Description:    //��������ݾ�˫�򲹳�����չ����Ч��
Input:          //handle �������
Input:          //iaxis	  ���
Input:          //iEnable  �Ƿ����ò���
Input:          //StartPos  ��ʼ����MPOSλ��
Input:          //maxpoint  ���������ܵ���
Input:          //DisOne   ÿ����������
Input:          //TablNum   ��������ֵ����TABLEϵͳ������ʼ������ַ
Input:          //pfDisancelist  ���䲹��ֵ�б�
Input:          //RevTablNum   ���򲹳�����ֵ����TABLEϵͳ������ʼ������ַ
Input:          //RevpfDisancelist  �������䲹��ֵ�б� �������ݷ�����������һ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Pitchset2(ZMC_HANDLE handle,int iaxis,int iEnable,float StartPos,uint32 maxpoint,float DisOne ,uint32 TablNum,float * pfDisancelist ,uint32 RevTablNum,float * RevpfDisancelist);


/*************************************************************
Description:    //��������ݾಹ��״̬��ȡ����չ����Ч��
Input:          //handle �������
Input:          //iaxis	  ���
Output:          //IfEnable  �Ƿ����ò���  0�ر�  -1����
Output:          //PitchDist  ��������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetPitchStatus(ZMC_HANDLE handle,int iaxis,int * IfEnable,float * PitchDist);

// ���������ϱ��ĺ�������
/*************************************************************
Description:    // ʹ�������ϱ�
Input:          // cycleindex:  �ϱ�ͨ����, 0-���ֵ-1
                    fintervalms:  �ϱ����ʱ��, ms��λ, ���ܵ��ڿ�����SERVO_PERIOD
                    psetesname �ϱ�����ѡ��, �﷨: ����1, ����2(index), ����3(index, numes)
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_CycleUpEnable(ZMC_HANDLE handle, uint32 cycleindex, float fintervalms, const char* psetesname);


/*************************************************************
Description:    // ȥʹ�������ϱ�
Input:          // cycleindex:  �ϱ�ͨ����, 0-���ֵ-1
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_CycleUpDisable(ZMC_HANDLE handle, uint32 cycleindex);



/*************************************************************
Description:	// �����ϱ��յ��İ�����, �������. ����ʹ��.
Input:			// 
Output: 		//
Return: 		// ����
*************************************************************/
uint32 __stdcall ZAux_CycleUpGetRecvTimes(ZMC_HANDLE handle, uint32 cycleindex);


/*************************************************************
Description:    // ǿ���ϱ�һ��, ���˶�ָ���idle���ܲ�׼ȷ������µ���.
Input:          // 
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_CycleUpForceOnce(ZMC_HANDLE handle, uint32 cycleindex);


/*************************************************************
Description:	// �������ϱ������ȡ����
Input:			// cycleindex -1, �Զ�ѡ��cycle���
					psetname	��������
					isetindex 	�������
					
Output: 		//	pvalue ����ֵ
Return: 		// ������
*************************************************************/
uint32 __stdcall  ZAux_CycleUpReadBuff(ZMC_HANDLE handle, uint32 cycleindex, const char *psetname, uint32 isetindex, double *pvalue);



/*************************************************************
Description:	// �������ϱ������ȡ����
Input:			// cycleindex -1, �Զ�ѡ��cycle���
					psetname	��������
					isetindex 	�������
					
Output: 		//	pvalue ����ֵ
Return: 		// ������
*************************************************************/
uint32 __stdcall  ZAux_CycleUpReadBuffInt(ZMC_HANDLE handle, uint32 cycleindex, const char *psetname, uint32 isetindex, int32*pvalue);


/*************************************************************
Description:    //��������ֱ�������岹 
Input:          //������handle
                 imode	bit0- bifabs	
						bit1- bifsp		�Ƿ�				
						bit2- bifresume	
						bit3- bifmovescan ����	
				iMoveLen			��д���˶�����
				imaxaxises			�����˶�������
				piAxislist			����б�
				pfDisancelist		�����б�  iMoveLen * imaxaxises
Output:         //
				iReBuffLen   ʣ�໺������·�����������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MultiLineN(ZMC_HANDLE handle,int imode,int iMoveLen, int imaxaxises, int *piAxislist, float *pfDisancelist,int *iReBuffLen);


/*************************************************************
Description:    //Ƥ��ͬ�������˶�
Input:          //������handle
				imode				ͬ��ģʽ -1����ģʽ  -2ǿ�ƽ��� 0-��һ������� 10-�ڶ�������� 20-�ڶ��������  С��λ-angle��Ƥ����ת�Ƕ�
				synctime			ͬ��ʱ�䣬ms��λ�����˶���ָ��ʱ������ɣ����ʱBASE�����Ƥ���ұ����ٶ�һ�¡�0��ʾ�����˶�����ٶȼ��ٶ�������ͬ��ʱ�䣬���ܲ�׼ȷ  
				syncposition		Ƥ�������屻��Ӧ��ʱƤ�����λ��
				syncaxis			Ƥ�������
				imaxaxises			����ͬ����������
				piAxislist			��վ����б�
				pfDisancelist		Ƥ�������屻��Ӧ��ʱ����ľ�������λ��
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveSync(ZMC_HANDLE handle,float  imode,int synctime, float syncposition, int syncaxis, int imaxaxises, int *piAxislist, float *pfDisancelist);

/*************************************************************
Description:    //����λ������ָ��
Input:          //������handle  
				iaxis	���
				imode	����ģʽ
				iTabStart	������������ݴ洢��tableλ�ã���һ��tableԪ�ش洢����ĸ���������洢��������꣬��ౣ�����= numes-1�����ʱѭ��д��
				iTabNum	ռ�õ�table����

Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_CycleRegist(ZMC_HANDLE handle,int iaxis, int imode,int iTabStart,int iTabNum);

/*************************************************************
Description:    //�˶���ȡ���������˶�
Input:          //������handle  
				base_axis	�岹������
				table_num	TABLE���
				fvalue		�޸�ֵ
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveCancel(ZMC_HANDLE handle,int32 base_axis,int32 Cancel_Axis,int iMode);


/*************************************************************
Description:   //Pdoд����
Input:          //������handle		
					inode �ڵ��
					index �����ֵ�
					subindex �Ӷ���
					type  ��������
Return:         //������
*************************************************************/
int32 __stdcall ZAux_BusCmd_NodePdoWrite(ZMC_HANDLE handle,uint32 inode,uint32 index,uint32 subindex ,uint32 type ,int  value);	

/*************************************************************
Description:   //Pdo������
Input:          //������handle		
				inode �ڵ��
				index �����ֵ�
				subindex �Ӷ���
				type  ��������
Return:         //������
*************************************************************/
int32 __stdcall  ZAux_BusCmd_NodePdoRead(ZMC_HANDLE handle,uint32 inode,uint32 index,uint32 subindex ,uint32 type ,int*  ivalue);		//PODд����

/*************************************************************
Description:   //ʾ��������
Input:          //������handle		
				iEnable		�Ƿ�ʹ��
				iPeriod		�������� �Կ���������Ϊ��λ
				iStartTab	������ʼTABLEλ��
				iStopTab	����ֹͣTABLEλ��
				iParaNum	�ɼ�����Դ���� ���8��
				ParaNamep	�ɼ�����Դ�ַ�����

Return:         //������
*************************************************************/
int32 __stdcall  ZAux_Scope(ZMC_HANDLE handle,int iEnable,int iPeriod,int iStartTab,int iStopTab,int iParaNum ,char * ParaNamep[8]);

/*************************************************************
Description:   //��ȡʾ������������
Input:          //������handle		

output:          //���ݳ���	ilen
Return:         //������
*************************************************************/
int32 __stdcall  ZAux_GetScopeLength(ZMC_HANDLE handle,int *ilen);

/*************************************************************
Description:    //Ӳ��λ�ñȽ���� �˶����巽ʽ
Input:          //������					handle
				//ģʽ						mode
				//����ڱ��				Opnum		4ϵ�� out 0-3ΪӲ��λ�ñȽ����
				//��һ���Ƚϵ�����״̬	Opstate		0-�ر� 1��
				//�๦�ܲ���				ModePara1
				//�๦�ܲ���				ModePara2
				//�๦�ܲ���				ModePara3
				//�๦�ܲ���				ModePara4

mode 1-�����Ƚ���,
		ModePara1 =  ��һ���Ƚϵ���������TABLE���
		ModePara2 =	 ���һ���Ƚϵ���������TABLE���
		ModePara3 =  ��һ�����жϷ���,  0-���긺��,  1- ��������,  -1-��ʹ�÷���
		ModePara4 =	 Ԥ��

mode 2- ֹͣ��ɾ��û��ɵıȽϵ�.
		ModePara1 =  Ԥ��
		ModePara2 =	 Ԥ��
		ModePara3 =  Ԥ��
		ModePara4 =	 Ԥ��

mode 3- ʸ���ȽϷ�ʽ
		ModePara1 =  ��һ���Ƚϵ���������TABLE���
		ModePara2 =	 ���һ���Ƚϵ���������TABLE���
		ModePara3 =  Ԥ��
		ModePara4 =	 Ԥ��

Mode=4 :ʸ���ȽϷ�ʽ, �����Ƚϵ�
		ModePara1 =  �Ƚϵ�����
		ModePara2 =	 Ԥ��
		ModePara3 =  Ԥ��
		ModePara4 =	 Ԥ��

Mode=5 :ʸ���ȽϷ�ʽ, ��������ģʽ
		ModePara1 =  �Ƚϵ�����
		ModePara2 =	 �ظ�����, һ�������ڱȽ�����, �������Ч״̬,�������Ч״̬.
		ModePara3 =  ���ھ���, ÿ������������Opstate, �����Ч״̬�ľ��루ModePara4����ԭΪ��Ч״̬.
		ModePara4 =	 �����Ч״̬�ľ���,  (ModePara3- ModePara4) Ϊ��Ч״̬����

Mode=6 :ʸ���ȽϷ�ʽ, ����ģʽ, ����ģʽһ����HW_TIMERһ��ʹ��.
		ModePara1 =  �Ƚϵ�����
		ModePara2 =	 �ظ�����, һ������ֻ�Ƚ�һ��
		ModePara3 =  ���ھ���, ÿ������������һ��
		ModePara4 =	 Ԥ��
Mode=7����HW_TIMERһ��ʹ��
	  ModePara1 = ��һ���Ƚϵ�VECTOR_MOVED��������TABLE���
	  ModePara2 = ���һ���Ƚϵ�VECTOR_MOVED��������TABLE���
	  ModePara3 =  Ԥ��
	  ModePara4 =	 Ԥ��
Mode=25, 26, 35,36, ��ά�ıȽ�ģʽ     25,26  2D�Ƚ�ģʽ      35,36 3D�Ƚ�ģʽ
	  ModePara1 = �Ƚ�λ��ÿ�������ҵ�����ƫ�����ƫ�Χ��ʼ�Ƚ�
	  ModePara2 = table����洢�ıȽϵ����
	  ModePara3 = ��һ���Ƚϵ���������table���
	  ModePara4 =  Ԥ��

��̬�޸�HW_TIMER������ʹ��ǰ��ǰ��HW_TIMER
		HwTimerOpenTime		��Чʱ�䣬us��λ
		HwTimerCycTime		����ʱ�䣬us��λ
		HwTimerReptimes		�ظ�����

Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveHwPswitch2(ZMC_HANDLE handle,int Axisnum,int Mode, int Opnum , int Opstate, float ModePara1, float ModePara2,float ModePara3,float ModePara4,float HwTimerOpenTime,float HwTimerCycTime,int HwTimerReptimes);


/*************************************************************
Description:    //�����϶����
Input:          //������handle  
				iaxis ���
				fdistance ����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_Backlash(ZMC_HANDLE handle, int iaxis, bool enable,float dist,float speed,float accel);

/*************************************************************
Description:    //table��ȡ, ����һ�ζ�ȡ���
Input:          //������handle  
				tabstart	��ȡTABLE��ʼ��ַ
				numes		��ȡ������
Output:         //pfValue  ���ʱ�������ռ�.
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_GetTable2(ZMC_HANDLE handle, int tabstart, int numes, double *pdoubleValue);

/*************************************************************
Description:    //����op����ǰ�򿪻�ر�
Input:          //������handle
				nAxis					���
				uTime					��ʱʱ��
				nOpnum					������ʱ�����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_MoveOpDelay(ZMC_HANDLE handle, float uTime, int nAxis);

/*************************************************************
Description:    //����ַ����˶��·�
Input:          handle					������
				pbuffer					�˶��ַ���
				buffsize				�ַ������ش�С
				File3Name				�������ɵ�3���ļ�����
				ifile3num				3���ļ����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_DownMem3FileRam(ZMC_HANDLE handle, const char* pbuffer, uint32 buffsize,char* File3Name,int32 ifile3num);


/*************************************************************
Description:    //�����·����ļ�
Input:          handle					������
				ifile3num				3���ļ����
				itasknum				�˶������
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Run3FileRam(ZMC_HANDLE handle,int32 ifile3num ,int32 itasknum);


/*************************************************************
Description:    // ��̬����3���ļ�, ��ȡ��д�Ŀռ�.
Input:          //������handle
				ifile3num				3���ļ����
Output:         // //premainbyte	ʣ��ؼ��ֽ���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_3FileRamGetRemainSpace(ZMC_HANDLE handle,int32 ifile3num, uint32 *premainbyte);


/*************************************************************
Description:    // ��̬����3���ļ�, ��������,
Input:          //������handle,  
				ifile3num				3���ļ����
				File3Name			����3���ļ���.3���ļ������Զ�����, �����ZAux_Run3FileRam����.
Output:         //premainbyte	ʣ��ؼ��ֽ���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_3FileRamDownBegin(ZMC_HANDLE handle, int32 ifile3num,uint32 *premainbyte,char*File3Name);

/*************************************************************
Description:    // ��̬����3���ļ�, һ�����ص����ݱ����������ĵ��л����,û���������ʱ, ������\n��β, ȫ���������ʱ, ��\0��β
								\0�ᵼ���������, ��Ҫ�����������ٴε���ZMC_Run3FileRam
Input:          //������handle
				ifile3num				3���ļ����
				pbuffer					�ļ��ַ���
				buffsize				�ַ�������
Output:         //premainbyte	ʣ��ؼ��ֽ���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_3FileRamDownPart(ZMC_HANDLE handle,int32 ifile3num, const char* pbuffer, uint32 buffsize, uint32 *premainbyte);


/*************************************************************
Description:    // ��̬����3���ļ�, ���ؽ���, �Զ���\0, ���ҵ��ú��ٴε��� ZMC_3FileRamDownPart �᷵�ش���.
Input:          //������handle
				ifile3num				3���ļ����
Output:         //ʣ��ؼ��ֽ���
Return:         //������
*************************************************************/
int32 __stdcall ZAux_3FileRamDownEnd(ZMC_HANDLE handle,int32 ifile3num);



/*************************************************************
Description:    //����3���ļ���RAM
Input:          //������handle �ļ���, ������3���ļ�
				pfilename			3���ļ�����
				pfilenameinControl  ֧��NC�ļ���, ���������, �����޷�����bas����NC�ļ�
				ifile3num				3���ļ����
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Down3FileRam(ZMC_HANDLE handle, const char* pfilename, const char* pfilenameinControl,int32 ifile3num);

/*************************************************************
Description:    //���ò岹�˶�OP��ǰ����
Input:          //������handle  
					iaxis ���
Output:         //fValue ,MOVE_OP��ǰ�����������, ȱʡ0����Ч, �����������ȱʡ���λ����ǰָ��ʸ������, ���ø������Ӻ�ָ��ʸ������.
Return:         //������
*************************************************************/
int32 __stdcall ZAux_Direct_SetMoveOPAdist(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //ZPJ��Ŀ�ļ�����ZAR�������ص�����������
Input:          //������handle
Input:          //ZpjName ZPJ�ļ�·��
Input:          //ZarName Zar�ļ�·��
Input			//pPass �������, ��APP_PASS  û������ʱpPass = NULL
Input			//uid �󶨿�����ΨһID�� 0-����
Input:          //���ص�RAM-ROM  0-RAM  1-ROM
Output:         //
Return:         //������
*************************************************************/
int32 __stdcall ZAux_ZpjDown(ZMC_HANDLE handle,const char *ZpjName,const char *ZarName,const  char *pPass, uint32 uid,uint32 run_mode);




/// <summary>
/// ��ļӼ���������������  20220107����.
/// </summary>
/// <param name="handle">���</param>
/// <param name="axis">����</param>
/// <param name="mode">[0- ȱʡֵ, ʹ��sramp������S����],
/// [ 6- ��������SS����, �Ӽ��ٶ���������������,SSģʽ��T�μ��ٻ�����87%�ļ���ʱ�䡣��ģʽ����ʱʹ��0ģʽ, ��������С�߶β岹],
/// [7- ��������,SS����, �Ӽ��ٶ��������������͡���̬�޸�������������岹���ܵ��¼Ӽ��ٶ��޷���������ʱ���л���0ģʽ����˽���SRAMPҲ���ú���ֵ],
/// [4-20220416����,��ʱ�����ٶ�, �ﵽ�����ʱ���ٶȽ���Ϊ0]</param>
/// <returns></returns>
int32 __stdcall ZAux_SetVpMode(ZMC_HANDLE handle, uint axis, uint mode);



/// <summary>
/// ��ľ�׼���op����
/// </summary>
/// <param name="handle">���</param>
/// <param name="axis">���</param>
/// <param name="mode">ģʽ:\
bit0��1-VP_SPEEDȱʡʹ�ò岹�ٶȣ�0-VP_SPEED ʹ�õ�����ٶ�\
bit1��1 - ʹ��MOVE_OP��ȷ������ܣ� 0 - MOVE_OPԭ���ķ�ʽ\
bit4��1 - �Դ����������ܵ��ᣬʹ�ñ�����λ�õ�MOVE_OP��׼��ʽ\
�����������岹ʱ��ʹ��BASE�˶����������</param>
/// <returns></returns>
int32 __stdcall ZAux_SetAxisZset(ZMC_HANDLE handle, uint axis, uint mode);


/// <summary>
/// ����������ɨ��
/// </summary>
/// <param name="handle">���</param>
/// <param name="slotNumber">��λ��</param>
/// <param name="retStr">����������ɺ󷵻ص��ַ�����</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_SlotScan(ZMC_HANDLE handle,uint slotNumber);

/// <summary>
/// ���߿���
/// </summary>
/// <param name="handle">���</param>
/// <param name="slotNumber">��λ��</param>
/// <param name="retStr">����������ɺ󷵻ص��ַ�����</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_SlotStart(ZMC_HANDLE handle, uint slotNumber);

/// <summary>
/// ����ֹͣ
/// </summary>
/// <param name="handle">���</param>
/// <param name="slotNumber">��λ��</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_SlotStop(ZMC_HANDLE handle, uint slotNumber);




/// <summary>
/// ��ȡ����ϵͳ���
/// </summary>
/// <param name="handle">���</param>
/// <param name="code">[0- �����������]��[1-֧�ֵ������]��[2-�����������]��[3-�����������]��[4- ����ģ������AIN]��[5-����ģ�����AOUT]��[6-PWM����]�� [7- BASIC���������������ж�����]��[8-���߲�λ��]��[9-3���ļ�����]��[10-����������]��[11-����������]��[12-�����Զ���������0-��֧��]�� [13-���绥����������0-��֧�֣� ���Ӷ�����֧�֣�]��[14-FLASH����]��[15-FLASH���С]��[16-VR����]�� [17-MODBUS_BIT����]��[18-MODBUS_REG����]��[19-��ʱ������]��[20-����ռ�]��[21-������������������ӦPLC��X�Ĵ�������]��[22-������������������ӦPLC��Y�Ĵ�������]��[23-�������AIN����]��[24-�������AOUT����]��[25-PLC������]��[26-PLC S�Ĵ���]��[27-PLC V�Ĵ���]��[28-PLC Z�Ĵ���]�� [29-PLC L�Ĵ���]��[30-HMI����������������HMI�뱾��HMI��]��[31-�����Դ�HMI����]</param>
/// <param name="value">��ȡ����ϵͳֵ</param>
/// <returns></returns>
int32 __stdcall ZAux_GetSysZfeature(ZMC_HANDLE handle,uint code,uint &value);



/// <summary>
///  ����ͨѶ��������
/// </summary>
/// <param name="handle">���</param>
/// <param name="value">ֵ</param>
/// <returns></returns>
int32 __stdcall ZAux_SetServoPeriod(ZMC_HANDLE handle,uint value);
/// <summary>
/// ����ͨѶ���ڻ�ȡ
/// </summary>
/// <param name="handle">���</param>
/// <param name="value">ֵ</param>
/// <returns></returns>
int32 __stdcall ZAux_GetServoPeriod(ZMC_HANDLE handle, uint &value);


/// <summary>
/// �豸�������ȡ
/// </summary>
/// <param name="handle">���</param>
/// <param name="slot">��λ��</param>
/// <param name="node">�ڵ�</param>
/// <param name="axisNumber">�������</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_GetNodeAxisCount(ZMC_HANDLE handle,uint slot,uint node,uint&axisNumber);

/// <summary>
/// ������PDO
/// </summary>
/// <param name="handle">���</param>
/// <param name="axis">��</param>
/// <param name="mode">pdoģʽ</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_SetDriveProfile(ZMC_HANDLE handle,uint axis,int mode);



/// <summary>
/// ��ȡ��PDO����
/// </summary>
/// <param name="handle">���</param>
/// <param name="axis">��</param>
/// <param name="mode">��ȡ��ģʽ</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_GetDriveProfile(ZMC_HANDLE handle, uint axis,int & mode);


/// <summary>
/// ӳ��������Io����ʼ���
/// </summary>
/// <param name="handle">���</param>
/// <param name="axis">��</param>
/// <param name="IoStart">io��ʼ���</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_SetDriveIO(ZMC_HANDLE handle, uint axis,uint IoStart);

/// <summary>
/// ��ȡӳ���������Io����ʼ���
/// </summary>
/// <param name="handle">���</param>
/// <param name="axis">��</param>
/// <param name="IoStart">io��ʼ���</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_GetDriveIO(ZMC_HANDLE handle, uint axis, uint &IoStart);

/// <summary>
/// ���ýڵ��豸��IO��ʼλ��
/// </summary>
/// <param name="handle">���</param>
/// <param name="slot">��</param>
/// <param name="node">�ڵ�</param>
/// <param name="IoStart">io��ʼ���</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_SetNodeIo(ZMC_HANDLE handle, uint slot, uint node, uint IoStart);


/// <summary>
/// ��ȡ�ڵ��豸��IO��ʼλ��
/// </summary>
/// <param name="handle">���</param>
/// <param name="slot">��</param>
/// <param name="node">�ڵ�</param>
/// <param name="IoStart">io��ʼ���</param>
/// <returns></returns>
int32 __stdcall ZAux_BusCmd_GetNodeIo(ZMC_HANDLE handle, uint slot, uint node, uint &IoStart);


/// <summary>
/// �����  һͣ�࣬�Ѽ���������Ϊһ�飬�������澯���ر����ڵ�����ʹ��(ECAT��Ʒ֧��)�����������������塣
/// </summary>
/// <param name="handle">���</param>
/// <param name="axisNumber">����</param>
/// <param name="axisList">���б�����</param>
/// <returns></returns>
int32 __stdcall ZAux_Direct_DisableGroup(ZMC_HANDLE handle,uint axisNumber ,uint* axisList);


/// <summary>
/// ���������������ʹ�ܡ�ʹ��EtherCAT����ʱ������ʹWDOG = 1��
/// </summary>
/// <param name="handle">���</param>
/// <param name="b">�Ƿ�ʹ��</param>
/// <returns></returns>
int32 __stdcall ZAux_Direct_SetWdog(ZMC_HANDLE handle, bool b);

/// <summary>
/// ��ȡ�����������ʹ��
/// </summary>
/// <param name="handle">���</param>
/// <param name="b">�Ƿ�ʹ��</param>
/// <returns></returns>
int32 __stdcall ZAux_Direct_GetWdog(ZMC_HANDLE handle, bool &b);


/// <summary>
/// �˶��е���
/// </summary>
/// <param name="handle">���</param>
/// <param name="baseAxis">����</param>
/// <param name="iaxisNumber">�����������</param>
/// <param name="iaddaxisList">��������б�</param>
/// <returns></returns>
int32 __stdcall ZAux_Direct_MoveAddax(ZMC_HANDLE handle, int baseAxis, uint iaxisNumber, int* iaddaxisList);




/// <summary>
/// �ռ�Բ�������˶� + �����岹�˶� 20130901 �Ժ�Ŀ������汾֧��
/// </summary>
/// <param name="handle">������handle</param>
/// <param name="imaxaxises">�����˶�������</param>
/// <param name="piAxislist">����б�</param>
/// <param name="fend1">��1�����˶��������1	����λ��</param>
/// <param name="fend2">��2�����˶��������1	����λ��</param>
/// <param name="fend3">��3�����˶��������1	����λ��</param>
/// <param name="fcenter1"> ��1�����˶��������2	����λ��</param>
/// <param name="fcenter2">��2�����˶��������2	����λ��</param>
/// <param name="fcenter3">��3�����˶��������2 ����λ��</param>
/// <param name="imode">ָ��ǰ�����������  0 ��ǰ�㣬�м�㣬�յ����㶨Բ�����������1Ϊ�յ����λ�ã��������2Ϊ�м�����λ�á�\
						1 ����С��Բ�����������1Ϊ�յ���룬�������2ΪԲ�ĵľ���λ�á�\
						2 ��ǰ�㣬�м�㣬�յ����㶨Բ���������1Ϊ�յ����λ�ã��������2Ϊ�м�����λ�á�\
						3 ������С��Բ�����ټ���������Բ���������1Ϊ�յ����λ�ã��������2ΪԲ�ĵľ���λ�á�</param>
/// <param name="fcenter4">��4�����˶�����λ��</param>
/// <param name="fcenter5">��5�����˶�����λ��</param>
/// <returns>������</returns>
int32 __stdcall ZAux_Direct_MSphericalAbs(ZMC_HANDLE handle, int imaxaxises, int* piAxislist, float fend1, float fend2, float fend3, float fcenter1, float fcenter2, float fcenter3, int imode, float fcenter4, float fcenter5);


/// <summary>
/// //�ռ�Բ������ + ���� �岹SP�˶� 20130901 �Ժ�Ŀ������汾֧��
/// </summary>
/// <param name="handle">������handle</param>
/// <param name="imaxaxises">�����˶�������</param>
/// <param name="piAxislist">����б�</param>
/// <param name="fend1">��1�����˶��������1	����λ��</param>
/// <param name="fend2">��2�����˶��������1	����λ��</param>
/// <param name="fend3">��3�����˶��������1	����λ��</param>
/// <param name="fcenter1">��1�����˶��������2	����λ��</param>
/// <param name="fcenter2">��2�����˶��������2	����λ��</param>
/// <param name="fcenter3"> ��3�����˶��������2 ����λ��</param>
/// <param name="imode">ָ��ǰ�����������:0 ��ǰ�㣬�м�㣬�յ����㶨Բ�����������1Ϊ�յ����λ�ã��������2Ϊ�м�����λ�á�\
						1 ����С��Բ�����������1Ϊ�յ����λ�ã��������2ΪԲ�ĵľ���λ�á�\
						2 ��ǰ�㣬�м�㣬�յ����㶨Բ���������1Ϊ�յ����λ�ã��������2Ϊ�м�����λ�á�\
						3 ������С��Բ�����ټ���������Բ���������1Ϊ�յ����λ�ã��������2ΪԲ�ĵľ���λ�á�</param>
/// <param name="fcenter4">��4�����˶�������� ����λ��</param>
/// <param name="fcenter5">��5�����˶�������� ����λ��</param>
/// <returns></returns>
int32 __stdcall ZAux_Direct_MSphericalAbsSp(ZMC_HANDLE handle, int imaxaxises, int* piAxislist, float fend1, float fend2, float fend3, float fcenter1, float fcenter2, float fcenter3, int imode, float fcenter4, float fcenter5);




#ifdef __cplusplus  
}  
#endif 


#endif











