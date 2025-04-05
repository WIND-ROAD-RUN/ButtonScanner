#pragma once

#include<memory>

#include"scc_Motion.h"


namespace zwy {
    namespace scc {
        class Motion;
        
    }
}

class GlobalStruct
{
public:
    std::unique_ptr<zwy::scc::Motion> motionPtr;
   
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