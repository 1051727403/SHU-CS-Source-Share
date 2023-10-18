## 寄存器

**通用寄存器**

AX (Accumulator)：累加寄存器，也称之为累加器；

BX (Base)：基地址寄存器；

CX (Count)：计数器寄存器；

DX (Data)：数据寄存器；

**变址寄存器**

SI (Source Index)：源变址寄存器；

DI (Destination Index)：目的变址寄存器；

**段寄存器：**

CS (Code Segment)：代码段寄存器；

DS (Data Segment)：数据段寄存器；

SS (Stack Segment)：堆栈段寄存器；

ES (Extra Segment)：附加段寄存器；

#### Flag寄存器

```assembly
of  ;溢出标志位, 记录有符号数运算
cf  ;溢出标志位, 记录无符号数运算
df  ;方向标志位, 用于串指令, df == 0 递增, 反之递减
if  ;中断允许标志位, if == 0 禁止可屏蔽中断
tf  ;跟踪标志位, tf == 0 cpu正常运行, tf == 1, cpu处于单步状态, 每执行一条指令自动产生一次中断
sf  ;符号标志位, 有符号数, 符号为0, sf == 0, 符号为1, sf == 1
zf  ;零标志位, 运算结果是否为0
af  ;调整标志位, 低4位是否进位或借位
pf  ;奇偶标志位, 运算结果是否为偶数
cf  ;进位标志位, 无符号数 记录进位和借位
```

#### 位移

```assembly
rol	 ;循环左移
ror  	 ;循环右移

```

#### 设置标志位

```assembly
cld		;设置df = 0
std     ;设置df = 1

cli     ;设置if = 0
sti     ;设置if = 1

clc     ;设置cf = 0
stc     ;设置cf = 1
cmc     ;cf取反

```

#### jmp

```assembly
jl    ;jump if 0
jz    ;若zf = 1, jump
jnz   ;若zf = 0, jump
js    ;若sf = 1, jump
jns   ;若sf = 0, jump
ja    ;若af = 1, jump
jna   ;若af = 0, jump
a
```

#### cmp

跳转指令的选择

```assembly
cmp ax, bx
jb EXIT
;若ax<bx 则跳转EXIT;


; 其他情况
if ax < bx -> jb
if ax > bx -> ja
if ax = bx -> je
```

#### lea

```assembly
Load Effective Address
```

## 伪指令

#### end start

```assembly
start:
 ...
end start
```

此处start标签可为任意名称

end表示该标签是程序的入口,并非表示标签需要结束, 段才需要声明结束(用 xx ends 声明)

end 之后的代码不会在进行编译

#### 输出字符

```assembly
mov dl 61H
mov ah 02H
int 21H
```

#### 输出字符串

```assembly
mov ds 00H
mov dx 00H
mov ah 09H
int 21H
```

#### 回车换行

```assembly
CRLF db 0ah, 0dh, '$'
```

#### forbidden

非法指令

```assembly
; 给段寄存器赋值

```

#### 寻址方式

```assembly
# 立即寻址方式
mov ax, 5	;ax = 5

# 寄存器寻址方式
mov ax, bx	;ax = bx

# 直接寻址方式
mov ax, [2000h]	;ax = ds:[2000h]

# 寄存器间接寻址方式
mov ax, [bx]	;ax = ds:[bx]

# 寄存器相对寻址方式
mov ax, [bx + offset]	; bx, bp, si, di 合法

# 基址变址寻址
mov ax, [bx][si]		; ax = ds:[bx]
mov ax, [bp][si]		; ax = ss:[bp]

# 相对基址变址寻址方式
mov ax, offset[bx][si]		; ax = ds:[bx+offset]
mov ax, offset[bp][si]		; ax = ss:[bp+offset]

# 

```

#### 16位乘法

```assembly
mov ax, 300
mov bx, 300
mul bx

=> 结果DX存放高位, AX存放低位
```

#### 16位除法

```assembly

```

## debug

-r  查看寄存器

    r cx   修改寄存器值

-u  查看内存汇编格式指令

-d 查看内存机器码格式指令

    d ds:0  查看ds:0地址处的指令

-t  单步执行命令

-g  运行直到断点或结束

-q  退出

-a [地址] 写入汇编



#### func

常用函数功能, 以更快的完成实验, 提升可读性, 减少bug


## Tutorial

使用masm汇编, 采用dosbox虚拟环境, 推荐vscode编辑器

课本IBM-PC汇编语言程序设计

#### Lesson 1

Materials:

1. HelloWorld.asm

Task:

    1. 了解汇编代码的结构, 掌握编译工具

#### Lesson 2

Materials:

    1. assembly.md

Task:

1. 学习基础指令 mov, add, sub, jmp, loop
2. 理解代码执行顺序
3. 构造一个错误的执行顺序
4. 使用Debug调试并观察结果

#### Lesson 3

method.jpg

理解call指令的底层

#### Lesson 4

Require: 理解函数栈

Task: 封装常用函数
