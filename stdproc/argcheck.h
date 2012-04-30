#ifndef ARGCHECK_H_INCLUDED
#define ARGCHECK_H_INCLUDED

#define BOOLEAN_T 0
#define CHARACTER_T 1
#define INTEGER_T 2
#define NUMBER_T 3
#define SYMBOL_T 4
#define STRING_T 5
#define VECTOR_T 6
#define PAIR_T 7
#define LIST_T 8
#define PROCEDURE_T 9

extern void check_arglst_len_eq(char *, int, cellpoint);
extern void check_arg_type(char *, char *, cellpoint, int);

#endif //ARGCHECK_H_INCLUDED
