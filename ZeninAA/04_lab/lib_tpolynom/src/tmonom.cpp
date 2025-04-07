#include "tmonom.h"
using namespace std;

TMonom::TMonom() {
    coeff_ = 0;
    degree_ = -1;
}

TMonom::TMonom(double coeff, int degree) {
    if (degree > 999 || degree < 0) throw exception("BadDegree!\n");
    coeff_ = coeff;
    degree_ = degree;
}

bool TMonom::operator<(const TMonom& data) const {
    return degree_ < data.degree_;
}

bool TMonom::operator<=(const TMonom& data) const {
    return degree_ <= data.degree_;
}

bool TMonom::operator>(const TMonom& data) const {
    return degree_ > data.degree_;
}

bool TMonom::operator>=(const TMonom& data) const {
    return degree_ >= data.degree_;
}
                                                                    
bool TMonom::operator==(const TMonom& data) const {
    return degree_ == data.degree_;
}

bool TMonom::operator!=(const TMonom& data) const {
    return degree_ != data.degree_;
}