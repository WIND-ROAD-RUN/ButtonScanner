#include "stdafx.h"
#include "cdm_ButtonScannerDlgAiLearn.h"
#include"oso_core.h"
#include <qdir.h>

rw::cdm::ButtonScannerDlgAiLearn::ButtonScannerDlgAiLearn(const rw::oso::ObjectStoreAssembly& assembly)
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
	learnInfoSign = learnInfoSignItem->getValueAsInt();
}

rw::cdm::ButtonScannerDlgAiLearn::ButtonScannerDlgAiLearn(const ButtonScannerDlgAiLearn& buttonScannerMainWindow)
{
	checkType = buttonScannerMainWindow.checkType;
}

rw::cdm::ButtonScannerDlgAiLearn& rw::cdm::ButtonScannerDlgAiLearn::operator=(const ButtonScannerDlgAiLearn& buttonScannerMainWindow)
{
	if (this != &buttonScannerMainWindow) {
		checkType = buttonScannerMainWindow.checkType;
	}
	return *this;
}

rw::cdm::ButtonScannerDlgAiLearn::operator rw::oso::ObjectStoreAssembly() const
{
	rw::oso::ObjectStoreAssembly assembly;
	assembly.setName("$class$ButtonScannerDlgAiLearn$");

	auto checkTypeItem = std::make_shared<oso::ObjectStoreItem>();
	checkTypeItem->setName("$variable$checkType$");
	checkTypeItem->setValueFromBool(checkType);
	assembly.addItem(checkTypeItem);

	auto learnInfoSignItem = std::make_shared<oso::ObjectStoreItem>();
	learnInfoSignItem->setName("$variable$learnInfoSign$");
	learnInfoSignItem->setValueFromString(learnInfoSign);
	assembly.addItem(learnInfoSignItem);

	return assembly;
}

bool rw::cdm::ButtonScannerDlgAiLearn::operator==(const ButtonScannerDlgAiLearn& account) const
{
	return checkType == account.checkType;
}

bool rw::cdm::ButtonScannerDlgAiLearn::operator!=(const ButtonScannerDlgAiLearn& account) const
{
	return !(*this == account);
}

void rw::cdm::ButtonScannerDlgAiLearn::Save()
{
	auto _StoreContext = std::make_unique<rw::oso::StorageContext>(rw::oso::StorageType::Xml);
	_StoreContext->save(*this, "path" + learnInfoSign);
}

rw::cdm::ButtonScannerDlgAiLearn* rw::cdm::ButtonScannerDlgAiLearn::GetNew(bool checkType)
{
	auto temp = new rw::cdm::ButtonScannerDlgAiLearn();
	temp->checkType = checkType;
	temp->checkType=
}

rw::cdm::ButtonScannerDlgAiLearn* rw::cdm::ButtonScannerDlgAiLearn::ReadConfig(std::string path)
{
	auto	_StoreContext = std::make_unique<rw::oso::StorageContext>(rw::oso::StorageType::Xml);
	QDir dir;

	QString dlgAiLearnFilePath = R"(config/dlgAiLearnConfig.xml)";
	QString dlgAiLearnFilePathFull = dir.absoluteFilePath(dlgAiLearnFilePath);
	QFileInfo dlgAiLearnFile(dlgAiLearnFilePathFull);


	if (!dlgAiLearnFile.exists()) {
		QDir configDir = QFileInfo(dlgAiLearnFilePathFull).absoluteDir();
		if (!configDir.exists()) {
			configDir.mkpath(".");
		}
		QFile file(dlgAiLearnFilePathFull);
		if (file.open(QIODevice::WriteOnly)) {
			file.close();
		}

		auto config = new rw::cdm::ButtonScannerDlgAiLearn();
		config->Save();
		return config;
	}
	else {
		auto assembly = _StoreContext->load(dlgAiLearnFilePathFull.toStdString());
		if (assembly) {
			auto loadDlgAiLearnConfig=new rw::cdm::ButtonScannerDlgAiLearn(*assembly);
			return loadDlgAiLearnConfig;
		}

	}
}

rw::cdm::ButtonScannerDlgAiLearn* rw::cdm::ButtonScannerDlgAiLearn::ReadLastConfig()
{
	return nullptr;
}

