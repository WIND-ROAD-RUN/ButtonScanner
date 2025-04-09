#include "stdafx.h"
#include "cdm_ButtonScannerDlgAiLearn.h"
#include"oso_core.h"
#include <qdir.h>
#include <filesystem> 
#include "PathGlobalStruct.h"

namespace fs = std::filesystem;

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
	QString pathQt = QString::fromStdString(PathGlobalStruct::AiLearnConfig + "\\" + learnInfoSign);

	QFileInfo dlgAiLearnFile(pathQt);
	if (!dlgAiLearnFile.exists()) {
		QDir configDir = QFileInfo(pathQt).absoluteDir();
		if (!configDir.exists()) {
			configDir.mkpath(".");
		}
		QFile file(pathQt);
		if (file.open(QIODevice::WriteOnly)) {
			file.close();
		}
	}

	auto _StoreContext = std::make_unique<rw::oso::StorageContext>(rw::oso::StorageType::Xml);
	_StoreContext->save(*this, pathQt.toStdString());
}

rw::cdm::ButtonScannerDlgAiLearn* rw::cdm::ButtonScannerDlgAiLearn::GetNew(bool checkType)
{
	auto temp = new rw::cdm::ButtonScannerDlgAiLearn();
	temp->checkType = checkType;
	temp->learnInfoSign = QDateTime::currentDateTime().toString("yyyyMMddHHmmss").toStdString();
	temp->Save();
	return temp;
}

rw::cdm::ButtonScannerDlgAiLearn* rw::cdm::ButtonScannerDlgAiLearn::ReadConfig(std::string path)
{
	auto	_StoreContext = std::make_unique<rw::oso::StorageContext>(rw::oso::StorageType::Xml);
	QDir dir;

	/*QString dlgAiLearnFilePath = R"(config/dlgAiLearnConfig.xml)";
	QString dlgAiLearnFilePathFull = dir.absoluteFilePath(dlgAiLearnFilePath);*/

	QString pathQt = QString::fromStdString(path);

	QFileInfo dlgAiLearnFile(pathQt);
	if (!dlgAiLearnFile.exists()) {


		auto config = new rw::cdm::ButtonScannerDlgAiLearn();
		config->Save();
		return config;
	}
	else {
		auto assembly = _StoreContext->load(pathQt.toStdString());
		if (assembly) {
			auto loadDlgAiLearnConfig = new rw::cdm::ButtonScannerDlgAiLearn(*assembly);
			return loadDlgAiLearnConfig;
		}

	}
}

rw::cdm::ButtonScannerDlgAiLearn* rw::cdm::ButtonScannerDlgAiLearn::ReadLastConfig()
{
	fs::path target_dir = PathGlobalStruct::AiLearnConfig; // Correct usage of the "fs" namespace

	// ���Ŀ¼�Ƿ����
	if (!fs::exists(target_dir)) {
		std::cerr << "����: Ŀ¼�����ڡ�\n";
	}

	std::vector<fs::directory_entry> files;

	// ����Ŀ¼���ռ����г����ļ�
	for (const auto& entry : fs::directory_iterator(target_dir)) {
		// ���������ļ�����ѡ��
		std::string filename = entry.path().filename().string();
		if (filename.empty() || filename[0] == '.') {
			continue;
		}

		// �����ǳ����ļ��ҷǷ�������
		if (fs::is_regular_file(entry.status()) && !fs::is_symlink(entry.status())) {
			files.emplace_back(entry);
		}
	}

	if (files.empty()) {
		return nullptr;
	}

	// ��ȡ�ļ������ַ�������
	std::vector<std::string> filenames;
	filenames.reserve(files.size());
	for (const auto& file : files) {
		filenames.emplace_back(file.path().filename().string());
	}

	// ���ļ�����������Ĭ���ֵ�˳��
	std::sort(filenames.begin(), filenames.end());

	// ��ȡ�ֵ�˳�������ļ���
	const std::string& max_filename = filenames.back();

	// ���Ҷ�Ӧ������·��
	std::optional<fs::path> max_file_path = std::nullopt;
	for (const auto& file : files) {
		if (file.path().filename().string() == max_filename) {
			max_file_path = file.path();
			break;
		}
	}

	return ReadConfig(max_file_path.value().string());
}

