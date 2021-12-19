
/*
 * HybridAnomalyDetector.cpp
 *
 * Author: Ori Angel 314617739
 */
#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector()
{
	// TODO Auto-generated constructor stub
}

HybridAnomalyDetector::~HybridAnomalyDetector()
{
	// TODO Auto-generated destructor stub
}

void HybridAnomalyDetector::learnNormal(const TimeSeries &ts)
{
	// TODO Auto-generated destructor stub
	map<string, vector<float>> csv = ts.csv;
	map<string, vector<float>>::iterator mapItrI;
	string sF2 = "";
	Shape localShape = line;
	for (mapItrI = csv.begin(); mapItrI != csv.end(); mapItrI++)
	{
		// m=coorealtion rate
		float minLineCorrelation = 0.9;
		float half = 0.5;
		float correlationCheck = -1;
		float currentMax = 0;
		map<string, vector<float>>::iterator mapItrJ;
		for (mapItrJ = next(mapItrI, 1); mapItrJ != csv.end(); mapItrJ++)
		{
			vector<float> vI = mapItrI->second;
			vector<float> vJ = mapItrJ->second;
			float p = abs(pearson(&vI[0], &vJ[0], vI.size()));
			// find correaltion above threshold
			if (p > half)
			{
				if (p > currentMax)
				{
					currentMax = p;
					// save second cor name
					sF2 = mapItrJ->first;
				}
				// c is diffrent then -1
				correlationCheck = 0;
			}
		}
		// there is correlation
		if (currentMax > half && currentMax < minLineCorrelation)
		{
			localShape = circle;
		}
		if (currentMax >= minLineCorrelation)
		{
			localShape = line;
		}
		if (correlationCheck != -1)
		{
			string f1 = mapItrI->first;
			vector<float> vI = csv.find(f1)->second;
			vector<float> vJ = csv.find(sF2)->second;
			Point *points = (Point *)malloc(vI.size() * sizeof(Point));

			for (int i = 0; i < vI.size(); i++)
			{

				Point point = Point(vI[i], vJ[i]);
				points[i] = point;
			}
			// make the struct
			correlatedFeatures c1;
			// threshold
			float maxThreshold = 0;
			if (localShape == line)
			{
				Line line = linear_reg(&points, vI.size());
				for (int i = 0; i < vI.size(); i++)
				{
					float num = dev(points[i], line);
					if (maxThreshold < num)
					{
						maxThreshold = num;
					}
				}
				maxThreshold = maxThreshold * 1.1;
				c1.lin_reg = line;
			}
			Circle circleObj = Circle({0, 0}, 0);
			if (localShape == circle)
			{
				circleObj = findMinCircle(&points, vI.size());
				circleObj.radius = circleObj.radius * 1.1;
				// cirecle radius is maxthereshold
				maxThreshold = circleObj.radius;
				c1.circle = circleObj;
			}
			string s1 = csv.find(f1)->first;
			string s2 = csv.find(sF2)->first;
			free(points);
			c1.feature1 = s1;
			c1.feature2 = s2;
			c1.corrlation = minLineCorrelation;
			c1.threshold = maxThreshold;
			c1.shape = localShape;
			insertCorrelatedFeature(c1);
		}
	}
	vector<correlatedFeatures> cf = getNormalModel();
	int a = 10;
}
