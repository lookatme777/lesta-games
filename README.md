# LESTA-GAMES

## Задание №1

- [x] На языке С/С++, написать алгоритм (функцию) определения четности целого числа, который будет аналогичен нижеприведенному по функциональности, но отличен по своей сути. Объяснить плюсы и минусы обеих реализаций.
C/C++ example:
```cpp
bool isEven(int value)
{
	return value % 2 == 0;
}
```

Побитовое И (**&**) с 1 проверяет последний бит числа. Если последний бит равен 0, число четное. Если 1 — нечетное.

```cpp
bool isEven2(int value)
{
	return (value & 1) == 0;
}
```

Во всех компиляторах кроме GCC есть оптимизация, следовательно компилятору нужно **меньше** команд, чтобы выполнить функцию.

<details>
	<summary>MVSC</summary>
	
```asm
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

bool isEven2(int value)
{
00007FF6A7D41810  mov         dword ptr [rsp+8],ecx  
00007FF6A7D41814  push        rbp  
00007FF6A7D41815  push        rdi  
00007FF6A7D41816  sub         rsp,0F8h  
00007FF6A7D4181D  lea         rbp,[rsp+20h]  
00007FF6A7D41822  lea         rcx,[__A573B7E6_main@cpp (07FF6A7D5206Ah)]  
00007FF6A7D41829  call        __CheckForDebuggerJustMyCode (07FF6A7D41366h)  
00007FF6A7D4182E  nop  
  return (value & 1) == 0;
00007FF6A7D4182F  mov         eax,dword ptr [value]  
00007FF6A7D41835  and         eax,1  
00007FF6A7D41838  test        eax,eax  
00007FF6A7D4183A  jne         isEven2+38h (07FF6A7D41848h)  
00007FF6A7D4183C  mov         dword ptr [rbp+0C0h],1  
00007FF6A7D41846  jmp         isEven2+42h (07FF6A7D41852h)  
00007FF6A7D41848  mov         dword ptr [rbp+0C0h],0  
00007FF6A7D41852  movzx       eax,byte ptr [rbp+0C0h]  
}
```
</details>


<details>
<summary>GCC</summary>
	
```asm
isEven2(int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi
        mov     eax, DWORD PTR [rbp-4]
        and     eax, 1
        test    eax, eax
        sete    al
        pop     rbp
        ret

isEven(int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi
        mov     eax, DWORD PTR [rbp-4]
        and     eax, 1
        test    eax, eax
        sete    al
        pop     rbp
        ret
```
</details>

<details>
<summary>CLANG</summary>

```asm
isEven2(int):                            # @isEven2(int)
        push    rbp
        mov     rbp, rsp
        mov     dword ptr [rbp - 4], edi
        mov     eax, dword ptr [rbp - 4]
        and     eax, 1
        cmp     eax, 0
        sete    al
        and     al, 1
        movzx   eax, al
        pop     rbp
        ret

isEven(int):                             # @isEven(int)
        push    rbp
        mov     rbp, rsp
        mov     dword ptr [rbp - 4], edi
        mov     eax, dword ptr [rbp - 4]
        mov     ecx, 2
        cdq
        idiv    ecx
        cmp     edx, 0
        sete    al
        and     al, 1
        movzx   eax, al
        pop     rbp
        ret
```
</details>






<br></br>
## Задание №2


- [x] На языке С++, написать минимум по 2 класса реализовывающих циклический буфер. Объяснить плюсы и минусы каждой реализации.

**Первый** [кольцевой буфер](https://github.com/lookatme777/lesta-games/tree/main/ringbuffer/ringbuffer) был реализован на основе собственного умного указателя, а **второй** был реализован при помощи [односвязного списка](https://github.com/lookatme777/lesta-games/tree/main/ringbufferv2/ringbufferV2/ringbufferV2). Отличие этих буферов лишь в скорости некоторых операций, которые приведены ниже. Выбор реализации завасит от поставленной задачи.

| based on | вставка в начало | вставка в конец | удаление с начала | удаление с конца | доступ по индексу | 
|----------|------------------|-----------------|-------------------|------------------|-------------------|
| **vector** | **O(n)** | **O(1)** | **O(n)** | **O(1)** | **O(1)** |
| **forward list** | **O(1)** | **O(1)** | **O(1)** | **O(1)** | **O(n)** |

## Задание №3

