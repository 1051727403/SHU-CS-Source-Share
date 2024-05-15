from socket import *

from PyQt5.QtWidgets import QApplication
from PyQt5 import uic
from PyQt5.QtCore import QThread, pyqtSignal

server_ip = '127.0.0.1'
server_port = '9002'


class Stats:
    def __init__(self):
        # 从文件中加载UI定义
        self.ui = uic.loadUi("UDPServer.ui")
        # 给文本输入框绑定事件
        self.ui.server_ip.setText(server_ip)
        self.ui.server_port.setText(server_port)
        self.ui.server_ip.textChanged.connect(self.handleServerIpChanged)
        self.ui.server_port.textChanged.connect(self.handleServerPortChanged)
        self.ui.start.clicked.connect(self.handleStartButtonClicked)
        # 成员变量
        self.server_message = ''
        self.udp = UDPThread()
        self.handleStartButtonClicked()

    # 启动server
    def handleStartButtonClicked(self):
        self.ui.start.setEnabled(False)
        # 开启一个新线程
        self.udp.start()
        self.udp.show.connect(self.display)

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


class UDPThread(QThread):
    show = pyqtSignal(str)

    def __init__(self):
        super(QThread, self).__init__()

    def run(self):
        self.show.emit(server_ip + ':' + str(server_port) + '\n' + '启动中...' + '\n')
        # 创建UDP socket
        # AF_INET表示使用的是IPv4地址, SOCK_DGRAM表示该socket是一个UDP socket
        server_socket = socket(AF_INET, SOCK_DGRAM)
        self.show.emit('创建UDP socket成功!\n')
        try:
            server_socket.bind(('', int(server_port)))
        except OSError:
            server_socket.close()
            self.show.emit('clear')
            self.show.emit('通常每个套接字地址(协议/网络地址/端口)只允许使用一次!' + '\n')
            self.show.emit('请重新启动~' + '\n')
            return
        self.show.emit('启动成功, 等待UDP请求...' + '\n')
        while True:
            message, client_address = server_socket.recvfrom(2048)
            self.show.emit('收到来自:' + str(client_address[0]) + '的信息: ' + message.decode() + '\n')
            modified_message = message.decode().upper()
            self.show.emit('返回修改后的信息: ' + modified_message + '\n')
            server_socket.sendto(modified_message.encode(), client_address)
            self.show.emit('---------------UDP请求完成---------------' + '\n')


if __name__ == '__main__':
    app = QApplication([])
    stats = Stats()
    stats.ui.show()
    app.exec_()
