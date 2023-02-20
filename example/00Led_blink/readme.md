<!--
 * @Author: rx-ted
 * @Date: 2023-02-18 21:30:26
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-02-20 08:49:13
-->
# 【国民技术N32项目移植】基于Arduino简单版的点灯项目移植

N32G4FR 简单移植arduino库，简单点灯熄灯，延迟开灯等  
反复的点亮LED一秒钟，然后关闭LED一秒钟。

## 功能

```c
// 创建Arduino.h
// 模仿函数
/**
 *  pinMode()
 * @param pin—引脚 GPIO序号 查看pin.c源代码
 * @param Mode—模式 1.输出(OUTPUT)模式;2.输入(INPUT)模式;3.输入上拉（INPUT_PULLUP）模式 
 */
pinMode(pin,Mode) // 函数：定义引脚模式

/**
 * digitalWrite()
 * @param pin：GPIO序号 查看pin.c源代码
 * @param value：HIGH或LOW
 */
digitalWrite(pin, value)
/**
 * delay()
 * @param ms 多少毫秒
 */
delay(ms)

```

## 代码

```c
int main(){
    int ledPin = PIN_GET(B,5);//定义引脚D3
    pinMode( ledPin, OUTPUT);
    while(1){
    digitalWrite(ledPin, HIGH);//LED灯亮
    delay(1000);//等待1秒
    digitalWrite(ledPin, LOW);//LED灯灭
    delay(1000);
    }
}
```

## 总结

实现了，脑子会想到与N32G4FR和Arduino完全相同的，是的arduino上的语法N32G4FR都兼容的。这让我们面对N32G4FR时省了不少的功夫.

## 演示结果
