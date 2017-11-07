#include<stdio.h>
#include<stdlib.h>
#define T_SIZE 1000

//creating Course-Student-Grade (CSG) schema
typedef struct CSG{
  char *course;
  int id;
  char *grade;

} CSG;
//T_CSG is a pointer to the schema CSG.
//This allows us to have an array of relations.
typedef struct CSG* T_CSG;

//creating StudentId-Name-Address-Phone (SNAP) schema
typedef struct SNAP {
  char *id;
  char *name;
  char *address;
  char *phone;
} SNAP;
//T_SNAP is the table in which all the SNAP values will be stored.
typedef struct SNAP* T_SNAP;



//creating Course-Prerequisite (CP) schema
typedef struct CP {
  char *course;
  char *preReq;
} CP;
typedef struct CP* T_CP;

//Course-Day-Hour schema
typedef struct CDH {
  char *course;
  char *day;
  char *hour;
} CDH;
//as usual, we have a table T_CDH
typedef stuct CDH* T_CDH;












int main() {
  T_CSG t = (CSG*) malloc(sizeof(CSG*) * T_SIZE);

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
