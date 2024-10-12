# $Lecture9$：高级渲染方法

## 1. 高级光线传播

光线传播是一个很复杂的事情，有很多提升效果的方法，如蒙特卡洛积分中概率密度函数的选择，进行路径追踪的方法，以及更高级的光子映射等

### 1.1 蒙特卡洛积分的估计

- 无偏估计：没有任何系统误差，无论使用多少样本，期望总保持一致
- 有偏估计：存在系统误差，即样本数量对期望会有影响
一种特殊的有偏估计：一致性估计(consistent)：当样本数量取无穷大时，没有系统误差

在图形学中，有偏估计会产生模糊，但是对于一致性估计当样本数量无穷大时则会变清晰

### 1.2 双向路径追踪（BDPT，Bidirectional Path Tracing）

BDPT是一种无偏的光线追踪方法

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-10%20232726.png" style="zoom: 67%;" />

- 从相机和光源两端出发对一条光路的子路进行追踪
- 将子路的两个端点连接得到一条光路
- 适用于光源在一个角落时效果较好
- 但是难以实现且非常慢

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-10%20232955.png" style="zoom:50%;" />

### 1.3 Metropolis光线追踪（MLT，Metropolis Light Transport）

MLT是一种无偏的光线追踪，基本思想是找到一条光路后，通过马尔科夫链的形式，根据当前的光线产生一个局部扰动，来生成与其靠近的下一条光线，可以生成任意形状的PDF

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20101333.png" style="zoom:67%;" />

- 适合做复杂的光路传播，只需要找到一条路径作为种子即可
- 是一种无偏估计
- 但是难以估计什么时候收敛
- 所有操作都是局部的，使得图片看上去比较脏
- 不能渲染动画，画面会发生闪烁和抖动

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20101544.png" style="zoom:50%;" />

### 1.4 光子映射（Photon Mapping）

由于光线的聚焦，再观察时会出现一些亮斑，这种现象称为：焦散（caustics）

而光子映射可以有效地实现这一效果，但光子映射是一种有偏的估计方法，在处理Specular-Diffuse-Specular（SDS）这一类材质时也有较好的渲染效果

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011103741288.png" alt="image-20241011103741288" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20103903.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20103924.png" style="zoom:50%;" />

光子映射主要分为三个阶段：

- 从光源发射光子，让光子发生弹射，直到打在发生漫反射物体的表面，记录光子的位置
- 从相机发出光子，让光子发生弹射，直到打在发生漫反射物体的表面，记录光子的位置
- 在第二次到达漫反射物体表面时，对光子的密度进行局部估计，找到离这个光子最近的N个光子，计算这些光子所占据的面积，最后得到局部密度

有偏的原因：$\frac{dN}{dA}\neq \frac{\Delta N}{\Delta A}$，只有当$dA$足够小时才接近正确

减小误差的方法：发出更多的光子，此时$\Delta A$会变小，更加接近$dA$

因此光子映射是有偏的但是是一致的

### 1.5 顶点合并连接（VCM，Vertex Connection and Merging）

VCM方法是一种BDPT与光子映射的结合

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20104616.png" style="zoom:67%;" />

- 如果在进行BDPT时两个端点无法被连接，而是可以融合，则不需要连接
- 在这些端点附近通过光子映射求密度的方式进行顶点的融合

### 1.6 实时辐射度算法（IR，Instant Radiosity）

基本思想是将已经照亮的表面当作光源继续发射光线

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20104939.png" style="zoom:67%;" />

- 从光源发出一次光线到达物体表面，物体表面能到达的点视为虚拟光源
- 继续使用这些虚拟光源照亮物体
- 可以快速渲染出一些主要发生漫反射的场景
- 但如果这些虚拟光源与着色点十分接近时，这些点会发生融合从而出现一些过亮的点
- 不能渲染Glossy的材质

## 2. 高级外观建模

在材质与外观一节中提到，材质本质上就是外观的一种形式，是光线与表面的作用不同所表现出来的外观，但是有一些传播介质无法用材质来解释，不发生在表面，而是在光线传播的过程中作用，如：云，雾，水体等

### 2.1 非表面模型

光会穿过这一类传播介质，而与光的作用也发生在介质内

#### 2.1.1 散射介质

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20105932.png" style="zoom:67%;" />

当光穿过散射介质时，任何一点可以部分吸收和散射

可以使用相位函数来描述参与介质中任意点的光散射角的分布

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20110049.png" style="zoom:67%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20110105.png" style="zoom:67%;" />

具体过程：

- 随机选择一个方向进行弹射
- 随机选择一个距离直行
- 对于每一个着色点将其连接到光源，通过前面学习到的渲染方程进行着色

#### 2.1.2 人物头发渲染

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20110313.png" style="zoom:50%;" />

头发是一个复杂的结构，仔细观察可以发现在头发上会出现两种不同的高光，一种是环境光所造成的较暗一点的高光，一种是穿过头发后发生的一些复杂传播形成的细碎的亮斑

（1）Kajiya-Kay Model

将头发视为一个会发生散射的柱体，光线会被散射在一个圆锥面上，但这个模型有一个缺点，最后做出来的渲染效果不经过优化的话会导致过亮

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20110708.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20110805.png" style="zoom:50%;" />

（2）Marschner Model

将头发视为即可发生反射也可发生折射的一种模型，R表示发生一次反射，T表示发生一次折射

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20110826.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20110945.png" style="zoom:50%;" />

