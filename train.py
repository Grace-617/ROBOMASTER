from ultralytics import YOLO
import os



def train():

    # 加载预训练模型

    model = YOLO(
        "yolov8n.pt"
    )



    # 开始训练

    results = model.train(

        data="dataset.yaml",

        epochs=50,

        imgsz=640,

        batch=8,

        device="cpu",


        # 数据增强

        hsv_h=0.015,

        hsv_s=0.7,

        hsv_v=0.4,


        # 保存路径

        project="runs",

        name="armor_train",


        workers=4

    )



    print(
        "训练完成!"
    )


    print(
        "最佳模型路径:"
    )

    print(
        "runs/armor_train/weights/best.pt"
    )



if __name__=="__main__":

    train()
