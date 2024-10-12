# $Lecture4$：光栅化

## 1. 视口变换

在经过了$MVP$变换后，需要将物体从标准空间转化到屏幕空间上，这一步即为视口变换

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-22%20173718.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-22%20173817.png" style="zoom:67%;" />

## 2. 光栅化

光栅化即为在栅格显示设备上绘制图形的一个过程

光栅化的基本单元是三角形：

- 三角形是最基本的多边形
- 三角形具有平面性
- 三角形可以明确定义内部与外部，通过向量的叉乘
- 任意多边形可以拆分成$N$个三角形

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-22%20174119.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-22%20174124.png" style="zoom:50%;" />

### 2.1 采样

采样：将所有光学信息离散成像素点的过程，其本质是函数的离散化，通过定义一个函数计算每一个像素点的函数值来判断是否在一个三角形内

```
伪代码如下：
bool inside(t, x, y) 
{
    if point(x, y) in triangle(t) 
    {
        return 1
    } 
    else 
    {
        return 0
    }
}

for (int x = 0; x < xmax; ++x) 
{
    for (int y = 0; y < ymax; ++y) 
    {
        image[x][y] = inside(tri, x + 0.5, y + 0.5);
    }
}
```

实际过程如下图所示：

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-22%20174648.png)

在绘制时并不会对整个屏幕上所有的像素点进行计算，而是对三角形所在包围盒内的点进行计算，由此诞生了一系列对于采样算法的优化，降低时间复杂度

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-22%20174819.png)

### 2.2 走样

当采取这样简单的绘制方式时，会发现出现了一些问题，当采样完成重新绘制这个图形时，明显发现图形中出现了一个问题**锯齿**。而出现这种问题的现象被称之为走样。走样会导致一些错误的现象出现如：锯齿，摩尔纹和车轮效应

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20231644.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20231814.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20231842.png" style="zoom:50%;" />

### 2.3 反走样

而在计算机图形学中，可以采取这样一种方法：先模糊后采样的方式来解决走样的问题，这一操作叫做反走样。通过一些例子可以看出这种先模糊后采样的操作的确是行之有效的。

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20232052.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20232107.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20232122.png" style="zoom:50%;" />

## 3. 采样理论

下面从理论的角度来阐明为什么先进行一步模糊操作可以解决走样的问题

在实际应用中，我们通过一定的采样率把连续信号转换为离散信号，然后再对离散信号进行处理。处理完后，我们又可以通过一定的重构方法把离散信号转换回连续信号，以便在实际系统中使用。

### 3.1 傅里叶级数

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20232319.png" style="zoom:67%;" />

通过模拟的方式，可以用一小段的正弦函数与余弦函数来不断的逼近一个任意的函数，这就是数学家傅里叶的想法：任何周期函数都可以用正弦函数和余弦函数所构成的无穷级数来表示

### 3.2 时域与频域

根据傅里叶级数可以对任意一个函数进行傅里叶变换
$$
F(\omega)=\int_{-\infty}^{\infty}f(x)e^{-2\pi i\omega x}dx
$$
其逆变换为：
$$
f(x)=\int_{-\infty}^{\infty}F(\omega)e^{2\pi i \omega x}d\omega
$$

- 傅里叶变换：将时域转换到频域
- 逆傅里叶变换：将频域转换到时域

### 3.3 走样原理

理想情况下，对一个连续信号进行采样后得到的离散信号，应该能够近似重构原始信号。然而，当采样频率低于原始信号的频率时，就会很容易出现走样的问题。换句话说，就是采样得到的离散信号无法近似重构原始信号。

下图所示，我们列举了几种信号，信号频率依次从高到低，我们使用相同的频率对这些信号进行采样。很显然，我们对低频信号进行采样时，由于采样频率大于信号频率，得到的离散信号可以近似重构原始信号；但是，我们对高频信号采样时，由于采样频率小于信号频率，得到的离散信号则无法近似重构原始信号。

因此走样的根本原因就是 **采样频率小于信号频率**。

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20233239.png" style="zoom: 50%;" />

## 4. 滤波

由傅里叶变换，可以将一幅图像从时域（以空间代表时间）转换到频域上

规定：从中心向边缘频率变高

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20233450.png" style="zoom:50%;" />

由此可以得到一些事实规律：

- 高频部分代表细节，边缘，噪声
- 低频占据绝大多数能量，其中直流分量能量占比最大
- 频率分部具有对称性

### 4.1 高通滤波

仅保留高频信号而丢失掉低频信号，这种方式为高通滤波

在图像中轮廓的边缘会发生剧烈变化，是一种高频信号

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20233629.png" style="zoom:50%;" />

### 4.2 低通滤波

仅保留低频信号而丢失掉高频信号，这种方式为低频滤波

低频信息通常为图像的内容，但会丢失掉轮廓信息

