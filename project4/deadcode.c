
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











//more dead Course-Student-Grade

  printf("Course name: %s\n", csg[0].attr[0]);
  printf("Student: %s\n", csg[0].attr[1]);
  printf("Grade: %s\n", csg[0].attr[2]);


  t1[0].id = 184;
  t1[1].id = 123;
  t1[2].id = 857;

  int i0 = hash(t1[0].id);
  int i1 = hash(t1[1].id);
  int i2 = hash(t1[2].id);

  printf("hash1: %d\n", i0);
  printf("hash2: %d\n", i1);
  printf("hash3: %d\n", i2);






  printf("index: %d\n", hash(t1[0].id));
  int index = hash(t1[0].id);
  HSNAP[index] =  t1;
  printf("%d\n", t1[0].id);

adding values in row 1 of the table t
  t[0].course = "CSC173";
  t[0].id = 12345;
  t[0].grade = "A";



adding values in row 2 of the table t
  t[1].course = "CSC171";
  t[1].id = 12345;
  t[1].grade = "A-";

  printf("%s\n", t[0].course);
  printf("%d\n", t[0].id);
  printf("%s\n", t[0].grade);


  printf("%s\n", t[1].course);
  printf("%d\n", t[1].id);
  printf("%s\n", t[1].grade);
