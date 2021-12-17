
/*
 * animaly_detection_util.cpp
 *
 * Author: Ori Angel 314617739
 */
#include "SimpleAnomalyDetector.h"
#include <stdlib.h>
#include <stdio.h>

SimpleAnomalyDetector::SimpleAnomalyDetector()
{
	// TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector()
{
	// TODO Auto-generated destructor stub
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts)
{
	// TODO Auto-generated destructor stub
	map<string, vector<float>> csv = ts.csv;
	map<string, vector<float>>::iterator mapItrI;
	string sF2 = "";
	Shape localShape = line;
	for (mapItrI = csv.begin(); mapItrI != csv.end(); mapItrI++)
	{
		// m=coorealtion rate
		float correlationRate = 0.9;
		float half = 0.5;
		float correlationCheck = -1;
		map<string, vector<float>>::iterator mapItrJ;
		for (mapItrJ = next(mapItrI, 1); mapItrJ != csv.end(); mapItrJ++)
		{
			vector<float> vI = mapItrI->second;
			vector<float> vJ = mapItrJ->second;
			float p = abs(pearson(&vI[0], &vJ[0], vI.size()));
			if (p >= half && p <= correlationRate)
			{
				// correlationRate = p;
				//  c is diffrent then -1
				correlationCheck = 0;
				// save second cor name
				sF2 = mapItrJ->first;
				// c = 0;
				localShape = circle;
			}
			if (p > correlationRate)
			{
				correlationRate = p;
				// c is diffrent then -1
				correlationCheck = 0;
				// save second cor name
				sF2 = mapItrJ->first;
				// c = 0;
				localShape = line;
			}
		}
		// there is correlation
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
			c1.corrlation = correlationRate;
			c1.threshold = maxThreshold;
			c1.shape = localShape;
			cf.push_back(c1);
		}
	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts)
{
	// TODO Auto-generated destructor stub
	vector<AnomalyReport> anomalyReport;
	map<string, vector<float>> csv = ts.csv;
	vector<correlatedFeatures>::iterator it;
	for (it = cf.begin(); it != cf.end(); it++) // iterating all corolated pairs
	{
		string s1 = it->feature1;
		string s2 = it->feature2;
		Line lin_reg = it->lin_reg;
		float threshold = it->threshold;
		int k = 1;
		map<string, vector<float>>::iterator mapItrI;
		map<string, vector<float>>::iterator mapItrJ;
		mapItrI = csv.begin();
		// finding the right keyss for our 2 featuers
		for (mapItrI = csv.begin(); mapItrI != csv.end(); ++mapItrI)
		{
			if (s1.compare(mapItrI->first) == 0)
			{
				for (mapItrJ = mapItrI; mapItrJ != csv.end(); ++mapItrJ)
				{
					if (s2.compare(mapItrJ->first) == 0)
					{
						vector<float> vI = mapItrI->second;
						vector<float> vJ = mapItrJ->second;

						vector<float>::iterator vecItrX;
						vector<float>::iterator vecItrY;
						vecItrY = vJ.begin();
						for (vecItrX = vI.begin(); vecItrX != vI.end(); ++vecItrX, ++vecItrY)
						{
							// checking every line for an anomaly
							Point p = Point(*vecItrX, *vecItrY);
							if (it->shape == line)
							{
								float deviation = dev(p, lin_reg);
								if (deviation > threshold)
									anomalyReport.push_back(AnomalyReport(s1 + "-" + s2, k));
							}
							if (it->shape == circle)
							{
								// check if point is in circle
								if (!(is_inside(it->circle, p)))
								{
									anomalyReport.push_back(AnomalyReport(s1 + "-" + s2, k));
								}
							}
							k++;
						}
					}
				}
			}
		}
	}
	return anomalyReport;
}
