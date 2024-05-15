class simNumpyArray(object):
    def __init__(self, p):
        '''可以接收列表、元组、range对象等类型的数据，并且每个元素都必须为数字'''
        if type(p) not in (list, tuple, range):
            print('data type error')
            return
        for item in p:
            #下面这行用来判断参数类型，可以这样写
            #if isinstance(item, (int, float, complex)):
            if type(item) not in (int, float, complex):
                print('data type error')
                return
        self.__data = [list(p)]
        self.__row = 1
        self.__col = len(p)

    #析构函数
    def __del__(self):
        del self.__data

    #修改大小，首先检查给定的大小参数是否合适
    def reshape(self, size):
        '''参数必须为元组或列表，如(row,col)或[row,col]
           row或col其中一个可以为-1，表示自动计算
        '''
        if not (isinstance(size, list) or isinstance(size, tuple)):
            print('size parameter error')
            return
        if len(size) != 2:
            print('size parameter error')
            return
        if (not isinstance(size[0],int)) or (not isinstance(size[1],int)):
            print('size parameter error')
            return
        if size[0] != -1 and size[1] != -1 and size[0]*size[1] != self.__row*self.__col:
            print('size parameter error')
            return
        #行数或列数为-1表示该值自动计算
        if size[0] == -1:
            if size[1] == -1 or (self.__row*self.__col)%size[1] != 0:
                print('size parameter error')
                return
        if size[1] == -1:
            if size[0] == -1 or (self.__row*self.__col)%size[0] != 0:
                print('size parameter error')
                return
                
        #重新合并数据
        data = [t for i in self.__data for t in i]
        #修改大小
        if size[0] == -1:
            self.__row = int(self.__row*self.__col/size[1])
            self.__col = size[1]
        elif size[1] == -1:
            self.__col = int(self.__row*self.__col/size[0])
            self.__row = size[0]
        else:
            self.__row = size[0]
            self.__col = size[1]            
        self.__data = [[data[row*self.__col+col] for col in range(self.__col)] for row in range(self.__row)]

    #在交互模式直接使用变量名作为表达式查看值时调用该函数
    def __repr__(self):
        #return repr('\n'.join(map(str, self.__data)))
        for i in self.__data:
            print(i)
        return ''

    #使用print()函数输出值时调用该函数
    def __str__(self):
        return '\n'.join(map(str, self.__data))
    
    #属性，矩阵转置
    @property
    def T(self):
        b = simNumpyArray([t for i in self.__data for t in i])
        b.reshape((self.__row, self.__col))
        b.__data = list(map(list,zip(*b.__data)))
        b.__row, b.__col = b.__col, b.__row
        return b

    #通用代码，适用于矩阵与整数、实数、复数的加、减、乘、除、整除、幂
    def __operate(self, n, op):
        b = simNumpyArray([t for i in self.__data for t in i])
        b.reshape((self.__row, self.__col))
        b.__data = [[eval(str(j)+op+str(n)) for j in item] for item in b.__data]
        return b

    #通用代码，适用于矩阵之间的加、减
    def __matrixAddSub(self, n, op):
        c = simNumpyArray([1])
        c.__row = self.__row
        c.__col = self.__col
        c.__data = [[eval(str(x[i])+op+str(y[i])) for i in range(len(x))] for x,y in zip(self.__data, n.__data)]
        return c
    
    #所有元素统一加一个数字，或者两个矩阵相加
    def __add__(self, n):
        #参数是整数或实数，则返回矩阵
        #其中的每个元素为原矩阵中元素与该整数或实数的加法结果
        if type(n) in (int, float, complex):
            return self.__operate(n, '+')
        elif isinstance(n, simNumpyArray):
            #如果参数为同类型矩阵，且大小一致，则为两个矩阵中对应元素相加
            if n.__row==self.__row and n.__col==self.__col:
                return self.__matrixAddSub(n, '+')
            else:
                print('two matrix must be the same size')
                return
        else:
            print('data type error')
            return
            
    #所有元素统一减一个数字，或者两个矩阵相减
    def __sub__(self, n):
        #参数是整数或实数，则返回矩阵
        #其中的每个元素为原矩阵中元素与该整数或实数的加法结果
        if type(n) in (int, float, complex):
            return self.__operate(n, '-')
        elif isinstance(n, simNumpyArray):
            #如果参数为同类型矩阵，且大小一致，则为两个矩阵中对应元素相减
            if n.__row==self.__row and n.__col==self.__col:
                #先实例化一个临时对象，其值临时为[1]
                return self.__matrixAddSub(n, '-')
            else:
                print('two matrix must be the same size')
                return
        else:
            print('data type error')
            return
            
    #所有元素统一乘一个数字，或者两个矩阵相乘
    def __mul__(self, n):
        #参数是整数或实数，则返回矩阵
        #其中的每个元素为原矩阵中元素与该整数或实数的加法结果
        if type(n) in (int, float, complex):
            return self.__operate(n, '*')
        elif isinstance(n, simNumpyArray):
            #如果参数为同类型矩阵，且第一个矩阵的列数等于第二个矩阵的行数
            if n.__row==self.__col:     
                data = []
                for row in self.__data:
                    t = []
                    for ii in range(n.__col):
                        col = [c[ii] for c in n.__data]
                        tt = sum([i*j for i,j in zip(row,col)])
                        t.append(tt)
                    data.append(t)
                c = simNumpyArray([t for i in data for t in i])
                c.reshape((self.__row, n.__col))
                return c
            else:
                print('size error.')
                return
        else:
            print('data type error')
            return
        
    #所有元素统一除以一个数字，本程序使用Python 3.5.1编写，真除法
    def __truediv__(self, n):
        if type(n) in (int, float, complex):
            return self.__operate(n, '/')
        else:
            print('data type error')
            return

    #矩阵元素与数字计算整商
    def __floordiv__(self, n):
        if type(n) in (int, float, complex):
            return self.__operate(n, '//')
        else:
            print('data type error')
            return
        
    #矩阵与数字的幂运算
    def __pow__(self, n):
        if type(n) in (int, float, complex):
            return self.__operate(n, '**')
        else:
            print('data type error')
            return

    #测试两个矩阵是否相等
    def __eq__(self, n):
        if isinstance(n, simNumpyArray):
            if self.__data == n.__data:
                return True
            else:
                return False
        else:
            print('data type error')
            return

    #测试矩阵自身是否小于另一个矩阵
    def __lt__(self, n):
        if isinstance(n, simNumpyArray):
            if self.__data < n.__data:
                return True
            else:
                return False
        else:
            print('data type error')
            return

    #成员测试运算符
    def __contains__(self, v):
        if v in self.__data:
            return True
        else:
            return False

    #支持迭代
    def __iter__(self):
        return iter(self.__data)

    #通用方法，计算三角函数
    def __triangle(self, method):
        try:
            b = simNumpyArray([t for i in self.__data for t in i])
            b.reshape((self.__row, self.__col))
            b.__data = [[eval("__import__('math')."+method+"("+str(j)+")") for j in item] for item in b.__data]
            return b
        except:
            return 'method error'
        
    #属性，对所有元素求正弦
    @property
    def Sin(self):        
        return self.__triangle('sin')

    #属性，对所有元素求余弦
    @property
    def Cos(self):
        return self.__triangle('cos')
