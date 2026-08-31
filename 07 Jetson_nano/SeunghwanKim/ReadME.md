# RPS YOLO TensorRT 실행 방법

## 1. 프로젝트 파일 구성

프로젝트 디렉터리는 다음과 같이 구성한다.

```text
project/
├── PR_01_PRS.py
├── requirements.txt
├── rps_yolo11n_v.onnx
├── rps_yolo11n_v.engine
└── trt_module.py
```

### 파일 설명

| 파일                     | 설명                                |
| ---------------------- | --------------------------------- |
| `PR_01_PRS.py`         | 가위바위보 인식 및 승패 판정을 수행하는 메인 실행 파일   |
| `requirements.txt`     | Python 실행에 필요한 패키지 목록             |
| `rps_yolo11n_v.onnx`   | YOLO 가위바위보 객체 탐지 모델               |
| `rps_yolo11n_v.engine` | ONNX 모델을 TensorRT Engine으로 변환한 파일 |
| `trt_module.py`        | TensorRT 관련 기능을 처리하는 모듈           |

---

## 2. Python 가상환경 생성

프로젝트 디렉터리에서 가상환경을 생성한다.

```bash
python3 -m venv venv
```

가상환경을 활성화한다.

```bash
source venv/bin/activate
```

정상적으로 활성화되면 터미널 앞에 `(venv)`가 표시된다.

---

## 3. 필요한 패키지 설치

`requirements.txt`에 정의된 패키지를 설치한다.

```bash
pip install -r requirements.txt
```

설치가 완료되면 주요 패키지를 확인한다.

```bash
python3 -c "import cv2; print('OpenCV:', cv2.__version__)"
```

```bash
python3 -c "from ultralytics import YOLO; print('Ultralytics OK')"
```

---

## 4. ONNX 모델

프로젝트에 다음 ONNX 모델을 준비한다.

```text
rps_yolo11n_v.onnx
```

모델의 Class ID는 다음과 같이 사용한다.

```text
0 → scissors
1 → rock
2 → paper
```

`PR_01_PRS.py`의 Class ID 설정과 학습된 모델의 Class ID 순서가 동일해야 한다.

---

## 5. ONNX → TensorRT Engine 변환

TensorRT Engine이 없는 경우 `trtexec`를 이용하여 ONNX 모델을 TensorRT Engine으로 변환한다.

### 5-1. ONNX 모델 경로

ONNX 모델은 다음 경로에 위치한다.

```text
/home/aidl/work/examples/rps_yolo11n_v.onnx
```

### 5-2. TensorRT Engine 변환

다음 명령어를 실행한다.

```bash
trtexec \
  --onnx=/home/aidl/work/examples/rps_yolo11n_v.onnx \
  --saveEngine=/home/aidl/work/examples/04_Object_Detection_Based_On-Device_AI/rps_yolo11n_v.engine \
  --fp16 \
  --allowGPUFallback
```

### 옵션 설명

| 옵션                   | 설명                             |
| -------------------- | ------------------------------ |
| `--onnx`             | 변환할 ONNX 모델 경로                 |
| `--saveEngine`       | 생성할 TensorRT Engine 파일 경로      |
| `--fp16`             | FP16 정밀도를 사용하여 추론 성능 향상        |
| `--allowGPUFallback` | 지원되지 않는 연산에 대해 GPU fallback 허용 |

변환이 정상적으로 완료되면 다음 파일이 생성된다.

```text
rps_yolo11n_v.engine
```

### 5-3. Engine 생성 확인

```bash
ls -lh /home/aidl/work/examples/04_Object_Detection_Based_On-Device_AI/rps_yolo11n_v.engine
```

---

## 6. TensorRT Engine 로드 테스트

생성된 TensorRT Engine을 Ultralytics에서 정상적으로 로드할 수 있는지 확인한다.

프로젝트 디렉터리로 이동한다.

```bash
cd /home/aidl/work/examples/04_Object_Detection_Based_On-Device_AI
```

다음 명령어를 실행한다.

```bash
python3 -c "from ultralytics import YOLO; model=YOLO('rps_yolo11n_v.engine', task='detect'); print('TensorRT Engine Load OK')"
```

다음과 같이 출력되면 Engine 로드가 정상적으로 이루어진 것이다.

```text
TensorRT Engine Load OK
```

