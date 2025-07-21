# 51115117
作業1
## 解題說明

本題要求實現ackermann function

### 解題策略

使用遞迴函數實現ackermann function內容

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
2. 空間複雜度：空間複雜度為 $O(m+n)$。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m$ $n$| 預期輸出 | 實際輸出 |
|----------|--------------|-----------|---------|
| 測試一   | $m = 1$ $n = 0$ | 2       | 2        |
| 測試二   | $m = 2$ $n = 5$ | 13      | 13       |
| 測試三   | $m = 3$ $n = 10$ | 8189    | 8189     |
| 測試四   | $m = 3$ $n = 13$ | 65533   | 異常拋出  |
| 測試五   | $m = 4$ $n = 1$ | 65533 | 異常拋出 |

### 編譯與執行指令
```shell
3 13

-----------------
Process exited after 7.53 seconds with return value 3221225725
```
### 結論

1.程式無法正確運行 $m >= 4$ 的情況，但 $m = 4$ $n = 0$ 時可運行。

2. $m = 3$ 時 $n <= 12 $ 可執行成功

## 申論及開發報告

### 使用遞迴原因

**簡單且直觀**

   遞迴的使用可以符合該函數定義，且易於實現
