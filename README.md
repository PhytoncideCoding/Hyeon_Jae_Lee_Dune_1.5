# 24학번 이현재
## <완성 부분>
### 1-1 ~ 2-4 ESC키 선택 취소, 상태창 비우기 까지 완성
## <미완성 도전 부분>
### 3-1 맨 왼쪽 샌드웜이 가장 가까운 유닛을 향해 이동하는 것을 구현하려 했으나 두번째로 가까운 하베스터로 이동하는 문제상황 발생
## <추가 기능>
### 2-2 추가 기능: 더블 방향키의 이동 범위가 맵 표시 창을 넘으면 해당 방향으로 갈 수 있는 최대한의 좌표로 이동
---
## 1) 준비

### 1-1 시작 화면 출력
#### <사용함수>
> **<engine.c>**
```
 void intro(void) 시작 화면 출력 함수
```
> **<display.c>**

> **<io.c>**
```
 void set_color(int color) 글 색, 글 배경색 설정 함수
```
### 1-2 종료 화면 출력
#### <사용함수>
> **<engine.c>**
```
 void outro(void) 종료화면 출력함수
```
> **<display.c>**

> **<io.c>**
```
void set_color(int color) 글 색, 글 배경색 설정 함수 

KEY get_key(void) 키입력을 받는 함수
```

### 1-3 자원 상태 출력
#### <사용함수>
> **<engine.c>**

> **<display.c>**
```
 void display_resource(RESOURCE resource) 자원 구조체 매개 변수로 입력 받아 자원 상태 출력 함수
```
> **<io.c>**
```
 void gotoxy(POSITION pos) pos 좌표로 이동하는 함수

 void set_color(int color) 글 색, 글 배경색 설정 함수 
```

### 1-4 초기 맵 표시창 출력
####
> **<engine.c>**
```
 void init_map_land_building_unit(void) 초기 맵 초기화 함수
```
> **<display.c>**
```
맵 버퍼링 함수
void project_map_f(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH])

초기 맵 상태 출력 함수
void display_map_f(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor,
	LAND_ATTRIBUTE Rocks,
	UNIT_ATTRIBUTE Sand_Worm
) 
```
> **<io.c>**
```
 void printc(POSITION pos, char ch, int color) 원하는 좌표로 이동해서 원하는 색상으로 문자 출력 함수
```
> **<common.h>**
```
 inline POSITION position_move_f(POSITION p1, POSITION p2) 두 좌표의 행, 열을 각각 더해서 새로운 좌표를 리턴해주는 인라인 함수
```
### 1-5 초기 직사각형 상태창 출력
#### <사용함수>
> **<engine.c>**
```
 void init_state_window_f(void) 상태창 초기상태 초기화 함수
```
> **<display.c>**
```
 void display_resource(RESOURCE resource) 자원 상태 출력 함수

상태창 직사각형 출력 함수
 void display_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH]) 

상태창 직사각형 버퍼링 함수
 void project_state_window_f(char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH],	char backbuf_state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH]) 
```
> **<io.c>**
+ void gotoxy(POSITION pos) pos 좌표로 이동하는 함수

+ void printc(POSITION pos, char ch, int color) 원하는 좌표로 이동해서 원하는 색상으로 문자 출력 함수
> **<common.h>**
```
두 좌표의 합을 구하는 인라인 함수
inline POSITION position_move_f(POSITION p1, POSITION p2)
```

### 1-6 초기 직사각형 시스템 메세지 창 출력
#### <사용함수>
> **<engine.c>**

> **<display.c>**
```
시스템 메시지창 버퍼링 함수
void project_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH],
	char backbuf_system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH])

시스템 메시지 창 화면 출력 함수
void display_system_message_w_f(char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH])
```
> **<io.c>**
```
void gotoxy(POSITION pos) pos 좌표로 이동하는 함수

void printc(POSITION pos, char ch, int color) 원하는 좌표로 이동해서 원하는 색상으로 문자 출력 함수
```
> **<common.h>**
```
두 좌표의 합을 구하는 인라인 함수
inline POSITION position_move_f(POSITION p1, POSITION p2)
```
### 1-7 초기 명령창 출력
#### <사용함수>
> **<engine.c>**

