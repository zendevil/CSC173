
//creating Course-Student-Grade (CSG) schema
typedef struct CSG{

  char *course;
  int id;
  char *grade;

} CSG;
//LCSG is a pointer to the schema CSG. the L prefix stands for 'list'
//This allows us to have an array, or list, of relations.
typedef struct CSG* LCSG;


//StudentId-Name-Address-Phone (SNAP) schema. //id is the key
typedef struct SNAP {
  int id;
  char *name;
  char *address;
  char *phone;
} SNAP;
LSNAP is the table in which all the SNAP values will be stored.
typedef struct SNAP* LSNAP;




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
