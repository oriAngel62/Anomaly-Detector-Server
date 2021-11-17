

/*
 * animaly_detection_util.cpp
 *
 * Author: Ori Angel 314617739
 */
#ifndef ANOMALYDETECTOR_H_
#define ANOMALYDETECTOR_H_

#include <string>
#include <vector>
#include "anomaly_detection_util.h"
#include "timeseries.h"
#include "math.h"
using namespace std;

// class TimeSeries
// { /*...*/
// };
class AnomalyReport
{
public:
	const string description;
	const long timeStep;
	AnomalyReport(string description, long timeStep) : description(description), timeStep(timeStep) {}
};

class TimeSeriesAnomalyDetector
{
public:
	virtual void learnNormal(const TimeSeries &ts) = 0;
	virtual vector<AnomalyReport> detect(const TimeSeries &ts) = 0;
	virtual ~TimeSeriesAnomalyDetector() {}
};

#endif /* ANOMALYDETECTOR_H_ */
