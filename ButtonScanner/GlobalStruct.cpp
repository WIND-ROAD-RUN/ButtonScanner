#include "stdafx.h"

#include "GlobalStruct.h"


GlobalStruct::GlobalStruct()
{
    motionPtr = std::make_unique<zwy::scc::Motion>();
    //�����ʼ��ZMotion�Լ���ز���
}
