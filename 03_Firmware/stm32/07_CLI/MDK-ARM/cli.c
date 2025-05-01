// CLI
// cli.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "cli.h"

// #define D_DEBUG 

typedef struct {
    char *cmd;
    uint8_t no;
    int (*cbf)(int, char**); // argc, char *argv[]);     // cbf : call back function
    char *remark;
} CMD_LIST_T;

// 함수 선언부
void cli_parser(char *str);
static int cli_help(int argc, char *argv[]);     // static : 외부에서 호출 하지 마라
static int cli_led(int argc, char *argv[]);
static int cli_mot(int argc, char *argv[]);

const CMD_LIST_T gCmdListObj[] = {         // const : RO(Read Only) 에만 올림
    {"help", 1, cli_help, "Help"},
    {"led" , 3, cli_led,  "LED [0...2] [on|off]" },
    {"mot" , 5, cli_mot,  "Mot [0...3] [cw|ccw] [0~100] [1..10]"},      // mot : 모터
    {NULL  , 0, NULL,     NULL}
};


#define D_DELIMITER     " ,.\r\n"       // Delimiter : 구분 짓기 위한 기준 문자 지정 

// command line interpreter : parser
// parsing : 문장 분석 or 문법적 관계 해석 
void cli_parser(char *str) {
    int argc = 0; 
    char *argv[10];
    char *ptr;
    
    ptr = strtok(str, D_DELIMITER);
    if (ptr == NULL) {
        return;
    }
    
    while (ptr != NULL) {
        //printf("%s \n", ptr);
        argv[argc] = ptr;
        argc++;
        ptr = strtok(NULL, D_DELIMITER);
    }
    
// for debugging
#if defined(D_DEBUG)        // #if defined(D_DEBUG) ~ #endif : 안에 있는 코드는 실행 안됨 
    printf("argc : %d \n", argc);
    
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] : %s \n", i, argv[i]);
    }
#endif
    
    for (int i = 0; gCmdListObj[i].cmd != NULL; i++) {
        if (strcmp(gCmdListObj[i].cmd, argv[0]) == 0) {
            if (gCmdListObj[i].no <= argc) {
                gCmdListObj[i].cbf(argc, argv);
            }
        }
    }
}

// 사용 방법 설명
static int cli_help(int argc, char *argv[]) {
    for (int i = 0; gCmdListObj[i].cmd != NULL; i++) {
        printf("%s \n", gCmdListObj[i].remark);
    }
    return 0;
}
static int cli_led(int argc, char *argv[]) {
    uint32_t no;
    
    no = (uint32_t)strtol(argv[1], NULL, 10);
    if (strcmp(argv[2], "on") == 0) {
        printf("led %d on \n", no);
        //led_on(no, true);
    } else if (strcmp(argv[2], "off") == 0) {
        printf("led %d off \n", no);
        //led_on(no, false);
    }
    return 0;
}
static int cli_mot(int argc, char *argv[]) {
    
    
    return 0;
}



// ==================================================================================
#if 0
// 전역 변수부
char str_parsing[] = "led 2 off \n";

void cli_main(void)
{
	cli_parser(str_parsing);
    
  /return 0;
}
#endif