将头发当作一个玻璃圆柱体，外层和内层材质不同，同时发生反射和投射

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011111049365.png" alt="image-20241011111049365" style="zoom:50%;" />

#### 2.1.3 动物毛发渲染

如果使用和人物头发渲染同样的方式来对动物的毛发进行渲染，结果发现具有很大的偏差

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20111213.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20111325.png" style="zoom:50%;" />

原因是动物毛发与人物头发虽然结构类似，但是不同结构的含量，占比有很大的差别，因此会产生误差

明显可以看出，在动物毛发中能发生光线散射的髓质会更多，因此光线更分散

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011111440172.png" alt="image-20241011111440172" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20111455.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20111512.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20111528.png" style="zoom:50%;" />

可以采用双层圆柱结构来描述这一特性，由此将光线分为了五类，除了单层圆柱中的三种，还有两类在内层圆柱中发生散射后的光线

#### 2.1.4 颗粒材质

与其他传播介质都是一个整体不同，颗粒材质是由细小颗粒之间的作用而形成的一种介质

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011111743949.png" alt="image-20241011111743949" style="zoom:50%;" />

这种介质可以通过一种程序化生成的方法来进行渲染

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20111907.png" style="zoom:50%;" />

### 2.2 复杂的表面模型

一些特殊的表面模型同样不止在表面与光线发生作用

#### 2.2.1 半透明材质

典型的半透明材质就是玉石

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20112116.png" style="zoom:33%;" /><img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20112135.png" style="zoom:33%;" />

#### 2.2.2 次表面散射

在表面下发生的散射，即发生在材质内

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20112239.png" style="zoom:50%;" />

是BRDF的一种延申，表示某一点出射光线的辐射亮度来源于另一点的辐射照度$S(x_i,\omega_i,x_o,\omega_o)$

对每一点都对表面进行一次积分，则修改方程即为：
$$
L(x_o,\omega_o)=\int_A\int_{H^2}S(x_i,\omega_i,x_o,\omega_o)L_i(x_i,\omega_i)\cos\theta_id\omega_idA
$$
一种近似方式为引入一对偶极子进行近似，引入两个点光源来近似次表面散射的效果

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20112730.png" style="zoom:50%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20112806.png" style="zoom:50%;" />

### 2.3 布料

布料由一系列缠绕的纤维构成

- 纤维缠绕构成股
- 股缠绕构成线

而对于线的编织方式同样存在多种可能

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20120729.png" style="zoom:50%;" />

对于布料有三种渲染方式：

- 将布料当作表面渲染，通过BRDF进行计算
- 将布料当作散射介质渲染，将布料中单个的纤维和分布的性质转化为散射参数
- 将布料当作真实的纤维渲染，类似于毛发渲染，一根一根纤维进行

### 2.4 细节外观

有时渲染的效果已经达到了一种很好的效果，但是看起来却没有实际的真实感，这是因为渲染的“过于完美”，而在实际生活中物体表面有着各种各样的细节

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20121316.png" style="zoom: 25%;" /><img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20121400.png" style="zoom:25%;" /><img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011121430224.png" alt="image-20241011121430224" style="zoom:25%;" />

原因是因为当采用微表面模型的BRDF时，法线的分布函数在理论中采用了标准的理论正态分布函数，但是实际状况要复杂的多

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20121616.png" style="zoom: 33%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20121633.png" style="zoom:33%;" />

而要做出这样的效果十分困难，其中一种是采用一种很大的法线贴图来表现细节，但是这种渲染方式极其慢

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20122020.png" style="zoom:50%;" />

重新考虑微表面模型，一个像素会覆盖很多微表面，可以通过将一个像素所覆盖的微表面模型的法线分布算出来替换光滑的法线分布用在微表面模型中

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20122308.png" style="zoom:33%;" />

对于较小的微表面来说，表现的更有该表面的特点；对于较大的微表面来说，表现得更具有统计学规律

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011122438669.png" alt="image-20241011122438669" style="zoom:33%;" />

而不同类型的法线贴图也会产生不同的效果

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011122517090.png" alt="image-20241011122517090" style="zoom:33%;" />

## 3. 波动光学

在光线追踪中，有一个重要的假设，光是一束束的，沿直线传播，但在物理中，光是有波粒二象性的，因此如果考虑光以波的形式传播，就会得到不同的结果，并且在微观下会发生衍射，干涉等现象，这种现象在某些渲染场景下更符合实际

闫令琪老师的一项重要研究就是：通过波动光学方程重写渲染方程

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20122749.png" style="zoom:50%;" />

波动光学的BRDF与几何相似，但是相对而言比较不连续

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20122933.png" style="zoom: 33%;" />

## 4. 程序化生成外观

在纹理学习中，提到过这样一个事情，可以通过定义不同的噪声函数，进行计算而不使用贴图来计算一些渲染细节，如大理石花纹，地形，水面，木头等

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20123158.png" style="zoom:33%;" /><img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20123212.png" style="zoom:33%;" /><img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/image-20241011123236483.png" alt="image-20241011123236483" style="zoom:33%;" />

<img src="https://vampire-1304919510.cos.ap-nanjing.myqcloud.com/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202024-10-11%20123255.png" style="zoom:50%;" />

```
if noise(x,y,z) > threshold:
	reflectance = 1
else
	reflectance = 0
```

