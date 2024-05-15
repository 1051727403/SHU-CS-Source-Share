from PyQt5.QtWidgets import QApplication
from PyQt5 import uic
from socket import *


class Stats:
    def __init__(self):
        # 从文件中加载UI定义
        self.ui = uic.loadUi("client.ui")
        # 给文本输入框绑定事件
        self.ui.target_ip.setText('127.0.0.1')
        self.ui.target_port.setText('9001')
        self.ui.target_ip.textChanged.connect(self.handleTargetIpChanged)
        self.ui.target_port.textChanged.connect(self.handleTargetPortChanged)
        self.ui.client_message.textChanged.connect(self.handleClientMessageChanged)
        self.ui.buttonGroup.buttonClicked.connect(self.handleButtonGroupClicked)
        self.ui.send.clicked.connect(self.handleSendButtonClicked)
        # 成员变量
        self.target_ip = '127.0.0.1'
        self.target_port = 9001
        self.option = 'TCP'
        self.client_message = ''
        self.recv_message = ''

    def handleSendButtonClicked(self):
        if self.target_ip == '' or self.target_port == 0 or self.client_message == '':
            print('输入error')
            return
        client_message = self.client_message
        if self.option == 'TCP':
            self.set_recv_message('开始执行...\n')
            # AF_INET表示使用IPv4地址, SOCK_STREAM表示该socket为TCP socket
            client_socket = socket(AF_INET, SOCK_STREAM)
            # 执行三次握手, 并建立TCP连接
            try:
                client_socket.connect((self.target_ip, self.target_port))
            except Exception:
                self.set_recv_message('握手失败, 请重试!\n')
                return
            self.set_recv_message('执行三次握手, 并建立TCP连接成功！' + '\n')
            # 发送信息
            client_socket.send(client_message.encode())
            self.set_recv_message('发送: ' + client_message + '\n')
            self.set_recv_message('到: ' + self.target_ip + ':' + str(self.target_port) + '\n')
            # 接收来自服务器的字节
            modified_sentence = client_socket.recv(2048)
            self.set_recv_message('收到信息: ' + modified_sentence.decode() + '\n')
            # 关闭socket
            client_socket.close()
            self.set_recv_message('TCP连接关闭！' + '\n')
            self.set_recv_message('-' * 35 + '\n')
        else:
            self.set_recv_message('开始执行...\n')
            # 创建UDP socket
            # AF_INET表示使用的是IPv4地址, SOCK_DGRAM表示该socket是一个UDP socket
            client_socket = socket(AF_INET, SOCK_DGRAM)
            # 向目的主机发送报文, message.encode()将字符串转为字节
            client_socket.sendto(client_message.encode(), (self.target_ip, int(self.target_port)))
            self.set_recv_message('发送: ' + self.client_message + '\n')
            self.set_recv_message('到: ' + self.target_ip + ': ' + str(self.target_port) + '\n')
            # 等待接收来自服务器的数据, 缓存长度2048, 从服务器接收的数据和服务器地址
            rec_message, server_address = client_socket.recvfrom(2048)
            self.set_recv_message('接收到来自: ' + server_address[0] + '\n')
            self.set_recv_message('接收到信息: ' + rec_message.decode() + '\n')
            # 关闭socket
            client_socket.close()
            self.set_recv_message('UDP连接关闭！' + '\n')
            self.set_recv_message('-' * 35 + '\n')

    def set_client_message(self, string):
        self.client_message += string
        self.ui.client_message.setPlainText(self.client_message)

    def set_recv_message(self, string):
        self.recv_message += string
        self.ui.server_message.setPlainText(self.recv_message)

    def handleClientMessageChanged(self):
        self.client_message = self.ui.client_message.toPlainText()

    def handleButtonGroupClicked(self):
        self.option = self.ui.buttonGroup.checkedButton().text()

    def handleTargetIpChanged(self):
        self.target_ip = self.ui.target_ip.text()

    def handleTargetPortChanged(self):
        self.target_port = self.ui.target_port.text()


if __name__ == '__main__':
    app = QApplication([])
    stats = Stats()
    stats.ui.show()
    app.exec_()