---

## 7. 프로그램 실행

프로젝트 디렉터리에서 메인 프로그램을 실행한다.

```bash
python3 PR_01_PRS.py
```

정상적으로 실행되면 카메라 화면이 출력되고 가위바위보 객체 탐지가 시작된다.

---

## 8. 프로그램 동작

카메라에 두 개의 손이 인식되면 각각의 손 모양을 기준으로 승패를 판정한다.

예:

```text
scissors vs rock
PLAYER 2 WIN
FPS: 28.5
```

손이 2개 미만으로 인식되는 경우:

```text
Waiting for 2 hands...
```

가 표시된다.

### 가위바위보 판정

| Player 1 | Player 2 | 결과           |
| -------- | -------- | ------------ |
| Rock     | Scissors | PLAYER 1 WIN |
| Scissors | Paper    | PLAYER 1 WIN |
| Paper    | Rock     | PLAYER 1 WIN |
| 동일한 손    | 동일한 손    | DRAW         |
| 그 외      | -        | PLAYER 2 WIN |

---

## 9. 종료 방법

프로그램 실행 중 카메라 창에서 `q` 키를 누르면 프로그램이 종료된다.

---

## 10. 전체 실행 순서

처음부터 실행하는 경우 다음 순서로 진행한다.

### ① 프로젝트 디렉터리 이동

```bash
cd /home/aidl/work/examples/04_Object_Detection_Based_On-Device_AI
```

### ② Python 가상환경 생성

```bash
python3 -m venv venv
```

### ③ 가상환경 활성화

```bash
source venv/bin/activate
```

### ④ 필요한 패키지 설치

```bash
pip install -r requirements.txt
```

### ⑤ ONNX → TensorRT Engine 변환

Engine이 없는 경우에만 실행한다.

```bash
trtexec \
  --onnx=/home/aidl/work/examples/rps_yolo11n_v.onnx \
  --saveEngine=/home/aidl/work/examples/04_Object_Detection_Based_On-Device_AI/rps_yolo11n_v.engine \
  --fp16 \
  --allowGPUFallback
```

### ⑥ Engine 생성 확인

```bash
ls -lh rps_yolo11n_v.engine
```

### ⑦ TensorRT Engine 로드 테스트

```bash
python3 -c "from ultralytics import YOLO; model=YOLO('rps_yolo11n_v.engine', task='detect'); print('TensorRT Engine Load OK')"
```

### ⑧ 프로그램 실행

```bash
python3 PR_01_PRS.py
```

### ⑨ 프로그램 종료

카메라 화면에서 `q` 키를 입력한다.

---

## 11. 주의사항

### 11-1. TensorRT Engine 환경 의존성

TensorRT Engine은 GPU, CUDA, TensorRT 환경에 영향을 받을 수 있다.

따라서 다른 Jetson 장치 또는 다른 TensorRT 환경에서 실행할 경우 기존 `.engine` 파일이 정상적으로 동작하지 않을 수 있다.

이 경우 해당 환경에서 ONNX 모델을 이용하여 TensorRT Engine을 다시 생성한다.

```bash
trtexec \
  --onnx=/home/aidl/work/examples/rps_yolo11n_v.onnx \
  --saveEngine=/home/aidl/work/examples/04_Object_Detection_Based_On-Device_AI/rps_yolo11n_v.engine \
  --fp16 \
  --allowGPUFallback
```

### 11-2. Class ID 확인

학습된 YOLO 모델의 Class ID 순서가 다음과 동일해야 한다.

```text
0 → scissors
1 → rock
2 → paper
```

Class ID가 다른 경우 `PR_01_PRS.py`의 `ansToText`를 수정해야 한다.

### 11-3. 카메라 확인

현재 프로그램은 기본 카메라 장치인 `0`번 카메라를 사용한다.

```python
cap = cv2.VideoCapture(0)
```

카메라 장치 번호가 다른 경우 해당 번호로 변경한다.

### 11-4. GPU 사용

YOLO 추론은 GPU `device=0`을 사용한다.

```python
results = model(
    frame,
    imgsz=320,
    conf=0.5,
    iou=0.45,
    device=0,
    verbose=False
)
```

따라서 NVIDIA Jetson의 CUDA 및 TensorRT 환경이 정상적으로 구성되어 있어야 한다.
