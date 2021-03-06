/**@<parser.h>::**/

extern int lookahead; // @ local

extern int gettoken (FILE *); // @ lexer.c

extern FILE *source, *object; // @ main.c

extern void match (int); // @ local

/* syntax names */
void mypas(void);
void body(void);
char **namelist(void);
int vartype(void);
void parmdef(void);
void declarative(void);
void imperative(void);
void stmtlist(void);
void stmt(void);
void ifstmt(void);
void whilestmt(void);
void repstmt(void);

int is_compatible(int, int);
int is_relop(void);
int expr(int);
int check_neg(int, int *);
int check_locality(int);
int check_compatibility(int, int);
void operation(int, int);
void type_convert(int);
int simple_expr(int);
int addop(void);
int mulop(void);
