# 凌风战队27赛季算法培训 - 装甲板检测追踪项目
本项目为机甲大师赛事场景下的装甲板检测与追踪系统，实现了“基于OpenCV传统视觉算法”与“基于YOLO深度学习算法”的两种装甲板识别方案。
项目针对比赛场景中装甲板目标具有：目标尺寸较小、运动速度快、光照变化明显、背景复杂、目标存在旋转和遮挡等特点，分别采用传统图像处理方法和深度学习方法进行检测，并实现视频场景下的连续目标追踪。

# 项目功能

## 1. OpenCV传统视觉检测（C++）

基于OpenCV实现装甲板检测流程：

* HSV颜色空间转换
* 红蓝颜色区域分割
* 二值化处理
* 形态学滤波
* 轮廓提取
* 灯条特征筛选
* 装甲板匹配
* 目标框绘制

实现流程：

```
输入图像/视频

        ↓

HSV颜色空间转换

        ↓

颜色阈值分割

        ↓

形态学处理

        ↓

轮廓检测

        ↓

灯条匹配

        ↓

装甲板定位

        ↓

输出检测结果
```

---

## 2. YOLO深度学习检测

基于 Ultralytics YOLOv8 实现装甲板目标检测。

主要功能：

* 红方装甲板检测
* 蓝方装甲板检测
* 图片检测
* 视频检测
* 实时目标追踪
* 模型训练与推理

---

# 项目结构

```
Armor-Detection-System
│
├── README.md
│
├── dataset
│   │
│   ├── images
│   │   ├── train
│   │   ├── val
│   │   └── test
│   │
│   ├── labels
│   │   ├── train
│   │   ├── val
│   │   └── test
│   │
│   └── dataset.yaml
│
│
├── OpenCV_CPP
│
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── ArmorDetector.cpp
│   ├── ArmorDetector.h
│   └── result
│
│
├── YOLO
│
│   ├── train.py
│   ├── detect.py
│   ├── track.py
│   │
│   ├── weights
│   │   └── best.pt
│   │
│   └── runs
│
│
├── demo
│
│   ├── input.mp4
│   └── output.mp4
│
│
├── requirements.txt
│
└── .gitignore

```

---

# 环境配置

## 硬件环境

* CPU：Intel Core i7
* GPU：NVIDIA RTX系列（可选）

## 软件环境

```
Windows 10/11

Python 3.10+

C++17

OpenCV 4.x

PyTorch 2.x

Ultralytics YOLOv8

Visual Studio Code
```

---

# 安装依赖

## YOLO环境

创建Python环境：

```bash
conda create -n armor python=3.10

conda activate armor
```

安装依赖：

```bash
pip install -r requirements.txt
```

requirements.txt:

```
ultralytics

opencv-python

numpy

torch

torchvision

```

---

# 数据集

## 数据来源

数据集来源：

* RoboMaster社区公开数据

## 标注工具

使用：

```
LabelImg
```

标注格式：

```
YOLO Format
```

类别定义：

| 类别        | 含义    |
| --------- | ----- |
| redarmor  | 红方装甲板 |
| bluearmor | 蓝方装甲板 |

数据划分：

```
train : 80%

val : 20%

```

---

# YOLO模型训练

## 模型选择

采用：

```
YOLOv8n
```

原因：

* 参数量较小
* 推理速度快
* 适合实时检测
* 方便后续部署

模型：

```
yolov8n.pt
```

---

## dataset.yaml

示例：

```yaml
path: ./dataset

train: images/train

val: images/val


names:

  0: redarmor

  1: bluearmor

```

---

## 开始训练

```bash
yolo detect train \
data=dataset.yaml \
model=yolov8n.pt \
epochs=100 \
imgsz=640 \
batch=8
```

训练完成后生成：

```
runs/detect/train/

        |
        |
        └── weights

              |
              ├── best.pt

              └── last.pt

```

---

# YOLO检测

## 图片检测

```bash
yolo detect predict \
model=runs/detect/train/weights/best.pt \
source=test.jpg \
save=True
```

---

## 视频检测

```bash
yolo detect predict \
model=weights/best.pt \
source=test.mp4 \
save=True
```

检测结果：

```
runs/detect/predict/
```

---

# YOLO目标追踪

使用ByteTrack算法实现连续目标跟踪。

运行：

```bash
yolo track predict \
model=weights/best.pt \
source=test.mp4 \
tracker=bytetrack.yaml
```

实现：

* 目标ID分配
* 视频连续跟踪
* 运动目标定位

---

# 模型训练结果

## 训练配置

| 参数    | 设置      |
| ----- | ------- |
| 模型    | YOLOv8n |
| 输入尺寸  | 640×640 |
| Epoch | 100     |
| Batch | 8       |
| 类别数量  | 2       |

## 评价指标

| 类别        | Precision | Recall | mAP50 |
| --------- | --------- | ------ | ----- |
| redarmor  | 待测试       | 待测试    | 待测试   |
| bluearmor | 待测试       | 待测试    | 待测试   |

---

# 效果展示

## OpenCV检测效果

功能：

* 红蓝目标分割
* 装甲板定位
* 实时框选

## YOLO检测效果

功能：

* 自动识别装甲板
* 输出类别
* 输出置信度

## 视频追踪效果

支持：

* 动态目标跟踪
* 连续帧检测

结果视频：

```
demo/output.mp4

```

---

# 常见问题

## 1. YOLO找不到数据集

检查：

```yaml
path:
train:
val:
```

是否正确。

---

## 2. GPU不可用

检查：

```python
import torch

print(torch.cuda.is_available())

```

返回：

```
True
```

说明GPU正常。

---

## 3. 视频检测速度慢

调整：

```bash
conf=0.5
```

或降低：

```
imgsz=416
```

---

# 参考资料

Ultralytics YOLO:

https://docs.ultralytics.com/

LabelImg:

https://github.com/HumanSignal/labelImg

RoboMaster社区:

https://bbs.robomaster.com/

---

# 作者

Name: Gai Sihan

Date: 2026.8

---

# License

This project is only used for learning and algorithm practice.

