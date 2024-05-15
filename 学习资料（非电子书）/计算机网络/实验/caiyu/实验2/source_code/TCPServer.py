from socket import *

from PyQt5.QtWidgets import QApplication
from PyQt5 import uic
from PyQt5.QtCore import QThread, pyqtSignal

server_ip = '127.0.0.1'
server_port = '9001'


class Stats:
    def __init__(self):
        # 从文件中加载UI定义
        self.ui = uic.loadUi("TCPServer.ui")
        # 给文本输入框绑定事件
        self.ui.server_ip.setText(server_ip)
        self.ui.server_port.setText(server_port)
        self.ui.server_ip.textChanged.connect(self.handleServerIpChanged)
        self.ui.server_port.textChanged.connect(self.handleServerPortChanged)
        self.ui.start.clicked.connect(self.handleStartButtonClicked)
        # 成员变量
        self.server_message = ''
        self.tcp = TCPThread()
        self.handleStartButtonClicked()

    # 启动server
    def handleStartButtonClicked(self):
        self.ui.start.setEnabled(False)
        # 开启一个新线程
        self.tcp.start()
        self.tcp.show.connect(self.display)

    def display(self, str):
        if str == 'clear':
            self.server_message = ''
            self.set_server_message('')
            return
        self.set_server_message(str)

    def set_server_message(self, string):
        self.server_message += string
        self.ui.server_message.setText(self.server_message)

    def handleServerIpChanged(self):
        server_ip = self.ui.server_ip.text()

    def handleServerPortChanged(self):
        server_port = self.ui.server_port.text()


class TCPThread(QThread):
    show = pyqtSignal(str)

    def __init__(self):
        super(QThread, self).__init__()

    def run(self):
        self.show.emit(server_ip + ':' + str(server_port) + '\n' + '启动中...' + '\n')
        # 创建欢迎socket
        server_socket = socket(AF_INET, SOCK_STREAM)
        self.show.emit('创建欢迎socket成功!\n')
        try:
            server_socket.bind(('', int(server_port)))
        except OSError:
            server_socket.close()
            self.show.emit('clear')
            self.show.emit('通常每个套接字地址(协议/网络地址/端口)只允许使用一次!' + '\n')
            self.show.emit('请修改端口号后重新启动~' + '\n')
            return
        # 设置请求的最大连接数
        server_socket.listen(10)
        self.show.emit('启动成功, 等待TCP请求...' + '\n')
        while True:
            # 完成握手, 创建连接socket
            connection_socket, address = server_socket.accept()
            self.show.emit('完成握手, 创建连接socket成功!\n')
            # 接收客户传递的信息
            message = connection_socket.recv(2048)
            self.show.emit('收到来自:' + str(address) + '的信息: ' + message.decode() + '\n')
            modified_message = message.decode().upper()
            connection_socket.send(modified_message.encode())
            self.show.emit('返回修改后的信息: ' + modified_message + '\n')
            # 关闭本次连接
            connection_socket.close()
            self.show.emit('关闭本次TCP连接\n')
            self.show.emit('---------------TCP请求完成---------------' + '\n')


if __name__ == '__main__':
    app = QApplication([])
    stats = Stats()
    stats.ui.show()
    app.exec_()
