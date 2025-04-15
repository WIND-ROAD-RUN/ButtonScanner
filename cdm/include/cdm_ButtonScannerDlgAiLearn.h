#pragma once
#include "oso_StorageContext.hpp"
#include <string>

namespace rw {
	namespace oso {
		class ObjectStoreAssembly;
	}
}
namespace rw
{
	namespace cdm {
		class ButtonScannerDlgAiLearn
		{
		public:
			ButtonScannerDlgAiLearn() = default;
			~ButtonScannerDlgAiLearn() = default;

			ButtonScannerDlgAiLearn(const rw::oso::ObjectStoreAssembly& assembly);
			ButtonScannerDlgAiLearn(const ButtonScannerDlgAiLearn& buttonScannerMainWindow);

			ButtonScannerDlgAiLearn& operator=(const ButtonScannerDlgAiLearn& buttonScannerMainWindow);
			operator rw::oso::ObjectStoreAssembly() const;
			bool operator==(const ButtonScannerDlgAiLearn& account) const;
			bool operator!=(const ButtonScannerDlgAiLearn& account) const;

		public:
			int checkType{ 1 };
			std::string  learnInfoSign{"undefined"};
			bool upLight{ false };
			bool downLight{ false };
			bool sideLight{ false };
		};
	}
}