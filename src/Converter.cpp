#include "Converter.h"
#include <sstream>
#include <iostream>

// Author: Hanif
// Year: 2018

Converter::Converter() {
    //ctor
}

void Converter::convert(const DocxParser & doc, const csv::Parser & csv) {
    std::stringstream ss;

    ss << bankconverter::kHeader << std::endl;

    for (Record record : doc.getRecords()) {
        ss << record.id << bankconverter::kDelimiter;
        //"ID,PROC_DATE,MID,CARDTYPE,TRX_DATE,AUTH,RRN,CARDNO,AMOUNT,NONFARE,RATE,DISC_AMT,AIRFARE,FLAG,NET_AMT,MERCHANT_REF_NUMBER";
        ss << doc.getProcDate() << bankconverter::kDelimiter;
        ss << bankconverter::kMerchantID << bankconverter::kDelimiter;
        ss << record.type[0] << bankconverter::kDelimiter;
        ss << record.txn_date << bankconverter::kDelimiter;
        ss << record.auth << bankconverter::kDelimiter;
        ss << bankconverter::kDelimiter; // RRN??
        ss << bankconverter::maskCard(bankconverter::removeAll(record.card_number, "-")) << bankconverter::kDelimiter; // [DONE] TODO: mask middle numbers
        ss << bankconverter::removeAll(record.amount, ",") << bankconverter::kDelimiter;
        ss << "0" <<bankconverter::kDelimiter; // nonfare?
        ss << record.rate << bankconverter::kDelimiter;
        ss << bankconverter::removeAll(record.disc_amount, ",") << bankconverter::kDelimiter;
        ss << "0" << bankconverter::kDelimiter; // airfare
        ss << "0" << bankconverter::kDelimiter; // flag
        ss << bankconverter::kDelimiter; // net_amt, TODO: sanitise & format currency
        ss << bankconverter::kDelimiter; // TODO: merchant_ref_number (match using first 6 and last 4 card number)

        ss << std::endl;
    }

    std::cout << std::endl << ss.str() << std::endl;

}

Converter::~Converter() {
    //dtor
}

std::string bankconverter::removeAll(const std::string & str, std::string v) {
    unsigned int pos;
    std::string s = str;
    while((pos = s.find(v)) != std::string::npos) {
        s = s.erase(pos, 1);
    }
    return s;
}

std::string bankconverter::maskCard(const std::string& str) {
    if (str.length() < 6 || str.length()-4 <= 0) {
        return str; // can't mask invalid card number
    }
    std::string s = str;
    const char rep[2] = {bankconverter::kCardMask, 0};
    for (int i=6; i < str.length()-4; i++) {
        s = s.replace(i, 1, rep);
    }
    return s;
}
