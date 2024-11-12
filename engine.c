#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "common.h"
#include "io.h"
#include "display.h"

/* ================= 전체 시간 전역변수 선언 =================== */
int sys_clock = 0;
/* ================= 화면 표시 전역 배열 선언 =================== */
//map
char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH] = { 0 };
//상태창
char state_window_arr[STATE_WINDOW_MAX_HEIGHT][STATE_WINDOW_MAX_WIDTH] = { 0 };
//시스템 메세지
char system_message_arr[SYSTEM_MESSAGE_W_HEIGHT][SYSTEM_MESSAGE_W_WIDTH] = { 0 };
//명령창
char command_window_arr[COMMAND_WINDOW_HEIGHT][COMMAND_WINDOW_WIDTH] = { 0 };
/* ================= 커서 위치 전역구조체 선언 =================== */
CURSOR cursor = { { 1, 1 }, {1, 1} };
/* ================= 자원 전역 구조체 선언 =================== */
RESOURCE Spice_Population = {
	.spice = 0,
	.spice_max = 0,
	.population = 0,
	.population_max = 0
};
/* ================= 지형 전역 구조체 선언 =================== */
LAND_ATTRIBUTE Rocks = {
.Land_Position = {{10, 7}, {4, 14}, {4, 15}, {5, 14}, {5, 15}, {10, 27},
				  {10, 28}, {11, 27}, {11, 28}, {7, 50}, {14, 42}},
.introduce_self = "+지형: 바위\n\
+설명: 샌드웜은 통과할수 없음\n",
.commands_info = "명령어: 없음\n"
};
LAND_ATTRIBUTE Spice = {
.Land_Position = { {MAP_HEIGHT - 6, 1}, {5, MAP_WIDTH - 2} },
.introduce_self = "스파이스 매장지(1~9)",
.commands_info = "명령어: 없음"
};
LAND_ATTRIBUTE Desert = {
.introduce_self = "사막: 건물을 지을 수 없음",
.commands_info = "명령어: 없음"
};
/* ================= 건물 전역 구조체 선언 =================== */
//아트레이디스 본진
BUILDING_ATTRIBUTE Atreides_Base = {
.pos = {{MAP_HEIGHT - 2, 1},{MAP_HEIGHT - 3, 1}, {MAP_HEIGHT - 2, 2}, {MAP_HEIGHT - 3, 2}},
.introduce_self = "+건물: 아트레이디스 본진(Base)\n\
+건설비용:없음\n\
+내구도: 50",
.commands_info = "H: 아트레이디스 하베스터 생산\n"
};
//아트레이디스 장판
BUILDING_ATTRIBUTE Atreides_Plate = {
.pos = {{MAP_HEIGHT - 2, 3},{MAP_HEIGHT - 3, 3}, {MAP_HEIGHT - 2, 4}, {MAP_HEIGHT - 3, 4}},
.introduce_self = "+건물: 아트레이디스 장판(P:Plate)\n\
+설명: 장판 위에 건물 건설가능\n\
+건설비용: 1\n\
+내구도: 없음\n\
",
.commands_info = "명령어: 없음\n"
};
BUILDING_ATTRIBUTE Atreides_Dormitory = {
.introduce_self = "+건물: 아트레이디스 숙소(D: Dormitory)\n\
+설명: 인구 최대치 증가(10)\n\
+건설비용: 2\n\
+내구도: 10",
.commands_info = "명령어: 없음\n"
};
BUILDING_ATTRIBUTE Atreides_Garage = {
.introduce_self = "+건물: 아트레이디스 창고(D: Dormitory)\n\
+설명: 스페이스 보관 최대치 증가(10)\n\
+건설비용: 4\n\
+내구도: 10",
.commands_info = "명령어: 없음\n"
};
//아트레이디스 병영
BUILDING_ATTRIBUTE Atreides_Barracks = {
.introduce_self = "+건물: 아트레이디스 병영(D: Dormitory)\n\
+설명: 보병생산\n\
+건설비용: 4\n\
+내구도: 20",
.commands_info = "명령어: 보병생산(S:Soldier)\n"
};
//아트레이디스 은신처
BUILDING_ATTRIBUTE Atreides_Shelter = {
.introduce_self = "+건물: 아트레이디스 은신처(S: Shelter)\n\
+설명: 특수유닛 생산\n\
+건설비용: 5\n\
+내구도: 30",
.commands_info = "명령어: 프레멘 생산(F: Fremen)\n"
};
//하코넨 본진
BUILDING_ATTRIBUTE Haconen_Base = {
.pos = {{1, MAP_WIDTH - 2}, {1, MAP_WIDTH - 3}, {2, MAP_WIDTH - 2} , {2, MAP_WIDTH - 3}},
.introduce_self = "건물: 하코넨 본진(Base)\n\
+건설비용:없음\n\
내구도: 50",
.commands_info = "H: 하코넨 하베스터 생산\n"
};
//하코넨 장판
BUILDING_ATTRIBUTE Haconen_Plate = {
.pos = {{1, MAP_WIDTH - 5}, {1, MAP_WIDTH - 4}, {2, MAP_WIDTH - 5} , {2, MAP_WIDTH - 4}},
.introduce_self = "+건물: 하코넨 장판(P:Plate)\n\
+설명: 장판 위에 건물 건설 가능\n\
+건설비용: 1\n\
+내구도: 없음\n\
",
.commands_info = "명령어: 없음"
};
BUILDING_ATTRIBUTE Haconen_Dormitory = {
.introduce_self = "+건물: 하코넨 숙소(D: Dormitory)\n\
+설명: 인구 최대치 증가(10)\n\
+건설비용: 2\n\
+내구도: 10",
.commands_info = "명령어: 없음\n"
};
BUILDING_ATTRIBUTE Haconen_Garage = {
.introduce_self = "+건물: 하코넨 창고(D: Dormitory)\n\
+설명: 스페이스 보관 최대치 증가(10)\n\
+건설비용: 4\n\
+내구도: 10",
.commands_info = "명령어: 없음\n"
};
BUILDING_ATTRIBUTE Haconen_Arena = {
.introduce_self = "+건물: 하코넨 투기장(A: Arena)\n\
+설명: 투사 생산\n\
+건설비용: 3\n\
+내구도: 15",
.commands_info = "명령어: 투사생산(F: Fighter)\n"
};
BUILDING_ATTRIBUTE Haconen_Factory = {
.introduce_self = "+건물: 하코넨 공장(F: Factory)\n\
+설명: 특수유닛 생산\n\
+건설비용: 5\n\
+내구도: 30",
.commands_info = "명령어: 중전차 생산(T: Heavy Tank)\n"
};
/* ================= 유닛 전역 구조체 선언 =================== */
// 아트레이디스 하베스터
UNIT_ATTRIBUTE Atreides_Harvestor = {
.pos = {MAP_HEIGHT - 4, 1}, //유닛의 첫 시작 좌표
.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2}, //최우측 하단
.representation = 'H',
.speed = 300,
.next_move_time = 300, //다음에 움직일 시간
.introduce_self = "+유닛: 아트레이디스 하베스터\n\
+생산비용: 5\n\
+인구수: 5\n\
+이동주기: 2000\n\
+공격력: 없음\n\
+공격주기: 없음\n\
+체력: 70\n\
+시야: 0",
.commands_info = "<명령어>\n\
+ H: Harvest\n\
+ M: Move\n"
};
//아트레이디스 프레멘
UNIT_ATTRIBUTE Atreides_Fremen = {
.introduce_self = "+유닛: 아트레이디스 프레멘\n\
+생산비용: 5\n\
+인구수: 2\n\
+이동주기: 400\n\
+공격력: 15\n\
+공격주기: 200\n\
+체력: 25\n\
+시야: 8",
.commands_info = "<명령어>\n\
+ M: 이동(Move)\n\
+ P: 순찰(Patrol)\n"
};
//아트레이디스 보병
UNIT_ATTRIBUTE Atreides_Solider = {
.introduce_self = "+유닛: 아트레이디스 보병\n\
+생산비용: 1\n\
+인구수: 1\n\
+이동주기: 1000\n\
+공격력: 5\n\
+공격주기: 800\n\
+체력: 15\n\
+시야: 1",
.commands_info = "<명령어>\n\
+ M: 이동(Move)\n\
+ P: 순찰(Patrol)\n"
};
// 하코넨 하베스터
UNIT_ATTRIBUTE Haconen_Harvestor = {
.pos = {3, MAP_WIDTH - 2}, //유닛의 첫 시작 좌표
.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2}, //최우측 하단
.representation = 'H',
.speed = 300,
.next_move_time = 300, //다음에 움직일 시간
.introduce_self = "+유닛: 하코넨 하베스터\n\
+생산비용: 5\n\
+인구수: 5\n\
+이동주기: 2000\n\
+공격력: 없음\n\
+공격주기: 없음\n\
+체력: 70\n\
+시야: 0",
.commands_info = "<명령어>\n\
+ H: Harvest\n\
+ M: Move\n"
};
//하코넨 투사
UNIT_ATTRIBUTE Haconen_Fighter = {
.introduce_self = "+유닛: 하코넨 투사\n\
+생산비용: 1\n\
+인구수: 1\n\
+이동주기: 1200\n\
+공격력: 6\n\
+공격주기: 600\n\
+체력: 10\n\
+시야: 1",
.commands_info = "<명령어>\n\
+ M: 이동(Move)\n\
+ P: 순찰(Patrol)\n"
};
//하코넨 투사
UNIT_ATTRIBUTE Haconen_Heavy_Tank = {
.introduce_self = "+유닛: 하코넨 투사\n\
+생산비용: 12\n\
+인구수: 5\n\
+이동주기: 3000\n\
+공격력: 40\n\
+공격주기: 4000\n\
+체력: 60\n\
+시야: 4",
.commands_info = "<명령어>\n\
+ M: 이동(Move)\n\
+ P: 순찰(Patrol)\n"
};
// 중립 샌드웜
UNIT_ATTRIBUTE Sand_Worm = {
.pos = {{4, 4}, {12, MAP_WIDTH - 10}},
.dest = {4, 4},
.representation = 'W',
.speed = 500,
.next_move_time = 500,
.introduce_self = "+유닛: 샌드웜(중립)\n\
+생산비용: 없음\n\
+인구수: 없음\n\
+이동주기: 2500\n\
+공격력: 무한대\n\
+공격주기: 10000\n\
+체력: 무한대\n\
+시야: 무한대",
.commands_info = "<명령어> : 없음"
};
// 중립 스켈레톤 유닛 나중에 layer2로 사용 고려
UNIT_ATTRIBUTE obj = {
	.pos = {{1, 1}}, //유닛의 첫 시작 좌표
	.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2}, //최우측 하단
	.representation = 'o',
	.speed = 300,
	.next_move_time = 300 //다음에 움직일 시간
};

