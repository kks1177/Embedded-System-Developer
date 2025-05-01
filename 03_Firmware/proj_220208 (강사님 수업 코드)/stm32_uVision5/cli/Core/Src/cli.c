#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "cli.h"

//#define D_DEBUG 

typedef struct {
    char *cmd;
    uint8_t no;
    int (*cbf)(int, char **); // argc, char *argv[]);
    char *remark;
} CMD_LIST_T;

static int cli_help(int argc, char *argv[]);
static int cli_led(int argc, char *argv[]);
static int cli_mot(int argc, char *argv[]);

const CMD_LIST_T gCmdListObj[] = {    
    { "help",   1,  cli_help,   "help"          },
    { "led",    3,  cli_led,    "led [0..2] [on|off]"   },
    { "mot",    5,  cli_mot,    "mot [0..3] [cw|ccw] [0~100] [1..10]"  },
    { NULL,     0,  NULL,       NULL            }
};

// 
static int cli_mot(int argc, char *argv[])
{
    return 0;
}

static int cli_led(int argc, char *argv[])
{
    uint32_t no;
    
    no = (uint32_t)strtol(argv[1], NULL, 10);
    if (strcmp(argv[2], "on") == 0) {
        printf("led %d on\n", no);
        //led_onoff(no, true);
    } else if (strcmp(argv[2], "off") == 0) {
        printf("led %d off\n", no);
        //led_onoff(no, false);
    }

    return 0;
}

static int cli_help(int argc, char *argv[])
{
    for (int i=0; gCmdListObj[i].cmd != NULL; i++) {
        printf("%s\n", gCmdListObj[i].remark);
    }
    return 0;
}


#define D_DELIMITER     " ,.\r\n"


// command line interpreter : parser
void cli_parser(char *str)
{
    int argc = 0;
    char *argv[10];
    char *ptr;
    
    ptr = strtok(str, D_DELIMITER);
    if (ptr == NULL) {
        return;
    }
    
    while (ptr != NULL) {
//        printf("%s\n", ptr);
        argv[argc] = ptr;
        argc++;
        ptr = strtok(NULL, D_DELIMITER);
    }
// for debugging
#if defined(D_DEBUG)    
    printf("argc : %d\n", argc);

    for (int i=0; i<argc; i++) {
        printf("argv[%d]:%s\n", i, argv[i]);
    }    
#endif    

    for (int i=0; gCmdListObj[i].cmd != NULL; i++) {
        if (strcmp(gCmdListObj[i].cmd, argv[0]) == 0) {
            if (gCmdListObj[i].no <= argc) {
                gCmdListObj[i].cbf(argc, argv);
            }
        }
    }
}


#if 0
//char str_parsing[] = "led 2 off\n";

void cli_main(void)
{
    cli_parser(str_parsing);
    
	return 0;
}
#endif

