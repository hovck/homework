# 51115117
作業2
## 解題說明

本題要求找出集合的每種可能性(包含空集合)

### 解題策略

根據子集合的數量( 如:空集合=選0 )來呼叫遞迴函數

使用遞回來實作內容，實作方法為:

使用第幾索引(index)( 程式碼中寫為in )作為 " 總陣列(  $cin>>input[n]$  )中的目前指向索引 "

使用目前大小(currentsize)( 程式碼中寫為cs )作為 " 目前已經被選擇的數量 "

使用目標大小(target)( 程式碼中寫為ts )作為 " 需要選擇的數量 "

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;

int spacecount=0;
const int MN = 20;
string input[MN];
string current[MN];
int n=0;
void set(int in, int cs, int ts) {
    if (in == n) {
        if (cs == ts) {
            cout << "(";
            for (int i = 0; i < cs; ++i) {
                cout << "\"" << current[i] << "\"";
                if (i < cs - 1) cout << ",";
            }
			cout << ")" << endl;}
        return;}
    current[cs] = input[in];
    set(in + 1, cs + 1, ts);
    set(in + 1, cs, ts);
}
int main() {
	while (cin >> input[n]) {
		++n;
		if (cin.peek() == '\n') break; // 偵測是否換行
	}
    for (int size = 0; size <= n; ++size) {
        cout << "Size=" << size << endl;
        set(0, 0, size);
    }
    return 0;
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(2^n)$。
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 | 預期輸出 | 實際輸出 |
|----------|--------------|-----------|---------|
| 測試一   | $1$ $2$ $3$ | $()$ $(1)$ $(2)$ $(3)$ $(1,2)$ $(1,3)$ $(2,3)$ $(1,2,3)$ |符合預期(故:太長了，但是是對的)|
| 測試二   | $1$ $2$ $3$ $4$| $()$ $(1)$ $(2)$ $(3)$ $(4)$ $(1,2)$ $(1,3)$ $(1,4)$ $(2,3)$ $(2,4)$ $(3,4)$ $(1,2,3)$ $(1,2,4)$ $(1,3,4)$ $(2,3,4)$ $(1,2,3,4)$|符合預期(故:太長了，但是是對的)|
| 測試三   | $a$ $c$ $b$ | $()$ $(a)$ $(c)$ $(b)$ $(a,c)$ $(a,b)$ $(c,b)$ $(a,c,b)$ |符合預期(故:太長了，但是是對的)|

### 編譯與執行指令
```shell
- C++ Compiler: C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe
- Command: g++.exe "D:\學校\c++\資料結構用\子集合.cpp" -o "D:\學校\c++\資料結構用\子集合.exe" -std=c++11 -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include" -I"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++" -L"C:\Program Files (x86)\Dev-Cpp\MinGW64\lib" -L"C:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\lib" -static-libgcc

```
### 結論

1.程式能正確執行所需內容。

2.由於MN=20的上限，因此輸入值最多只能為長度20的陣列。

3.由於方便觀看，程式碼(cout)與測試案例的預期輸出其實有些許差距。

4.程式碼為將輸入內容全拆為字串作處理，因此若是內容本身就不按照順序 如: $(a,c,b)$ 則輸出內容就不按照順序(如測試三結果)，而是按照陣列的順序而定

## 申論及開發報告

### 使用遞迴的原因

因為剛學到要用遞迴，且我暫時還沒想到用迴圈的方式
