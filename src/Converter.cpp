#include "Converter.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Author: Hanif
// Year: 2018

Converter::Converter() {
    //ctor
}

std::string Converter::convert(const DocxParser & doc, const csv::Parser & csv) {
    std::stringstream ss;

    ss.precision(3);

    ss << bankconverter::kHeader << std::endl;

    for (Record record : doc.getRecords()) {
        ss << record.id << bankconverter::kDelimiter;
        //"ID,PROC_DATE,MID,CARDTYPE,TRX_DATE,AUTH,RRN,CARDNO,AMOUNT,NONFARE,RATE,DISC_AMT,AIRFARE,FLAG,NET_AMT,MERCHANT_REF_NUMBER";
        ss << bankconverter::formatDate(doc.getProcDate()) << bankconverter::kDelimiter;
        ss << bankconverter::kMerchantID << bankconverter::kDelimiter;
        ss << record.type[0] << bankconverter::kDelimiter;
        ss << bankconverter::formatDate(record.txn_date) << bankconverter::kDelimiter;
        ss << record.auth << bankconverter::kDelimiter;
        ss << "0" << bankconverter::kDelimiter; // RRN??
        ss << bankconverter::maskCard(bankconverter::removeAll(record.card_number, "-")) << bankconverter::kDelimiter; // [DONE] TODO: mask middle numbers
        ss << bankconverter::removeAll(record.amount, ",") << bankconverter::kDelimiter;
        ss << "0" <<bankconverter::kDelimiter; // nonfare?
        ss << std::fixed << bankconverter::toDouble(record.rate) << bankconverter::kDelimiter;
        ss << std::fixed << bankconverter::toDouble(bankconverter::removeAll(record.disc_amount, ",")) << bankconverter::kDelimiter;
        ss << "0" << bankconverter::kDelimiter; // airfare
        ss << "0" << bankconverter::kDelimiter; // flag
        double amt = bankconverter::toDouble(bankconverter::removeAll(record.amount, ","));
        double discAmt = bankconverter::toDouble(bankconverter::removeAll(record.disc_amount, ","));
        double net = amt-discAmt;
        ss << std::fixed << net << bankconverter::kDelimiter; // [DONE] net_amt, TODO: sanitise & format currency
        ss << bankconverter::findMerchantNumber(record, csv); // [DONE] TODO: merchant_ref_number (match using first 6 and last 4 card number)

        ss << std::endl;
    }

    std::cout << std::endl << ss.str() << std::endl;
    return ss.str();

}


Converter::~Converter() {
    //dtor
}


// IMPORTANT TODO: use index lookup for fast O(1) access
std::string bankconverter::findMerchantNumber(const Record & record, const csv::Parser & parser) {
    std::string masked = bankconverter::maskCard(bankconverter::removeAll(record.card_number, "-"));
    for (int i=0;i < parser.rowCount(); i++) {
        csv::Row row = parser.getRow(i);
        if (row["masked_card_number"] == masked) {
            return row["trn"];
        }
    }
    return "";
}

double bankconverter::toDouble(const std::string & str) {
    return atof(str.c_str());
}

std::string bankconverter::formatDate(const std::string & str) {
    tm tempTm;
	sscanf(str.c_str(),"%2d/%2d/%2d",&tempTm.tm_mday,&tempTm.tm_mon,&tempTm.tm_year);
    std::stringstream ss;
    ss << "20" << tempTm.tm_year << tempTm.tm_mon << tempTm.tm_mday; //TODO: Do not hardcode year
    return ss.str();
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
