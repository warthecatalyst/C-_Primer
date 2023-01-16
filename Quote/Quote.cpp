#include "Quote.h"

string Quote::isbn() const {
    return bookNo;
}

double Quote::net_price(size_t n) const {
    return n*price;
}

double Bulk_Quote::net_price(size_t n) const{
    if(n<quantity){
        return n*price;
    }
    return (1-discount)*n*price;
}

double print_total(ostream& os,const Quote& item,size_t n){
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
    << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}
