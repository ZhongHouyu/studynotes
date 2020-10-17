#开发记录4 Pyside2官方文档中文版  

该文档主要基于qt公司的官方pyside2官方文档做出翻译和整理  

##PySide2开发文档  


###开始第一个Qt应用  

####环境需求
在Python环境下开始开发Qt应用之前，我们应该先安装配置好相应的python环境：

	>Python 2.7 或者3.5+  
	>推荐使用一个虚拟环境，如venv 或 virtuallenv  

####安装  

安装好python之后，通过pip安装PySide2，在终端中输入以下命令：  

	pip install PySide2   #下载最新的版本  

注意：windows平台上使用pip前请检查自己的环境变量是否添加相关内容，否则需要进入pip所在文件下才能运行  

####检查安装  
通过运行以下命令检查你的安装是否成功，并得知自己的PySide2版本等相关信息  

```
import PySide2.QtCore

#打印PySide2版本
# e.g. 5.11.1a1
print(PySide2.__version__)

# 得到版本信息的一个序列
# e.g. (5, 11, 1, 'a', 1)
print(PySide2.__version_info__)

# 打印当前PySide2对应的qt版本
# e.g. "5.11.2"
print(PySide2.QtCore.__version__)

# 得到相应qt版本信息的一个序列
# e.g. (5, 11, 2)
print(PySide2.QtCore.__version_info__)  

```   
至此，pyside2相关的配置工作就完成了  


####创建一个简单的应用  

在配置好环境后，用几行代码就可以开发出能输出”hello world“的简单程序，下面将会介绍完成这个简单程序的几个步骤：  

1.创建一个新py文件 hello world.py，并添加以下几个import项：  
```
import sys
import random
from PySide2 import QtCore, QtWidgets, QtGui
```  
pyside2提供了许多Qt开发相关的API，QtCore, QtWidgets, QtGui是非常常用的包，后面会有更详细的介绍  

2.创建一个类MyWidget，继承于QWidget，并包含QPushButton 和 QLabel两个实例  

···
class MyWidget(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.hello = ["Hallo Welt", "Hei maailma", "Hola Mundo", "Привет мир"]

        self.button = QtWidgets.QPushButton("Click me!")
        self.text = QtWidgets.QLabel("Hello World")
        self.text.setAlignment(QtCore.Qt.AlignCenter)

        self.layout = QtWidgets.QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.button)
        self.setLayout(self.layout)

        self.button.clicked.connect(self.magic)


    def magic(self):
        self.text.setText(random.choice(self.hello))
···
在MyWidget类中有一个magic函数，通过产生随机数来选择不同语言的“你好”  

3.现在，在主函数中示例一个MyWidget，并展示它  

```
if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())
```   

运行程序，点击下方的按钮就可以看到不同的“你好”了  
<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-pyside2/hello.png" />
</div>  


###PySide2模块介绍  

####基础模块  

这些是创建一个 Widget-based界面的主要模块  

||
|  :----:|  :----| 
| Qt.Core | 提供了非图形界面功能的核心功能，如槽、属性、基类、序列等 | 
| Qt.GUI| 在QtCroe的基础上扩展了GUI功能，如事件、窗口、屏幕、OpenGl、基于栅格的2D绘图板，图像等 | 
| Qt.Widgets| 提供应用中常用的控件，如组成你图像界面的按钮、表格等 |   

####QML与Qt Quick  
通过以下模块实现 QML文件与python的交互  

||
|  :----:|  :----| 
| Qt.QML | 提供与PythonAPI交互的基础功能 | 
| Qt.Quick| 提供能在Qt应用中使用QtQucik的类 | 
| Qt.QuickWidgets| 提供能在Qt应用中使用的QQuickWidget类 |   

####数据可视化  

统计图（charts）、流程图（diagrams）、动画（animations）：这些模块能让你在的界面中使用这些功能


||
|  :----:|  :----| 
| Qt.Charts | 提供一般统计图的绘制方法 | 
| Qt.DataVisualization| 提供能在3D维度展现你的数据的方法 | 


####多媒体  

实现声音、视频、硬件的交互

||
|  :----:|  :----| 
| Qt.Multimedia | 提供基础的多媒体功能 | 
| Qt.MultimediaWidgets| 提供基于widget的多媒体API | 

####网络引擎  

如果尼电应用是基于一个浏览器或者要与网络应用交互，那么这些模块可以实现那些功能  


||
|  :----:|  :----| 
| Qt.WebEngineWidgets | 提供widgets来处理网络相关内容 | 
| Qt.WebChannel| 实现服务器-客户端的端到端的交互功能 | 