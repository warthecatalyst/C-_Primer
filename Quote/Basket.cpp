#include "Basket.h"

double Bucket::total_receipt(ostream &os) const
{
    double sum = 0.0;
    for(auto iter = items.cbegin();iter != items.cend();iter = items.upper_bound(*iter)){
        sum += print_total(os,**iter,items.count(*iter));
    }
    os << "Total Sale: " << sum << endl;  //print last price
    return sum;
}