而模糊处理就是基于低频滤波来实现的

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20233927.png" style="zoom:50%;" />

### 4.3 带通滤波

只保留一部分频率范围内的信后为带通滤波

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20234019.png" style="zoom:50%;" />

<img src="C:\Users\Vampire\AppData\Roaming\Typora\typora-user-images\image-20240923234037423.png" alt="image-20240923234037423" style="zoom:50%;" />

### 4.4 卷积

由前置知识可知，实现模糊的方式即为一种低通滤波，而实现低通滤波的一种方式即称为：**卷积**

在数学上其连续的定义为：
$$
(f*g)(n)=\int_{-\infty}^{\infty}f(\tau)g(n-\tau)d\tau
$$
其离散的定义为：
$$
(f*g)(n)=\sum_{r=-\infty}^{\infty}f(\tau)g(n-\tau)
$$
在图像处理上的应用即可简单视为一种平均

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20234844.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20234911.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20235014.png" style="zoom:67%;" />

即这一效果，参考：https://www.zhihu.com/question/22298352/answer/228543288

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/v2-15fea61b768f7561648dbea164fcb75f_720w.webp)

卷积与傅里叶变换结合时有一个性质：两函数的傅里叶变换的乘积等于它们卷积后的傅里叶变换

根据这个性质我们就可以对图像进行模糊化操作，先对函数即卷积方式进行傅里叶变换，相乘后所得到的频谱再进行一次逆傅里叶变换即可实现图像的模糊

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20235444.png" style="zoom:50%;" />

## 5. 反走样的方法

走样的根本原因是 **采样频率小于信号频率**，因此发生了混频的现象。在不提高采样频率的前提下，通过 **先滤波，后采样** 的方式可以实现反走样，其本质是**过滤掉信号中大于采样频率的信号分量**

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20235619.png" style="zoom:50%;" />

那么通过对一个像素内做卷积的形式，就可以得到图像对于像素的覆盖率从而实现模糊的操作

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-23%20235739.png" style="zoom:50%;" />

由此可以得出几种不同的反走样方式

### 5.1 $MSAA$ （多重采样抗锯齿）

将一个像素内的采样点从一个增加到多个，然后对像素内的采样点做卷积，逼近实际的覆盖率，这种采样方式成为多重采样，可以有效的抗锯齿

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-24%20000214.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-24%20000225.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-24%20000254.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-24%20000312.png" style="zoom:50%;" />

### 5.2 $FXAA$（快速近似抗锯齿）

在图像处理层面所做的一种抗锯齿操作，得到一幅有锯齿的图形后，通过图像处理找到边界，进行图像匹配，将边界换成没有锯齿的边界

### 5.3 $TAA$（时间性抗锯齿）

通过复用上一帧的计算结果，在此帧选取像素内不同的点，然后进行颜色的混合，进行卷积操作，即用时间上的多重采样代替$MSAA$中的空间上的多重采样

### 5.4 $DLSS$（帧生成，超分辨率）

利用深度学习对一个像素周围的像素进行猜测，达到一种多重采样的效果，即为超分辨率

## 6. 遮挡与可见

在学习了如何通过先模糊，再采样的方式来对图像进行光栅化后，下面学习当光栅化三角形时会遇到的另一个问题：遮挡与可见性的问题。在有遮挡的情况下将$3D$空间转换到$2D$空间上时，应该如何绘制

### 6.1 画家算法

画家算法：按照画家绘画时的先后顺序来进行绘制，先画远的物体，再画近的物体

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-25%20091728.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-25%20092121.png" style="zoom:50%;" />

但是画家算法遇到当前这种情况，三个物体之间互相存在遮挡关系时，画家算法无法确定应该先画哪个三角形，因此无法准确光栅化

### 6.2 深度缓冲算法($Z-Buffer$)

采用两个缓冲区来进行$z$值的更新

- 原有的帧缓冲区存储每个像素的颜色信息
- 增加深度缓冲区存储每个像素的深度值

此时我们改变$z$值的定义：$z$值越小表示离相机越近，$z$值越大表示离相机越远

深度缓冲区记录每个像素当前的最小深度值

```
伪代码实现：
for(each triangle T)
{
	for(each sample(x, y, z) in T)
	{
		if(z < zbuffer[x, y])			//当深度更小时更新深度信息
		{
			framebuffer[x, y] = rgb;	//更新rgb值
			zbuffer[x,y] = z;		    //更新深度值
		}
	}
}
```

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-25%20092802.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-25%20092830.png" style="zoom:67%;" />

初始化每一个像素的深度值为无穷大，光栅化红色三角形，再光栅化蓝色三角形时，更新蓝色三角形所覆盖的像素单元，这是就可以正确处理遮罩关系，并且深度缓冲算法的时间复杂度为线性，增加了一倍的空间复杂度