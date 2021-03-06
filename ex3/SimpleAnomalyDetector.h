/*
 * animaly_detection_util.cpp
 *
 * Author: Ori Angel 314617739
 */
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "minCircle.h"

enum Shape
{
	line,
	circle
};
struct correlatedFeatures
{
	string feature1, feature2; // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold; // multyply 1.1
	Circle circle = Circle({0, 0}, 0);
	Shape shape;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector
{
	vector<correlatedFeatures> cf;

public:
	SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries &ts);
	virtual vector<AnomalyReport> detect(const TimeSeries &ts);
	void insertCorrelatedFeature(correlatedFeatures c1);
	vector<correlatedFeatures> getNormalModel()
	{
		return cf;
	}
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
