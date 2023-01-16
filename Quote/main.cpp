#include "global.h"
#include "Bk_Quote.h"

int main(void){
    Quote *basic_quote = new Quote("book1",2);
    Quote *discount_quote = new Bulk_Quote("book2",3,10,0.33333);
    Quote *bk_quote = new Bk_Quote("book3",4,20,0.25);
    print_total(cout,*basic_quote,20);
    print_total(cout,*discount_quote,20);
    print_total(cout,*bk_quote,40);
    vector<Quote*> quotes;
    quotes.push_back(basic_quote);
    quotes.push_back(discount_quote);
    quotes.push_back(bk_quote);
    for(auto quote:quotes){
        print_total(cout,*quote,40);
    }
    return 0;
}