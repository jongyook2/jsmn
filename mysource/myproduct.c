#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../jsmn.h"
#include "../myproduct.h"
//#define f(a) #a
//#define DEBUG_MODE
/*
* A small example of jsmn parsing when JSON structure is known and number of
* tokens is predictable.
*/


char *readJSONFILE(){
  FILE *fp;
  char input[256];
  int len = 0;
  //strcat(file,"data4.json");
  fp = fopen("myproduct.json" , "rt");

  char *save = (char *)malloc(sizeof(char) * 256);
  while(1){
    fgets(input , sizeof(input) , fp);
    if( feof(fp) ) {
      break ;
    }
    len += strlen(input);
    save= realloc(save, len + 1);
    strcat(save, input);
    //malloc, ralloc
  }

  //printf("%s\n", JSON_STRING);

  fclose(fp);
  return save;
}
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
  strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}
int selectName(char *name){
  if(strcmp(name,"disomall")==0)
    return disomall;
  else if(strcmp(name,"kakamuka")==0)
    return kakamuka;
  else if(strcmp(name,"costco")==0)
      return costco;
    else if(strcmp(name,"nationalwoman")==0)
        return nationalwoman;

  }

int makeProduct(char *json, jsmntok_t *t, int tokcount, product_t *p[]){
int i=0;
int temp=1;
int j=0;

p[j]=(product_t*)malloc(sizeof(product_t));
for(i;i<tokcount;i++){
    if(jsoneq(json, &t[i], "company") == 0){

        if(t[i].parent!=temp){
          j++;
          temp=t[i].parent;

          p[j]=(product_t*)malloc(sizeof(product_t));

        }
        char company[20];
        char name[20];
        char price[10];
        char rate[2];
        char df[5];

        sprintf(company, "%.*s", t[i+1].end-t[i+1].start, json+t[i+1].start);
        p[j]->company=selectName(company);
        sprintf(p[j]->name, "%.*s", t[i+3].end-t[i+3].start, json+t[i+3].start);
        sprintf(price, "%.*s", t[i+5].end-t[i+5].start, json+t[i+5].start);
        p[j]->price=atoi(price);
        sprintf(rate, "%.*s", t[i+7].end-t[i+7].start, json+t[i+7].start);
        p[j]->rate=atoi(rate);
        sprintf(df, "%.*s", t[i+9].end-t[i+9].start, json+t[i+9].start);
        p[j]->deliveryfee=atoi(df);

    }
}
return j;
}

int totalprice(product_t* p[], int index){
  return  p[index]->price+p[index]->deliveryfee;
}
char *convert(int index){
  return comlist[index];
}

void printProduct(product_t* p[], int pcount){
  int i=0;
  
  printf("*************************************************************************\n");
  printf("번호\t제품명   \t판매자\t        가격\t평점\t배송료\t결제금액\n");
  printf("*************************************************************************\n");
  for(i;i<pcount;i++){
    printf("%d\t%-6s   \t%-13s\t%d\t%d\t%d\t%d\n",i+1,
    p[i]->name, convert(p[i]->company), p[i]->price, p[i]->rate, p[i]->deliveryfee,
    totalprice(p,i));
  }
}






//checking
int main() {

  int i;
  int r;
  int *k;
  jsmn_parser p;

  jsmntok_t t[128]; /* We expect no more than 128 tokens */
  product_t *chocolist[20];
  char *JSON_STRING=readJSONFILE();
  jsmn_init(&p);
  r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));

  i=makeProduct(JSON_STRING, t, r, chocolist);
  printProduct(chocolist,4);
  //printf("%d\n",i);


//}
  //printf("%d",strlen(nameTokIndex));

  // if (r < 0) {
  // 	printf("Failed to parse JSON: %d\n", r);
  // 	return 1;
  // }
  //
  // /* Assume the top-level element is an object */
  // if (r < 1 || t[0].type != JSMN_OBJECT) {
  // 	printf("Object expected\n");
  // 	return 1;
  // }
  //
  // /* Loop over all keys of the root object */
  // for (i = 1; i < r; i++) {
  // 	if (jsoneq(JSON_STRING, &t[i], "name") == 0) {
  // 		/* We may use strndup() to fetch string value */
  // 		printf("- name: %.*s\n", t[i+1].end-t[i+1].start,
  // 				JSON_STRING + t[i+1].start);
  // 		i++;
  // 	} else if (jsoneq(JSON_STRING, &t[i], "keywords") == 0) {
  // 		/* We may additionally check if the value is either "true" or "false" */
  // 		printf("- keywords: %.*s\n", t[i+1].end-t[i+1].start,
  // 				JSON_STRING + t[i+1].start);
  // 		i++;
  // 	} else if (jsoneq(JSON_STRING, &t[i], "description") == 0) {
  // 		/* We may want to do strtol() here to get numeric value */
  // 	printf("- UID: %.*s\n", t[i+1].end-t[i+1].start,
  // 				JSON_STRING + t[i+1].start);
  // 		i++;
  // 	} else if (jsoneq(JSON_STRING, &t[i], "examples") == 0) {
  // 		/* We may want to do strtol() here to get numeric value */
  // 			printf("examples:\n");
  // 			int j;
  // 			if (t[i+1].type != JSMN_ARRAY) {
  // 			continue; /* We expect groups to be an array of strings */
  // 		}
  // 		for (j = 0; j < t[i+1].size; j++) {
  // 			jsmntok_t *g = &t[i+j+2];
  // 			printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
  // 		}
  // 		i += t[i+1].size + 1;
  //
  // 	}
  // 	/*} else if (jsoneq(JSON_STRING, &t[i], "examples") == 0) {
  // 		int j;
  // 		printf("- Groups:\n");
  // 		if (t[i+1].type != JSMN_ARRAY) {
  // 			continue; /* We expect groups to be an array of strings */
  // 	/*	}
  // 		for (j = 0; j < t[i+1].size; j++) {
  // 			jsmntok_t *g = &t[i+j+2];
  // 			printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
  // 		}
  // 		i += t[i+1].size + 1;
  // 	} else {
  // 		printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
  // 				JSON_STRING + t[i].start);
  // 	}*/
  // }
  int a;
  for( a=0;a<i;a++){
    free(chocolist[a]);}

  return EXIT_SUCCESS;
}
