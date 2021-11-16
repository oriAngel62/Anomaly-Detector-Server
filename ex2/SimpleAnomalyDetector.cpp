
#include "SimpleAnomalyDetector.h"
#include <stdlib.h>

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
	for (mapItrI = csv.begin(); mapItrI != csv.end(); ++mapItrI)
	{
		// m=coorealtion => suppose to be above 0.9?
		float m = 0.9;
		float c = -1;
		// float p=0;
		map<string, vector<float>>::iterator mapItrJ;

		map<string, vector<float>>::iterator mapCor1;
		map<string, vector<float>>::iterator mapCor2;
		for (mapItrJ = next(mapItrI, 1); mapItrJ != csv.end(); ++mapItrJ)
		{
			vector<float> vI = mapItrI->second;
			vector<float> vJ = mapItrJ->second;
			float p = abs(pearson(&vI[0], &vJ[0], vI.size()));
			if (p > m)
			{
				m = p;
				mapCor1 = mapItrI;
				mapCor2 = mapItrJ;
				//c is diffrent then -1
				c = 0;
			}
		}
		//there is correlation
		if (c != -1)
		{
			vector<float> vI = mapCor1->second;
			vector<float> vJ = mapCor2->second;
			Point *points;
			// Point **toPoints = &points;
			// vector<*point> points;

			//search in vector values
			// vector<float>::iterator vecItrX;
			// vector<float>::iterator vecItrY;
			// int i = 0;
			// vecItrX = vI.begin();
			// vecItrY = vJ.begin();

			for (int i = 0; i < vI.size(); i++)
			{

				// Point p = Point(*vecItrX, *vecItrY);
				// float n=*vecItrX.;
				points[i].x = vI[i];
				points[i].y = vJ[i];
				// m[i] = p;
				// vecItrX++;
				// vecItrY++;
				// i++;
			}
			//make the struct

			Line line = linear_reg(&points, mapCor1->second.size());
			string s1 = mapCor1->first;
			string s2 = mapCor2->first;
			//threshold
			float maxThreshold = 0;
			for (int i = 0; i < mapCor1->second.size(); i++)
			{
				float num = dev(points[i], line);
				if (maxThreshold < num)
				{
					maxThreshold = num;
				}
			}
			struct correlatedFeatures c1;
			c1.feature1 = s1;
			c1.feature2 = s2;
			c1.lin_reg = line;
			c1.threshold = maxThreshold * 1.1;
			// correlatedFeatures c1(s1, s2, m, l, t * 1.1);
			cf.push_back(c1);
		}
	}

	// 	FOR 𝑖 ← 1 TO 𝑁
	// 𝑚 ← 0 , 𝑐 ← (−1)
	// FOR 𝑗 ← 𝑖 + 1 TO 𝑁
	// IF (𝜌 ← |𝑝𝑒𝑎𝑟𝑠𝑜𝑛(𝑓𝑖
	// , 𝑓𝑗)|) > 𝑚 THEN 𝑚 ← 𝜌 , 𝑐 ← 𝑗
	// IF 𝑐 ≠ (−1) THEN associate 𝑓𝑖 and 𝑓𝑗 as correlated features
}

// float findThreshold(Point **points)
// {

// 	float maxThreshold = 0;
// 	for ()
// }

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts)
{
	// TODO Auto-generated destructor stub
	vector<AnomalyReport> anomalyReport;
	map<string, vector<float>> csv = ts.csv;
	vector<correlatedFeatures>::iterator it;
	for (it = cf.begin(); it != cf.end(); it++) //iterating all corolated pairs
	{
		string s1 = it->feature1;
		string s2 = it->feature2;
		Line lin_reg = it->lin_reg;
		float threshold = it->threshold;
		int k = 1;
		map<string, vector<float>>::iterator mapItrI;
		map<string, vector<float>>::iterator mapItrJ;
		mapItrI = csv.begin();
		for (mapItrI = csv.begin(); mapItrI != csv.end(); ++mapItrI) //finding the right keyss for our 2 featuers
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
						{ //checking every line for an anomaly
							Point p = Point(*vecItrX, *vecItrY);
							float deviation = dev(p, lin_reg);
							if (deviation > threshold)
								anomalyReport.push_back(AnomalyReport(s1 + "-" + s2, k));
							k++;
						}
					}
				}
			}
		}
	}
	return anomalyReport;
}
