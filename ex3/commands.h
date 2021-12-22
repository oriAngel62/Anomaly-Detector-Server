

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include <string.h>
#include <fstream>
// #include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO
{
public:
	virtual string read() = 0;
	virtual void write(string text) = 0;
	virtual void write(float f) = 0;
	virtual void read(float *f) = 0;
	// virtual void read(int fromLine,int toLine)=0;
	virtual void close() = 0;
	virtual ~DefaultIO() {}
};

struct startAndEndTime
{
	int start, end;
};

// you may add additional methods here
// implement here your command classes
// class share_command
// {
// public:
// 	shared_ptr<HybridAnomalyDetector> shareAnomalyDetector;
// };
// };

// you may add here helper classes

// you may edit this class
class Command
{
protected:
	DefaultIO *dio;
	HybridAnomalyDetector *sharedDetector;
	// shared_ptr<HybridAnomalyDetector> sharedAnomalyDetector;

public:
	Command(DefaultIO *dio, HybridAnomalyDetector *had) : dio(dio), sharedDetector(had){};
	virtual void execute() = 0;
	virtual ~Command()
	{
	}
};

class upload_command : public Command
{
public:
	// DefaultIO *dio;
	upload_command(DefaultIO *dio, HybridAnomalyDetector *had) : Command(dio, had){
																	 // this->dio = dio;

																 };

	void copyToCSV(DefaultIO *dio, string stopWord, string newFileName)
	{
		// Create and open a text file
		ofstream CSVFile; //(newFileName);
		CSVFile.open(newFileName);
		string line,
			word;
		bool done = false;
		while (!done)
		{
			line = dio->read();
			// rest of the file
			if (line.compare(stopWord) != 0)
			{
				CSVFile << line << endl;
			}
			else
			{
				// end with creating the csv file

				done = true;
			}
		}
		CSVFile.close();
	}
	virtual void execute()
	{
		string firstMsg = "Please upload your local train CSV file.\n";
		string secondMsg = "Upload complete.\n";
		string thirdMsg = "Please upload your local test CSV file.\n";
		string pathCSVTrain = "anomalyTrain.csv";
		string pathCSVTest = "anomalyTest.csv";
		string stopWord = "done";
		// const char comma = ',';
		//  fstream tmpf;
		//   tmpf.open(pathCSV);
		dio->write(firstMsg);
		copyToCSV(dio, stopWord, pathCSVTrain);
		dio->write(secondMsg); // done
		dio->write(thirdMsg);
		copyToCSV(dio, stopWord, pathCSVTest);
		dio->write(secondMsg); // done
	}
};

class get_set_treshold : public Command
{
public:
	// DefaultIO *dio;
	get_set_treshold(DefaultIO *dio, HybridAnomalyDetector *had) : Command(dio, had){
																	   // this->dio = dio;
																   };

	virtual void execute()
	{
		float numChosen;
		string value;
		float i = sharedDetector->getMinTreshold();
		string minTresholdStr(to_string(i));
		string str1 = "The current correlation threshold is ";
		string str2 = "Type a new threshold\n";
		str1.append(minTresholdStr);
		str1.append("\n");
		string wrongOption = "please choose a value between 0 and 1.\n";
		do
		{
			dio->write(str1);
			dio->write(str2);
			value = dio->read();
			numChosen = stod(value); // from str to float
			if (!(numChosen > 0 && numChosen < 1))
				dio->write(wrongOption);
		} while (!(numChosen > 0 && numChosen < 1));
		sharedDetector->setMinTreshold(numChosen);
		return;
	}
};

class anomaly_detection_command : public Command
{
public:
	anomaly_detection_command(DefaultIO *dio, HybridAnomalyDetector *had) : Command(dio, had)
	{
	}
	virtual void execute()
	{
		string endCommand = "anomaly detection complete.\n";
		TimeSeries tsTrain("anomalyTrain.csv");
		sharedDetector->learnNormal(tsTrain);

		// // suppose to be in anomal detector command
		// TimeSeries tsTest("anomalyTest.csv");
		// vector<AnomalyReport> ar = sharedDetector->detect(tsTest);
		// for (int i = 0; i < ar.size(); i++)
		// {
		// 	string s1 = to_string(ar[i].timeStep);
		// 	string s2 = ar[i].description;
		// 	dio->write(s1 + "\t" + s2);
		// }
		dio->write(endCommand);
		// TimeSeries tsTest("anomalyTest.csv");
		// sharedDetector.detect(tsTest);
		// dio->write(endCommand);
	}
};

