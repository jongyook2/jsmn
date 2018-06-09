#include <stdio.h>
#define f(a) #a
typedef enum{
	disomall = 0,
	kakamuka = 1,
	costco = 2,
	nationalwoman = 3
} company_t;

static char *comlist[]={
	f(disomall),
	f(kakamuka),
	f(costco),
	f(nationalwoman)
};

typedef struct{
	company_t company;
	char name[20];
	int price;
	int rate;
	int deliveryfee;
} product_t;
