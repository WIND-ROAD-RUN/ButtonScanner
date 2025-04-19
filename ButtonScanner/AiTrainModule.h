#pragma once

#include <QThread>
#include <QDebug>
#include <atomic>

#include"imeot_ModelEngineOT.h"

#include"opencv2/opencv.hpp"

enum class ModelType
{
	Segment,
	ObejectDetection,
};

class AiTrainModule : public QThread
{
	Q_OBJECT
private:
	ModelType _modelType;
public:
	void setModelType(ModelType type) { _modelType = type; }
private:
	int _frameHeight;
	int _framWidth;
public:
	using labelAndImg = QPair<QString, rw::imeot::ProcessRectanglesResultOT>;
	using DataItem = QPair<QString, QString>;
	explicit AiTrainModule(QObject* parent = nullptr);

	~AiTrainModule() override;

	void startTrain();

private:
	std::unique_ptr<rw::imeot::ModelEngineOT> labelEngine;
private:
	rw::imeot::ProcessRectanglesResultOT getBody(std::vector<rw::imeot::ProcessRectanglesResultOT>& processRectanglesResult, bool& hasBody);
	QVector<DataItem> getDataSet(const QVector<labelAndImg> & annotationDataSet, ModelType type,int classId);
	QVector<DataItem> getSegmentDataSet(const QVector<labelAndImg>& annotationDataSet, int classId);
	QVector<DataItem> getObjectDetectionDataSet(const QVector<labelAndImg>& annotationDataSet, int classId);
private:
	void clear_older_trainData();
public:
	cv::Mat getMatFromPath(const QString & path);
protected:
	void run() override;
private:
	QVector<labelAndImg> annotation_data_set(bool isBad);
signals:
	void appRunLog(QString log);

};

