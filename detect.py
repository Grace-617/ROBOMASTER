from ultralytics import YOLO
import cv2



# 模型路径

MODEL_PATH = (

"./runs/armor_train/weights/best.pt"

)



# 测试图片

IMAGE_PATH = (

"test.jpg"

)



def detect():


    model = YOLO(
        MODEL_PATH
    )



    results = model.predict(

        source=IMAGE_PATH,

        imgsz=640,

        conf=0.4,

        save=True

    )



    for result in results:


        boxes = result.boxes



        for box in boxes:


            cls = int(
                box.cls[0]
            )


            conf = float(
                box.conf[0]
            )


            name = (
                model.names[cls]
            )


            print(

                f"{name}: {conf:.2f}"

            )



if __name__=="__main__":

    detect()