/* ================= 화면 초기화 함수 선언 =================== */
void init_map_land_building_unit(void);
void init_state_window_f(void);
void init_system_message_f(void);
void init_command_message_f(void);
/* ================= 시작, 종료 화면 표시 함수 선언 =================== */
void intro(void);
void outro(void);
/* ================= 커서 이동 제어 함수 선언=================== */
void cursor_move(DIRECTION dir);
void cursor_move2_f(DIRECTION dir);
/* ================= 유닛 이동 제어 함수 선언=================== */
POSITION sample_obj_next_position(void);
void sample_obj_move(void);

double distance_by_position_f(POSITION p1, POSITION p2);
POSITION next_position_sand_worm_f(void);
void sand_worm_move(void);

/* ================= 1)인트로 함수=================== */
void intro(void) {
	set_color(INTRO_OUTTRO_TITLE);
	printf("++++++++++++++++<    DUNE 1.5     >++++++++++++++++++\n");
	set_color(INTRO_OUTTRO_CONTENT);
	printf("=====================================================\n");
	printf("[\"I must not fear. Fear is the mind killer. Fear is ]\n");
	printf("[the little-death that brings total obliteration    ]\n");
	printf("[                                                   ]\n");
	printf("[I will face my fear and I will permit it to pass   ]\n");
	printf("[over me and through me. And when it has gone past  ]\n");
	printf("[I will turn the inner eye to see its path          ]\n");
	printf("[                                                   ]\n");
	printf("[Where the fear has gone there will be nothing      ]\n");
	printf("[Only I will remain.\"                               ]\n");
	printf("[                                                   ]\n");
	printf("[ -Paul Atreides-                                   ]\n");
	printf("=====================================================\n");
	Sleep(500);
	system("cls");
}
/* ================= 1) outro 함수=================== */
void outro(void) {
	set_color(INTRO_OUTTRO_TITLE);
	printf("+++++++++++++++++++++<     Good Game      >++++++++++++++++++++++++\n");
	set_color(INTRO_OUTTRO_CONTENT);
	printf("===================================================================\n");
	printf("[Only the person who think \"I can make it\" can write the codes.   ]\n");
	printf("[Thank you for enjoying the game                                  ]\n");
	printf("===================================================================\n");
	exit(0);
}
/* ================= 1)유닛, 빌딩, 지형 초기화 함수=================== */
void init_map_land_building_unit() {
	// layer 0(map[0])에 지형 생성
	for (int i = 0; i < MAP_WIDTH; i++) {
		map[0][0][i] = '#'; //상단과 하단 밑줄 표시
		map[0][MAP_HEIGHT - 1][i] = '#';
	}

	for (int k = 0; k < 11; k++) {
		int i = Rocks.Land_Position[k].row;
		int j = Rocks.Land_Position[k].column;
		map[0][i][j] = 'R';
	}

	for (int i = 1; i < MAP_HEIGHT - 1; i++) {
		map[0][i][0] = '#';
		map[0][i][MAP_WIDTH - 1] = '#';
		for (int j = 1; j < MAP_WIDTH - 1; j++) {
			//아트레이디스 본진 건물
			if (MAP_HEIGHT - 3 <= i && i <= MAP_HEIGHT - 2 && j >= 1 && j <= 2) {
				map[0][i][j] = 'B';
			}
			//하코넨 본진
			else if (1 <= i && i <= 2 && MAP_WIDTH - 3 <= j && j <= MAP_WIDTH - 2) {
				map[0][i][j] = 'B';
			}
			/*	else if ( i == 10 && j == 7 ||
					  4 <= i && i<= 5 && 14 <= j && j <= 15 ||
					  10 <= i && i <= 11 && 27 <= j && j <= 28||
					  i == 7 && j == 50 ||
					  i == 14 && j == 42)
			{
				map[0][i][j] = 'R';
			}*/
			//아트레이디스 기본장판
			else if (MAP_HEIGHT - 3 <= i && i <= MAP_HEIGHT - 2 && 3 <= j && j <= 4) {
				map[0][i][j] = 'P';
			}
			//하코넨 기본 장판
			else if (1 <= i && i <= 2 && MAP_WIDTH - 5 <= j && j <= MAP_WIDTH - 4) {
				map[0][i][j] = 'P';
			}
			//아트레이디스 초기 스파이스
			else if (i == (MAP_HEIGHT - 6) && j == 1) {
				map[0][i][j] = '5';
			}
			//하코넨 초기 스파이스
			else if (i == 5 && j == MAP_WIDTH - 2) {
				map[0][i][j] = '5';
			}
			else if (map[0][i][j] == '\0') {
				map[0][i][j] = ' ';
			}

		}
	}
	// layer 1의 기본값을 -
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			map[1][i][j] = -1;
		}
	}

	//유닛 레이어의 유닛의 가로 위치와 세로 위치에 유닛 초기화
	//초기 위치에 저장
	map[1][obj.pos[0].row][obj.pos[0].column] = 'o';
	map[1][Atreides_Harvestor.pos[0].row][Atreides_Harvestor.pos[0].column] = 'H';
	map[1][Haconen_Harvestor.pos[0].row][Haconen_Harvestor.pos[0].column] = 'H';
	map[1][Sand_Worm.pos[0].row][Sand_Worm.pos[0].column] = 'W';
	map[1][Sand_Worm.pos[1].row][Sand_Worm.pos[1].column] = 'W';
}
//상태 정보 창 초기화
void init_state_window_f(void) {
	for (int i = 0; i < STATE_WINDOW_MAX_WIDTH; i++) {
		state_window_arr[0][i] = '#'; //상단과 하단 밑줄 표시
		state_window_arr[STATE_WINDOW_MAX_HEIGHT - 1][i] = '#';
	}
	for (int i = 1; i < STATE_WINDOW_MAX_HEIGHT - 1; i++) {
		state_window_arr[i][0] = '#';
		state_window_arr[i][STATE_WINDOW_MAX_WIDTH - 1] = '#';
		for (int j = 1; j < STATE_WINDOW_MAX_WIDTH - 1; j++) {
			state_window_arr[i][j] = ' ';
		}
	}
}
// 시스템 메세지 창 초기화
void init_system_message_f(void) {
	for (int i = 0; i < SYSTEM_MESSAGE_W_WIDTH; i++) {
		system_message_arr[0][i] = '#'; //상단과 하단 밑줄 표시
		system_message_arr[SYSTEM_MESSAGE_W_HEIGHT - 1][i] = '#';
	}
	for (int i = 1; i < SYSTEM_MESSAGE_W_HEIGHT - 1; i++) {
		system_message_arr[i][0] = '#';
		system_message_arr[i][SYSTEM_MESSAGE_W_WIDTH - 1] = '#';
		for (int j = 1; j < SYSTEM_MESSAGE_W_WIDTH - 1; j++) {
			system_message_arr[i][j] = ' ';
		}
	}
}
// 명령어 메세지 창 초기화
void init_command_message_f(void) {
	for (int i = 0; i < COMMAND_WINDOW_WIDTH; i++) {
		command_window_arr[0][i] = '#';
		command_window_arr[COMMAND_WINDOW_HEIGHT - 1][i] = '#';
	}
	for (int i = 1; i < COMMAND_WINDOW_HEIGHT - 1; i++) {
		command_window_arr[i][0] = '#';
		command_window_arr[i][COMMAND_WINDOW_WIDTH - 1] = '#';
		for (int j = 1; j < COMMAND_WINDOW_WIDTH - 1; j++) {
			command_window_arr[i][j] = ' ';
		}
	}
}
//===================================커서 이동 함수================================//
// 1. 새로운 위치가 영역으로 표시된 내부 영역 인지 확인
// 2. 지정한 방향으로 커서 이동
void cursor_move(DIRECTION dir) {
	//현재 커서의 위치
	POSITION curr = cursor.current;
	// 현재 커서의 위치와 방향키 벡터를 더해서 새로운 커서의 위치를 저장한다.
	POSITION new_pos = position_by_arrow_move_f_mac(curr, dir);
	// 커서가 #테두리 안에 위치하는 지 확인

	if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && \
		1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {
		//cursor 이전 위치와 현재 위치를 초기화 해서 display_cursor_f에 활용
		cursor.previous = cursor.current;
		cursor.current = new_pos;
	}
}

