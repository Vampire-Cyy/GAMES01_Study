# $Lecture10$：相机与透镜

## 1. 视场

相机的基本成像原理就是小孔成像，而视场（FOV，Field of View）则是用来描述拍摄的范围

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20124414.png" style="zoom:50%;" />

### 1.1 焦距对视场的影响

当传感器大小一定时，FOV随着焦距的增加而减小

通常在描述视场时，用以35mm的底片为基准：

- 17mm is wide angle 104° 
- 50mm is a “normal” lens 47°
- 200mm is telephoto lens 12° 

### 1.2 传感器对视场的影响

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011130936359.png" alt="image-20241011130936359" style="zoom: 50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011130959292.png" alt="image-20241011130959292" style="zoom:50%;" />

通常，相机的传感器越大，焦距越长那么相机越好

## 2. 曝光

照相考虑的光照时间不是单位时间而是总体时间

- $H=T\times E$
- 曝光时间T由快门控制
- 辐射照度H由传感器上一个单位区域接收光的能量和镜头的光圈还有焦距控制

### 2.1 曝光的影响因素

- 光圈大小（F数）
- 快门时间（Shuttle Speed）
- 感光度（ISO）

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011131337942.png" alt="image-20241011131337942" style="zoom:50%;" />

### 2.2 ISO（gain）

ISO本质上一种光学增益，在放大增亮图片细节的同时也会放大噪声，并且ISO对图片的作用是线性的

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011131605396.png" alt="image-20241011131605396" style="zoom:50%;" />

### 2.3 F-Stop

F数一般用来表示光圈的大小，与光圈的直径成反比，其实是焦距除以光圈的直径

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011131743130.png" alt="image-20241011131743130" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011131811573.png" alt="image-20241011131811573" style="zoom:33%;" />

### 2.4 快门

快门可以用于调节曝光度，快门时间越长，物体显示越模糊

运动模糊，即为快门打开时会拍摄到一段运动，运动模糊从某种程度上来说会增加一定的真实感

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011141544652.png" alt="image-20241011141544652" style="zoom:50%;" />

机械快门在进行拍摄时会有一小段开合的时间差，而此时如果拍摄高速运动的物体就容易发生变形的问题，这种现象称为：Rolling Shutter

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011141746371.png" alt="image-20241011141746371" style="zoom:33%;" />

### 2.5 F数和快门的关系

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011141827723.png" alt="image-20241011141827723" style="zoom:67%;" />

在选择时要综合考虑景深和运动模糊的问题

### 2.6 高速和延时摄影

高速摄影：快门时间极短，每秒派更多的照片

延时摄影：长曝光时间，小光圈

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011151841419.png" alt="image-20241011151841419" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011151856041.png" alt="image-20241011151856041" style="zoom:50%;" />

## 3. 薄透镜近似

透镜是一个很复杂的物理元件，而为了简洁地描述一些这类元件的普遍规律需要简化这一类元件

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011152033541.png" alt="image-20241011152033541" style="zoom:50%;" />

### 3.1 理想化薄透镜

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011152102463.png" alt="image-20241011152102463" style="zoom:50%;" />

对于透镜的理想化模型，需要满足三个特征：

- 所有进入透镜的平行光一定过焦点
- 过焦点的在透镜后一定是平行光
- 焦距可以变化

### 3.2 透镜公式

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011152223992.png" alt="image-20241011152223992" style="zoom:50%;" />

利用相似即可推导出公式

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011152307471.png" alt="image-20241011152307471" style="zoom:50%;" />

消去$h_o,h_i$

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011152556203.png" alt="image-20241011152556203" style="zoom:50%;" />

### 3.3 散焦模糊

当物体远离焦平面时，聚焦后的点不在传感器平面，但是光线仍然会继续传播至传感器平面，因此一个点在传感器上就会成为一个面

这样一种现象称为：模糊（Defoucus Blur）

而这个面产生的直径称为：Circle of confusion，模糊圆

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011152854971.png" alt="image-20241011152854971" style="zoom:50%;" />

有这样一个公式：
$$
\frac{C}{A}=\frac{d^{\prime}}{z_i}=\frac{|z_s-z_i|}{z_i}\\\\
与F-Stop联系起来\\\\
C=A\frac{|z_s-z_i|}{z_i}=\frac{f}{N}\frac{|z_s-z_i|}{z_i}
$$
<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011153155687.png" alt="image-20241011153155687" style="zoom:50%;" />

### 3.4 基于理想薄透镜的光线追踪

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011153506873.png" alt="image-20241011153506873" style="zoom:33%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011153955689.png" alt="image-20241011153955689" style="zoom: 50%;" />

在渲染之前需要进行一些设置：

- 定义sensor的大小，即成像平面大小，定义透镜的属性，即焦距和光圈的大小
- 定义透镜和物体的距离$z_o$——物距
- 根据透镜方程计算相应的深度$z_i$——相距

渲染过程：

- 通过透镜的特征先确定$x^{\prime\prime\prime}$的位置
- 对sensor上的每个像素$x^{\prime}$采样
- 在透镜上随机取样一点$x^{\prime\prime}$
- 计算$x^{\prime\prime}$到$x^{\prime\prime\prime}$的辐射亮度

### 3.5 景深

景深其实就是模糊的范围，景深大则模糊的范围小，景深小模糊的范围大

光圈越大，景深越小；光圈越小，景深越大

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011154723340.png" alt="image-20241011154723340" style="zoom:50%;" />

理论上来说，景深就是在场景内对应的CoC足够小的距离范围

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011154938670.png" alt="image-20241011154938670" style="zoom: 33%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011154956276.png" alt="image-20241011154956276" style="zoom:33%;" />

DOF就是景深，即成像清晰的一段范围，景深外的物体成像模糊
