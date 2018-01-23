#ifndef RECORD_H
#define RECORD_H
#include <string>

// Author: Hanif
// Year: 2018

class Record {
public:
    Record();
    virtual ~Record();

    unsigned int id;
    std::string o_batchrate, batch, seq, type, txn_date, auth, card_number, amount, rate, disc_amount;

protected:

private:

};

#endif // RECORD_H
