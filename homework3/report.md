
# 51115117
作業3
## 解題說明

本題要求多項式相加，相乘

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

class poly;
//儲存單位 term
class term {
    //讓operator能存取term的內容
    friend class poly;
    friend ostream& operator<<(ostream& os, const poly& p);
private:
    //一個組成的單位為 coef*x^exp
    float coef;
    int exp;
};
//將多項式與實際實作分開
class poly {
    //讓operator能存取poly的內容
    friend ostream& operator<<(ostream& os, const poly& p);
    friend istream& operator>>(istream& is, poly& p);
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
    poly multiply(const poly& b) const;
    float eval(float f);
    void newterm(float coef, int exp);
    void read_terms(int num_terms);
};
//主程式碼
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
        cout << a.multiply(b) << endl;
        cout << endl;
    }
    return 0;
}

//預設給10容量，不夠再提供newterm
poly::poly() {
    capacity = 10;
    terms = 0;
    termarray = new term[capacity];
}
//複製其他多項式
poly::poly(const poly& other) {
    capacity = other.capacity;
    terms = other.terms;
    termarray = new term[capacity];
    for (int i = 0; i < terms; i++) {
        termarray[i] = other.termarray[i];
    }
}
//把=的operator修改成，刪除舊termarray 並提供到新的
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
//解構
poly::~poly() {
    delete[] termarray;
}
//塞入新內容時會呼叫
void poly::newterm(float coef, int exp) {
    //如果 coef==0 該項不存在，無須存儲所以返回
    if (coef == 0) return;
    //如果terms == capacity，塞滿了，重新呼叫一個capacity*2大小的
    if (terms == capacity) {
        capacity *= 2;
        term *temp = new term[capacity];
        for (int i = 0; i < terms; i++) {
            temp[i] = termarray[i];
        }
        delete[] termarray;
        termarray = temp;
    }
    int i = 0;
    /*找插入位置 i，使新項的指數不會自己新開一個位置，只去找到跟自己exp一樣或當目前的exp>所有已被存儲的exp
      如果找到相同的exp，則合併coef:
      1.如果合併後coef為0，移除該項，terms--
      2.如果合併後coef>0(其餘狀況)，將新項插入i位置，增加 terms
    */
    //尋找插入位置
    while (i < terms && termarray[i].exp > exp) {
        i++;
    }
    //相等時
    if (i < terms && termarray[i].exp == exp) {
        termarray[i].coef += coef;
        if (termarray[i].coef == 0) {
            for (int j = i; j < terms - 1; j++) {
                termarray[j] = termarray[j + 1];
            }
            terms--;
        }
        return;
    }
    for (int j = terms; j > i; j--) {
        termarray[j] = termarray[j - 1];
    }
    termarray[i].coef = coef;
    termarray[i].exp = exp;
    terms++;
}
//多重輸入
void poly::read_terms(int num_terms) {
    terms = 0;
    for (int i = 0; i < num_terms; i++) {
        float coef;
        int exp;
        cin >> coef >> exp;
        newterm(coef, exp);
    }
}
//相加
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
//相乘
poly poly::multiply(const poly& b) const {
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
//輸出為 coef x ^ exp，不在第一項輸出+
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
//讀num_terms+read_terms讀到指定量的內容
istream& operator>>(istream& is, poly& p) {
    int num_terms;
    is >> num_terms;
    p.read_terms(num_terms);
    return is;
}

```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O( a*n^4 )$。
2. 空間複雜度：空間複雜度為 $O( n^2 )$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 a m n | 預期輸出 | 實際輸出 |
|----------|--------------|-----------|---------|
| 測試一   | $1 3 3 5 5 4 4 3 3 2 1 6 5 3 2$ | 加法 : $11x^5+4x^4+3x^3+3x^2+2x$ | 符合預期(故:太長了，但是是對的) |
| 測試一   | $1 3 3 5 5 4 4 3 3 2 1 6 5 3 2$ | 乘法 : $30x^10+24x^9+18x^8+15x^7+22x^6+17x^5+6x^4$ | 符合預期(故:太長了，但是是對的) |

### 編譯與執行指令
```shell
- C++ Compiler: C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe
- Command: g++.exe "D:\學校\c++\資料結構用\polynomi.cpp" -o "D:\學校\c++\資料結構用\polynomi.exe" -std=c++11 -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++" -L"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib" -L"C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\lib" -static-libgcc
```
### 結論

1.程式能正確執行所需內容。

2.就算不按照順序輸入，也可以輸出對的答案

## 申論及開發報告

### 使用稀疏矩陣原因

因為有實作的要求
