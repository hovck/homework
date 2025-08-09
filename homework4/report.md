
# 51115117

作業4

## 解題說明

本題要求多項式的 + - * / 並用link array做實作

### 解題策略

用儲存單位(term)與多項式(poly)存儲完整多項式
每個非0單位都被用一個單位(term)作儲存
多個單位組成完整多項式(poly)

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <math.h>
using namespace std;

class poly;  //多項式物件宣告

class term { //單片物件宣告(概念:coef x ^ exp)
  friend class poly;
  friend ostream& operator<<(ostream& os, const poly& p);
private:
  float coef;  // 多項式的係數
  int exp;     // 多項式的指數
  term* next;  // 指向下一個項的指標
public:
  // 構造函數，初始化係數、指數和下一個節點
  term(float c, int e, term* n = nullptr) : coef(c), exp(e), next(n) {}
};

class poly {
    friend ostream& operator<<(ostream& os, const poly& p);
    friend istream& operator>>(istream& is, poly& p);
private:
    term* head; // 鏈結串列頭指標
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

// 主函數，處理多個測試案例，讀取兩個多項式並輸出加、減、乘、除結果
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

// 預設建構函數，初始化空多項式，頭指標設為空
poly::poly() {
    head = nullptr;
}

// 複製建構函數，複製另一個多項式的串列
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

// =運算，刪掉目前的串列並複製到另一個多項式
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

// 解構
poly::~poly() {
    term* current = head;
    while (current) {
        term* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

// 插入新片，指數從高到低排序，然後合併同類項
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

// 讀取指定數量的片，清空原串列並插入新項
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

// +運算，將兩個多項式相加，合併同類項
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

// -運算，將兩個多項式相減，合併同類項
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

// *運算，將兩個多項式相乘，生成所有項後排序並合併
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

// /運算，多項式長除法，返回商多項式
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

// 計算多項式在f處的值
float poly::eval(float f) {
    float result = 0;
    for (term* p = head; p; p = p->next) {
        result += p->coef * pow(f, p->exp);
    }
    return result;
}

// <<改寫，格式為 "coef" "x^" "exp"，不是首項且係數是正數時加 +
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

// >>改寫，用read_terms來讀多項式
istream& operator>>(istream& is, poly& p) {
    int num_terms;
    is >> num_terms;
    p.read_terms(num_terms);
    return is;
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O( a * n²)$。
2. 空間複雜度：空間複雜度為 $O( n² )$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 a m n | 預期輸出 | 實際輸出 |
|----------|--------------|-----------|---------|
| 測試一   | $1 3 3 5 5 4 4 3 3 2 1 6 5 3 2$ 等同於( $A:5x^5+4x^4+3x^3  B:2x^1+6x^5+3x^2$ ) | 加法 : $11x^5+4x^4+3x^3+3x^2+2x$| $11x^5+4x^4+3x^3+3x^2+2x$ |
| 測試一   | $1 3 3 5 5 4 4 3 3 2 1 6 5 3 2$ 等同於( $A:5x^5+4x^4+3x^3  B:2x^1+6x^5+3x^2$ ) | 乘法 : $30x^10+24x^9+18x^8+15x^7+22x^6+17x^5+6x^4$ | $30x^10+24x^9+18x^8+15x^7+22x^6+17x^5+6x^4$ |
| 測試一   | $1 3 3 5 5 4 4 3 3 2 1 6 5 3 2$ 等同於( $A:5x^5+4x^4+3x^3  B:2x^1+6x^5+3x^2$ ) | 減法 : $-1x^5+4x^4+3x^3-3x^2-2x$ | $-1x^5+4x^4+3x^3-3x^2-2x$ |
| 測試一   | $1 3 3 5 5 4 4 3 3 2 1 6 5 3 2$ 等同於( $A:5x^5+4x^4+3x^3  B:2x^1+6x^5+3x^2$ ) | 除法 : $5/6$| $0.83333$ |

### 編譯與執行指令
```shell
- C++ Compiler: C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe
- Command: g++.exe "D:\學校\c++\資料結構用\linkpoly.cpp" -o "D:\學校\c++\資料結構用\linkpoly.exe" -std=c++11 -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++" -L"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib" -L"C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\lib" -static-libgcc
```
### 結論

1.在除法出現其實出現不了的東西時(多項式後項比前項大(如: $5x^5/6x^6$ ))會出現的結果實際上只包含部分內容。

2.其餘部分計算都為正確

## 申論及開發報告

### 使用連結串列原因

因為有實作的要求
