﻿#ifndef MOTION_H
#define MOTION_H
#include<QString>
#include"zauxdll2.h"
#include"zmotion.h"


namespace zwy {
    namespace scc {
        class Motion
        {
        public:
            Motion();

            //打开控制器
            bool OpenBoard(char* ipAdress);
            //关闭板卡
            void CloseBoared();
            //    //获取板卡连接状态
            //    bool GetBoardStatue( );
                //设置轴的类型
            void SetAxisType(int axis, int value);
            //设置ModBus的类型
            void  SetModbus(uint16 adress, uint16 num, uint8 value);

            //设置轴的脉冲当量
            void SetAxisPulse(int axis, float value);
            //  设置轴运动速度
            void SetAxisRunSpeed(int axis, float value);
            //  设置轴运动加速度
            void SetAxisAcc(int axis, float value);
            //  设置轴运动减速度
            void SetAxisDec(int axis, float value);
            //获取当前轴的位置
             //  设置轴运动
            void AxisRun(int axis, float value);
            //返回轴的参数
            void GetAxisLocation(int axis, float& value);
            //获取输入IO状态
            bool GetIOIn(int portNum);
            //获取输出IO状态
            bool GetIOOut(int portNum);
            //获取输入IO状态
            bool GetAllIOIN(int portNum);
            //设置输出IO状态
            void SetIOOut(int portNum, bool state);
            //单轴停止运动
            void Single_Stop(int axis);
            //停止所有轴
            void StopAllAxis();
            //单轴运动
            void Single_Move(int axis, int dir, float speed = 20, float acc = 1000, float dec = 1000, float units = 0);
            //单轴运动
            void Single_Move(int axis, double dir);
            //轴位置清零
            void SetLocationZero(int axis);
            //获取板卡状态
            bool getBoardState();
            //获取板卡状态
            float getAxisSpeed(int axis);
            //设置io
            void SetIOOut(int axis, int ioNUm, bool state, int iotime);

            void  SetModbus(uint16 adress, uint16 num, float value);
            void  GetModbus(uint16 adress, uint16 num, float& value);
            bool isOPen;

        private:
            ZMC_HANDLE g_handle = NULL;


        };
    
    }
}



#endif // MOTION_H
