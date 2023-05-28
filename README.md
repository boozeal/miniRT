# miniRT

1. 개요

Ray tracing 기법을 활용한 3d 그래픽 프로그램

2. 구현한 내용 설명

다수의 오브젝트들이 다수의 광원에 의해 비춰지는 장면을 출력한다.
- Shading
- Bump map texture
- UV mapping
- Anti aliasing
- Phong reflection
등의 기법 적용

3. 실행 방법

(Mac 환경에서 실행 가능)
make로 빌드 후 miniRT 실행 프로그램에 rt 디렉토리에 있는 맵 파일(.rt) 확장자 파일을 인자로 주어 실행한다.
ex) ./miniRT ./rt/earth.rt
