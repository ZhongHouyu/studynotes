#开发记录3 Pyside2开发GUI  

###背景  
关于QT与PyQt关系  
Qt 是一个跨平台的 C++图形用户界面库，由挪威 TrollTech 公司于1995年底出品。  

Trolltech 公司在 1994 年成立，但是在 1992 年，成立 Trolltech 公司的那批程序员 就已经开始设计 Qt 了，Qt 的第一个商业版本于 1995 年推出。  

2008年1月31日，诺基亚Nokia公司宣布通过公开竞购的方式收购    

TrollTech公司，旗下包括Qt在内的技术都归入Nokia旗下。并且Nokia针对自己的移动设备平台规划的需要，将Qt按不同的版本发行。  

###环境：  
python:3.8.6  
ptside：5.15.1  


###信号与槽  
一个应用中，各个对象的通信与交互才能彼此配合、完成我们需要的功能。  

在QT中，人们设计了信号与槽的机制来解决这个问题。 
 
一般情况下，我们说某个对象发生了某些事，必须让另一个对象做出反应。在QT中，一个对象可以发出一个信号，而另一个对象必须要有接收信号的槽，才能完成一次事件的传递。  

在发出信号和接收信号之前，我们还必须连接信号和槽才能生效，如果不连接，那么多信号和槽都不知道谁对应谁。
在下面这段代码中，button的点击信号，与方法 greeting  使用方法 button.clicked.connect 建立连接，在这里，clicked就是信号，greetings就是槽  

```
class Form(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("my form")
        self.edit = QLineEdit("write name here...")
        self.button = QPushButton("show greetings")
        layout = QVBoxLayout()
        layout.addWidget(self.edit)
        layout.addWidget(self.button)
        self.setLayout(layout)
        self.button.clicked.connect(self.greetings)

    @Slot()
    def greetings(self):
        print("Hello", self.edit.text())
```

参考网址：https://doc.qt.io/qtforpython/contents.html  


###类继承与super()调用父类方法   

创建自己的类Form（继承于QDialog），通过super()函数调用父类QDialog的方法 init（）新建一个dialog窗口，然后用父类的方法setWindowTitle()改变窗口标题  
```
class Form(QDialog):
	def __init__(self, parent=None):
 		super().__init__(parent)
		self.setWindowTitle("my form"）
```
运行以下代码：
```
app = QApplication(sys.argv)
form = Form()
form.show()
sys.exit(app.exec_())
```  
结果如下所示：  

<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-qt/super-1.png" />
</div>

