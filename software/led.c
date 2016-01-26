#include <unistd.h>
#include <stdio.h>
#include <time.h>


#define	H	0x76
#define	E	0x79
#define	L	0x38
#define	O	0x3F
#define	U	0x3E
#define	R	0x50
#define	D	0x5E
#define SPACE	0x00
#define TRUE	1
#define FALSE	0

/*******************
 * GLOBAL VARIABLES
 *******************/
volatile int * led = (int *) 0xFF200040;
// red LED address
volatile int * switchptr = (int *) 0xFF200030;
// SW slider switch address
volatile int * hex3_hex0 = (int *) 0xFF200020;
// hex3 - hex 0 addr
volatile int * hex5_hex4 = (int *) 0xFF200010;
// hex5 - hex 4 addr
volatile int * keys = (int *) 0xFF200000;
//volatile int * key1 = ((int *) 0xFF200000) & (1<<0);
//volatile int * key1 = ((int *) 0xFF200000) & (1<<1);
//volatile int * key2 = ((int *) 0xFF200000) & (1<<2);
//volatile int * key3 = ((int *) 0xFF200000) & (1<<3);
unsigned int speed = 5;		// determines the length of the delay 
int progress = 0; 	// indicates how many squares the message has travelled


void delay(int n)
{
	long i, j;
	int tmp = 1;

//	time_t start = clock();
	for (i = 0; i<100000*n; i++) {
		if (*keys != 0) {
			//for (j=0; j<4000; j++) {
			//	tmp *= 12345;
			//}
			return;
		}
		tmp *= 12345;
	}

//	printf("%d, %d, %d\n", start, clock(), CLOCKS_PER_SEC);
}

void shift(void)
{
	int buf;

	buf = (*hex3_hex0 & 0xFF000000) >> 24;
	*hex5_hex4 <<= 8;
	*hex5_hex4 += buf;
	*hex3_hex0 <<= 8;
}

void insert(int l)
{
	shift();
	*hex3_hex0 += l;
}

void clear(void)
{
	*hex3_hex0 = 0;
	*hex5_hex4 = 0;
}

void display(char message[], int len)
{
	insert(message[progress++]);
	if (progress == len) progress = 0;
	//delay(speed);
}

int main(void)
{
	int switch_value;
	int buf= 0;
	//char hello_str[13] = {0x76, 0x79, 0x38, 0x38, 0x3F, 0x00, 0x3E, 0x3E, 0x3F, 0x50, 0x38, 0x5E, 0x00}; // array containing hello world message
	char hello_str[13] = {H, E, L, L, O, SPACE, U, U, O, R, L, D, SPACE}; // array containing hello world message
	//int custom = *(switchptr);
	char custom_str[6] = {0};
	int paused = 0;

	int i, j;
	int tmp;

	enum states {
		HELLO,
		CUSTOM
	};
	
	enum states state = HELLO;

	clear();

	while (1) {
		if (*keys != 0) {	// poll for key presses
			switch (*keys) {
				case 1: // key 0 is pressed
					paused = !paused;
					*led = paused;
					delay(1);
				break;
				case 2: // key 1 is pressed
					*led = 2;
					if (speed > 1) speed -= 1;
				break;
				case 4: // key 2 is pressed
					*led = 4;
					if (speed < 9) speed += 1;
				break;
				case 8: // key 3 is pressed
					*led = 8;
					if (state == HELLO) {
						state = CUSTOM;
						custom_str[1] = *switchptr & 0x7F;
						custom_str[0] = (*switchptr & 0x380) >> 7;
					} else {
						state = HELLO;
					}
					clear();
					progress = 0;
				break;

			}
			for (j=0; j<500000; j++) {
				tmp *= 12345;
			}
		} else {
			*led = *led & 0x01;	// Clear small LEDs except the last one.
		}


		switch (state) {
			case HELLO:
				if (paused) continue;
				display(hello_str, 13);
				break;
			case CUSTOM:
				if (paused) {
					// Read and display
						
					custom_str[1] = *switchptr & 0x7F;
					custom_str[0] = (*switchptr & 0x380) >> 7;
					clear();
					insert(custom_str[0]);
					insert(custom_str[1]);
					if (progress > 2) 
						for(i = 0; i < progress - 2; i++) shift();


					//*hex3_hex0 = (*hex3_hex0 & 0xFFFFFF00) + (*switchptr & 0xFF);
					//custom_str[progress] = *switchptr & 0x7F;
				} else {
					display(custom_str, 6);
/*
					if (progress == 0) insert((custom & 0x380)>>7);
					else if (progress == 1) insert((custom & 0x7F));
					else shift();
					
					progress++;

*/					if (progress == 7) progress = 0;
				}
				break;
		}
		delay(speed);
	}

	return 0;
}
