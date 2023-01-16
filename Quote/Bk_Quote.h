#ifndef BK_QUOTE_H_PREFIX
#define BK_QUOTE_H_PREFIX   

#include "global.h"
#include "Quote.h"

class Bk_Quote : public Disc_Quote{
public:
    Bk_Quote() = default; 
    Bk_Quote(const string& book, double price, size_t qty, double disc):Disc_Quote(book,price,qty,disc){}
    double net_price(size_t n) const override;
};

#endif