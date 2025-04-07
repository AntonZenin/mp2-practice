#include "ringheadlist.h"
#include "tpolynom.h"
using namespace std;

TPolynom::TPolynom(const string& name) : monoms() {
	this->name = name;
	bool res = check(name);
	smash_pol(name);		
}

TPolynom::TPolynom(const headlist<TMonom>& list) {
	if (list.IsEmpty()) {
		name = "";
		monoms = headlist<TMonom>();
		return;
	}
	headlist<TMonom> tmp_l(list);
	tmp_l.Reset();
	while (!tmp_l.IsEnded()) {
		InsertToSort(tmp_l.GetCurr()->data);			
		tmp_l.Next();
	}
	if (monoms.IsEmpty()) {							
		TMonom zero(0, 0);
		monoms.InsertFirst(zero);
	}
	name = ToString();
}

TPolynom::TPolynom(const TPolynom& p) : monoms(p.monoms), name(p.name) {}

bool TPolynom::check(const string& name) {														
	string correct = "0123456789xyz*^+-";
	for (char ch : name) {
		if (correct.find(ch) == string::npos) return false;
	}

	return true;
}

void TPolynom::InsertToSort(const TMonom& monom) {												
	monoms.Reset();
	if (monom.coeff_ == 0 && monom.degree_ != 0) { return; }
	if (monom.coeff_ == 0 && monom.degree_ == 0 && !monoms.IsEmpty()) { return; }

	if (monoms.IsEmpty() || monoms.GetCurr()->data > monom) {
		monoms.InsertFirst(monom);
		return;
	}

	while (!monoms.IsEnded() && monoms.GetCurr()->data < monom) {
		monoms.Next();
	}
	if (monoms.IsEnded()) {
		monoms.InsertLast(monom);
		return;
	}

	if (monoms.GetCurr()->data == monom) {
		monoms.GetCurr()->data.coeff_ = monoms.GetCurr()->data.coeff_ + monom.coeff_;
		if (monoms.GetCurr()->data.coeff_ == 0) {
			monoms.Remove(monoms.GetCurr()->data);
		}
		return;
	}
	monoms.InsertBefore(monom, monoms.GetCurr()->data);
}


string TPolynom::ToString() const {
	string str;
	TPolynom new_this(*this);
	if (new_this.monoms.IsEmpty()) {
		return "0.00";
	}
	bool firstTerm = true;
	new_this.monoms.Reset();

	if (new_this.monoms.GetCurr()->data.coeff_ == 0
		&&
		new_this.monoms.GetCurr()->data.degree_ == 0
		) {
		return "0";
	}
	while (!new_this.monoms.IsEnded()) {
		int deg = new_this.monoms.GetCurr()->data.degree_;
		double coeff = new_this.monoms.GetCurr()->data.coeff_;
		int x = deg / 100;
		int y = (deg % 100) / 10;
		int z = deg % 10;
		if (coeff != 0) {
			if (!firstTerm) {
				str += ((coeff > 0) ? "+" : "-");
			}
			else {
				if (coeff < 0) str += '-';
				firstTerm = false;
			}
			if (abs(coeff) != 1 || deg == 0) {
				char buf[15];
				sprintf(buf, "%.2f", abs(coeff));
				str += string(buf);
			}
			string mul_symbol = ((abs(coeff) == 1) ? "" : "*");
			if (x != 0) {
				str += (mul_symbol + "x") + ((x != 1) ? "^" + to_string(x) : "");
			}
			if (y != 0) {
				mul_symbol = (x == 0) ? mul_symbol : "*";
				str += (mul_symbol + "y") + ((y != 1) ? "^" + to_string(y) : "");
			}
			if (z != 0) {
				mul_symbol = (x == 0 && y == 0) ? mul_symbol : "*";
				str += (mul_symbol + "z") + ((z != 1) ? "^" + to_string(z) : "");
			}
		}
		new_this.monoms.Next();
	}
	return str;
}

TPolynom TPolynom::operator-() const {								
	TPolynom negativePol(*this);

	while (!negativePol.monoms.IsEnded()) {
		negativePol.monoms.GetCurr()->data.coeff_ = negativePol.monoms.GetCurr()->data.coeff_ * (-1);
		negativePol.monoms.Next();
	}
	negativePol.name = negativePol.ToString();
	return negativePol;
}

TPolynom TPolynom::operator+(const TPolynom& p) {
	TPolynom res(p);

	monoms.Reset();
	while (!monoms.IsEnded()) {
		res.InsertToSort(monoms.GetCurr()->data);
		monoms.Next();
	}
	if (res.monoms.IsEmpty()) {
		TMonom zero(0, 0);
		res.monoms.InsertFirst(zero);
	}
	res.name = res.ToString();
	return res;
}

TPolynom TPolynom::operator-(const TPolynom& p) {
	TPolynom res = (*this) + (-p);
	res.name = res.ToString();
	return res;
}

TPolynom TPolynom::operator*(const TPolynom& p) {
	TPolynom res_pol;
	TPolynom tmp_p(p);

	monoms.Reset();
	while (!monoms.IsEnded()) {
		tmp_p.monoms.Reset();
		while (!tmp_p.monoms.IsEnded()) {
			TMonom mon1 = monoms.GetCurr()->data;
			TMonom mon2 = tmp_p.monoms.GetCurr()->data;
			double newCoeff = mon1.coeff_ * mon2.coeff_;
			int newDegree = mon1.degree_ + mon2.degree_;

			if (newDegree > 999) throw exception("invalid_degree");

			res_pol.InsertToSort(TMonom(newCoeff, newDegree));
			tmp_p.monoms.Next();
		}

		monoms.Next();
	}
	if (res_pol.monoms.IsEmpty()) {
		TMonom zero(0, 0);
		res_pol.monoms.InsertFirst(zero);
	}
	res_pol.name = res_pol.ToString();
	return res_pol;
}

