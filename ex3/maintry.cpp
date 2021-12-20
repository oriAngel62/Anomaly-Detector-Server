
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
void readCsv()
{
    // File pointer
    fstream f;
    // Open an existing file
    f.open("input.txt", ios::in);
    // first line
    string firstLine;
    getline(f, firstLine);

    int indexMenu = stoi(firstLine);
    if (indexMenu != 1)
    {
        exit(1);
    }
    else
    {
        const char comma = ',';
        string line, word;
        ofstream out("file.csv");
        while (getline(f, line))
        {
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
                out.close();
                break;
            }
        }
    }
    f.close();
}
// small test
int main()
{
    // STDtest std("input.txt", "output.txt");
    // CLI cli(&std);
    // cli.start();
    // cli.start();
    // std.close();
    // check("output.txt","expectedOutput.txt");
    readCsv();
    cout << "done" << endl;
    return 0;
}
