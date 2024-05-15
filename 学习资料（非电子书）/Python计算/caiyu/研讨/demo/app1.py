# 导入Flask类
from flask import Flask

# Flask类接收一个参数__name__
app = Flask(__name__)


# 装饰器的作用是将路由映射到视图函数index
@app.route('/')
def index():
    return 'Hello World'


# 路由传递的参数默认当做string处理，这里指定int，尖括号中冒号后面的内容是动态的
@app.route('/user/<int:id>')
def router_test(id):
    return '%d' % id


# Flask应用程序实例的run方法启动WEB服务器
if __name__ == '__main__':
    app.run()
