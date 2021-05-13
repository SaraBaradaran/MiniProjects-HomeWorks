
typedef double (func_t) (double);

struct symrec
{
  char *name;  
  int type;    
  union
  {
    double var;    
    func_t *fun; 
  } value;
  struct symrec *next; 
};

typedef struct symrec symrec;

extern symrec *sym_table;

symrec *putsym (char const *name, int sym_type);
symrec *getsym (char const *name);