> **<display.c>**
```
명령창 직사각형 버퍼링 함수
void project_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH],
	char backbuf_command_w_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH])

명령 창 직사각형 출력 함수
void display_command_message_w_f(char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH])
```
> **<io.c>**
```
void gotoxy(POSITION pos) pos 좌표로 이동하는 함수

void printc(POSITION pos, char ch, int color) 원하는 좌표로 이동해서 원하는 색상으로 문자 출력 함수
```
> **<common.h>**
```
두 좌표의 합을 구하는 인라인 함수
inline POSITION position_move_f(POSITION p1, POSITION p2)
```

### 2-1 커서 방향키로 이동, 투명함 구현: 지형 유닛 그대로, 색깔로만 표시
#### <사용함수>
> **<engine.c>**

> **<display.c>**
```
void display_cursor_f(CURSOR cursor,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor)
```
> **<io.c>**
```
void gotoxy(POSITION pos) pos 좌표로 이동하는 함수

void printc(POSITION pos, char ch, int color) 원하는 좌표로 이동해서 원하는 색상으로 문자 출력 함수
```
> **<common.h>**
```
두 좌표의 합을 구하는 인라인 함수
inline POSITION position_move_f(POSITION p1, POSITION p2)
```

### 2-2 방향키 더블 클릭: 각 방향키를 짧게 두 번 누르면 여러번 이동
### 2-2 추가 기능: 더블 방향키의 이동 범위가 맵 표시 창을 넘으면 해당 방향으로 갈 수 있는 최대한의 좌표로 이동
#### <사용함수>
> **<engine.c>**
```
방향키 1회 입력에 따라 커서의 이전 위치와 현재 위치를 초기화 
void cursor_move(DIRECTION dir)

방향키 2회 입력에 따라 커서의 이전 위치와 현재 위치를 초기화
추가기능: 커서가 맵 안에 위치 하지 않은면 해당 방향으로 갈수 있는 가능한 최대의 위치로 커서의 현재 위치를 설정 
void cursor_move2_f(DIRECTION dir)
```
> **<display.c>**
```
void display_cursor_f(CURSOR cursor,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	UNIT_ATTRIBUTE Haconen_Harvestor)
```
> **<io.c>**
```
방향키 입력받는 함수
KEY get_key(void)

```
> **<common.h>**
```
방향키인지 확인하는 매크로 함수
#define is_arrow_key_f_mac(k)

화살표 '키'(KEY)를 '방향'(DIRECTION)으로 변환하는 매크로함수 
#define key_to_direction_f_mac(k)

커서의 기존 위치 벡터p를 1회 키 입력 방향 벡터d 와 더하는 매크로 함수 
#define position_by_arrow_move_f_mac(p, d)

방향키 1회 입력을 POSITION 벡터로 변환해서 좌표를 연산할 준비를 도와주는 함수
inline POSITION dtop(DIRECTION d)

위치 벡터p를 2회 키 입력 방향 벡터d 와 더하는 매크로 함수
#define position_by_arrow_move2_f_mac(p, d)

더블 방향키 입력을 POSITION 벡터로 변환해서 좌표를 연산할 준비를 도와주는 함수
inline POSITION dtop_f_inline(DIRECTION Key)
```

