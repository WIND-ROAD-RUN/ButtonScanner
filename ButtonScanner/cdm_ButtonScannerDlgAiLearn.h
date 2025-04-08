#pragma once
#include "oso_StorageContext.hpp"
#include <string>
//#include <QDir>
//#include <QString>
//#include <QFileInfo>
//#include <QFile>
//#include <QIODevice>

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
			/// <summary>
			/// 1:¼ì²âÑÕÉ«£¬2:¼ì²âµ¶ÐÍ
			/// </summary>
			int checkType{ 1 };
			std::string  learnInfoSign;
			
		
		public:
			void Save();
			static ButtonScannerDlgAiLearn* GetNew(bool checkType);
			static ButtonScannerDlgAiLearn* ReadConfig(std::string path);
			static ButtonScannerDlgAiLearn* ReadLastConfig();
			
		};
	}
}