bool TPolynom::operator==(const TPolynom& p) const {
	TPolynom new_this(*this);
	TPolynom new_p(p);

	while (!new_p.monoms.IsEnded() && !new_this.monoms.IsEnded()) {
		if (new_p.monoms.GetCurr()->data != new_this.monoms.GetCurr()->data) return false;
		new_p.monoms.Next();
		new_this.monoms.Next();
	}
	if (new_p.monoms.IsEnded() && new_this.monoms.IsEnded()) return true;

	return false;
}

double TPolynom::operator()(double x, double y, double z) const {
	double result = 0;
	TPolynom tmp_this(*this);

	while (!tmp_this.monoms.IsEnded()) {
		double mn;
		mn = tmp_this.monoms.GetCurr()->data.coeff_;
		mn *= pow(x, tmp_this.monoms.GetCurr()->data.degree_ / 100);
		mn *= pow(y, tmp_this.monoms.GetCurr()->data.degree_ / 10 % 10);
		mn *= pow(z, tmp_this.monoms.GetCurr()->data.degree_ % 10);

		result += mn;
		tmp_this.monoms.Next();
	}
	return result;
}

TPolynom TPolynom::dx() const {
	TPolynom dx_pol;
	TPolynom tmp_this(*this);

	while (!tmp_this.monoms.IsEnded()) {
		if (tmp_this.monoms.GetCurr()->data.degree_ / 100 != 0) {
			double newCoeff = tmp_this.monoms.GetCurr()->data.coeff_ * (tmp_this.monoms.GetCurr()->data.degree_ / 100);
			int newDegree = tmp_this.monoms.GetCurr()->data.degree_ - 100;

			dx_pol.InsertToSort(TMonom(newCoeff, newDegree));
		}

		tmp_this.monoms.Next();
	}

	return dx_pol;
}

TPolynom TPolynom::dy() const {
	TPolynom dy_pol;
	TPolynom tmp_this(*this);

	while (!tmp_this.monoms.IsEnded()) {
		if (tmp_this.monoms.GetCurr()->data.degree_ / 10 % 10 != 0) {
			double newCoeff = tmp_this.monoms.GetCurr()->data.coeff_ * (tmp_this.monoms.GetCurr()->data.degree_ / 10 % 10);
			int newDegree = tmp_this.monoms.GetCurr()->data.degree_ - 10;

			dy_pol.InsertToSort(TMonom(newCoeff, newDegree));
		}

		tmp_this.monoms.Next();
	}

	return dy_pol;
}

TPolynom TPolynom::dz() const {
	TPolynom dz_pol;
	TPolynom tmp_this(*this);

	while (!tmp_this.monoms.IsEnded()) {
		if (tmp_this.monoms.GetCurr()->data.degree_ % 10 != 0) {
			double newCoeff = tmp_this.monoms.GetCurr()->data.coeff_ * (tmp_this.monoms.GetCurr()->data.degree_ % 10);
			int newDegree = tmp_this.monoms.GetCurr()->data.degree_ - 1;

			dz_pol.InsertToSort(TMonom(newCoeff, newDegree));
		}

		tmp_this.monoms.Next();
	}

	return dz_pol;
}

const TPolynom& TPolynom::operator=(const TPolynom& p) {
	if (this == &p) {
		return (*this);
	}

	name = p.name;
	monoms = p.monoms;

	return *(this);
}


void TPolynom::smash_pol(const string& name) {
	string str = name;
	while (!str.empty()) {
		int degree = 0;
		size_t j = str.find_first_of("+-", 1);
		string monom = str.substr(0, j);
		if (monom[monom.length() - 1] == '^') {
			throw exception("Negative degree");
		}
		str.erase(0, j);

		string coefficent = monom.substr(0, monom.find_first_of("xyz"));
		TMonom tmp;
		tmp.coeff_ = (coefficent == "" || coefficent == "+") ? 1 : (coefficent == "-") ? -1 : stod(coefficent);
		monom.erase(0, monom.find_first_of("xyz"));

		for (size_t i = 0; i < monom.size(); ++i) {
			if (isalpha(monom[i])) {
				int exp = 1;
				if (monom[i + 1] == '^') {
					size_t exp_start = i + 2;
					while (isdigit(monom[exp_start])) {
						exp_start++;
					}
					exp = stoi(monom.substr(i + 2, exp_start - i - 2));
				}
				switch (monom[i]) {
				case 'x':
					degree += exp * 100;
					break;
				case 'y':
					degree += exp * 10;
					break;
				case 'z':
					degree += exp * 1;
					break;
				default:
					throw ("exp");
					break;
				}
			}
		}
		tmp.degree_ = degree;
		if (tmp.coeff_ != 0) {
			this->InsertToSort(tmp);
		}
	}
	if (this->monoms.IsEmpty()) {
		TMonom zero(0, 0);
		this->monoms.InsertFirst(zero);
	}
	this->name = this->ToString();
}

