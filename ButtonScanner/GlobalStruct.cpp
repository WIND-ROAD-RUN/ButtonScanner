#include "stdafx.h"

#include "GlobalStruct.h"


GlobalStruct::GlobalStruct()
{
    //文件路径记得修改
    std::string enginePath = R"(C:\Users\34615\Desktop\best.engine)";
    std::string namePath = R"(C:\Users\34615\Desktop\index.names)";
    modelEnginePtr = std::make_unique<rw::ime::ModelEngine>(enginePath,namePath);
    motionPtr = std::make_unique<zwy::scc::Motion>();
    //这里初始化ZMotion以及相关操作
}
