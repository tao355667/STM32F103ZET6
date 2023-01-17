# STM32F103ZET6

为了毕设学STM32，然而只学了一点，就感觉可以直接开始做了，故这里程序不多

开发板：正点原子战舰V3开发板（STM32F103ZET6），搭配7寸屏幕

开发方式：库函数开发（虽然落后，但当时上了贼船懒得改了）

IDE：Keil5

**STM32内部功能套路：**（GPIO、中断、定时器、看门狗等）

1. 了解该模块的作用和使用方法。
2. 查API（知道基本API的功能），找模板（网上找别人的程序，看他怎么用，照猫画虎）。
3. 建立小项目测试调参，将调好的程序移植进项目。

**外设套路：**（输入：传感器、鼠标、键盘、手柄 | 输出：LED、屏幕、继电器）

1. 看模块手册，知道引脚作用，正确接线。
2. 向店家要驱动程序，若没有则自己也可根据手册写（主要是时序图要搞懂）。
3. 建立小项目测试调参，测试模块的各功能。模块的数据可用串口/LED查看。
4. 测试完成后，将小项目中的程序移植进项目。

**带操作系统和GUI库开发：**

STM32F103ZET6可以加入小的操作系统管理任务，如FreeRTOS，UCOS-III

STM32F103ZET6外接屏幕后，可用GUI库，如EMWIN，LittleVGL

操作系统和GUI库要先移植进项目，才能进行开发

**参考资料：**

主要是正点原子的库函数开发手册

正点原子：<http://47.111.11.73/docs/boards/stm32/zdyz_stm32f103_warship.html>

野火：<https://doc.embedfire.com/products/link/zh/latest/index.html>

安富莱：<https://www.armbbs.cn/forum.php>

STM32官方文档：<https://www.stmcu.com.cn/Designresource/list/STM32F1/document/document>
