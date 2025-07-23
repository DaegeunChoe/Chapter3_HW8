# Chapter3_HW8
내일배움캠프 Chapter3 과제8번 제출용 저장소

[채점 자가진단 (블로그 글, 클릭시 이동)]()


## Environment

개발은 Windows x86에서 이루어졌으며, 사용한 Unreal Engine 버전은 5.5.4 입니다.


## Youtube
[![ALTTEXT]()


## 시작 맵 정보
`/Game/Maps/MenuLevel.MenuLevel` 파일을 사용하면 됩니다.


## 메인 메뉴 UI 설명

<img width="696" height="563" alt="image" src="https://github.com/user-attachments/assets/704ed5ad-99a5-492f-80be-76436888cf14" />

* Start: 게임을 시작합니다.
* Exit: 게임을 종료합니다.

## Files

### Contents
- Content/
  * Blueprints/
    - 각종 블루프린트. 폰, 플레이어컨트롤러, 게임모드베이스...
    - TestButton/, TestText/
      * 테스트용 Actors (버튼과 텍스트)
  * DataTables/
    - 각종 블루프린트. 폰, 플레이어컨트롤러, 게임모드베이스...
  * Maps/
    - MenuLevel (시작 맵)
    - BasicLevel, IntermediateLevel, AdvancedLevel
  * UI/
    - WBP_GameOver: 게임오버 UI
    - WBP_MainMenu: 게임을 시작할 때 나타나는 메인 메뉴
    - WBP_HUD: 게임 진행중에 나타나는 헤드업 디스플레이
  

### Source Codes

- Source/SpartaProject/Public/
  * Character 관련
    - SpartaCharacter.h
  * 게임 진행 관련
    - 레벨 및 웨이브 진행을 관리하며, 게임의 상태(점수, 남은시간, 획득한 코인 등)을 관리한다.
    - SpartaGameInstance.h
    - SpartaGameMode.h
    - SpartaGameState.h
  * PlayerController 및 UI 관련
    - 모든 UI(Widget)은 PlayerController에서 관리한다.
    - SpartaPlayerController.h
  * Item 관련
    - BaseItem.h: 모든 아이템의 부모 클래스
    - OnlyOnceItem.h: 한번만 작용하는 아이템
    - SpikeItem.h: 스파이크 함정
    - Fragments/: 아이템의 기능을 정의하기 위한 Fragments 클래스 모음
