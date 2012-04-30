#ifndef ATOM_H_INCLUDED
#define ATOM_H_INCLUDED

extern cellpoint is_null(cellpoint);
extern cellpoint is_pair(cellpoint);

//char
extern cellpoint make_char(char);
extern cellpoint is_char(cellpoint);
extern char get_char(cellpoint);

//integer
extern cellpoint make_integer(int);
extern int get_integer(cellpoint);
extern cellpoint is_integer(cellpoint);
extern cellpoint is_number(cellpoint);

//boolean 
extern cellpoint a_true;
extern cellpoint a_false;
extern void bool_init(void);
extern cellpoint make_boolean(boolean);
extern cellpoint is_boolean(cellpoint);
extern boolean is_true(cellpoint);
extern boolean is_false(cellpoint);

//symbol
extern cellpoint obarray;
extern void init_obarray(void);
extern cellpoint make_symbol(char *);
extern char *get_symbol(cellpoint);
extern cellpoint is_symbol(cellpoint);

//string
extern cellpoint make_string(int, cellpoint);
extern cellpoint is_string(cellpoint);
extern int string_len(cellpoint);
extern cellpoint string_ref(cellpoint, int);
extern void string_set(cellpoint, int, cellpoint);
extern cellpoint chars_2_string(char *);
extern char *get_string(cellpoint);

//vector
extern cellpoint make_vector(int, cellpoint);
extern cellpoint is_vector(cellpoint);
extern int vector_len(cellpoint);
extern cellpoint vector_ref(cellpoint, int);
extern void vector_set(cellpoint, int, cellpoint);

//primitive procedure
extern cellpoint make_prim_proc(cellpoint, prim_proc_t);
extern cellpoint is_prim_proc(cellpoint);
extern prim_proc_t prim_proc_obj(cellpoint);

//compound procedure
extern cellpoint make_procedure(void);
extern cellpoint is_compound_proc(cellpoint);

#endif //ATOM_H_INCLUDED
