#include "cdm_ButtonScannerDlgProductSet.h"
#include"oso_core.h"

rw::cdm::ButtonScannerDlgProductSet::ButtonScannerDlgProductSet(const rw::oso::ObjectStoreAssembly& assembly)
{
    auto isAccountAssembly = assembly.getName();
    if (isAccountAssembly != "$class$ButtonScannerDlgProductSet$")
    {
        throw std::runtime_error("Assembly is not $class$ButtonScannerDlgProductSet$");
    }

    auto outsideDiameterEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$outsideDiameterEnable$"));
    if (!outsideDiameterEnableItem) {
        throw std::runtime_error("$variable$outsideDiameterEnable is not found");
    }
	outsideDiameterEnable = outsideDiameterEnableItem->getValueAsBool();

	auto outsideDiameterValueEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$outsideDiameterEnable$"));
	if (!outsideDiameterEnableItem) {
		throw std::runtime_error("$variable$outsideDiameterEnable is not found");
	}
	outsideDiameterEnable = outsideDiameterEnableItem->getValueAsBool();

	auto outsideDiameterEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$outsideDiameterEnable$"));
	if (!outsideDiameterEnableItem) {
		throw std::runtime_error("$variable$outsideDiameterEnable is not found");
	}
	outsideDiameterEnable = outsideDiameterEnableItem->getValueAsBool();
	bool outsideDiameterEnable{ false };
	double outsideDiameterValue{ 0 };
	double outsideDiameterDeviation{ 0 };

	double photography{ 0 };
	double blowTime{ 0 };

	bool edgeDamageEnable{ false };
	double edgeDamageSimilarity{ false };

	bool shieldingRangeEnable{ false };
	double outerRadius{ 0 };
	double innerRadius{ 0 };

	bool poreEnable{ false };
	bool paintEnable{ false };

	bool holesCountEnable{ false };
	double holesCountValue{ 0 };

	bool brokenEyeEnable{ false };
	double brokenEyeSimilarity{ 0 };

	bool crackEnable{ false };
	double crackSimilarity{ 0 };

	bool apertureEnable{ false };
	double apertureValue{ 0 };
	double apertureSimilarity{ 0 };

	bool holeCenterDistanceEnable{ false };
	double holeCenterDistanceValue{ 0 };
	double holeCenterDistanceSimilarity{ 0 };

	bool specifyColorDifferenceEnable{ false };
	double specifyColorDifferenceR{ 0 };
	double specifyColorDifferenceG{ 0 };
	double specifyColorDifferenceB{ 0 };
	double specifyColorDifferenceDeviation{ 0 };

	bool largeColorDifferenceEnable{ false };
	double largeColorDifferenceDeviation{ 0 };

	bool grindStoneEnable{ false };
	bool blockEyeEnable{ false };
	bool materialHeadEnable{ false };
}

rw::cdm::ButtonScannerDlgProductSet::ButtonScannerDlgProductSet(const ButtonScannerDlgProductSet& buttonScannerMainWindow)
{
}

rw::cdm::ButtonScannerDlgProductSet& rw::cdm::ButtonScannerDlgProductSet::operator=(const ButtonScannerDlgProductSet& buttonScannerMainWindow)
{
	// TODO: 在此处插入 return 语句
}

rw::cdm::ButtonScannerDlgProductSet::operator rw::oso::ObjectStoreAssembly() const
{
}

bool rw::cdm::ButtonScannerDlgProductSet::operator==(const ButtonScannerDlgProductSet& account) const
{
	return false;
}

bool rw::cdm::ButtonScannerDlgProductSet::operator!=(const ButtonScannerDlgProductSet& account) const
{
	return false;
}
