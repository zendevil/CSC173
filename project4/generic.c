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
