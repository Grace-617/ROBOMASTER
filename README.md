# 凌风战队27赛季算法培训 - 装甲板检测追踪项目
本项目为机甲大师赛事场景下的装甲板检测与追踪系统，实现了“基于OpenCV传统视觉算法”与“基于YOLO深度学习算法”的两种装甲板识别方案。
项目针对比赛场景中装甲板目标具有：目标尺寸较小、运动速度快、光照变化明显、背景复杂、目标存在旋转和遮挡等特点，分别采用传统图像处理方法和深度学习方法进行检测，并实现视频场景下的连续目标追踪。

项目分别采用：

- 基于 OpenCV 的传统计算机视觉算法
- 基于 Ultralytics YOLOv8 的深度学习目标检测算法

完成红蓝双方步兵装甲板的检测，并结合目标追踪算法实现视频场景下的连续目标跟踪。

针对 RoboMaster 比赛环境中装甲板具有：

- 目标尺寸小
- 运动速度快
- 光照变化明显
- 背景复杂
- 目标姿态变化大

等特点，项目进行了针对性的算法设计与优化，提高模型在实际比赛场景中的适应能力。

---

# 项目功能

## 1. 基于 OpenCV 的传统视觉装甲板检测

采用传统图像处理方法，实现无需神经网络推理的装甲板识别。

主要流程：

```
输入图像

↓

BGR转HSV颜色空间

↓

红蓝灯条区域提取

↓

二值化处理

↓

形态学操作

↓

轮廓检测

↓

灯条几何特征筛选

↓

装甲板匹配

↓

输出检测框
```

实现功能：

- 红蓝颜色区域识别
- 灯条轮廓提取
- 长宽比筛选
- 灯条位置匹配
- 装甲板区域定位
- 检测结果可视化


---

## 2. 基于 YOLOv8 的深度学习装甲板检测

采用 Ultralytics YOLOv8 目标检测框架，对自定义装甲板数据集进行训练，实现自动化目标识别。

主要流程：

```
输入图片/视频

↓

YOLOv8模型推理

↓

目标类别预测

↓

Bounding Box定位

↓

置信度筛选

↓

输出检测结果
```

支持：

- 红方装甲板检测
- 蓝方装甲板检测
- 图片检测
- 视频检测
- 摄像头实时检测


---

## 3. 装甲板目标追踪

在 YOLO 检测基础上，引入目标追踪算法，实现动态视频中的连续目标跟踪。

流程：

```
视频输入

↓

YOLO目标检测

↓

目标匹配

↓

轨迹更新

↓

输出目标ID
```

实现：

- 装甲板连续跟踪
- 目标编号保持
- 运动轨迹记录


---

# 数据集说明

## 数据来源

数据集来源于：

- RoboMaster赛事公开素材
- 公开装甲板检测数据集
- 自行采集与整理的数据


## 数据标注

采用：

- 标注工具：labelImg
- 标注格式：YOLO格式

类别定义：

| 类别 | 含义 |
|-|-|
| redarmor | 红方步兵装甲板 |
| bluearmor | 蓝方步兵装甲板 |


数据格式：

```
dataset

├── images

│   ├── train

│   └── val


└── labels

    ├── train

    └── val
```


数据划分：

- 训练集：80%
- 验证集：20%


---

# YOLO模型训练

## 基础模型

采用：

```
YOLOv8n
```

进行迁移学习训练。

选择轻量化模型原因：

- 参数量较少
- 推理速度快
- 方便后续部署到嵌入式设备


模型特点：

| 参数 | 数值 |
|-|-|
| 网络模型 | YOLOv8n |
| 输入尺寸 | 640×640 |
| 训练轮次 | 50 epochs |
| Batch Size | 8 |
| 标注类别 | 2类 |


---

# 模型优化

针对 RoboMaster 装甲板检测场景，进行了以下优化：

## 1. 自定义数据集训练

使用红蓝装甲板图片进行模型微调，提高模型对比赛目标的识别能力。


## 2. 小目标检测优化

针对远距离装甲板目标：

- 增加有效训练样本
- 调整输入尺寸
- 优化检测阈值

提高小目标检测效果。


## 3. 复杂背景适应

针对赛场中：

- 灯光变化
- 背景干扰
- 机器人遮挡

等情况进行训练，提高模型鲁棒性。


---

# 环境配置

## 软件环境

```
Python >= 3.8

PyTorch

Ultralytics YOLOv8

OpenCV

C++17
```


## Python依赖安装

```bash
pip install -r requirements.txt
```


## OpenCV环境

要求：

- Visual Studio / VS Code
- C++17
- OpenCV 4.x


---

# 使用方法


## 一、OpenCV传统算法运行


进入目录：

```bash
cd OpenCV_CPP
```


编译运行：

```bash
cmake .
make
```


运行后输入测试图片：

输出：

- 装甲板位置
- 检测框


---

## 二、YOLO模型训练


运行：

```bash
yolo detect train \
data=dataset.yaml \
model=yolov8n.pt \
epochs=50 \
batch=8 \
imgsz=640
```


训练完成后生成：

```
runs/detect/train/weights/best.pt
```


---

## 三、YOLO图片检测


运行：

```bash
yolo detect predict \
model=best.pt \
source=test.jpg \
save=True
```


---

## 四、YOLO视频检测与追踪


运行：

```bash
yolo detect predict \
model=best.pt \
source=test.mp4 \
save=True
```


输出：

- 检测框视频
- 目标类别
- 置信度


---

# 项目目录结构

```
RM_Armor_Detection

├── README.md

├── dataset

│   ├── images

│   │   ├── train

│   │   └── val

│   │

│   └── labels

│       ├── train

│       └── val


├── OpenCV_CPP

│   ├── main.cpp

│   ├── armor_detector.cpp

│   ├── armor_detector.h

│   └── CMakeLists.txt


├── YOLO

│   ├── train.py

│   ├── detect.py

│   ├── track.py

│   └── best.pt


├── results

│   ├── images

│   └── videos


└── requirements.txt
```


---

# 实验结果


## OpenCV传统视觉检测效果


实现：

- 灯条识别
- 装甲板定位
- 结果可视化


---

## YOLO检测效果



评价指标：

|类别|Precision|Recall|mAP|
|-|-|-|-|
|redarmor|待补充|待补充|待补充|
|bluearmor|待补充|待补充|待补充|


---

## 视频追踪效果


实现：

- 动态目标检测
- 连续帧追踪
- 目标ID保持


---

# 项目总结

本项目完成了 RoboMaster 场景下装甲板检测与追踪系统的设计，实现了传统计算机视觉算法与深度学习算法两种技术路线。

其中：

- OpenCV方案利用颜色、轮廓和几何约束，实现快速装甲板定位；
- YOLO方案利用深度学习模型，提高复杂环境下目标检测能力；
- 结合追踪算法，实现动态场景中的连续目标跟踪。

通过本项目实践，对计算机视觉中的图像处理、目标检测、模型训练以及机器人视觉感知流程进行了深入学习。


---

# 作者

Gai Sihan
2026.8


Computer Vision Algorithm Practice

完成时间：2026年
