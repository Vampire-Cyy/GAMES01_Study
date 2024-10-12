# $Lecture3$：变换

## 1. $2$ 维坐标的线性变换

### 1.1 缩放

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20224801.png" style="zoom:50%;" />

$$
\begin{matrix}
	\left [
	\begin{array}\\
	x^{\prime}\\
	y^{\prime}\\
	\end{array}
	\right]
\end{matrix} = \begin{matrix}
	\left[
	\begin{array}\\
	s_x&0\\
	0&s_y\\
	\end{array}
	\right]
\end{matrix} \begin{matrix}
	\left[
	\begin{array}\\
	x\\
	y\\
	\end{array}
	\right]
\end{matrix}
$$

### 1.2 对称

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20225624.png" style="zoom:50%;" />
$$
\begin{matrix}
	\left[
	\begin{array}\\
	x^{\prime}\\
	y^{\prime}\\
	\end{array}
	\right]
\end{matrix} = \begin{matrix}
	\left[
	\begin{array}\\
	-1&0\\
	0&1\\
	\end{array}
	\right]
\end{matrix} \begin{matrix}
	\left[
	\begin{array}\\
	x\\
	y\\
	\end{array}
	\right]
\end{matrix}
$$

### 1.3 切变

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20230024.png" style="zoom:50%;" />
$$
\begin{matrix}
	\left[
	\begin{array}\\
	x^{\prime}\\
	y^{\prime}\\
	\end{array}
	\right]
\end{matrix}
=
\begin{matrix}
	\left[
	\begin{array}\\
	1&a\\
	0&1\\
	\end{array}
	\right]
\end{matrix}
\begin{matrix}
	\left[
	\begin{array}\\
	x\\
	y\\
	\end{array}
	\right]
\end{matrix}
$$
``注意：将图片y轴标准化为1后再乘上对应的矩阵``

### 1.4 旋转（绕原点且为逆时针）

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20230519.png" style="zoom:50%;" />
$$
\begin{matrix}
	\left[
	\begin{array}\\
	x^{\prime}\\
	y^{\prime}
	\end{array}
	\right]
\end{matrix}
=
\begin{matrix}
	\left[
	\begin{array}\\
	\cos \theta&-\sin \theta\\
	\sin \theta&\cos \theta\\
	\end{array}
	\right]
\end{matrix}
\begin{matrix}
	\left[
	\begin{array}\\
	x\\
	y\\
	\end{array}
	\right]
\end{matrix}
$$

## 2. $2$维坐标的仿射变换

### 2.1 齐次坐标

$2$维的点：$(x,y,1)^T$

$2$维的向量：$(x,y,0)^T$

拓展：如果$(x,y,w)^T$代表一个$2$维的点，则其代表$(x/w,y/w,1)(w\not=0)$

### 2.2 平移

$$
\begin{matrix}
	\left[
	\begin{array}\\
	x^{\prime}\\
	y^{\prime}\\
	w^{\prime}
	\end{array}
	\right]
\end{matrix}
=
\begin{matrix}
	\left[
	\begin{array}\\
	1&0&t_x\\
	0&1&t_y\\
	0&0&1\\
	\end{array}
	\right]
\end{matrix}
\begin{matrix}
	\left[
	\begin{array}\\
	x\\
	y\\
	1\\
	\end{array}
	\right]
\end{matrix}
=\begin{matrix}
	\left[
	\begin{array}\\
	x+t_x\\
	y+t_y\\
	1\\
	\end{array}
	\right]
\end{matrix}
$$

### 2.3 仿射变换

仿射变换 = 线性变换 + 平移
$$
\begin{matrix}
	\left[
	\begin{array}\\
	x^{\prime}\\
	y^{\prime}\\
	\end{array}
	\right]
\end{matrix}
=
\begin{matrix}
	\left[
	\begin{array}\\
	a&b\\
	c&d\\
	\end{array}
	\right]
\end{matrix}
\begin{matrix}
	\left[
	\begin{array}\\
	x\\
	y\\
	\end{array}
	\right]
\end{matrix}
+
\begin{matrix}
	\left[
	\begin{array}\\
	t_x\\
	t_y\\
	\end{array}
	\right]
\end{matrix}
$$
齐次坐标下：
$$
\begin{matrix}
	\left[
	\begin{array}\\
	x^{\prime}\\
	y^{\prime}\\
	1\\
	\end{array}
	\right]