class anomaly_report_command : public Command
{
public:
	anomaly_report_command(DefaultIO *dio, HybridAnomalyDetector *had) : Command(dio, had)
	{
	}
	virtual void execute()
	{
		string endCommand = "Done.\n";
		TimeSeries tsTest("anomalyTest.csv");

		vector<AnomalyReport> ar = sharedDetector->detect(tsTest);
		for (int i = 0; i < ar.size(); i++)
		{
			string s1 = to_string(ar[i].timeStep);
			string s2 = ar[i].description;
			s1.append("\t");
			s1.append(s2);
			s1.append("\n");
			dio->write(s1);
		}
		dio->write(endCommand);
	}
};

class upload_and_analyze_command : public Command
{
public:
	// DefaultIO *dio;
	upload_and_analyze_command(DefaultIO *dio, HybridAnomalyDetector *had) : Command(dio, had){
																				 // this->dio = dio;

																			 };

	vector<startAndEndTime> getStartAndEndTimes()
	{
		// Create and open a text file
		string line, firstVal, secondVal;

		TimeSeries tsSupport("anomalyTest.csv");
		string stopWord = "done";
		vector<startAndEndTime> allTimes;
		vector<string> strTimes;
		bool done = false;
		while (!done)
		{
			line = dio->read();
			// rest of the file
			if (line.compare(stopWord) != 0)
			{
				startAndEndTime data;
				size_t pos = 0;
				if (pos = line.find(","))
				{
					firstVal = line.substr(0, pos);
					secondVal = line.substr(pos + 1, line.length() - 1);
					strTimes.push_back(firstVal);
					strTimes.push_back(secondVal);
				}
				data.start = stoi(strTimes[0]);
				data.end = stoi(strTimes[1]);
				allTimes.push_back(data);
				strTimes.clear();
			}
			else
			{
				// end with creating the csv file

				done = true;
			}
		}
		return allTimes;
	}

	map<string, vector<startAndEndTime>> uninoTogther(vector<AnomalyReport> ar)
	{
		map<string, vector<startAndEndTime>> reportMap;
		int range = 0;
		if (ar.size() > 0)
		{
			int prevTimeStep = ar[0].timeStep;
			string prevDescription = ar[0].description;
			vector<startAndEndTime> vectorOneCloumn;
			bool diffrentCloumn = false;
			int initialTImeStep = prevTimeStep;
			for (int i = 1; i < ar.size(); i++)
			{
				int timeStep = ar[i].timeStep;
				string description = ar[i].description;
				// same range in same clumn
				if (timeStep == prevTimeStep + 1 && prevDescription == description)
				{
					range++;
				}
				// new range in same cloumn
				if (timeStep != prevTimeStep + 1 && prevDescription == description)
				{
					startAndEndTime SAET = {initialTImeStep, initialTImeStep + range};
					vectorOneCloumn.push_back(SAET);
					range = 0;
					diffrentCloumn = true;
					initialTImeStep = timeStep;
				}
				// end with cloumn
				if ((timeStep != prevTimeStep + 1 && prevDescription != description) || (i + 1 == ar.size()))
				{
					if (!diffrentCloumn)
					{
						startAndEndTime SAET = {initialTImeStep, initialTImeStep + range};
						vectorOneCloumn.push_back(SAET);
						initialTImeStep = timeStep;
					}

					reportMap.insert({prevDescription, vectorOneCloumn});
					range = 0;
					prevDescription = description;
					vectorOneCloumn.clear();
				}
				prevTimeStep = timeStep;
				diffrentCloumn = false;
			}
		}
		return reportMap;
	}

	int getn()
	{
		std::ifstream f("anomalyTest.csv");
		std::string line;
		long i;
		for (i = 0; std::getline(f, line); ++i)
			;
		return i - 1;
	}

