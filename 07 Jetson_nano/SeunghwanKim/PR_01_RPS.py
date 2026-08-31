import cv2
from ultralytics import YOLO
import time

# 1. TensorRT 엔진 로드
model = YOLO("rps_yolo11n_v.engine", task="detect")

# 카메라
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)

# 윈도우 설정
cv2.namedWindow('cam', cv2.WINDOW_NORMAL)
cv2.resizeWindow('cam', 320 + 40, 240 + 60)

# Class ID
ansToText = {
    0: 'scissors',
    1: 'rock',
    2: 'paper'
}

# FPS
prev_time = time.time()
fps = 0.0


# ==========================================
# 가위바위보 승패 함수
# ==========================================
def get_rps_result(hand1, hand2):

    # 같은 손
    if hand1 == hand2:
        return "DRAW"

    # hand1 승리 조건
    if (
        (hand1 == "rock" and hand2 == "scissors") or
        (hand1 == "scissors" and hand2 == "paper") or
        (hand1 == "paper" and hand2 == "rock")
    ):
        return "PLAYER 1 WIN"

    return "PLAYER 2 WIN"


while cap.isOpened():

    success, frame = cap.read()

    if not success:
        break

    # ==========================================
    # 2. YOLO 추론
    # ==========================================
    results = model(
        frame,
        imgsz=320,
        conf=0.5,
        iou=0.45,
        device=0,
        verbose=False
    )

    result = results[0]

    # class 이름 변경
    result.names = ansToText

    # ==========================================
    # 3. 인식된 손의 종류 가져오기
    # ==========================================
    hands = []

    if result.boxes is not None:

        for cls, conf in zip(
            result.boxes.cls.tolist(),
            result.boxes.conf.tolist()
        ):

            class_id = int(cls)

            if class_id in ansToText:
                hands.append(ansToText[class_id])

    # ==========================================
    # 4. 손이 2개일 때 승패 판정
    # ==========================================
    rps_result = "Waiting..."

    if len(hands) >= 2:

        # 가장 먼저 인식된 2개만 사용
        hand1 = hands[0]
        hand2 = hands[1]

        rps_result = get_rps_result(hand1, hand2)

    # ==========================================
    # 5. YOLO 결과 화면 출력
    # ==========================================
    frame = result.plot()

    # ==========================================
    # 6. 승패 결과 출력
    # ==========================================
    if len(hands) >= 2:

        hand_text = f"{hands[0]} vs {hands[1]}"

        cv2.putText(
            frame,
            hand_text,
            (10, 60),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.7,
            (255, 255, 255),
            2,
            lineType=cv2.LINE_AA
        )

        cv2.putText(
            frame,
            rps_result,
            (10, 95),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            (0, 255, 0),
            2,
            lineType=cv2.LINE_AA
        )

    else:

        cv2.putText(
            frame,
            "Waiting for 2 hands...",
            (10, 60),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.7,
            (0, 255, 255),
            2,
            lineType=cv2.LINE_AA
        )

    # ==========================================
    # 7. FPS 계산
    # ==========================================
    cur_time = time.time()
    dt = cur_time - prev_time

    if dt > 0:
        fps = 1.0 / dt

    prev_time = cur_time

    cv2.putText(
        frame,
        f"FPS: {fps:.1f}",
        (10, 30),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.8,
        (0, 255, 0),
        2,
        lineType=cv2.LINE_AA
    )

    # 화면 출력
    cv2.imshow("cam", frame)

    # q 종료
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()
