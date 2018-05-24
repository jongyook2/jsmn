#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../jsmn.h"

/*
 * A small example of jsmn parsing when JSON structure is known and number of
 * tokens is predictable.
 */


 char *readJSONFILE(){
    FILE *fp;
    char input[256];
    int len = 0;
    fp = fopen("data.json" , "rt");

    char *save = (char *)malloc(sizeof(char) * 256);
    while(1){
       fgets(input , sizeof(input) , fp);
       if( feof(fp) ) {
          break ;
       }
       len += strlen(input);
       realloc(save, len + 1);
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
void jsonNameList(char *jsontr, jsmntok_t *t, int tokcount,int *nameTokIndex){
  printf("***** Name List ******\n");
  int i; int j=0;
  for (i = 1; i < tokcount; i++) {
    if(t[i].type==JSMN_STRING){
    if(t[i].size>0){
      nameTokIndex[j]=i;
      ++j;
    printf("[Name %d] %.*s\n",j,t[i].end-t[i].start,jsontr + t[i].start);

  }
}
}
}
void printNameList(char *jsontr, jsmntok_t *t, int *nameTokIndex){
  int i=0;
  while(nameTokIndex[i]!=0){
  ++i;
    printf("[Name %d] %.*s\n",i,t[nameTokIndex[i-1]].end-t[nameTokIndex[i-1]].start,jsontr + t[nameTokIndex[i-1]].start);
  }
}
void selectNameList(char *jsontr, jsmntok_t *t, int *nameTokIndex){
  int num;
  while(num!=0){
  printf("select Name's no (exit:0) >> ");
  scanf("%d",&num);
  printf("[Name %d] %.*s\n",num,t[nameTokIndex[num-1]].end-t[nameTokIndex[num-1]].start,jsontr + t[nameTokIndex[num-1]].start);
  printf("%.*s\n",t[nameTokIndex[num-1]+1].end-t[nameTokIndex[num-1]+1].start,jsontr + t[nameTokIndex[num-1]+1].start);
}
}
int main() {
	int i;
	int r;
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 tokens */
	char *JSON_STRING=readJSONFILE();
  char nameTokIndex[100]={0};
	jsmn_init(&p);
	r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
  jsonNameList(JSON_STRING,t,r,nameTokIndex);
  //printNameList(JSON_STRING,t,nameTokIndex);
  selectNameList(JSON_STRING,t,nameTokIndex);

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
	return EXIT_SUCCESS;
}
