# Learning_OpenGL

### Open GL 이란?

##### OpenGL은 주로 그래픽과 이미지를 조작하는 데 사용할 수 있는 많은 기능을 제공하는 API(Application Programming Interface)로 간주된다. 그러나 OpenGL 자체는 API가 아니라 Khronos 그룹이 개발하고 유지 관리하는 규격에 불과하다.

##### OpenGL 규격은 각 기능의 결과/출력이 무엇이어야 하는지, 그리고 각 기능의 수행 방법을 정확하게 지정한다. 그런 다음 이 기능이 어떻게 작동해야 하는지에 대한 해결책을 제시하는 것은 이 규격을 구현하는 개발자의 몫이다. OpenGL 규격은 구현 세부 정보를 제공하지 않기 때문에 실제 개발된 버전의 OpenGL은 결과가 규격을 준수하면 다른 구현을 가질 수 있다.

### 관련 지식

#### 콜백 함수
##### 1. 다른 함수의 인자로써 이용되는 함수. / 2. 어떤 이벤트에 의해 호출되어지는 함수.

![image](https://user-images.githubusercontent.com/52204522/107848926-de336200-6e3a-11eb-9ab2-c63a4358cec1.png)

#### 이중 버퍼(Double Buffer)
##### 응용 프로그램이 단일 버퍼를 그릴 때 결과 이미지에 깜빡임 문제가 발생함. 결과 출력 영상이 한순간에 그려지는 것이 아니라 픽셀 단위로 그려지고 보통 왼쪽에서 오른쪽, 위에서 아래로 그려지기 때문인데, 버퍼를 두개를 만들어서 전면 버퍼에는 최종 출력물을, 후면 버퍼에는 렌더링 명령을 담당하여 렌더링 명령이 끝나면 후면 버퍼와 전면 버퍼를 스왑하여 표시함으로써, 깜빡임 문제를 해결함.

### 사용 라이브러리

#### GLFW(Graphics Library Framework)
##### OpenGL과 함께 사용하기위한 경량 유틸리티 라이브러리. window와 OpenGL 컨텍스트를 생성 및 관리 할 수 있으며 조이스틱, 키보드 및 마우스 입력을 처리 할 수 있다.

#### GLM(OpenGL Mathematics)
##### GLSL을 기반으로하는 그래픽 소프트웨어에 사용 가능한 C++ 수학 라이브러리.

#### GLAD
##### OpenGL 드라이버는 다양한 버전이 있기 때문에 컴파일 시에 대부분의 함수의 위치를 알 수 없고, 이 때문에 런타임에 질의하여야 함. 그 후에 필요한 함수의 위치를 검색하여 나중에 사용할 수 있도록 함수 포인터에 저장해야 하는데, 이러한 귀찮은 작업들을 관리해주는 오픈소스 라이브러리가 GLAD 이다.

#### 참고 자료

##### [나무위키 Open GL](https://namu.wiki/w/OpenGL)
##### [LearnOpenGL](https://learnopengl.com/Getting-started/OpenGL)
##### [OpenGL Tutorial by Michael Grieco](https://www.youtube.com/watch?v=_POT8K638VY&list=PLysLvOneEETPlOI_PI4mJnocqIpr2cSHS)

##### [이중 버퍼](https://satisfactoryplace.tistory.com/18)
