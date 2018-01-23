#ifndef CONVERTER_H
#define CONVERTER_H
#include <string>
#include <vector>
#include <Record.h>
#include <DocxParser.h>
#include <CSVparser.hpp>



// Author: Hanif
// Year: 2018

namespace bankconverter {
    const std::string kHeader
        = "ID,PROC_DATE,MID,CARDTYPE,TRX_DATE,AUTH,RRN,CARDNO,AMOUNT,NONFARE,RATE,DISC_AMT,AIRFARE,FLAG,NET_AMT,MERCHANT_REF_NUMBER";

    const std::string kMerchantID
        = "000001988030000";

    const std::string kDelimiter = ",";
    const char kCardMask = 'X';

    std::string findMerchantNumber(const Record &, const csv::Parser &);
    double toDouble(const std::string &);
    std::string formatDate(const std::string &);
    std::string removeAll(const std::string &, std::string);
    std::string maskCard(const std::string &);


}

class Converter {
public:
    Converter();
    virtual ~Converter();

    std::string convert(const DocxParser &, const csv::Parser &);

protected:

private:

};

#endif // CONVERTER_H
