# 关于Swampy.Turtle中画图函数

在TurtleWorld模块之中，可以通过两类写法控制乌龟：

1. `bob.fd(100)`----> Turtlename.functionname() 对象.方法(形参)
2. `fd(bob, 100)` ---->  functionname(Turtlename) 方法(形参)

## 1. 对象.方法(形参)

第1种方式易于理解，原因是Turtle类之中实现了fd方法，则由Turtle类创建出的对象可以使用fd方法。

和普通函数相比，在类中定义的成员方法有一点不同(类方法、静态方法此处不讨论)，就是**第一参数**永远是**类的本身实例变量**`self`，并且调用时，不用传递该参数。例如下图(**TurtleWorld.py, line 176**)中的类内成员函数

<img src="C:\Users\Silence\AppData\Roaming\Typora\typora-user-images\image-20220321165115870.png" alt="image-20220321165115870" style="zoom:67%;" />

下图使用工具验证：(Pychram快捷键`ctrl + p`)

![image-20220321165451574](C:\Users\Silence\AppData\Roaming\Typora\typora-user-images\image-20220321165451574.png)



## 2. 方法(形参)

第2种方式，通过阅读TurtleWorld模块的源码，可以找到此模块的作者在下图处(**TurtleWorld.py, line 225**)定义了全局变量，这些全局变量(fd/bk/lt...)为Turtle类中成员方法的引用。由于均为全局变量，因此可以在`__main__`函数之中直接使用，并且这些全局变量(fd/bk/lt...)的值也没有被改变，也无需再使用`global`声明

<img src="C:\Users\Silence\AppData\Roaming\Typora\typora-user-images\image-20220321164030601.png" alt="image-20220321164030601" style="zoom: 67%;" />

下图粗体说明光标位置处对应第一个形参self,形参类型为Turtle

![image-20220321165507550](C:\Users\Silence\AppData\Roaming\Typora\typora-user-images\image-20220321165507550.png)

## 3. 总结

下面举一个同类型的例子，进一步说明：

<img src="C:\Users\Silence\AppData\Roaming\Typora\typora-user-images\image-20220321171734645.png" alt="image-20220321171734645" style="zoom:67%;" />

同时借助一些工具，观察变量的类型，可以更好地理解**python中万物皆对象**的思想

<img src="C:\Users\Silence\AppData\Roaming\Typora\typora-user-images\image-20220321171900226.png" alt="image-20220321171900226" style="zoom:67%;" />