\end{matrix}
=
\begin{matrix}
	\left[
	\begin{array}\\
	a&b&t_x\\
	c&d&t_y\\
	0&0&1\\
	\end{array}
	\right]
\end{matrix}
\begin{matrix}
	\left[
	\begin{array}\\
	x\\
	y\\
	1\\
	\end{array}
	\right]
\end{matrix}
$$

$$
缩放矩阵：S(s_x,s_y)
=
\begin{matrix}
	\left[
	\begin{array}\\
	s_x&0&0\\
	0&s_y&0\\
	0&0&1
	\end{array}
	\right]
\end{matrix}
$$

$$
旋转矩阵：R(\alpha)
=
\begin{matrix}
	\left[
	\begin{array}\\
	\cos \alpha&-\sin \alpha&0\\
	\sin \alpha&\cos \alpha&0\\
	0&0&1\\
	\end{array}
	\right]
\end{matrix}
$$

$$
平移矩阵：T(t_x,t_y)
=
\begin{matrix}
	\left[
	\begin{array}\\
	1&0&t_x\\
	0&1&t_y\\
	0&0&1
	\end{array}
	\right]
\end{matrix}
$$

## 3. 复杂变换

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20232159.png" style="zoom:50%;" />

**注意顺序**

当进行一系列的仿射变换，其对应的齐次左边下的矩阵分别为：$A_1,A_2,A_3 \cdots$时

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20232407.png" style="zoom:50%;" />

可以先做$A_1A_2A_3\cdots A_n$的矩阵乘法

对于绕任意一点旋转，可以先将其平移至原点，旋转后再平移回原位置：

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20232634.png)



## 4. $3$维坐标变换

### 4.1 $3$维的齐次化坐标

$3$维的点：$(x,y,z,1)^T$

$3$维的向量：$(x,y,z,0)^T$

### 4.2 $3$维下的仿射变换

$$
\begin{matrix}
	\left[
	\begin{array}\\
	x^{\prime}\\
	y^{\prime}\\
	z^{\prime}\\
	1\\
	\end{array}
	\right]
