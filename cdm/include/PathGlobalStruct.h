#pragma once  

#include <string>  
 

struct PathGlobalStruct
{
	static inline std::string AiLearn = R"(AiLearn)";  
	static inline std::string AiLearnConfig = R"(AiLearn\AiLearnConfig)";
	static inline std::string AiLearnImage= R"(AiLearn\Images)";
	static inline std::string AiLearnData = R"(AiLearn\Datas)";
	static inline std::string AiLearnDataBad = R"(Bad)";
	static inline std::string AiLearnDataGood = R"(Good)";
	static inline std::string AiLearnDataTran = R"(Tran)";
	static inline std::string AiLearnDataVal = R"(Val)";
	static inline std::string AiLearnDataYoloText = R"(YoloText)";
};
