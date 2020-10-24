# Saliency Detection：A Spactral Residual Approach #  

在信息学理论中，一张图像的信息$H(Image)$可以分为特意性信息$H(Innovation)$和需要被过滤的多余信息$H(Prior Knowledge)$两部分，即：
$$
H(Image)=H(Innovation)+H(Prior Knowledge)
$$

该文献主要根据 $1/f$ 定律，即自然图像的频谱强度均值$\mathcal{A}(f)$ 与频率的倒数成正比关系，即：  
$$ E{\mathcal{A}(f)}\varpropto 1/f$$   

在 log-log 尺度中，自然图像频谱在垂直方向上的求均值后（即在同一频率下的均值）近似是一条直线
<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-papers/log-log spectrum.png" />
</div> 

值得注意的是，这个图是通过大量的自然图像计算得到，单一图片不可能得到，但可以通过对单一图片的频域图做一次均值滤波，用来模拟多张图片在同一频率上的平均过程  

均值滤波后的频谱具有上述定律一般图像的特性，那么，把原图的频谱图与均值滤波后的频谱相减(频谱残差)，所得到的便是单张图片的特异性信息，即图片的显著性信息(Saliency)  

算法主要步骤如下所示：
对于一张图片$\mathcal{I}(x)$
1.  $\mathcal{A}(f)=\mathbb{R}(\mathbb{F}[\mathcal{I}(x)])$  
2.  $\mathcal{P}(f)=\angle\mathbb{F}[\mathcal{I}(x)]$
3.  $\mathcal{L}(f)=log(\mathcal{A}(f))$
4.  $\mathcal{R}(f)=\mathcal{L}(f)-h_{n}(f)*\mathcal{L}(f)$
5.  $\mathcal{S}(x)=g(x)*\mathbb{F}^{-1}[exp(\mathcal{R}(f)+\mathcal{P}(f))]^{2}$

其中$\mathbb{F}$和$\mathbb{F}^{-1}$分别为傅里叶变换与傅里叶反变换，$h_{n}(f)$为大小为n的均值滤波器，$g(x)$为高斯滤波器，$\mathcal{P}(f)$为相位谱  

saliency map to object map：  
$$\mathcal{O}(x)=\begin{cases}
1& if\ \mathcal{S}\text{(x)>threshold}\\\\
0 &\text{otherwise}
\end{cases}$$

测试图如下所示：  

<div align="center">
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-papers/giraffe.png" />
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-papers/giraffe-SM.png" />
<img src="https://gitee.com/zhy1997/notepic/raw/master/pic/notepic-papers/giraffe-OM.png" />
</div> 