	void checkPosNegFrame(map<string, vector<startAndEndTime>> reportMap, vector<startAndEndTime> exceptionVec)
	{
		string positiveRateMsg = "True Positive Rate: ";
		string negativeRateMsg = "False Positive Rate: ";
		int P = exceptionVec.size();
		// num of rows in ts
		int n = getn();
		int sumN = 0;
		for (int i = 0; i < exceptionVec.size(); i++)
		{
			int start = exceptionVec[i].start;
			int end = exceptionVec[i].end;
			sumN = end - start + 1;
		}
		int N = n - sumN;

		int TPCount = 0;
		int FPCount = 0;
		vector<bool> reportCutException;
		for (int i = 0; i < exceptionVec.size(); i++)
		{
			reportCutException.push_back(false);
		}
		map<string, vector<startAndEndTime>>::iterator mapItrKeys;
		for (mapItrKeys = reportMap.begin(); mapItrKeys != reportMap.end(); ++mapItrKeys) // iterating over map's values
		{
			vector<startAndEndTime> v = mapItrKeys->second;
			vector<startAndEndTime>::iterator vecItr;
			for (vecItr = v.begin(); vecItr != v.end(); ++vecItr)
			{
				startAndEndTime range = *vecItr;
				int startReport = range.start;
				int endReport = range.end;
				// check TP
				//  isTruePositive=report is in exception field
				bool isTruePositive = false;
				bool isFalsePositive = false;
				int counterOut = 0;
				for (int i = 0; i < exceptionVec.size(); i++)
				{

					int startException = exceptionVec[i].start;
					int endException = exceptionVec[i].end;
					// report is in not cut exception
					if (endReport < startException || startReport > endException)
					{
						counterOut++;
					}
					else
					{
						reportCutException[i] = true;
					}
				}
				if (counterOut == exceptionVec.size())
				{
					FPCount++;
				}
				counterOut = 0;
			}
		}
		for (int i = 0; i < exceptionVec.size(); i++)
		{
			if (reportCutException[i])
			{
				TPCount++;
			}
		}
		// String.format("%.2f", a)

		float f1 = (TPCount * 1000) / P;
		float f2 = (FPCount * 1000) / N;
		f1 = floor(f1);
		f2 = floor(f2);
		f1 = f1 / 1000;
		f2 = f2 / 1000;
		double t = ((double)TPCount / (double)P) * 1000.0;
		double TPRate = (double)trunc(t) / 1000.0;
		t = ((double)FPCount / (double)N) * 1000.0;
		double FPRate = (double)trunc(t) / 1000.0;
		dio->write(positiveRateMsg + to_string(f1) + "\n");
		dio->write(negativeRateMsg + to_string(f2) + "\n");
	}

	virtual void execute()
	{

		string firstMsg = "Please upload your local anomalies file.\n";
		string secondMsg = "Upload complete.\n";
		dio->write(firstMsg);
		dio->write(secondMsg);
		TimeSeries tsTest("anomalyTest.csv");
		vector<AnomalyReport> ar = sharedDetector->detect(tsTest);
		map<string, vector<startAndEndTime>> reportMap = uninoTogther(ar);

		vector<startAndEndTime> exceptionVec = getStartAndEndTimes();
		checkPosNegFrame(reportMap, exceptionVec);
		int a = 10;
	}
};

// string cutString(string s)
// {
// 	bool dot = flase;
// 	int indexDot = 0;
// 	string newS = "";
// 	int count = 0;
// 	for (int i = 0; i < s.length(); i++)
// 	{
// 		if (s[i] == ".")
// 		{
// 			dot = true;
// 			indexDot = i;
// 		}
// 		newS = newS + s[i];
// 	}
// 	if (!dot)
// 	{
// 		return newS;
// 	}
// 	else
// 	{
// 		for (int i = s.length(); i < indexDot; i--)
// 		{
// 			if (s[i] == "0")
// 			{
// 				count++;
// 			}
// 		}
// 		s = s.substring(0, s.length() - 1 + count);
// 	}
// }

//

#endif /* COMMANDS_H_ */