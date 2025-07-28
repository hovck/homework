#include <iostream>
#include <math.h>
using namespace std;
class poly;
class term {
    friend class poly;
    friend ostream& operator<<(ostream& os, const poly& p);
private:
    float coef;
    int exp;
};

class poly {
private:
    term *termarray;
    int capacity;
    int terms;
public:
    poly();
    poly(const poly& other);
    poly& operator=(const poly& other);
    ~poly();
    poly add(const poly& b) const;
    poly sub(const poly& b) const;
    poly mul(const poly& b) const;
    poly div(const poly& b) const;
    float eval(float f);
    void newterm(float coef, int exp);
    void read_terms(int num_terms);
    friend ostream& operator<<(ostream& os, const poly& p);
    friend istream& operator>>(istream& is, poly& p);
};

poly::poly() {
    capacity = 10;
    terms = 0;
    termarray = new term[capacity];
}

poly::poly(const poly& other) {
    capacity = other.capacity;
    terms = other.terms;
    termarray = new term[capacity];
    for (int i = 0; i < terms; i++) {
        termarray[i] = other.termarray[i];
    }
}

poly& poly::operator=(const poly& other) {
    if (this != &other) {
        delete[] termarray;
        capacity = other.capacity;
        terms = other.terms;
        termarray = new term[capacity];
        for (int i = 0; i < terms; i++) {
            termarray[i] = other.termarray[i];
        }
    }
    return *this;
}

poly::~poly() {
    delete[] termarray;
}

void poly::newterm(float coef, int exp) {
    if (terms == capacity) {
        capacity *= 2;
        term *temp = new term[capacity];
        for (int i = 0; i < terms; i++) {
            temp[i] = termarray[i];
        }
        delete[] termarray;
        termarray = temp;
    }
    termarray[terms].coef = coef;
    termarray[terms].exp = exp;
    terms++;
}

void poly::read_terms(int num_terms) {
    terms = 0;
    for (int i = 0; i < num_terms; i++) {
        float coef;
        int exp;
        cin >> coef >> exp;
        newterm(coef, exp);
    }
}

poly poly::add(const poly& b) const {
    poly result;
    int i = 0, j = 0;
    while (i < terms && j < b.terms) {
        if (termarray[i].exp > b.termarray[j].exp) {
            result.newterm(termarray[i].coef, termarray[i].exp);
            i++;
        } else if (termarray[i].exp < b.termarray[j].exp) {
            result.newterm(b.termarray[j].coef, b.termarray[j].exp);
            j++;
        } else {
            float newcoef = termarray[i].coef + b.termarray[j].coef;
            if (newcoef != 0) {
                result.newterm(newcoef, termarray[i].exp);
            }
            i++;
            j++;
        }
    }
    while (i < terms) {
        result.newterm(termarray[i].coef, termarray[i].exp);
        i++;
    }
    while (j < b.terms) {
        result.newterm(b.termarray[j].coef, b.termarray[j].exp);
        j++;
    }
    return result;
}

poly poly::sub(const poly& b) const {
    poly result;
    int i = 0, j = 0;
    while (i < terms && j < b.terms) {
        if (termarray[i].exp > b.termarray[j].exp) {
            result.newterm(termarray[i].coef, termarray[i].exp);
            i++;
        } else if (termarray[i].exp < b.termarray[j].exp) {
            result.newterm(-b.termarray[j].coef, b.termarray[j].exp);
            j++;
        } else {
            float newcoef = termarray[i].coef - b.termarray[j].coef;
            if (newcoef != 0) {
                result.newterm(newcoef, termarray[i].exp);
            }
            i++;
            j++;
        }
    }
    while (i < terms) {
        result.newterm(termarray[i].coef, termarray[i].exp);
        i++;
    }
    while (j < b.terms) {
        result.newterm(-b.termarray[j].coef, b.termarray[j].exp);
        j++;
    }
    return result;
}

poly poly::mul(const poly& b) const {
    poly result;
    const int max_terms = terms * b.terms;
    term* temp = new term[max_terms];
    int temp_count = 0;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < b.terms; j++) {
            temp[temp_count].coef = termarray[i].coef * b.termarray[j].coef;
            temp[temp_count].exp = termarray[i].exp + b.termarray[j].exp;
            temp_count++;
        }
    }

    for (int i = 0; i < temp_count - 1; i++) {
        for (int j = i + 1; j < temp_count; j++) {
            if (temp[i].exp < temp[j].exp) {
                term t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int i = 0;
    while (i < temp_count) {
        float coef_sum = temp[i].coef;
        int current_exp = temp[i].exp;
        int j = i + 1;
        while (j < temp_count && temp[j].exp == current_exp) {
            coef_sum += temp[j].coef;
            j++;
        }
        if (coef_sum != 0) {
            result.newterm(coef_sum, current_exp);
        }
        i = j;
    }

    delete[] temp;
    return result;
}

poly poly::div(const poly& b) const {
    poly quotient;
    if (b.terms == 0 || b.termarray[0].coef == 0) {
        return quotient;
    }
    poly dividend = *this;
    if (dividend.terms == 0) {
        return quotient;
    }
    while (dividend.terms > 0 && dividend.termarray[0].exp >= b.termarray[0].exp) {
        float newcoef = dividend.termarray[0].coef / b.termarray[0].coef;
        int newexp = dividend.termarray[0].exp - b.termarray[0].exp;
        poly temp;
        temp.newterm(newcoef, newexp);
        quotient = quotient.add(temp);
        poly subtractor;
        for (int i = 0; i < b.terms; i++) {
            subtractor.newterm(b.termarray[i].coef * newcoef, b.termarray[i].exp + newexp);
        }
        dividend = dividend.sub(subtractor);
        poly cleaned_dividend;
        for (int i = 0; i < dividend.terms; i++) {
            if (dividend.termarray[i].coef != 0 && dividend.termarray[i].exp >= 0) {
                cleaned_dividend.newterm(dividend.termarray[i].coef, dividend.termarray[i].exp);
            }
        }
        dividend = cleaned_dividend;
    }
    return quotient;
}

float poly::eval(float f) {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termarray[i].coef * pow(f, termarray[i].exp);
    }
    return result;
}

ostream& operator<<(ostream& os, const poly& p) {
    if (p.terms == 0) {
        os << "0";
        return os;
    }
    bool first = true;
    for (int i = 0; i < p.terms; i++) {
        if (p.termarray[i].coef != 0) {
            if (!first && p.termarray[i].coef > 0) os << "+";
            if (p.termarray[i].coef != 1 || p.termarray[i].exp == 0)
                os << p.termarray[i].coef;
            if (p.termarray[i].exp > 0) {
                os << "x";
                if (p.termarray[i].exp > 1) os << "^" << p.termarray[i].exp;
            }
            first = false;
        }
    }
    return os;
}

istream& operator>>(istream& is, poly& p) {
    int num_terms;
    is >> num_terms;
    p.read_terms(num_terms);
    return is;
}

int main() {
    int a;
    cin >> a;
    while (a--) {
        int m, n;
        cin >> m >> n;
        poly a, b;
        a.read_terms(m);
        b.read_terms(n);
        cout << endl;
        cout << a.add(b) << endl;
        cout << a.mul(b) << endl;
        cout << a.sub(b) << endl;
        cout << a.div(b) << endl;
        cout << endl;
    }
    return 0;
}