void cursor_move2_f(DIRECTION dir) {
	POSITION curr = cursor.current;
	// 현재 커서의 위치와 방향키 벡터를 더해서 새로운 커서의 위치를 저장한다.
	POSITION new_pos = position_by_arrow_move2_f_mac(curr, dir);
	// 커서가 #테두리 안에 위치하는 지 확인
	if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && \
		1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {
		//cursor 이전 위치와 현재 위치를 초기화 해서 display_cursor_f에 활용
		cursor.previous = cursor.current;
		cursor.current = new_pos;
	}
	else {
		if (dir == 1) {
			new_pos.row = 1;
			cursor.previous = cursor.current;
			cursor.current = new_pos;
		}
		else if (dir == 2) {
			new_pos.column = 1;
			cursor.previous = cursor.current;
			cursor.current = new_pos;
		}
		else if (dir == 3) {
			new_pos.column = MAP_WIDTH - 2;
			cursor.previous = cursor.current;
			cursor.current = new_pos;
		}
		else if (dir == 4) {
			new_pos.row = MAP_HEIGHT - 2;
			cursor.previous = cursor.current;
			cursor.current = new_pos;
		}
	}
}
/* ================= sample object movement =================== */
POSITION sample_obj_next_position(void) {
	// 현재 위치와 목적지를 비교해서 이동 방향 결정	
	//obj 전역변수
	POSITION diff = position_subtraction_f_inline(obj.dest, obj.pos[0]);
	DIRECTION dir;

	// 목적지에 도달한 경우
	if (diff.row == 0 && diff.column == 0) {
		if (obj.dest.row == 1 && obj.dest.column == 1) {
			// topleft --> bottomright로 목적지 설정
			POSITION new_dest = { MAP_HEIGHT - 2, MAP_WIDTH - 2 };
			obj.dest = new_dest;
		}
		else {
			// bottomright --> topleft로 목적지 설정
			POSITION new_dest = { 1, 1 };
			obj.dest = new_dest;
		}
		return obj.pos[0]; //잠시 대기
	}

	// 가로축, 세로축 거리를 비교해서 더 먼 쪽 축으로 이동
	//가로축 이동
	if (abs(diff.row) >= abs(diff.column)) {
		dir = (diff.row >= 0) ? d_down : d_up;
	}
	//세로축 이동
	else {
		dir = (diff.column >= 0) ? d_right : d_left;
	}
	
	POSITION next_pos = position_by_arrow_move_f_mac(obj.pos[0], dir);
	if (1 <= next_pos.row && next_pos.row <= MAP_HEIGHT - 2 && \
		1 <= next_pos.column && next_pos.column <= MAP_WIDTH - 2 && \
		map[1][next_pos.row][next_pos.column] < 0) {
		return next_pos; // position_by_arrow_move_f_mac()으로 계산한 위치로 이동
	}
	else {
		return obj.pos[0];  // 제자리
	}
}

