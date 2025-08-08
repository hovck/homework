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
    term* next;
public:
    term(float c, int e, term* n = nullptr) : coef(c), exp(e), next(n) {}
};
class poly {
    friend ostream& operator<<(ostream& os, const poly& p);
    friend istream& operator>>(istream& is, poly& p);
private:
    term* head; // Linked list head pointer
public:
    poly();
    poly(const poly& other);
    poly& operator=(const poly& other);
    ~poly();
    poly operator+(const poly& b) const;
    poly operator-(const poly& b) const;
    poly operator*(const poly& b) const;
    poly operator/(const poly& b) const;
    float eval(float f);
    void newterm(float coef, int exp);
    void read_terms(int num_terms);
};
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
        cout << (a + b) << endl;
        cout << (a * b) << endl;
        cout << (a - b) << endl;
        cout << (a / b) << endl;
        cout << endl;
    }
    return 0;
}
poly::poly() {
    head = nullptr;
}
poly::poly(const poly& other) {
    head = nullptr;
    term* current = other.head;
    term* tail = nullptr;
    while (current) {
        term* new_node = new term(current->coef, current->exp, nullptr);
        if (!head) {
            head = new_node;
            tail = head;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        current = current->next;
    }
}
poly& poly::operator=(const poly& other) {
    if (this != &other) {
        // Free current linked list
        term* current = head;
        while (current) {
            term* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        // Copy other's linked list
        current = other.head;
        term* tail = nullptr;
        while (current) {
            term* new_node = new term(current->coef, current->exp, nullptr);
            if (!head) {
                head = new_node;
                tail = head;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
            current = current->next;
        }
    }
    return *this;
}
poly::~poly() {
    term* current = head;
    while (current) {
        term* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}
void poly::newterm(float coef, int exp) {
    if (coef == 0) return; // Ignore zero coefficient terms
    term* new_node = new term(coef, exp, nullptr);
    // Empty list, insert directly
    if (!head) {
        head = new_node;
        return;
    }
    // Find insertion point, keeping exponents in descending order
    term* prev = nullptr;
    term* current = head;
    while (current && current->exp > exp) {
        prev = current;
        current = current->next;
    }
    // Check for same exponent (combine terms)
    if (current && current->exp == exp) {
        current->coef += coef;
        if (current->coef == 0) {
            // Remove term if coefficient becomes zero
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
        }
        delete new_node; // No longer needed
        return;
    }
    // Insert new node
    if (prev) {
        prev->next = new_node;
        new_node->next = current;
    } else {
        new_node->next = head;
        head = new_node;
    }
}
void poly::read_terms(int num_terms) {
    term* current = head;
    while (current) {
        term* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    for (int i = 0; i < num_terms; i++) {
        float coef;
        int exp;
        cin >> coef >> exp;
        newterm(coef, exp);
    }
}
poly poly::operator+(const poly& b) const {
    poly result;
    term* p1 = head;
    term* p2 = b.head;
    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            result.newterm(p1->coef, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            result.newterm(p2->coef, p2->exp);
            p2 = p2->next;
        } else {
            float newcoef = p1->coef + p2->coef;
            if (newcoef != 0) {
                result.newterm(newcoef, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1) {
        result.newterm(p1->coef, p1->exp);
        p1 = p1->next;
    }
    while (p2) {
        result.newterm(p2->coef, p2->exp);
        p2 = p2->next;
    }
    return result;
}
poly poly::operator-(const poly& b) const {
    poly result;
    term* p1 = head;
    term* p2 = b.head;
    while (p1 && p2) {
        if (p1->exp > p2->exp) {
            result.newterm(p1->coef, p1->exp);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            result.newterm(-p2->coef, p2->exp);
            p2 = p2->next;
        } else {
            float newcoef = p1->coef - p2->coef;
            if (newcoef != 0) {
                result.newterm(newcoef, p1->exp);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1) {
        result.newterm(p1->coef, p1->exp);
        p1 = p1->next;
    }
    while (p2) {
        result.newterm(-p2->coef, p2->exp);
        p2 = p2->next;
    }
    return result;
}
poly poly::operator*(const poly& b) const {
    poly result;
    term* temp_head = nullptr;
    term* temp_tail = nullptr;
    for (term* p1 = head; p1; p1 = p1->next) {
        for (term* p2 = b.head; p2; p2 = p2->next) {
            term* new_node = new term(p1->coef * p2->coef, p1->exp + p2->exp, nullptr);
            if (!temp_head) {
                temp_head = new_node;
                temp_tail = new_node;
            } else {
                temp_tail->next = new_node;
                temp_tail = new_node;
            }
        }
    }
    term* current = temp_head;
    while (current) {
        result.newterm(current->coef, current->exp);
        term* temp = current;
        current = current->next;
        delete temp;
    }
    return result;
}
poly poly::operator/(const poly& b) const {
    poly quotient;
    if (!b.head || b.head->coef == 0) return quotient;
    poly dividend = *this;
    if (!dividend.head) return quotient;
    while (dividend.head && dividend.head->exp >= b.head->exp) {
        float newcoef = dividend.head->coef / b.head->coef;
        int newexp = dividend.head->exp - b.head->exp;
        poly temp;
        temp.newterm(newcoef, newexp);
        quotient = quotient + temp;
        poly subtractor;
        for (term* p = b.head; p; p = p->next) {
            subtractor.newterm(p->coef * newcoef, p->exp + newexp);
        }
        dividend = dividend - subtractor;
        poly cleaned_dividend;
        for (term* p = dividend.head; p; p = p->next) {
            if (p->coef != 0 && p->exp >= 0) {
                cleaned_dividend.newterm(p->coef, p->exp);
            }
        }
        dividend = cleaned_dividend;
    }
    return quotient;
}
float poly::eval(float f) {
    float result = 0;
    for (term* p = head; p; p = p->next) {
        result += p->coef * pow(f, p->exp);
    }
    return result;
}
ostream& operator<<(ostream& os, const poly& p) {
    if (!p.head) {
        os << "0";
        return os;
    }
    bool first = true;
    for (term* current = p.head; current; current = current->next) {
        if (current->coef != 0) {
            if (!first && current->coef > 0) os << "+";
            if (current->coef != 1 || current->exp == 0)
                os << current->coef;
            if (current->exp > 0) {
                os << "x";
                if (current->exp > 1) os << "^" << current->exp;
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
