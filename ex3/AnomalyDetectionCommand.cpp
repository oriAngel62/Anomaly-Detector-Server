

#include "commands.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// upload_command::upload_command(DefaultIO *dio)
// {
//     this->dio = dio;
// }

upload_command::~upload_command()
{
}

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

void upload_command::execute()
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
    // ofstream outTrain(pathCSVTrain);
    copyToCSV(dio, stopWord, pathCSVTrain);
    dio->write(secondMsg); // done
    // TimeSeries ts("anomalyTrain.csv");
    // out.close(pathCSVTrain);
    // HybridAnomalyDetector ad;
    // ad.learnNormal(ts);
    dio->write(thirdMsg);
    copyToCSV(dio, stopWord, pathCSVTest);
    dio->write(secondMsg); // done
    // TimeSeries ts2("testFile1.csv");
    // vector<AnomalyReport> r = ad.detect(ts2);
    // to do figure how to save all the new info
}