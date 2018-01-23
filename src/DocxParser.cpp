#include "DocxParser.h"
#include <fstream>
#include <iostream>


// Author: Hanif
// Year: 2018

DocxParser::DocxParser(std::string _path) : path(_path) {
}

void DocxParser::parse() {
    std::ifstream fs;
    std::string line;
    fs.open(path.c_str());

    if (fs.bad() || !fs.is_open()) {
        std::cout << "Doc is bad." << std::endl;
        return;
    }
    bool foundDate = false;
    while (fs.good()) {
        std::getline(fs, line);
        if (!foundDate) {
            foundDate = matchProcDate(line);
        }
        matchRows(line);
    }

    fs.close();

    // PROC\s+DATE\s+:\s+(\d{2}\/\d{2}\/\d{2})
    //std::string procdate;

    // header(not complete): (\w+(?:[.-]\w+){0,1}\s+){11}(?=\n)
    //std::string header;

    // row matches:
    // (\d{5})\s+(\d{5})\s+(\d{3})\s+([A-Z]{2})\s+(\d{2}\/\d{2}\/\d{2})\s+(\d{6})\s+((\d{4}-){3}\d{4})\s+([\d,]+)\s+(\d+.\d+)\s+([\d,]+)

}

void DocxParser::matchRows(const std::string &line) {
    //
    std::regex reg(rowRegex);
    std::smatch match;
    Record record;
    if (std::regex_search(line, match, reg)) {
        record.id = records.size() + 1;
        record.o_batchrate = match[1];
        record.batch = match[2];
        record.seq = match[3];
        record.type = match[4];
        record.txn_date = match[5];
        record.auth = match[6];
        record.card_number = match[7];
        record.amount = match[8];
        record.rate = match[9];
        record.disc_amount = match[10];
        //std::cout << match[0] << std::endl;
        records.push_back(record);
    }
}

bool DocxParser::matchProcDate(const std::string &line) {
    std::regex reg(procDateRegex);
    std::smatch match;
    bool found = std::regex_search(line, match, reg);
    if (found && match.size() > 1) {
        procDate = match[1];
        std::cout << procDate << std::endl;
    }
    return found;
}


DocxParser::~DocxParser() {
    //dtor
}
