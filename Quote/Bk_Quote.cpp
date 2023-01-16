#include "Bk_Quote.h"

double Bk_Quote::net_price(size_t n) const{
    if(n<=quantity){
        return (1-discount)*price*n;
    }
    return (1-discount)*price*quantity+(n-quantity)*price;
}