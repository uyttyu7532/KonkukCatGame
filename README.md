# konkukcat 

건냥이 키우기


> 플레이하는 동안 건냥이의 각 욕구를 충족시켜 만족도가 0이 되지 않도록 하고, 최종적으로 Level 10이 될 때까지 건냥이를 무사히 키워내는 것이 게임의 목적이다. 이 프로그램은 게임의 기능을 한다.



### 컴파일 방법

 $ gcc konkukcat.c -lpthread

  
 ### 실행 방법

 $ ./a.out


### 게임 설명

 * 텍스트를 이용해 화면에 이미지를 띄우며 진행된다. 
 
 *	기본 게임화면에는 [ 배부름, 잠, 즐거움, 깔끔함 ] 의 욕구 별 만족도와 기본적인 메뉴, 옵션이 표시된다. 각각의 만족도를 채우기 위한 행위로 다음과 같은 행동 옵션 4가지가 제시된다.
행동 종류: 0. eat  1. sleep  2. play  3. clean

*	만족도는 기본 50에서 시작되며 하나의 만족도라도 0이 되면 게임이 종료된다. (단, 만족도 최댓값 = 100)

*	만족도를 채우기 위한 옵션을 택하면 해당되는 만족도가 올라가고 그에 맞는 건냥이의 이미지가 출력된다.

*	만족도는 시간에 따라 랜덤으로 깎인다. 이 때 플레이 시간에 따라 건냥이가 Level up 할수록 만족도가 더 빨리 깎인다.

*	Level이 10이 되면 건냥이가 죽지 않고 게임이 종료된다.


### 실행 화면
<https://www.youtube.com/watch?v=b1C5iSv_GE0&feature=youtu.be>
