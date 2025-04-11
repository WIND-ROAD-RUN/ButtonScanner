#pragma once  

#include <string>  
 

struct PathGlobalStruct
{
	static inline std::string AiLearn = R"(AiLearn)";  
	static inline std::string AiLearnYoloDataYaml = R"(AiLearn\data.yaml)";
	static inline std::string AiLearnConfig = R"(AiLearn\AiLearnConfig)";
	static inline std::string AiLearnImage= R"(AiLearn\Images)";
	static inline std::string AiLearnData = R"(AiLearn\Datas)";
	static inline std::string AiLearnDataBad = R"(Bad)";
	static inline std::string AiLearnDataGood = R"(Good)";
	static inline std::string AiLearnDataTranImages = R"(tran\images)";
	static inline std::string AiLearnDataValImages = R"(val\images)";
	static inline std::string AiLearnDataTranLabel = R"(tran\labels)";
	static inline std::string AiLearnDataValLabel = R"(val\labels)";
};
