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

			auto upLightItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$upLight$"));
			if (!upLightItem) {
				throw std::runtime_error("$variable$upLight is not found");
			}
			upLight = upLightItem->getValueAsBool();

			auto downLightItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$downLight$"));
			if (!downLightItem) {
				throw std::runtime_error("$variable$downLight is not found");
			}
			downLight = downLightItem->getValueAsBool();

			auto sideLightItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$sideLight$"));
			if (!sideLightItem) {
				throw std::runtime_error("$variable$sideLight is not found");
			}
			sideLight = sideLightItem->getValueAsBool();
		}

		ButtonScannerDlgAiLearn::ButtonScannerDlgAiLearn(
			const ButtonScannerDlgAiLearn& buttonScannerMainWindow)
		{
			checkType = buttonScannerMainWindow.checkType;
			learnInfoSign = buttonScannerMainWindow.learnInfoSign;
			upLight = buttonScannerMainWindow.upLight;
			downLight = buttonScannerMainWindow.downLight;
			sideLight = buttonScannerMainWindow.sideLight;
		}

		ButtonScannerDlgAiLearn& ButtonScannerDlgAiLearn::operator=(const ButtonScannerDlgAiLearn& buttonScannerMainWindow)
		{
			if (this != &buttonScannerMainWindow) {
				checkType = buttonScannerMainWindow.checkType;
				learnInfoSign = buttonScannerMainWindow.learnInfoSign;
				upLight = buttonScannerMainWindow.upLight;
				downLight = buttonScannerMainWindow.downLight;
				sideLight = buttonScannerMainWindow.sideLight;
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

			auto upLightItem = std::make_shared<oso::ObjectStoreItem>();
			upLightItem->setName("$variable$upLight$");
			upLightItem->setValueFromBool(upLight);
			assembly.addItem(upLightItem);

			auto downLightItem = std::make_shared<oso::ObjectStoreItem>();
			downLightItem->setName("$variable$downLight$");
			downLightItem->setValueFromBool(downLight);
			assembly.addItem(downLightItem);

			auto sideLightItem = std::make_shared<oso::ObjectStoreItem>();
			sideLightItem->setName("$variable$sideLight$");
			sideLightItem->setValueFromBool(sideLight);
			assembly.addItem(sideLightItem);

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