### 2-3 선택(스페이스바)
### -오브젝트 위에서 스페이스바를 누르면 선택하고, 상태 & 명령 표시(사막지형도 포함)
### -오브젝트가 선택된상태에서 다른 오브젝트를 선택하면 즉시 대상 전환
#### <사용함수>
> **<engine.c>**
```
```
> **<display.c>**
```
선택에 의한 상태창 출력 제어 함수
void state_window_by_k_space(CURSOR cursor, LAND_ATTRIBUTE Rocks, 
	 LAND_ATTRIBUTE Spice, LAND_ATTRIBUTE Desert, UNIT_ATTRIBUTE Sand_Worm,
	 BUILDING_ATTRIBUTE Atreides_Base,  BUILDING_ATTRIBUTE Atreides_Plate, 
	 UNIT_ATTRIBUTE Atreides_Harvestor, 
	 BUILDING_ATTRIBUTE Haconen_Base, BUILDING_ATTRIBUTE Haconen_Plate,
	 UNIT_ATTRIBUTE Haconen_Harvestor)

선택에 의한 명령어 출력 제어 함수
void command_message_by_k_space(CURSOR cursor, LAND_ATTRIBUTE Rocks,
	LAND_ATTRIBUTE Spice, UNIT_ATTRIBUTE Sand_Worm,
	BUILDING_ATTRIBUTE Atreides_Base, BUILDING_ATTRIBUTE Atreides_Plate,
	UNIT_ATTRIBUTE Atreides_Harvestor,
	BUILDING_ATTRIBUTE Haconen_Base, BUILDING_ATTRIBUTE Haconen_Plate,
	UNIT_ATTRIBUTE Haconen_Harvestor)
```
> **<io.c>**
```
다른 오브젝트 선택 시 기존 상태창에 빈 칸을 출력해서 문자열 삭제하는 함수
void reset_state_window_f(POSITION State_Window_Pos, char blank_character, int color)

좌표로 이동하는 함수
void gotoxy(POSITION pos) pos 

글 배경, 글 색상 변경함수
void set_color(int color)

해당하는 오브젝트의 소개 정보를 출력하는 함수
void print_state_info_f(POSITION State_Window_Pos,
	char introduce_self[(STATE_WINDOW_MAX_WIDTH - 2) * (STATE_WINDOW_MAX_HEIGHT - 2)], int color)

다른 오브젝트 선택 시 기존 명령어 창 빈 칸으로 출력해서 화면에서 삭제하는 함수
void reset_command_window_f(POSITION Command_Window_Pos, char blank_character, int color)

선택에 의한 해당 오브젝트의 명령어 문자열 출력 함수
void print_command_message_info(POSITION Command_Window_Pos,
	char commands_info[(COMMAND_WINDOW_WIDTH - 2) * (COMMAND_WINDOW_HEIGHT - 2)], int color)
```
> **<common.h>**
```
두 좌표의 합을 구하는 인라인 함수
inline POSITION position_move_f(POSITION p1, POSITION p2)
```

### 2-4 ESC키 선택 취소, 상태창 비우기
#### <사용함수>
> **<engine.c>**
```
```
> **<display.c>**
```
ESC키 입력으로 상태창, 명령어 창 비우는 함수
void eraser_state_command_window(void)
```
> **<io.c>**
```
다른 오브젝트 선택 시 기존 상태창에 빈 칸을 출력해서 문자열 삭제하는 함수
void reset_state_window_f(POSITION State_Window_Pos, char blank_character, int color)

좌표로 이동하는 함수
void gotoxy(POSITION pos) pos 

글 배경, 글 색상 변경함수
void set_color(int color)

다른 오브젝트 선택 시 기존 명령어 창 빈 칸으로 출력해서 화면에서 삭제하는 함수
void reset_command_window_f(POSITION Command_Window_Pos, char blank_character, int color)
```
> **<common.h>**
```
두 좌표의 합을 구하는 인라인 함수
inline POSITION position_move_f(POSITION p1, POSITION p2)
```
### 3-1 두 하베스터를 대상으로 가장 가까운 유닛을 찾아서 이동하는 샌드웜 구현(미완)(도전중)
### 거리를 구하는 함수 작성(완료)
#### <사용함수>
> **<engine.c>**
```
거리를 구하는 함수 (완료)
double distance_by_position_f(POSITION p1, POSITION p2)

맨 왼쪽 샌드웜의 위치를 제어하는 함수 [미완]
void sand_worm_move_f(void)

<부분함수 2> [미완]
샌드웜의 새로운 위치를 리턴하는 함수 
POSITION next_position_sand_worm_f(void)
최단 

<부분함수 3> [미완]
샌드웜과 유닛의 최단 거리를 목적지로 변경하는 함수
POSITION next_destination_sand_worm_f(void)
```
> **<display.c>**
```
```
> **<io.c>**
```
```
> **<common.h>**
```
```
---

