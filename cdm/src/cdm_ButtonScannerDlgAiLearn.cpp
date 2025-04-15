#include"cdm_ButtonScannerDlgAiLearn.h"

namespace rw
{
	namespace cdm
	{
		ButtonScannerDlgAiLearnRefactor::ButtonScannerDlgAiLearnRefactor(const rw::oso::ObjectStoreAssembly& assembly)
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

		ButtonScannerDlgAiLearnRefactor::ButtonScannerDlgAiLearnRefactor(
			const ButtonScannerDlgAiLearnRefactor& buttonScannerMainWindow)
		{
			checkType = buttonScannerMainWindow.checkType;
			learnInfoSign = buttonScannerMainWindow.learnInfoSign;
		}

		ButtonScannerDlgAiLearnRefactor& ButtonScannerDlgAiLearnRefactor::operator=(const ButtonScannerDlgAiLearnRefactor& buttonScannerMainWindow)
		{
			if (this != &buttonScannerMainWindow) {
				checkType = buttonScannerMainWindow.checkType;
				learnInfoSign = buttonScannerMainWindow.learnInfoSign;
			}
			return *this;
		}

		ButtonScannerDlgAiLearnRefactor::operator rw::oso::ObjectStoreAssembly() const
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

		bool ButtonScannerDlgAiLearnRefactor::operator==(const ButtonScannerDlgAiLearnRefactor& account) const
		{
			return (checkType == account.checkType) &&
				(learnInfoSign == account.learnInfoSign);
		}
		bool ButtonScannerDlgAiLearnRefactor::operator!=(const ButtonScannerDlgAiLearnRefactor& account) const
		{
			return !(*this == account);
		}
	}
}
