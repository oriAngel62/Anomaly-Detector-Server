

/*
 * HybridAnomalyDetector.h
 *
 * Author: Ori Angel 314617739
 */
#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector : public SimpleAnomalyDetector
{
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
