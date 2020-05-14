#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <panel.h>
#include <ctype.h>


#define FOREVER 		1
#define STR_MAX_LEN 		100
#define S_TO_WAIT 		5
#define MILIS_TO_WAIT		0
#define KEYBOARD		0
#define QUIT			"quit"
#define SELECT_ERROR		-1
#define SELECT_EVENT		1
#define SELECT_NO_EVENT		0

typedef struct{
int scor;
int spatiu;
char nume[8];
}dec;
