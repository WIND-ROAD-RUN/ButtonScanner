#include "stdafx.h"

#include "GlobalStruct.h"


GlobalStruct::GlobalStruct()
{
    motionPtr = std::make_unique<zwy::scc::Motion>();
    //这里初始化ZMotion以及相关操作
}
