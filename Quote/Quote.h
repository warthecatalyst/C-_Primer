#ifndef QUOTE_H_PREFIX
#define QUOTE_H_PREFIX
#include "global.h"

class Quote{
public:
    Quote() = default;
    Quote(const Quote&) = default;
    Quote(Quote&&) = default;
    Quote& operator=(const Quote&) = default;
    Quote& operator=(Quote&&) = default;
    Quote(const string& book, double sales_price):bookNo(book),price(sales_price){}
    string isbn() const;
    virtual double net_price(std::size_t n) const;
    virtual ~Quote() = default;
    virtual Quote* clone() const & {return new Quote(*this);}
    virtual Quote* clone() && {return new Quote(std::move(*this));}
private:
    string bookNo;
protected:
    double price = 0.0;    
};

class Disc_Quote : public Quote{
public:
    Disc_Quote() = default;
    Disc_Quote(const string& book, double price, size_t qty, double disc):Quote(book,price), quantity(qty), discount(disc){}

    double net_price(size_t n) const = 0;
protected:
    size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_Quote : public Disc_Quote{
public:
    using Disc_Quote::Disc_Quote;
    Bulk_Quote* clone() const &{
        return new Bulk_Quote(*this);
    }
    Bulk_Quote* clone() && {
        return new Bulk_Quote(std::move(*this));
    }
    double net_price(size_t) const override;
};


double print_total(ostream& os,const Quote& item,size_t n);

#endif