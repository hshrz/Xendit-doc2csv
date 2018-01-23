#include <iostream>
#include <DocxParser.h>
#include <Converter.h>
#include <CSVparser.hpp>


// Author: Hanif
// Year: 2018

using namespace std;

int main(int argc, char ** args) {
    if (argc < 3) {
        cout << "Path to a converted docx file and the superset csv file are required." << endl << "Make sure the bank doc has been converted to a txt field then try running with args:" << endl << endl;
        cout << "\tbank2csv [path to superset csv] [path to txt converted bank doc]" << endl;
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
        conv.convert(docParser, csvParser);
    } catch (csv::Error &err) {
        cout << "Could not parse CSV file: " << err.what() << endl;
        return -1;
    }

    return 0;
}
