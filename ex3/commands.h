

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
// #include <string.h>
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
	HybridAnomalyDetector sharedDetector;
	// shared_ptr<HybridAnomalyDetector> sharedAnomalyDetector;

public:
	Command(DefaultIO *dio, const HybridAnomalyDetector &had) : dio(dio), sharedDetector(had){};
	virtual void execute() = 0;
	virtual ~Command() {}
};

class upload_command : public Command
{
public:
	// DefaultIO *dio;
	upload_command(DefaultIO *dio, const HybridAnomalyDetector &had) : Command(dio, had){
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
	get_set_treshold(DefaultIO *dio, const HybridAnomalyDetector &had) : Command(dio, had){
																			 // this->dio = dio;
																		 };

	virtual void execute()
	{
		float numChosen;
		string value;
		float i = sharedDetector.getMinTreshold();
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
		sharedDetector.setMinTreshold(numChosen);
		return;
	}
};

class anomaly_detection_command : public Command
{
public:
	anomaly_detection_command(DefaultIO *dio, const HybridAnomalyDetector &had) : Command(dio, had)
	{
	}
	virtual void execute()
	{
		string endCommand = "anomaly detection complete.\n";
		TimeSeries tsTrain("anomalyTrain.csv");
		sharedDetector.learnNormal(tsTrain);

		// suppose to be in anomal detector command
		TimeSeries tsTest("anomalyTest.csv");
		vector<AnomalyReport> ar = sharedDetector.detect(tsTest);
		for (int i = 0; i < ar.size(); i++)
		{
			string s1 = to_string(ar[i].timeStep);
			string s2 = ar[i].description;
			dio->write(s1 + "\t" + s2);
		}
		dio->write(endCommand);
		// TimeSeries tsTest("anomalyTest.csv");
		// sharedDetector.detect(tsTest);
		// dio->write(endCommand);
	}
};

class anomaly_report_command : public Command
{
public:
	anomaly_report_command(DefaultIO *dio, const HybridAnomalyDetector &had) : Command(dio, had)
	{
	}
	virtual void execute()
	{
		string endCommand = "Done\n";
		TimeSeries tsTest("anomalyTest.csv");

		vector<AnomalyReport> ar = sharedDetector.detect(tsTest);
		for (int i = 0; i < ar.size(); i++)
		{
			string s1 = to_string(ar[i].timeStep);
			string s2 = ar[i].description;
			s1.append("	");
			dio->write(s1 + "\t" + s2);
		}
		dio->write(endCommand);
	}
};
#endif /* COMMANDS_H_ */
