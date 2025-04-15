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
		class ButtonScannerDlgAiLearnRefactor
		{
		public:
			ButtonScannerDlgAiLearnRefactor() = default;
			~ButtonScannerDlgAiLearnRefactor() = default;

			ButtonScannerDlgAiLearnRefactor(const rw::oso::ObjectStoreAssembly& assembly);
			ButtonScannerDlgAiLearnRefactor(const ButtonScannerDlgAiLearnRefactor& buttonScannerMainWindow);

			ButtonScannerDlgAiLearnRefactor& operator=(const ButtonScannerDlgAiLearnRefactor& buttonScannerMainWindow);
			operator rw::oso::ObjectStoreAssembly() const;
			bool operator==(const ButtonScannerDlgAiLearnRefactor& account) const;
			bool operator!=(const ButtonScannerDlgAiLearnRefactor& account) const;

		public:
			int checkType{ 1 };
			std::string  learnInfoSign;


		public:
			void Save();
			static ButtonScannerDlgAiLearnRefactor* GetNew(int checkType);
			static ButtonScannerDlgAiLearnRefactor* ReadConfig(std::string path);
			static ButtonScannerDlgAiLearnRefactor* ReadLastConfig();

		};
	}
}