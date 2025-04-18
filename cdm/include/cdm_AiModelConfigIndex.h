#pragma once

#include<string>
#include<vector>

#include"cdm_AiModelConfig.h"

namespace rw {
	namespace oso {
		class ObjectStoreAssembly;
	}
}

namespace rw
{
	namespace cdm
	{
		struct ConfigIndexItem
		{
		public:
			std::string root_path{};
			std::string model_name{};
			ModelType model_type{ModelType::Undefined};
			long id;
		public:
			ConfigIndexItem() = default;
			~ConfigIndexItem() = default;

			ConfigIndexItem(const ConfigIndexItem& item);
			ConfigIndexItem(const rw::oso::ObjectStoreAssembly& assembly);
			ConfigIndexItem& operator=(const ConfigIndexItem& item) = default;
			operator rw::oso::ObjectStoreAssembly() const;

			bool operator==(const ConfigIndexItem& item) const;
			bool operator!=(const ConfigIndexItem& item) const;
		};

		class AiModelConfigIndex
		{
		public:
			AiModelConfigIndex() = default;
			~AiModelConfigIndex() = default;
			AiModelConfigIndex(const rw::oso::ObjectStoreAssembly& assembly);
			AiModelConfigIndex(const AiModelConfigIndex& buttonScannerMainWindow);
			AiModelConfigIndex& operator=(const AiModelConfigIndex& buttonScannerMainWindow);
			operator rw::oso::ObjectStoreAssembly() const;
			bool operator==(const AiModelConfigIndex& account) const;
			bool operator!=(const AiModelConfigIndex& account) const;
		public:
			std::vector<ConfigIndexItem> modelIndexs;
		};




	}
}
