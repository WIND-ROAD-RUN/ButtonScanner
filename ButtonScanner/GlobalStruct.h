#pragma once

#include<memory>

#include"scc_Motion.h"

#include"ime_ModelEngine.h"

namespace zwy {
    namespace scc {
        class Motion;
        
    }
}


class GlobalStruct
{
public:
    std::unique_ptr<zwy::scc::Motion> motionPtr;

    std::unique_ptr<rw::ime::ModelEngine> modelEnginePtr1;

    std::unique_ptr<rw::ime::ModelEngine> modelEnginePtr2;

    std::unique_ptr<rw::ime::ModelEngine> modelEnginePtr3;

    std::unique_ptr<rw::ime::ModelEngine> modelEnginePtr4;

   
public:
    static GlobalStruct& getInstance()
    {
        static GlobalStruct instance;
        return instance;
    }

    GlobalStruct(const GlobalStruct&) = delete;
    GlobalStruct& operator=(const GlobalStruct&) = delete;

private:
    GlobalStruct();
    ~GlobalStruct() = default;

};