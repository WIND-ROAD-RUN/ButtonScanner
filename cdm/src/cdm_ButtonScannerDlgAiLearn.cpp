#include"cdm_ButtonScannerDlgAiLearn.h"

namespace rw
{
	namespace cdm
	{
		ButtonScannerDlgAiLearn::ButtonScannerDlgAiLearn(const rw::oso::ObjectStoreAssembly& assembly)
		{
			auto isAccountAssembly = assembly.getName();
			if (isAccountAssembly != "$class$ButtonScannerDlgAiLearn$")
			{
				throw std::runtime_error("Assembly is not $class$ButtonScannerDlgAiLearn$");
			}

			auto checkTypeItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$checkType$"));
			if (!checkTypeItem) {
				throw std::runtime_error("$variable$checkType is not found");
			}
			checkType = checkTypeItem->getValueAsInt();

			auto learnInfoSignItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$learnInfoSign$"));
			if (!learnInfoSignItem) {
				throw std::runtime_error("$variable$learnInfoSign is not found");
			}
			learnInfoSign = learnInfoSignItem->getValueAsString();
		}

		ButtonScannerDlgAiLearn::ButtonScannerDlgAiLearn(
			const ButtonScannerDlgAiLearn& buttonScannerMainWindow)
		{
			checkType = buttonScannerMainWindow.checkType;
			learnInfoSign = buttonScannerMainWindow.learnInfoSign;
		}

		ButtonScannerDlgAiLearn& ButtonScannerDlgAiLearn::operator=(const ButtonScannerDlgAiLearn& buttonScannerMainWindow)
		{
			if (this != &buttonScannerMainWindow) {
				checkType = buttonScannerMainWindow.checkType;
				learnInfoSign = buttonScannerMainWindow.learnInfoSign;
			}
			return *this;
		}

		ButtonScannerDlgAiLearn::operator rw::oso::ObjectStoreAssembly() const
		{
			rw::oso::ObjectStoreAssembly assembly;
			assembly.setName("$class$ButtonScannerDlgAiLearn$");

			auto checkTypeItem = std::make_shared<oso::ObjectStoreItem>();
			checkTypeItem->setName("$variable$checkType$");
			checkTypeItem->setValueFromInt(checkType);
			assembly.addItem(checkTypeItem);

			auto learnInfoSignItem = std::make_shared<oso::ObjectStoreItem>();
			learnInfoSignItem->setName("$variable$learnInfoSign$");
			learnInfoSignItem->setValueFromString(learnInfoSign);
			assembly.addItem(learnInfoSignItem);

			return assembly;
		}

		bool ButtonScannerDlgAiLearn::operator==(const ButtonScannerDlgAiLearn& account) const
		{
			return (checkType == account.checkType) &&
				(learnInfoSign == account.learnInfoSign);
		}
		bool ButtonScannerDlgAiLearn::operator!=(const ButtonScannerDlgAiLearn& account) const
		{
			return !(*this == account);
		}
	}
}
