#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../jsmn.h"
#include "../productlist.h"

/*
* A small example of jsmn parsing when JSON structure is known and number of
* tokens is predictable.
*/


char *readJSONFILE(char *file){
  FILE *fp;
  char input[256];
  int len = 0;
  strcat(file,".json");
  fp = fopen(file , "rt");

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
void jsonNameList(char *jsontr, jsmntok_t *t, int tokcount,NameTokInfo *nameTokInfo){
  //printf("***** Name List ******\n");
  int i; int j=0;
  for (i = 1; i < tokcount; i++) {
    if(t[i].type==JSMN_STRING){
      if(t[i].size>0){
        //if(t[i].parent!){
          nameTokIndex[j]=i;
          ++j;
      //   if(t[i].parent==0){
      //
      //   printf("[Name %d] %.*s\n",j,t[i].end-t[i].start,jsontr + t[i].start);
       }
      }
    }
  }

void printNameList(char *jsontr, jsmntok_t *t, int *nameTokIndex,int *nt){
  int i=0,j=1;
  int temp=0;
  if(t[t[t[t[nameTokIndex[1]].parent].parent].parent].type==JSMN_STRING){
    temp=t[nameTokIndex[1]].parent;
  }
  else{
   temp=t[nameTokIndex[0]].parent;}
  printf("***** Name List ******\n");
  while(nameTokIndex[i]!=0){
    if(t[t[nameTokIndex[i]].parent].parent==t[temp].parent){
      //nt=realloc(nt,sizeof(int)*j);
      nt[j-1]=nameTokIndex[i];

    printf("[Name %d] %.*s\n",j,t[nameTokIndex[i]].end-t[nameTokIndex[i]].start,jsontr + t[nameTokIndex[i]].start);
    j++;
  }
    ++i;
}
}
void selectNameList(char *jsontr, jsmntok_t *t, int *nameTokIndex){
  int num;
  while(1){
    printf("select Name's no (exit:0) >> ");
    scanf("%d",&num);
    if(num==0){return ;}
    if(nameTokIndex[num-1]==0) {printf("not correct name number retry!"); continue;}
    printf("[Name %d] %.*s\n",num,t[nameTokIndex[num-1]].end-t[nameTokIndex[num-1]].start,jsontr + t[nameTokIndex[num-1]].start);
    printf("%.*s\n",t[nameTokIndex[num-1]+1].end-t[nameTokIndex[num-1]+1].start,jsontr + t[nameTokIndex[num-1]+1].start);
  }
}
void ObjectNameList(char *jsontr, jsmntok_t *t, int *nameTokIndex, int *objectList){
  printf("***** Object List ******\n");
  int i=0;
  int j=1;
  int index=0;
  int temp=0;
  if(t[t[t[t[nameTokIndex[1]].parent].parent].parent].type==JSMN_STRING){
    temp=t[t[nameTokIndex[1]].parent].parent;
  }
  else{
   temp=t[t[nameTokIndex[0]].parent].parent;}
  while(nameTokIndex[i]!=0){
    index=nameTokIndex[i];
    if(t[index-1].parent==temp){

      objectList=realloc(objectList,sizeof(int)*j);
      objectList[j-1]=index-1;

      printf("[Name %d] %.*s\n",j,t[index+1].end-t[index+1].start,jsontr + t[index+1].start);
      j++;
    }
    i++;
  }
}
// void check(jsmntok_t *t, int *objectList, int *nameTokIndex, int *nt, int **ntD){
//   ntD=(int *)malloc(sizeof(int)*(sizeof(objectList)/sizeof(int)));
//
//   for()
//     if(t[nt[i]].parent==objectList[])
//       a++;
//     else if()
//   }
// }

void printSelectObjectNameList(char *jsontr,jsmntok_t *t, int *objectList,int *nameTokIndex, int *nt){
  int num=0;

  int j=0;
  int k=0;
  while(1){
  printf("원하는 번호 입력 (Exit: 0) : ");
  scanf("%d",&num);
  int i=0;
  if(num==0){return ;}
  int o1=objectList[num-1];

  while(nt[i]!=0){
    if(t[nt[i]].parent==o1){
      break;
  }
  i++;
}
  printf("%.*s : %.*s\n",t[o1+1].end-t[o1+1].start,jsontr + t[o1+1].start,t[o1+2].end-t[o1+2].start,jsontr + t[o1+2].start);
  while(nt[i+1]!=0){

    if(t[nt[i+1]].parent==o1){

    printf("\t[%.*s]\t%.*s\n",t[nt[i+1]].end-t[nt[i+1]].start,jsontr + t[nt[i+1]].start,t[nt[i+1]+1].end-t[nt[i+1]+1].start,jsontr + t[nt[i+1]+1].start);

  }

  i++;
}
}
}
void printList(char *jsontr,jsmntok_t *t){
  printf("*********************************************\n");
  printf("번호\t제품명\t제조사\t가격\t개수\n");
  printf("*********************************************\n");
  printf("%d");
}



//checking
int main() {
  int i;
  int r;
  int *k;
  jsmn_parser p;
  char name[20];
  jsmntok_t t[128]; /* We expect no more than 128 tokens */
  while(1){
  printf("원하는 파일명 입력: ");
  scanf("%s",&name);
  if(name==NULL){printf("%s.json 파일이 존재하지 않습니다",name); break;}
  char *JSON_STRING=readJSONFILE(name);
  int nameTokIndex[200]={0};
  //int *nt=(int*)malloc(sizeof(int));
  int nt[20]={0};
  int **ntD;
  int *objectList = (int *)malloc(sizeof(int));
  jsmn_init(&p);
  r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
  printf("%d\n",t[t[2].parent].parent);
  printf("%d\n",t[20].parent);
  jsonNameList(JSON_STRING,t,r,nameTokIndex);
  printNameList(JSON_STRING,t,nameTokIndex,nt);
  //selectNameList(JSON_STRING,t,nameTokIndex);
  ObjectNameList(JSON_STRING,t,nameTokIndex,objectList);
  printSelectObjectNameList(JSON_STRING,t,objectList,nameTokIndex,nt);
}
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
  return EXIT_SUCCESS;
}
