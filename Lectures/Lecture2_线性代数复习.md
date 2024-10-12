# $Lecture2$ :线性代数复习

## 1.向量

$\begin{matrix}
    \vec A =
    \left( \begin{array}\\
	x \\
	y\\
	\end{array} \right)
	\end{matrix}$     $\begin{matrix}
    		\ A^T=
    		\left( \begin{array}\\
			x,y\\
			\end{array} \right)
			\end{matrix}$      $|\vec A|=\sqrt{x^2+y^2}$

$\hat a = \frac{\vec a}{|\vec a|}$


### 1.1 向量的点乘

$\vec a \cdot \vec b =|\vec a||\vec b|\cos \theta$

$\cos \theta = \frac{\vec a \cdot \vec b}{|\vec a||\vec b|}=\hat a \cdot \hat b$

$2$维向量相乘：

$\begin{matrix}
    \vec a \cdot \vec b =
    \left( \begin{array}\\
	x_a \\
	y_a\\
	\end{array} \right)
	\end{matrix}\cdot$ $\begin{matrix}
    \left( \begin{array}\\
	x_b \\
	y_b\\
	\end{array} \right)
	\end{matrix}$$=x_ax_b+y_ay_b$

$3$维向量相乘：

$\vec a\cdot \vec b=$$\begin{matrix}
    \left( \begin{array}\\
	x_a\\
	y_a\\
	z_a\\
	\end{array} \right)
	\end{matrix}$$\cdot$$\begin{matrix}
	\left( \begin{array}\\
	x_b\\
	y_b\\
	z_b\\
	\end{array} \right)
	\end{matrix}
	$$=x_ax_b+y_ay_b+z_az_b$

### 1.2 投影向量

$\vec b_\perp=|\vec b|\cos \theta\cdot\hat a$

![](https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-19%20235517.png)

### 1.3 利用向量的点乘判断方向

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-19%20235631.png" style="zoom:67%;" />

### 1.4 向量的叉乘

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-19%20235706.png" style="zoom: 50%;" />

$\vec x \times \vec y=+\vec z$

$\vec y \times \vec z = +\vec x$

$\vec z \times \vec x = +\vec y$

$\vec a \times \vec b =$$\begin{matrix}
	\left( \begin{array}\\
	y_az_b - y_bz_a\\
	z_ax_b - x_az_b\\
	x_ay_b - y_ax_b\\
	\end{array} \right)
	\end{matrix}$

$\vec a \times \vec b =$$\begin{matrix}
	\left( \begin{array}\\
	0&-z_a&y_a\\
	z_a&0&-x_a\\
	-y_a&x_a&0\\
	\end{array} \right)
	\end{matrix}$ $\cdot$ $\begin{matrix}
	\left( \begin{array}\\
	x_b\\
	y_b\\
	z_b\\
	\end{array} \right)
	\end{matrix}$	

### 1.5 利用向量的叉乘判断方向及内外

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20213407.png" style="zoom:50%;" />

当$\vec a \times \vec b>0$时可知$\vec b$在$\vec a$左侧，反之则在右侧

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-09-20%20213641.png" style="zoom:50%;" />

当$\overrightarrow{AB} \times \overrightarrow{AP}>0$ 且 $\overrightarrow{BC} \times \overrightarrow{BP}>0$ 且 $\overrightarrow{CP} \times \overrightarrow{CA}>0$时，说明点$P$在$\bigtriangleup ABC$内部（点$ABC$逆时针排布）

### 1.6正交化

$|\vec u|=|\vec v|=|\vec w|=1$

$\vec u \cdot \vec v = \vec v \cdot \vec w = \vec u \cdot \vec w=0$

$\vec w = \vec u \times \vec v$ （右手系）

$\vec p = (\vec p \cdot \vec u)\vec u + (\vec p \cdot \vec v)\vec v + (\vec p \cdot \vec w)\vec w$

## 2. 矩阵

### 2.1 矩阵的乘法

$(M \times N)(N \times P)=(M \times P)$

$\begin{matrix}
	\left( 
	\begin{array}\\
	1&3\\
	5&2\\
	0&4\\
	\end{array} 
	\right)
\end{matrix}$ $\begin{matrix}
	\left( \begin{array}\\
	3&6&9&4\\
	2&7&8&3\\
	\end{array} 
	\right)
\end{matrix}=$ $\begin{matrix}
	\left(
	\begin{array}\\
	9&27&33&13\\
	19&44&61&26\\
	8&28&32&12\\
	\end{array}
	\right)
\end{matrix}$

### 2.2 矩阵的运算规律

$(AB)^T=B^TA^T$

$(AB)^{-1}=B^{-1}A^{-1}$

### 2.3 矩阵表示向量的乘法

$\vec a \cdot \vec b = \vec a^{T} \vec b =
\begin{matrix}
	\left(
	\begin{array}\\
	x_a&y_a&z_a\\
	\end{array}
	\right)
\end{matrix} \begin{matrix}
	\left(
	\begin{array}\\
	x_b\\
	y_b\\
	z_b\\
	\end{array}
	\right)
\end{matrix}
=x_ax_b+y_ay_b+z_az_b$

$\vec a \times \vec b =$$A*b$$\begin{matrix}
	\left( \begin{array}\\
	0&-z_a&y_a\\
	z_a&0&-x_a\\
	-y_a&x_a&0\\
	\end{array} \right)
	\end{matrix}$ $\cdot$ $\begin{matrix}
	\left( \begin{array}\\
	x_b\\
	y_b\\
	z_b\\
	\end{array} \right)
	\end{matrix}$	

$A$为$\vec a$的叉乘矩阵
