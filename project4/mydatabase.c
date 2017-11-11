#include<stdio.h>
#include<stdlib.h>
#define LSIZE 5


typedef struct {
  int nAttr;
  char *attr;
} tuple;


typedef struct {
  tuple schema;
  tuple *entries;
  int size;
} table;


typedef struct {
  int nTuples;
  table * tables;
} db;


//creating Course-Student-Grade (CSG) schema
typedef struct CSG{
  char *course;
  int id;
  char *grade;

} CSG;
//LCSG is a pointer to the schema CSG. the L prefix stands for 'list'
//This allows us to have an array, or list, of relations.
typedef struct CSG* LCSG;
typedef LCSG HCSG[LSIZE]; //H stands for hashtable

//StudentId-Name-Address-Phone (SNAP) schema. //id is the key
typedef struct SNAP {
  int id;
  char *name;
  char *address;
  char *phone;
} SNAP;
//LSNAP is the table in which all the SNAP values will be stored.
//typedef struct SNAP* LSNAP;
typedef LSNAP HASHTABLE[LSIZE];



//creating Course-Prerequisite (CP) schema
typedef struct CP {
  char *course;
  char *preReq;
} CP;
typedef struct CP* LCP;
typedef LCP HCP[LSIZE];

//Course-Day-Hour schema
typedef struct CDH {
  char *course;
  char *day;
  char *hour;
} CDH;
//as usual, we have a table LCDH
typedef struct CDH* LCDH;
typedef LCDH HCDH[LSIZE];


int hash(int key) {
  return key % LSIZE;
}


int main() {
  LCSG t = (CSG*) malloc(sizeof(CSG*) * LSIZE);

  LSNAP t1 = (SNAP*) malloc(sizeof(SNAP*) * LSIZE);
  LSNAP t2 = (SNAP*) malloc(sizeof(SNAP*) * LSIZE);
  LSNAP t3 = (SNAP*) malloc(sizeof(SNAP*) * LSIZE);
  t1[0].id = 184;
  t1[1].id = 123;
  t1[2].id = 857;

  int i0 = hash(t1[0].id);
  int i1 = hash(t1[1].id);
  int i2 = hash(t1[2].id);

  printf("hash1: %d\n", i0);
  printf("hash2: %d\n", i1);
  printf("hash3: %d\n", i2);

  HSNAP[i0] = t1;




  // printf("index: %d\n", hash(t1[0].id));
  // int index = hash(t1[0].id);
  // HSNAP[index] =  t1;
  // printf("%d\n", t1[0].id);

//adding values in row 1 of the table t
  t[0].course = "CSC173";
  t[0].id = 12345;
  t[0].grade = "A";



//adding values in row 2 of the table t
  t[1].course = "CSC171";
  t[1].id = 12345;
  t[1].grade = "A-";

  printf("%s\n", t[0].course);
  printf("%d\n", t[0].id);
  printf("%s\n", t[0].grade);


  printf("%s\n", t[1].course);
  printf("%d\n", t[1].id);
  printf("%s\n", t[1].grade);
  return 0;
}
