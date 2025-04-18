#include <iostream>
#include <thread>
#include <vector>
#include "dsl_PriorityQueue.hpp"
#include"cdm_AiModelConfig.h"
#include "cdm_AiModelConfigIndex.h"
#include"oso_StorageContext.hpp"

using namespace std;
using namespace rw::dsl;
using namespace rw::oso;
using namespace rw::cdm;

int main() {
	std::string path = R"(C:\Users\rw\Desktop\1\test.xml)";
	std::string path1 = R"(C:\Users\rw\Desktop\1\test1.xml)";
	StorageContext storage(StorageType::Xml);
	AiModelConfig config;
	storage.save(config, path);

	AiModelConfigIndex configIndex;
	ConfigIndexItem item;
	item.model_type = ModelType::BladeShape;
	item.model_name = "test";
	item.root_path = "asd";
	item.id = 123;
	configIndex.modelIndexs.push_back(item);
	configIndex.modelIndexs.push_back(item);
	configIndex.modelIndexs.push_back(item);
	configIndex.modelIndexs.push_back(item);
	configIndex.modelIndexs.push_back(item);
	configIndex.modelIndexs.push_back(item);
	configIndex.modelIndexs.push_back(item);

	storage.save(configIndex, path1);

	
	AiModelConfig configIndex1(*(storage.load(path).get()));

	std::cout <<(configIndex1 == config)  << std::endl;

	AiModelConfigIndex configIndex2(*(storage.load(path1).get()));
	std::cout << (configIndex2 == configIndex) << std::endl;

	return 0;
}