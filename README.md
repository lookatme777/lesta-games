# LESTA-GAMES

## Задание №1

- [x] На языке С/С++, написать алгоритм (функцию) определения четности целого числа, который будет аналогичен нижеприведенному по функциональности, но отличен по своей сути. Объяснить плюсы и минусы обеих реализаций.
C/C++ example:
```cpp
bool isEven(int value)
{
	return value%2==0;
}
```

Побитовое И (**&**) с 1 проверяет последний бит числа. Если последний бит равен 0, число четное. Если 1 — нечетное.

```cpp
bool isEven2(int value)
{
	return (value & 1) == 0;
}
```

| CODE | MVSC | **GCC 14.1** | **CLANG 18.1.0** |
|------|------|--------------|------------------|
| return value%2 == 0; | ```asm
bool isEven(int value)
{
00007FF681B31D20  mov         dword ptr [rsp+8],ecx  
00007FF681B31D24  push        rbp  
00007FF681B31D25  push        rdi  
00007FF681B31D26  sub         rsp,0F8h  
00007FF681B31D2D  lea         rbp,[rsp+20h]  
00007FF681B31D32  lea         rcx,[__A573B7E6_main@cpp (07FF681B4206Ah)]  
00007FF681B31D39  call        __CheckForDebuggerJustMyCode (07FF681B31366h)  
00007FF681B31D3E  nop  
  return value % 2 == 0;
00007FF681B31D3F  mov         eax,dword ptr [value]  
00007FF681B31D45  cdq  
00007FF681B31D46  and         eax,1  
00007FF681B31D49  xor         eax,edx  
00007FF681B31D4B  sub         eax,edx  
00007FF681B31D4D  test        eax,eax  
00007FF681B31D4F  jne         isEven+3Dh (07FF681B31D5Dh)  
00007FF681B31D51  mov         dword ptr [rbp+0C0h],1  
00007FF681B31D5B  jmp         isEven+47h (07FF681B31D67h)  
00007FF681B31D5D  mov         dword ptr [rbp+0C0h],0  
00007FF681B31D67  movzx       eax,byte ptr [rbp+0C0h]  
}
```
| return (value&1) == 0; |





<br></br>
## Задание №2


- [x] На языке С++, написать минимум по 2 класса реализовывающих циклический буфер. Объяснить плюсы и минусы каждой реализации.

**Первый** [кольцевой буфер](https://github.com/lookatme777/lesta-games/tree/main/ringbuffer/ringbuffer) был реализован на основе собственного умного указателя, а **второй** был реализован при помощи [односвязного списка](https://github.com/lookatme777/lesta-games/tree/main/ringbufferv2/ringbufferV2/ringbufferV2). Отличие этих буферов лишь в скорости некоторых операций, которые приведены ниже. Выбор реализации завасит от поставленной задачи.

| based on | вставка в начало | вставка в конец | удаление с начала | удаление с конца | доступ по индексу | 
|----------|------------------|-----------------|-------------------|------------------|-------------------|
| **vector** | **O(n)** | **O(1)** | **O(n)** | **O(1)** | **O(1)** |
| **forward list** | **O(1)** | **O(1)** | **O(1)** | **O(1)** | **O(n)** |

## Задание №3

