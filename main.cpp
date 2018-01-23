#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <DocxParser.h>
#include <Converter.h>
#include <CSVparser.hpp>


// Author: Hanif
// Year: 2018

using namespace std;

void save(string name, const string& contents) {
    string file = name.substr(0, name.find_last_of('.')) + ".csv";
    ofstream fs(file.c_str());
    fs << contents;
    fs.flush();
    if (fs.bad()) {
        cout << "Could not save as a CSV file" << endl;
    } else {
        cout << "Saved " << file << " successfully" << endl;
    }
    fs.close();
}

int main(int argc, char ** args) {
    if (argc < 3) {
        cout << "Path to a converted docx file and the superset csv file are required." << endl << "Make sure the doc has been converted to a txt file then try running with args:" << endl << endl;
        cout << "\tdoc2csv [path to superset csv] [path to txt converted doc]" << endl;
        return 1;
    }
    cout << "Parsing " << args[2] << "..." << endl;
    DocxParser docParser(args[2]);
    docParser.parse();

    cout << docParser.getRecords().size() << " records within statement." << endl << endl;
    try {
        cout << "Loading " << args[1] << "..." << endl;
        csv::Parser csvParser(args[1]);

        cout << "Converting " << args[2] << " to CSV..." << endl;

        Converter conv;
        string c = conv.convert(docParser, csvParser);

        save(args[2], c);
    } catch (csv::Error &err) {
        cout << "Could not parse CSV file: " << err.what() << endl;
        return -1;
    }

    return 0;
}
