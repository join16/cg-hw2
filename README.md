# Computer Graphics Homework #2

### (a.k.a. Snow Hunter)

###### 2013147544 조인

1. 프로그램 설명
  - Homework #2 스펙에 맞춰 구현된 OpenGL C++ 프로그램
  - src/main.cpp = 메인 소스 코드.  src/lib/* = 추가적으로 구현한 custom classes
  - 특이점
    + glutIdleFunc 대신 glutTimerFunc, glutPostRedisplay를 사용하여 10ms 마다 rendering 하도록 구현 (과제 spec)
    + snowMan들이 정면만 바라보며 오는 것이 아니라, 현재 유저의 위치를 바라보며 전진하도록 구현
      * 초기 생성 시 사용자 위치를 향해 바라보며 전진함
      * 이후, snowMan이 일정 거리 이상을 움직였을 경우, 다시 현재 사용자 위치를 바라보며 전진하도록 전진방향 재설정
    + 좌측 상단에 collided snowMan count 출력 (과제 spec)
    + bounding box 대신, user와 snowMan의 body radius의 합과 두 body sphere 중점 사이의 거리를 비교하여 collision 체크 (강의 중 교수님 말씀)
    + snowMans는 finite 하므로, 초기에 1000개의 snowMan 생성
      * 초기에 생성될 때에는 disabled된 상태. (enabled된 snowMan만 움직이고, 화면에 그려짐)
      * 이후, 새로운 snowMan을 생성할 때, 현재 있는 snowMans 중 disabled된 snowMan 하나를 고른 후, 좌표 및 속도 재설정, enable함

  - 추가 구현사항
    + super snowMan: 3초에 한번씩, 빨간색 snowMan이 생성됨. 이는 기존의 snowMan보다 2배 빠름
    + direction of snowMan: 주기적으로 카메라를 바라보며 전진하도록 재설정
    + Pause 기능: Space 입력 시, 일시정지. 다시 space 입력하면 resume

2. 프로그램 조작방법
  - 왼쪽, 오른쪽 방향키: 사용자 (카메라)를 좌,우 로 이동
  - 위, 아래 방향키: 카메라 시점 조정
  - space: 일시정지
  - q: 프로그램 종료

3. 빌드 방법
  - Makefile 사용: make 또는 make all 실행
  - cmake 사용: cmake가 설치되어 있을 경우, bin/output 실행

4. 참고사항
  - OS X 운영체제 기준으로 library links를 적용하였기 때문에, 다른 OS에서 작동 불가능