\end{matrix}
=
\begin{matrix}
	\left[
	\begin{array}\\
	a&b&c&t_x\\
	d&e&f&t_y\\
	g&h&i&t_z\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
\begin{matrix}
	\left[
	\begin{array}\\
	x\\
	y\\
	z\\
	1\\
	\end{array}
	\right]
\end{matrix}
$$

$$
缩放矩阵：S(s_x,s_y,s_z)=
\begin{matrix}
	\left[
	\begin{array}\\
	s_x&0&0&0\\
	0&s_y&0&0\\
	0&0&s_z&0\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
\\
平移矩阵:T(t_x,t_y,t_z)=
\begin{matrix}
	\left[
	\begin{array}\\
	1&0&0&t_x\\
	0&1&0&t_y\\
	0&0&1&t_z\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
\\
旋转矩阵：R_x(\alpha)=
\begin{matrix}
	\left[
	\begin{array}\\
	1&0&0&0\\
	0&\cos \alpha&-\sin \alpha&0\\
	0&\sin \alpha&\cos \alpha&0\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
\\
R_y(\alpha)=
\begin{matrix}
	\left[
	\begin{array}\\
	\cos \alpha&0&\sin \alpha&0\\
	0&1&0&0\\
	-\sin\alpha&0&\cos\alpha&0\\
	0&0&0&1
	\end{array}
	\right]
\end{matrix}
\\
R_z(\alpha)=
\begin{matrix}
	\left[
	\begin{array}\\
	\cos\alpha&-\sin\alpha&0&0\\
	\sin\alpha&\cos\alpha&0&0\\
	0&0&1&0\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
$$

### 4.3 罗德里格斯旋转公式

在$3$维空间下，任意的一个旋转$R_{xyz}(\alpha.\beta,\gamma)=R_x(\alpha)R_y(\beta)R_z(\gamma)$

罗德里根旋转公式：
$$
R(\vec n, \alpha)
=
\cos(\alpha)I + (1-\cos(\alpha))nn^T + sin(\alpha)
\begin{matrix}
	\left[
	\begin{array}\\
	0&-n_z&n_y\\
	n_z&0&-n_x\\
	-n_y&n_x&0\\
	\end{array}
	\right]
\end{matrix}
$$
公式推导：

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-21%20151954.png" style="zoom:67%;" />

对于空间中任意向量$\vec s$​：将其向旋转轴$\vec n$与垂直于旋转轴的方向上分解有：
$$
\vec s = \vec s_{\perp} + \vec s_{\parallel}
$$
其旋转后所得到的向量：$\vec n^{\prime}$​同理有：
$$
\vec s^{\prime} = \vec s^{\prime}_{\perp} + \vec s^{\prime}_{\parallel}
$$
以$\hat a$方向为转轴，$\vec s_{\perp}$方向为$\vec b$方向，有：
$$
\hat b = \frac{\vec s_{\perp}}{|\vec s_{\perp}|}
\\
\hat c = \hat a \times \hat b 
= \frac{\hat a \times \vec s_{\perp}}{|\vec s_{\perp}|}
=\frac{\hat a \times (\vec s - \vec s_{\parallel})}{|\vec s_{\perp}|}
=\frac{\hat a \times \vec s}{|\vec s_{\perp}|}
\\ 
\hat b = - \hat a \times \hat c
$$
旋转后$\vec s_{\parallel}$不变，$\vec s_{\perp}$旋转角度$\alpha$​，则有：
$$
\begin{align}
\vec s^{\prime}_{\perp} 
&= |\vec s_{\perp}|\cos\alpha \hat b + |\vec s_{\perp}|\sin \alpha \hat c
\\
\\
\vec s_{\parallel}
&=\vec s在\hat a上的投影向量
\\
&=\hat a(\vec s\cdot\hat a)
\\
\\
\vec s^{\prime} 
&= \vec s^{\prime}_{\perp} + \vec s_{\parallel}
=\vec s^{\prime}_{\perp} + \vec s - \vec s_{\perp}
\\
&=\cos \alpha \vec s_{\perp} + \sin \alpha \hat a \times \vec s +\vec s - \vec s_{\perp}
\\
&=\vec s + (\cos \alpha -1)\vec s_{\perp} + \sin\alpha\cdot\hat a\times \vec s
\\
&=\vec s + (\cos \alpha-1)(\vec s - \vec s_{\parallel}) + \sin \alpha N\cdot\vec s
\\
&=\cos\alpha\vec s - (\cos\alpha-1)\hat a(\vec s\cdot\hat a) +\sin \alpha N\cdot\vec s
\\
&=\cos\alpha\vec s - (\cos\alpha-1)nn^T\vec s + \sin \alpha N\cdot\vec s
\\
&=(\cos\alpha I + (1-\cos\alpha)nn^T+\sin\alpha N)\cdot \vec s
\\
\\
\therefore
R(\vec n,\alpha)
&=\cos\alpha I+(1-\cos\alpha)nn^T+\sin\alpha N
\\
当\alpha极小时，R(\vec n,\alpha) &=I+\sin\alpha N = I+\alpha N
\end{align}
$$

## 5.  观测变换

### 5.1 视图变换

如何拍一张照片：

- 找一个地方让人们站过去（模型变换）
- 找一个位置放相机（视图变换）
- 摆造型（投影变换）

先定义三个方向：

- 相机的位置为$\vec e$
- 相机面朝的方向为$\vec g$
- 相机朝上的方向为$\vec t$

相机与物体的相对位置始终是不变的，所以我们可以将相机平移至原点，以相机所在位置建系

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-21%20163722.png)

以此建系后：相机朝上的方向为$y$轴，面朝的方向为$-z$轴

接下来对相机平移至原点，坐标轴转到指定位置做变换：

- 先平移至原点
- 将$\vec g$旋转至$-z$轴方向
- 将$\vec t$旋转至$y$方向
- 将$\vec g \times \vec t$旋转至$x$方向

则可得：$M_{view}=R_{view}T_{view}$

易知$T_{view}=\begin{matrix}
	\left[
	\begin{array}\\
	1&0&0&-x_e\\
	0&1&0&-y_e\\
	0&0&1&-z_e\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}$

考虑先求其逆变换$R_{view}^{-1}$，则相当于将$x$轴旋转至 $\vec g \times \vec t$，$y$轴旋转至$\vec t$，$z$轴旋转至$-\vec g$
$$
R_{view}^{-1}
=
\begin{matrix}
	\left[
	\begin{array}\\
	x_{\hat g \times\hat t}&x_t&x_{-g}&0\\
	y_{\hat g \times\hat t}&y_t&y_{-g}&0\\
	z_{\hat g \times\hat t}&z_t&z_{-g}&0\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
\\
R是一个正交矩阵，则有R^{-1}=R^T,R=(R^{-1})^T\\
R_{view}
=
\begin{matrix}
	\left[
	\begin{array}\\
	x_{\hat g \times\hat t}&y_{\hat g \times\hat t}&z_{\hat g \times\hat t}&0\\
	x_t&y_t&z_t&0\\
	x_{-g}&y_{-g}&z_{-g}&0\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
$$

### 5.2 投影变换

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-21%20165645.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20240921165706732.png" style="zoom:67%;" />

也即有无影消点的区别

#### 5.2.1 正交变换

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-21%20165912.png" style="zoom: 67%;" />

一种简单的方式就是将相机放在原点，面朝$-z$轴，向上为$y$轴，丢掉z轴即可

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-21%20170118.png)

对于正交投影，其观测空间为一个$z$轴无限长的长方体

为了方便计算，将这个长方体的观测空间统一正则化为一个$[-1,1]^3$的立方体

这个正则化的变换矩阵为：
$$
M_{ortho}
=
\begin{matrix}
	\left[
	\begin{array}\\
	\frac{2}{r-l}&0&0&0\\
	0&\frac{2}{t-b}&0&0\\
	0&0&\frac{2}{n-f}&0\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
\begin{matrix}
	\left[
	\begin{array}\\
	1&0&0&-\frac{r+l}{2}\\
	0&1&0&-\frac{t+b}{2}\\
	0&0&1&-\frac{n+f}{2}\\
	0&0&0&1\\
	\end{array}
	\right]
\end{matrix}
$$
**注意：在右手系下$n>f$**

又物体与相机的相对位置不变，对空间中所有物体进行同样的变换即可

#### 5.2.2 透视变换

考虑这一变换过程，可以分两步：

- 将透视变换对应的台体通过变换转化到正交变换的立方体上
- 进行正交变换

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-21%20180650.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-21%20180709.png" style="zoom:67%;" />

对任意一个点进行上述操作后可得：

$M_{persp\to ortho}^{(4\times4)}(x,y,z,1)^T=(nx/z,ny/z,?,1)=(nx,ny,?,z)$

易得矩阵$M_{persp\to ortho}$的$1,2,4$行：
$$
M_{persp\to ortho}
=
\begin{matrix}
	\left[
	\begin{array}\\
	n&0&0&0\\
	0&n&0&0\\
	0&0&A&B\\
	0&0&1&0\\
	\end{array}
	\right]
\end{matrix}
$$
经过变换后有两个性质：

- 近平面上的点$z$不变
- 原平面上的点$z$不变

取两个特殊点：$[x,y,n,1]^T$和$[0,0,f,1]^T$

则有：$[0,0,A,B][x,y,n,1]^T=[nx,ny,n^2,n]$

$[0,0,A,B][0,0,f,1]^T=[fx,fy,f^2,f]$

解方程组：
$$
\left\{ 
\begin{array}{ll}
An+B = n^2\\
Af+B=f^2\\
\end{array} 
\right.
\Longrightarrow
\left\{ 
\begin{array}{ll}
A=n+f\\
B=-nf\\
\end{array} 
\right.
$$
求得矩阵：
$$
M_{persp\to ortho}
=
\begin{matrix}
	\left[
	\begin{array}\\
	n&0&0&0\\
	0&n&0&0\\
	0&0&n+f&-nf\\
	0&0&1&0\\
	\end{array}
	\right]
\end{matrix}
$$
那么最后我们将所有的物体乘上$M_{ortho}M_{persp\to ortho}$即可得到完成$MVP$变换的物体坐标

### 5.3 裁剪

无论是正交投影还是透视投影，我们都将观测空间转换成了一个规范立方体，同时将转换矩阵应用到空间中的所有物体中。

之后，我们就可以通过规范立方体对空间进行裁剪，只保留规范立方体内的物体，如下所示。很显然，只有在规范立方体中的部分才是我们可以看见的部分。

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/projection-12.png)

### 5.4 视口变换

将我们所正则化后的$2D$画布投影到屏幕上

即将$[-1,1]^2$的平面转换到$[0,width]\times[0,height]$这样一个平面上

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/projection-13.png)

最后得到视口变换的矩阵：
$$
M_{viewport}
=
\begin{matrix}
	\left[
	\begin{array}\\
	\frac{width}{2}&0&0&\frac{width}{2}\\
	0&\frac{height}{2}&0&\frac{height}{2}\\
	0&0&1&0\\
	0&0&0&0\\
	\end{array}
	\right]
\end{matrix}
$$
即：切变+平移
