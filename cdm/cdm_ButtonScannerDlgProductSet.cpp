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

	auto outsideDiameterValueItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$outsideDiameterValue$"));
	if (!outsideDiameterValueItem) {
		throw std::runtime_error("$variable$outsideDiameterValue is not found");
	}
	outsideDiameterValue = outsideDiameterValueItem->getValueAsDouble();

	auto outsideDiameterDeviationItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$outsideDiameterDeviation$"));
	if (!outsideDiameterDeviationItem) {
		throw std::runtime_error("$variable$outsideDiameterDeviation is not found");
	}
	outsideDiameterDeviation = outsideDiameterDeviationItem->getValueAsDouble();
	 
	auto photographyItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$photography$"));
	if (!photographyItem) {
		throw std::runtime_error("$variable$photography is not found");
	}
	photography = photographyItem->getValueAsDouble();

	auto blowTimeItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$blowTime$"));
	if (!blowTimeItem) {
		throw std::runtime_error("$variable$blowTime is not found");
	}
	blowTime = blowTimeItem->getValueAsDouble();

	auto edgeDamageEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$edgeDamageEnable$"));
	if (!edgeDamageEnableItem) {
		throw std::runtime_error("$variable$edgeDamageEnable is not found");
	}
	edgeDamageEnable = edgeDamageEnableItem->getValueAsBool();

	auto edgeDamageSimilarityItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$edgeDamageSimilarity$"));
	if (!edgeDamageSimilarityItem) {
		throw std::runtime_error("$variable$edgeDamageSimilarity is not found");
	}
	edgeDamageSimilarity = edgeDamageSimilarityItem->getValueAsBool();

	auto shieldingRangeEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$shieldingRangeEnable$"));
	if (!shieldingRangeEnableItem) {
		throw std::runtime_error("$variable$shieldingRangeEnable is not found");
	}
	shieldingRangeEnable = shieldingRangeEnableItem->getValueAsBool();

	auto outerRadiusItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$outerRadius$"));
	if (!outerRadiusItem) {
		throw std::runtime_error("$variable$outerRadius is not found");
	}
	outerRadius = outerRadiusItem->getValueAsDouble();

	auto innerRadiusItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$innerRadius$"));
	if (!innerRadiusItem) {
		throw std::runtime_error("$variable$innerRadius is not found");
	}
	innerRadius = innerRadiusItem->getValueAsDouble();
 
	auto poreEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$poreEnable$"));
	if (!poreEnableItem) {
		throw std::runtime_error("$variable$poreEnable is not found");
	}
	poreEnable = poreEnableItem->getValueAsBool();

	auto paintEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$paintEnable$"));
	if (!paintEnableItem) {
		throw std::runtime_error("$variable$paintEnable is not found");
	}
	paintEnable = paintEnableItem->getValueAsBool();

	auto holesCountEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$holesCountEnable$"));
	if (!holesCountEnableItem) {
		throw std::runtime_error("$variable$holesCountEnable is not found");
	}
	holesCountEnable = holesCountEnableItem->getValueAsBool();
	 
	auto holesCountValueItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$holesCountValue$"));
	if (!holesCountValueItem) {
		throw std::runtime_error("$variable$holesCountValue is not found");
	}
	holesCountValue = holesCountValueItem->getValueAsDouble();

	auto brokenEyeEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$brokenEyeEnable$"));
	if (!brokenEyeEnableItem) {
		throw std::runtime_error("$variable$brokenEyeEnable is not found");
	}
	brokenEyeEnable = brokenEyeEnableItem->getValueAsBool();

	auto brokenEyeSimilarityItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$brokenEyeSimilarity$"));
	if (!brokenEyeSimilarityItem) {
		throw std::runtime_error("$variable$brokenEyeSimilarity is not found");
	}
	brokenEyeSimilarity = brokenEyeSimilarityItem->getValueAsDouble();

	auto crackSimilarityItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$crackSimilarity$"));
	if (!crackSimilarityItem) {
		throw std::runtime_error("$variable$crackSimilarity is not found");
	}
	crackSimilarity = crackSimilarityItem->getValueAsDouble();

	auto crackEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$crackEnable$"));
	if (!crackEnableItem) {
		throw std::runtime_error("$variable$crackEnable is not found");
	}
	crackEnable = crackEnableItem->getValueAsBool();

	auto apertureEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$apertureEnable$"));
	if (!apertureEnableItem) {
		throw std::runtime_error("$variable$apertureEnable is not found");
	}
	apertureEnable = apertureEnableItem->getValueAsBool();

	auto apertureValueItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$apertureValue$"));
	if (!apertureValueItem) {
		throw std::runtime_error("$variable$apertureValue is not found");
	}
	apertureValue = apertureValueItem->getValueAsDouble();

	auto apertureSimilarityItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$apertureSimilarity$"));
	if (!apertureSimilarityItem) {
		throw std::runtime_error("$variable$apertureSimilarity is not found");
	}
	apertureSimilarity = apertureSimilarityItem->getValueAsDouble();
	 
	auto holeCenterDistanceEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$holeCenterDistanceEnable$"));
	if (!holeCenterDistanceEnableItem) {
		throw std::runtime_error("$variable$holeCenterDistanceEnable is not found");
	}
	holeCenterDistanceEnable = holeCenterDistanceEnableItem->getValueAsBool();

	auto holeCenterDistanceValueItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$holeCenterDistanceValue$"));
	if (!holeCenterDistanceValueItem) {
		throw std::runtime_error("$variable$holeCenterDistanceValue is not found");
	}
	holeCenterDistanceValue = holeCenterDistanceValueItem->getValueAsDouble();

	auto holeCenterDistanceSimilarityItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$holeCenterDistanceSimilarity$"));
	if (!holeCenterDistanceSimilarityItem) {
		throw std::runtime_error("$variable$holeCenterDistanceSimilarity is not found");
	}
	holeCenterDistanceSimilarity = holeCenterDistanceSimilarityItem->getValueAsDouble();
 
	auto specifyColorDifferenceEnableItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$specifyColorDifferenceEnable$"));
	if (!specifyColorDifferenceEnableItem) {
		throw std::runtime_error("$variable$specifyColorDifferenceEnable is not found");
	}
	specifyColorDifferenceEnable = specifyColorDifferenceEnableItem->getValueAsDouble();

	auto specifyColorDifferenceRItem = oso::ObjectStoreCoreToItem(assembly.getItem("$variable$specifyColorDifferenceR$"));
	if (!specifyColorDifferenceRItem) {
		throw std::runtime_error("$variable$specifyColorDifferenceR is not found");
	}
	specifyColorDifferenceR = specifyColorDifferenceRItem->getValueAsDouble();

	 
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
	return *this;
}

rw::cdm::ButtonScannerDlgProductSet::operator rw::oso::ObjectStoreAssembly() const
{
	rw::oso::ObjectStoreAssembly assembly;
	assembly.setName("$class$ButtonScannerDlgProductSet$");


	return assembly;
}

bool rw::cdm::ButtonScannerDlgProductSet::operator==(const ButtonScannerDlgProductSet& account) const
{
	return false;
}

bool rw::cdm::ButtonScannerDlgProductSet::operator!=(const ButtonScannerDlgProductSet& account) const
{
	return false;
}
