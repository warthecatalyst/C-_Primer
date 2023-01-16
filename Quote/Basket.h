#include "Quote.h"

class Bucket{
public:
    void add_item(const Quote& sale){
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }

    void add_item(Quote&& sale){
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }

    double total_receipt(ostream&) const;
private:
    static bool compare(const shared_ptr<Quote> &lhs,const shared_ptr<Quote> &rhs){
        return lhs->isbn() < rhs->isbn();
    }

    multiset<shared_ptr<Quote>, decltype(compare)*> items{compare};
};