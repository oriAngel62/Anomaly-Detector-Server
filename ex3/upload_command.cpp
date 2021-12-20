

#include "upload_command.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

upload_command::upload_command(DefaultIO *dio) : dio(dio) {}

upload_command::~upload_command()
{
}

void upload_command::execute()
{
    string firstMsg = "Please upload your local train CSV file.\n";
    string secondMsg = "Upload complete.\n";
    string pathCSV = "anomalyTrain.csv";
    const char comma = ',';
    string line, word;
    // fstream tmpf;
    //  tmpf.open(pathCSV);
    dio->write(firstMsg);
    ofstream out(pathCSV);
    bool done = false;
    while (done)
    {
        line = dio->read();
        // rest of the file
        if (line.compare("done") != 0)
        {
            stringstream ss(line);
            bool first = true;
            while (ss >> word) // get successive words per line
            {
                if (!first)
                    out << comma; // second and later words need a separator
                out << word;
                first = false;
            }
            out << '\n'; // end of line of output
        }
        else
        {
            // end with creating the csv file

            done = true;
        }
    }
    dio->write(secondMsg);
    TimeSeries ts(pathCSV);
    out.close(pathCSV);
    SimpleAnomalyDetector ad;
    ad.learnNormal(ts);
    dio->write(firstMsg);
}