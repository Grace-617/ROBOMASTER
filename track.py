from ultralytics import YOLO



MODEL_PATH = (

"./runs/armor_train/weights/best.pt"

)



VIDEO_PATH = (

"test.mp4"

)



def track():


    model = YOLO(
        MODEL_PATH
    )



    results = model.track(

        source=VIDEO_PATH,

        imgsz=640,

        conf=0.4,


        tracker="bytetrack.yaml",


        save=True,

        show=False

    )



    print(
        "视频追踪完成!"
    )



if __name__=="__main__":

    track()
