#ifndef DOCXPARSER_H
#define DOCXPARSER_H
#include <string>
#include <vector>
#include <regex>
#include <Record.h>


// Author: Hanif
// Year: 2018



class DocxParser {
public:
    DocxParser(std::string);
    virtual ~DocxParser();
    void parse();

    const std::vector<Record> & getRecords() const { return records; }
    std::string getProcDate() const { return procDate; }

protected:

private:
    std::string path;
    std::string procDate;
    std::vector<Record> records;

    void matchRows(const std::string &);
    bool matchProcDate(const std::string &);

    const std::string rowRegex = "(\\d{5})\\s+(\\d{5})\\s+(\\d{3})\\s+([A-Z]{2})\\s+(\\d{2}\\/\\d{2}\\/\\d{2})\\s+(\\d{6})\\s+((?:\\d{4}-){3}\\d{4})\\s+([\\d,]+)\\s+(\\d+.\\d+)\\s+([\\d,]+)";
    const std::string procDateRegex = "PROC\\s+DATE\\s+:\\s+(\\d{2}\\/\\d{2}\\/\\d{2})";
};

#endif // DOCXPARSER_H