void sample_obj_move(void) {
	//0.3초간 아무것도 리턴 x
	if (sys_clock <= obj.next_move_time) {
		// 아직 시간이 안되면 아무것도 리턴하지 않음 while루프의 다음 구문으로
		return;
	}
	//시간이 된 순간

	// 오브젝트(건물, 유닛 등)은 layer1(map[1])에 저장
	// 움직이기 전에 원래 있던 위치를 -1로 표시
	map[1][obj.pos[0].row][obj.pos[0].column] = -1;
	// 오브젝트 포지션에 대한 변화를 초기화
	obj.pos[0] = sample_obj_next_position();
	map[1][obj.pos[0].row][obj.pos[0].column] = obj.representation;

	obj.next_move_time = sys_clock + obj.speed;
}
///* ================= 3-1) 거리를 구하는 함수 =================== */
double distance_by_position_f(POSITION p1, POSITION p2) {
	POSITION subtraction = position_subtraction_f_inline(p1, p2);
	double distance = sqrt(pow(subtraction.row, 2) + pow(subtraction.column, 2));
	return distance;
}

//* ================= 3-1) 샌드웜과의 최단 거리를 샌드웜의 목적지로 구현하는 함수 =================== */
POSITION next_position_sand_worm_f(void) {
	//거리들을 배열에 저장
	double distances_of_sand_worm_arr[COMPARING_WITH_SAND_WORM] = { 0 };
	for (int i = 0; i < COMPARING_WITH_SAND_WORM; i++) {
		if (i == 0) {
			distances_of_sand_worm_arr[i] = distance_by_position_f(Sand_Worm.pos[0], Atreides_Harvestor.pos[0]);
		}
		else if (i == 1) {
			distances_of_sand_worm_arr[i] = distance_by_position_f(Sand_Worm.pos[0], Haconen_Harvestor.pos[0]);
		}
	}
	//가장 짧은 거리의 유닛의 위치를 목저지로 저장
	double shortest_of_sand_worm = distances_of_sand_worm_arr[0];
	Sand_Worm.dest = Atreides_Harvestor.pos[0];
	for (int i = 1; i < COMPARING_WITH_SAND_WORM; i++) {
		if (i == 1 && (shortest_of_sand_worm > distances_of_sand_worm_arr[i]) ) {
			Sand_Worm.dest = Haconen_Harvestor.pos[0];
		}
	}
	POSITION diff = position_subtraction_f_inline(Sand_Worm.dest, Sand_Worm.pos[0]);
	DIRECTION dir;

	
	if (diff.row == 0 && diff.column == 0) {
		return Sand_Worm.pos[0];
	}
	// 가로축, 세로축 거리를 비교해서 더 먼 쪽 축으로 이동
	//가로축 이동
	if (abs(diff.row) >= abs(diff.column)) {
		dir = (diff.row >= 0) ? d_down : d_up; // d_down이 4 d_up가 1
	}
	//세로축 이동
	else {
		dir = (diff.column >= 0) ? d_right : d_left; // d_right 3 d_left 2
	}
	//절대값 비교를 통해 정한 방향을 새로운 위치를 계산하기 위해 활용
	POSITION Next_Sand_Worm_Pos = position_by_arrow_move_f_mac(Sand_Worm.pos[0], dir);

	if (1 <= Next_Sand_Worm_Pos.row && Next_Sand_Worm_Pos.row <= MAP_HEIGHT - 2 && \
		1 <= Next_Sand_Worm_Pos.column && Next_Sand_Worm_Pos.column <= MAP_WIDTH - 2 && \
		map[1][Next_Sand_Worm_Pos.row][Next_Sand_Worm_Pos.column] < 0 &&
		map[0][Next_Sand_Worm_Pos.row][Next_Sand_Worm_Pos.column] != 'R') {
		return Next_Sand_Worm_Pos;
	}
	else if (1 <= Next_Sand_Worm_Pos.row && Next_Sand_Worm_Pos.row <= MAP_HEIGHT - 2 && \
			 1 <= Next_Sand_Worm_Pos.column && Next_Sand_Worm_Pos.column <= MAP_WIDTH - 2 && \
			 map[1][Next_Sand_Worm_Pos.row][Next_Sand_Worm_Pos.column] < 0 && map[0][Next_Sand_Worm_Pos.row][Next_Sand_Worm_Pos.column] == 'R') {
		//위 방향키 인 경우
		if (dir == 1 || dir == 4) {
			dir = (diff.column >= 0) ? d_right : d_left;
			Next_Sand_Worm_Pos = position_by_arrow_move_f_mac(Sand_Worm.pos[0], dir);
			return Next_Sand_Worm_Pos;
		}
		else if (dir == 2 || dir == 3) {
			dir = (diff.row >= 0) ? d_down : d_up;
			Next_Sand_Worm_Pos = position_by_arrow_move_f_mac(Sand_Worm.pos[0], dir);
			return Next_Sand_Worm_Pos;
		}
	}
	//하베스터를 마났을 때 잡아먹음
	else if (1 <= Next_Sand_Worm_Pos.row && Next_Sand_Worm_Pos.row <= MAP_HEIGHT - 2 && \
			1 <= Next_Sand_Worm_Pos.column && Next_Sand_Worm_Pos.column <= MAP_WIDTH - 2 && \
			map[1][Next_Sand_Worm_Pos.row][Next_Sand_Worm_Pos.column] == 'H') 
	{
		map[1][Next_Sand_Worm_Pos.row][Next_Sand_Worm_Pos.column] == 'W';
		return Next_Sand_Worm_Pos;
	}
}
///* ================= 3-1) Sand_Worm의 움직임 구현 =================== */
void sand_worm_move(void) {
	//map에 대한 sand_worm의 정의 다시 보기
	if (sys_clock <= Sand_Worm.next_move_time) {
		// 아직 시간이 안되면 아무것도 리턴하지 않음 while루프의 다음 구문으로
		return;
	}
	// 오브젝트(건물, 유닛 등)은 layer1(map[1])에 저장
	// 기존 위치를 -1로 표시
	map[1][Sand_Worm.pos[0].row][Sand_Worm.pos[0].column] = -1;

	// 오브젝트 포지션에 대한 변화를 초기화
	Sand_Worm.pos[0] = next_position_sand_worm_f();
	map[1][Sand_Worm.pos[0].row][Sand_Worm.pos[0].column] = Sand_Worm.representation;
	Sand_Worm.next_move_time = sys_clock + Sand_Worm.speed;
}

