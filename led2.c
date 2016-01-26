#define	H	0x76
#define	E	0x79
#define	L	0x38
#define	O	0x3F
#define	U	0x3E
#define	R	0x50
#define	D	0x5E
#define SPACE	0x00
#include <unistd.h>
#include <stdio.h>

volatile int * led = (int *) 0xFF200040;
// red LED address
volatile int * switchptr = (int *) 0xFF200030;
// SW slider switch address
volatile int * hex3_hex0 = (int *) 0xFF200020;
// hex3 - hex 0 addr
volatile int * hex5_hex4 = (int *) 0xFF200010;
// hex5 - hex 4 addr
volatile int * keys = (int *) 0xFF200000;
volatile int * key0 = ((int *) 0xFF200000) & (1<<0);
volatile int * key1 = ((int *) 0xFF200000) & (1<<1);
volatile int * key2 = ((int *) 0xFF200000) & (1<<2);
volatile int * key3 = ((int *) 0xFF200000) & (1<<3);


// Simple test program 

int delay(int n)
{
	long i;
	int tmp = 1;
	for (i = 0; i<1000000*n; i++) {
		tmp *= 12345;
	}
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

int main(void)
{
	//printf("%d\n", sizeof(int));
	//printf("%d\n", sizeof(long));
	//printf("%d\n", sizeof(long long));




	int switch_value;
	int buf, buf2 = 0;

	clear();

	//buf = H; buf <<= 8;
	//buf += E; buf <<= 8;
	//buf += L; buf <<= 8;
	//buf += L;
	//*hex3_hex0 = buf;
	insert(H);
	while(*button != 0);
	delay(1);
	insert(E);
	while(*button != 0);
	delay(1);
	insert(L);
	while(*button != 0);
	delay(1);
	insert(L);
	while(*button != 0);
	delay(1);
	insert(O);
	while(*button != 0);
	delay(1);
	insert(SPACE);
	while(*button != 0);
	delay(1);
	insert(U);
	delay(1);
	insert(U);
	delay(1);
	insert(O);
	delay(1);
	insert(R);
	delay(1);
	insert(L);
	delay(1);
	insert(D);
	

	//while(1);


	//while (1)
	//{
	//	switch_value = *(switchptr);
	//	*(led) = switch_value;

	//	buf = H; buf <<= 8;
	//	//buf += E; buf <<= 8;
	//	//buf += L; buf <<= 8;
	//	//buf += L;
	//	//*(hex3_hex0) = buf;
	//	*(hex3_hex0) = H;
	//	delay(1);
	//	*(hex3_hex0) = E;
	//	delay(1);
	//	*(hex3_hex0) = L;
	//	delay(1);
	//	*(hex3_hex0) = L;
	//	delay(1);
	//	
	//	//*(hex5_hex4) <<= 8;
	//	//buf2 = 0xF000 && buf;
	//	//buf2 >>= 12;
	//	//*(hex5_hex4) += buf2;
	//}
	return 0;
}
