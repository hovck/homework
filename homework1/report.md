# 51115117
作業1
## 解題說明

本題要求實現ackermann function

### 解題策略

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;
unsigned int ack(unsigned int m, unsigned int n) {
	if (m == 0) {return n + 1;}
	if (n == 0) {return ack(m-1,1);}
	return ack(m-1, ack(m,n-1));
}
int main() {
	int m,n;
	cin >> m >>n;
	cout << "A(" << m << ", " << n << ") = " << ack(m, n) << "\n";
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O()$。
2. 空間複雜度：空間複雜度為 $O()$。

## 測試與驗證

### 測試案例
### 編譯與執行指令
```shell
```
### 結論
## 申論及開發報告
### 原因
