#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "common.h"
#include "io.h"
#include "display.h"
//init 변경하기
	void init(void);
	void intro(void);
	void outro(void);
	void cursor_move(DIRECTION dir);
	void sample_obj_move(void);
	POSITION sample_obj_next_position(void);

	/* ================= control =================== */
	//전체 시간 0초부터 시작
	int sys_clock = 0;		//
	// 두개의 좌표가 저장된 cursor 구조체
	CURSOR cursor = { { 1, 1 }, {1, 1} };

	/* ================= game data =================== */
	//map에 대한 디자인
	char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH] = { 0 };

	RESOURCE Spice_Population = {
		.spice = 0,
		.spice_max = 0,
		.population = 0,
		.population_max = 0
	};

	UNIT_ATTRIBUTE  Atreides_Base = {
		.pos = {1, 2},
		.attachment = 'A'
	};

	UNIT_ATTRIBUTE  Haconen_Base = {
	.attachment = 'H'
	};

	UNIT_ATTRIBUTE obj = {
		.pos = {1, 1}, //유닛의 첫 시작 좌표
		.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2}, //최우측 하단
		.representation = 'o',
		.speed = 300,
		.next_move_time = 300 //다음에 움직일 시간
	};

	UNIT_ATTRIBUTE Atreides_Harvestor = {
		.pos = {MAP_HEIGHT - 4, 1}, //유닛의 첫 시작 좌표
		.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2}, //최우측 하단
		.attachment = 'A',
		.representation = 'H',
		.speed = 300,
		.next_move_time = 300 //다음에 움직일 시간
	};

	UNIT_ATTRIBUTE Haconen_Harvestor = {
		.pos = {3, MAP_WIDTH-2}, //유닛의 첫 시작 좌표
		.dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2}, //최우측 하단
		.attachment = 'H',
		.representation = 'H',
		.speed = 300,
		.next_move_time = 300 //다음에 움직일 시간
	};

	UNIT_ATTRIBUTE Sand_Worm[2] = {
		{.pos = {4, 4}}, {.pos = {12, MAP_WIDTH - 10}}
	};

	/* ================= main() =================== */
	int main(void) {
		//무엇에 랜덤을 사용하는지 알아야 한다.
		//srand((unsigned int)time(NULL));
		//(1) 시작 intro함수
		intro();
		//(2) 0번 평면 환경 디자인 배열저장, 1번 평면 유닛 디자인 배열 저장 함수 
		init();
		//(3) 1. 자원에 대해서 출력 2. 맵 정보에 대해서 출력 3. 이전 위치/ 현재 위치 출력

		display_resource(Spice_Population);
		display_map(map, Atreides_Harvestor, Haconen_Harvestor);
		display_cursor(cursor, Atreides_Harvestor, Haconen_Harvestor);
		while (1) {
			// (4) loop 돌 때마다 0부터 시작해서 0.01초 마다 키 입력 확인 
			
			// 열거체 변수를 하나의 값으로서 사용
			// 입력한 키가 항상저장된다.
			KEY key = get_key();

			// //매크로 함수로 방향키인지 확인
			// 방향키 입력으로 커서가 움직인다. 
			if (is_arrow_key_f_mac(key)) {
				//방향키에 대한 정수값 새로운 열거체로 정의 되어 들어간다.
				cursor_move(key_to_direction_f_mac(key));
			}
			else {
				// 방향키 외의 입력
				switch (key) {
				case k_quit:  set_color(INTRO_OUTTRO_CONTENT); system("cls"); outro(); // 5번 입력시
				case k_none: //0번 입력시
				case k_undef: //6번 입력시
				default: break;
				}
			}

			// 샘플 오브젝트 동작
			sample_obj_move();

			// 화면 출력
			display_resource(Spice_Population);
			display_map(map, Atreides_Harvestor, Haconen_Harvestor);
			display_cursor(cursor, Atreides_Harvestor, Haconen_Harvestor);
			// 시간의 단위
			Sleep(TICK);
			sys_clock += 1000;
		}
	}

	/* ================= subfunctions =================== */
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

	void init(void) {
		// layer 0(map[0])에 지형 생성
		for (int j = 0; j < MAP_WIDTH; j++) {
			map[0][0][j] = '#'; //상단과 하단 밑줄 표시
			map[0][MAP_HEIGHT - 1][j] = '#';
		}

		for (int i = 1; i < MAP_HEIGHT - 1; i++) {
			map[0][i][0] = '#';
			map[0][i][MAP_WIDTH - 1] = '#';
			for (int j = 1; j < MAP_WIDTH - 1; j++) {
				//아트레이디스 본진
				if (MAP_HEIGHT - 3 <= i && i <= MAP_HEIGHT - 2 && j >= 1 && j <= 2) {
					map[0][i][j] = 'B';
				}
				//하코넨 본진
				else if (1 <= i && i <= 2 && MAP_WIDTH - 3 <= j && j <= MAP_WIDTH - 2) {
					map[0][i][j] = 'B';
				}
				//아트레이디스 기본장판
				else if(MAP_HEIGHT - 3 <= i && i <= MAP_HEIGHT - 2 && 3 <= j && j <= 4) {
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
				//바위 지형
				else if (i == 10 && j == 7 ||
						4 <= i && i <= 5 && 14 <= j && j <= 15 ||
						10 <= i && i <= 11 && 27 <= j && j <= 28 ||
						i == 7 && j == 50 ||
						i == 14 && j == 42
						)
				{
					map[0][i][j] = 'R';
				}
				else {
					map[0][i][j] = ' ';
				}
				
			}
		}
		// layer 1(map[1])은 비워 두기(-1로 채움)
		for (int i = 0; i < MAP_HEIGHT; i++) {
			for (int j = 0; j < MAP_WIDTH; j++) {
				map[1][i][j] = -1;
			}
		}
		
		//유닛 레이어의 유닛의 가로 위치와 세로 위치에 유닛 초기화
		//초기 위치에 저장
		map[1][obj.pos.row][obj.pos.column] = 'o';
		map[1][Atreides_Harvestor.pos.row][Atreides_Harvestor.pos.column] = 'H';
		map[1][Haconen_Harvestor.pos.row][Haconen_Harvestor.pos.column] = 'H';
		map[1][Sand_Worm[0].pos.row][Sand_Worm[0].pos.column] = 'W';
		map[1][Sand_Worm[1].pos.row][Sand_Worm[1].pos.column] = 'W';
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
			//cursor 이전 위치와 현재 위치를 초기화 해서 display_cursor에 활용
			cursor.previous = cursor.current;
			cursor.current = new_pos;
		}
	}

	/* ================= sample object movement =================== */
	POSITION sample_obj_next_position(void) {
		// 현재 위치와 목적지를 비교해서 이동 방향 결정	
		//obj 전역변수
		POSITION diff = position_subtraction_f_inline(obj.dest, obj.pos);
		DIRECTION dir;

		// 지금은 단순히 원래 자리로 왕복
		// 가로축과 세로축에서 모두 차이가 없을 때
		// 목적지 도착시 차이가 없어진다.
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
			return obj.pos;
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

		//위의 방향키 변화에 대해
		// validation check
		// next_pos가 맵을 벗어나지 않고, (지금은 없지만)장애물에 부딪히지 않으면 
		// 다음 위치로 이동
		// 지금은 충돌 시 아무것도 안 하는데, 
		// 나중에는 장애물을 피해가거나 적과 전투를 하거나... 등등
		POSITION next_pos = position_by_arrow_move_f_mac(obj.pos, dir);
		if (1 <= next_pos.row && next_pos.row <= MAP_HEIGHT - 2 && \
			1 <= next_pos.column && next_pos.column <= MAP_WIDTH - 2 && \
			map[1][next_pos.row][next_pos.column] < 0) {
			return next_pos;
		}
		else {
			return obj.pos;  // 제자리
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
		//음수를 저장하는 이유는 프론트 버퍼에 이전 표시는 전달하지 않기 위해서
		map[1][obj.pos.row][obj.pos.column] = -1;
		// 오브젝트 포지션에 대한 변화를 초기화
		obj.pos = sample_obj_next_position();
		map[1][obj.pos.row][obj.pos.column] = obj.representation;
		
		obj.next_move_time = sys_clock + obj.speed;
	}