# -*- coding:utf-8 -*-
# Filename: MyArray.py
# --------------------
# Function description: Array and its operating
# --------------------
# Author: Dong Fuguo
# QQ: 306467355
# Email: dongfuguo2005@126.com
#--------------------
# Date: 2014-11-18, Updated on 2016-4-15
# --------------------


class MyArray:
    '''All the elements in this array must be numbers'''
    __value = []

    def __IsNumber(self, n):
        if not isinstance(n, (int, float, complex)):
            return False
        return True

    def __init__(self, *args):
        if not args:
            self.__value = []
        else:
            for arg in args:
                if not self.__IsNumber(arg):
                    print('All elements must be numbers')
                    return
            self.__value = list(args)

    #重载运算符+
    #数组中每个元素都与数字n相加，或两个数组相加，返回新数组
    def __add__(self, n):
        if self.__IsNumber(n):
            #数组中所有元素都与数字n相加
            b = MyArray()
            b.__value = [item+n for item in self.__value]
            return b
        elif isinstance(n, MyArray):
            #两个等长的数组对应元素相加
            if len(n.__value)==len(self.__value):
                c = MyArray()
                c.__value = [i+j for i, j in zip(self.__value, n.__value)]
                #for i, j in zip(self.__value, n.__value):
                #    c.__value.append(i+j)
                return c
            else:
                print('Lenght not equal')                
        else:
            print('Not supported')

    #重载运算符-
    ##数组中每个元素都与数字n相减，返回新数组
    def __sub__(self, n):
        if not self.__IsNumber(n):
            print('- operating with ', type(n), ' and number type is not supported.')
            return
        b = MyArray()
        b.__value = [item-n for item in self.__value]
        return b

    #重载运算符*
    #数组中每个元素都与数字n相乘，返回新数组
    def __mul__(self, n):
        if not self.__IsNumber(n):
            print('* operating with ', type(n), ' and number type is not supported.')
            return
        b = MyArray()
        b.__value = [item*n for item in self.__value]
        return b

    #重载运算符/
    #数组中每个元素都与数字n相除，返回新数组
    def __truediv__(self, n):
        if not self.__IsNumber(n):
            print(r'/ operating with ', type(n), ' and number type is not supported.')
            return
        b = MyArray()
        b.__value = [item/n for item in self.__value]
        return b

    #重载运算符//
    #数组中每个元素都与数字n整除，返回新数组
    def __floordiv__(self, n):
        if not isinstance(n, int):
            print(n, ' is not an integer')
            return
        b = MyArray()
        b.__value = [item//n for item in self.__value]
        return b

    #重载运算符%
    #数组中每个元素都与数字n求余数，返回新数组
    def __mod__(self, n):
        if not self.__IsNumber(n):
            print(r'% operating with ', type(n), ' and number type is not supported.')
            return
        b = MyArray()
        b.__value = [item%n for item in self.__value]
        return b

    #重载运算符**
    #数组中每个元素都与数字n进行幂计算，返回新数组
    def __pow__(self, n):
        if not self.__IsNumber(n):
            print('** operating with ', type(n), ' and number type is not supported.')
            return
        b = MyArray()
        b.__value = [item**n for item in self.__value]
        return b

    def __len__(self):        
        return len(self.__value)

    #直接使用该类对象作为表达式来查看对象的值
    def __repr__(self):
        #equivalent to return `self.__value`
        return repr(self.__value)

    #支持使用print()函数查看对象的值
    def __str__(self):
        return str(self.__value)

    #追加元素
    def append(self, v):
        if not self.__IsNumber(v):
            print('Only number can be appended.')
            return
        self.__value.append(v)

    #获取指定下标的元素值，支持使用列表或元组指定多个下标
    def __getitem__(self, index): 
        length = len(self.__value)
        #如果指定单个整数作为下标，则直接返回元素值
        if isinstance(index, int) and 0<=index<length: 
            return self.__value[index]
        #使用列表或元组指定多个整数下标
        elif isinstance(index, (list,tuple)):
            for i in index:
                if not (isinstance(i,int) and 0<=i<length):
                    return 'index error'
            result = []
            for item in index:
                result.append(self.__value[item])
            return result
        else:
            return 'index error'

    #修改元素值，支持使用列表或元组指定多个下标，同时修改多个元素值
    def __setitem__(self, index, value):
        length = len(self.__value)
        #如果下标合法，则直接修改元素值
        if isinstance(index, int) and 0<=index<length:
            self.__value[index] = value
        #支持使用列表或元组指定多个下标
        elif isinstance(index, (list,tuple)):
            for i in index:
                if not (isinstance(i,int) and 0<=i<length):
                    raise Exception('index error')
            #如果下标和给的值都是列表或元组，并且个数一样，则分别为多个下标的元素修改值
            if isinstance(value, (list,tuple)):
                if len(index) == len(value):
                    for i, v in enumerate(index):
                        self.__value[v] = value[i]
                else:
                    raise Exception('values and index must be of the same length')
            #如果指定多个下标和一个普通值，则把多个元素修改为相同的值
            elif isinstance(value, (int,float,complex)):
                for i in index:
                    self.__value[i] = value
            else:
                raise Exception('value error')
        else:
            raise Exception('index error')

    #支持成员测试运算符in，测试数组中是否包含某个元素
    def __contains__(self, v):        
        if v in self.__value:
            return True
        return False

    #模拟向量内积
    def dot(self, v):
        if not isinstance(v, MyArray):
            print(v, ' must be an instance of MyArray.')
            return
        if len(v) != len(self.__value):
            print('The size must be equal.')
            return
        return sum([i*j for i,j in zip(self.__value, v.__value)])
        #b = MyArray()
        #for m, n in zip(v.__value, self.__value):
        #    b.__value.append(m * n)
        #return sum(b.__value)

    #重载运算符==，测试两个数组是否相等
    def __eq__(self, v):
        if not isinstance(v, MyArray):
            print(v, ' must be an instance of MyArray.')
            return False
        if self.__value == v.__value:
            return True
        return False

    #重载运算符<，比较两个数组大小
    def __lt__(self, v):
        if not isinstance(v, MyArray):
            print(v, ' must be an instance of MyArray.')
            return False
        if self.__value < v.__value:
            return True
        return False

if __name__ == '__main__':
    print('Please use me as a module.')