/* ================= main() =================== */
int main(void) {
	//srand((unsigned int)time(NULL)); 3)에서 사용
	//1) intro함수
	intro();
	//1) 유닛, 지형 초기화 함수
	init_map_land_building_unit();
	init_state_window_f();
	init_system_message_f();
	init_command_message_f();

	display_resource(Spice_Population);
	display_map_f(map, Atreides_Harvestor, Haconen_Harvestor, Rocks, Sand_Worm);
	display_state_window_f(state_window_arr);
	display_system_message_w_f(system_message_arr);
	display_command_message_w_f(command_window_arr);
	display_cursor_f(cursor, Atreides_Harvestor, Haconen_Harvestor);
	while (1) {
		KEY key1 = get_key();
		if (is_arrow_key_f_mac(key1)) {
			Sleep(WAITING_SECOND_ARROW);
			KEY key2 = get_key();
			if (is_arrow_key_f_mac(key2)) {
				cursor_move2_f(key_to_direction_f_mac(key2));
			}
			else {
				cursor_move(key_to_direction_f_mac(key1));
			}			
		}
		else {
			switch (key1) {
			case k_esc: eraser_state_command_window(); break;
			case k_space:
				state_window_by_k_space(cursor, Rocks, 
					  Spice, Desert, Sand_Worm,
					  Atreides_Base, Atreides_Plate, Atreides_Harvestor,
					  Haconen_Base, Haconen_Plate, Haconen_Harvestor);
				command_message_by_k_space(cursor, Rocks, Spice, Sand_Worm,
					  Atreides_Base, Atreides_Plate, Atreides_Harvestor,
					  Haconen_Base, Haconen_Plate, Haconen_Harvestor);
				break;
				//1) outro 함수
			case k_quit:  set_color(INTRO_OUTTRO_CONTENT); system("cls"); outro();
			case k_none:
			case k_undef:
			default: break;
			}
		}
		// 샘플 오브젝트 동작
		sample_obj_move();
		sand_worm_move();
		

		display_resource(Spice_Population);
		display_map_f(map, Atreides_Harvestor, Haconen_Harvestor, Rocks, Sand_Worm);
		display_state_window_f(state_window_arr);
		display_system_message_w_f(system_message_arr);
		display_command_message_w_f(command_window_arr);
		display_cursor_f(cursor, Atreides_Harvestor, Haconen_Harvestor);
		// 시간의 단위
		Sleep(TICK);
		sys_clock += 10;
	}
	return 0;
}