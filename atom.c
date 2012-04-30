#include "common.h"
#include <string.h>

/*****************************************************************
 *This file provides maker, predicate & sellector for atomic objects,
 *such as boolean, charactor, number, symbol, string, vector, procedure.
*******************************************************************/
extern struct cons_cell *the_cons_cells;
extern cellpoint free_point;
extern boolean memory_enough(int);

static cellpoint make_atom(uint type, uint val)
{
	the_cons_cells[free_point].car = type;
	the_cons_cells[free_point].cdr = val;
//	printf("%d\n", free_point);
	return free_point++;
}
static uint atom_type(cellpoint cp)
{
	return the_cons_cells[cp].car;
}
static uint atom_obj(cellpoint cp)
{
	return the_cons_cells[cp].cdr;
}
static boolean is_atom(cellpoint cp)
{
    return (atom_type(cp) & ATOM_BIT) ? true : false;
}

cellpoint is_null(cellpoint point)
{
    return (point == NIL) ? a_true : a_false;
}
cellpoint is_pair(cellpoint cp)
{
	if (is_false(is_null(cp)) && !is_atom(cp)){
		return a_true;
	}else {
		return a_false;
	}
}

///////////////////////////////////////////////////
//character
//maker: make_char
//predicate: is_char
//sellector: get_char
///////////////////////////////////////////////////
cellpoint make_char(char ch)
{
	if (!memory_enough(1)){
		//calls garbage collection
		garbage_collection();
	}
	return make_atom(ATOM_BIT|CHARACTER_BIT, ch);
}
cellpoint is_char(cellpoint cp)
{
    if (is_atom(cp) && (atom_type(cp) & CHARACTER_BIT)){
		return a_true;
	}else {
		return a_false;
	}
}
char get_char(cellpoint cp)
{
    return (char)atom_obj(cp);
}

/////////////////////////////////////////////////////
//integer maker,  predicate & sellector
//////////////////////////////////////////////////
cellpoint make_integer(int arg)
{
	if (!memory_enough(1)){
		//calls garbage collection
		garbage_collection();
	}
	return make_atom(ATOM_BIT|INTEGER_BIT, arg);
}
int get_integer(cellpoint point)
{
    return atom_obj(point);
}
cellpoint is_integer(cellpoint point)
{
	if (is_atom(point) && (atom_type(point) & INTEGER_BIT)){
		return a_true;
	}else {
		return a_false;
	}
}
cellpoint is_number(cellpoint point)
{
    return is_integer(point);
}

////////////////////////////////////////////////////////////
//boolean maker, predicate & sellector
////////////////////////////////////////////////////////////
cellpoint a_true = NIL;
cellpoint a_false = NIL;
void bool_init(void)
{
	a_true = make_atom(ATOM_BIT|BOOLEAN_BIT, true);
	a_false = make_atom(ATOM_BIT|BOOLEAN_BIT, false);
}
cellpoint make_boolean(boolean b)
{
    if (b == true){
        return a_true;
    }else {
        return a_false;
    }
}
cellpoint is_boolean(cellpoint cp)
{
    if (is_atom(cp) && (atom_type(cp) & BOOLEAN_BIT)){
		return a_true;
	}else {
		return a_false;
	}
}
boolean is_true(cellpoint cp)
{
    return is_false(cp) ? false : true;
}
boolean is_false(cellpoint cp)
{
	return (cp == a_false) ? true : false;
}

////////////////////////////////////////////////////////////////
//symbol 
//maker: make_symbol
//predicate: is_symbol
//sellector: get_symbol
////////////////////////////////////////////////////////////
#define OBARRAY_LEN 89
cellpoint obarray;
void init_obarray(void)
{
	obarray = make_vector(OBARRAY_LEN, NIL);
}
static int compute_obarray_index(char *sym)
{
    int sum = 0;
    while(*sym != '\0'){
        sum += *sym++;
    }
    return sum % OBARRAY_LEN;
}
static cellpoint lookup_symbol(char *sym)
{
    int ind = compute_obarray_index(sym);
    cellpoint p = vector_ref(obarray, ind);
    while(p != NIL){
		cellpoint s = car(p);
        if(strcmp(sym, get_symbol(s)) == 0){
            return s;
        }
        p = cdr(p);
    }
    return NIL;
}
static void interning_symbol(char *sym, cellpoint cp)
{
    int ind = compute_obarray_index(sym);
	cellpoint p = vector_ref(obarray, ind);
	vector_set(obarray, ind, cons(cp, p));
}
cellpoint make_symbol(char *sym)
{
    cellpoint cp = lookup_symbol(sym);
    if (cp != NIL){
        //the symbol has been created
        return cp;
    }
	if (!memory_enough(1)){
		//calls garbage collection
		garbage_collection();
	}
    char *new_sym = (char *)malloc(strlen(sym)+1);
    if(new_sym == NULL){
        perror("Error:malloc error. -- CREATE_SYMBOL\n");
		error_handler();
    }
    strcpy(new_sym, sym);
    cp = make_atom(ATOM_BIT|SYMBOL_BIT, (uint)new_sym);
    interning_symbol(new_sym, cp);
    return cp;
}
char *get_symbol(cellpoint cp)
{
    return (char *)atom_obj(cp);
}
cellpoint is_symbol(cellpoint cp)
{
    if (is_atom(cp) && (atom_type(cp) & SYMBOL_BIT)){
		return a_true;
	}else {
		return a_false;
	}
}

///////////////////////////////////////////////////////////////
//string
//maker: make_string
//predicate: is_string
//sellector: string_ref
//setter: string_set
///////////////////////////////////////////////////////////////
cellpoint make_string(int k, cellpoint ch)
{
	if (!memory_enough(k/2 + 1)){
		//store the args
		car_set(allocons, ch);
		cdr_set(allocons, NIL);
		//call garbage collection
		garbage_collection();
		//restore the args
		ch = car(allocons);
	}
 	
    cellpoint cpstr = make_atom(ATOM_BIT|STRING_BIT, k);
	int i;

	for (i=0; i < k; i += 2){
		if (i+1 == k){
			cons(ch, NIL);
		}else {
			cons(ch, ch);
		}
	}
    return cpstr;
}
cellpoint is_string(cellpoint cp)
{
    if (is_atom(cp) && (atom_type(cp) & STRING_BIT)){
		return a_true;
	}else {
		return a_false;
	}
}
int string_len(cellpoint str)
{
	return cdr(str);
}
cellpoint string_ref(cellpoint str, int ind)
{
	if (ind < 0 || ind >= string_len(str)){
        printf("Error: the index %d out of the range. The length of string is %d. -- STRING-REF\n", ind, string_len(str));
		error_handler();
    }
	cellpoint s = str + ind / 2 + 1;
	if (ind % 2 == 0){
		return car(s);
	}else {
		return cdr(s);
	}
}
void string_set(cellpoint str, int ind, cellpoint ch)
{
    if (ind < 0 || ind >= string_len(str)){
        printf("Error: the index %d out of the range. The length of string is %d.-- STRING-SET\n", ind, string_len(str));
		error_handler();
    }
	cellpoint s = str + ind / 2 + 1;
	if (ind % 2 == 0){
		car_set(s, ch);
	}else {
		cdr_set(s, ch);
	}
}
cellpoint chars_2_string(char *str)
{
    int i,len = strlen(str);
    cellpoint cpstr = make_string(len, '\0');
 
	for (i=0; i < len; ++i){
		string_set(cpstr, i, make_char(*(str+i)));
	}
    return cpstr;
}
char *get_string(cellpoint str)
{
	int i;
	int len = string_len(str);
	char *s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL){
		printf("Error: malloc error.\n");
		error_handler();
	}
	for (i=0; i < len; ++i){
		*(s+i) = get_char(string_ref(str, i));
	}
	*(s+len) = '\0';
	return s;
}

/////////////////////////////////////////////////////////
//vector
//maker: make_vector
//predicate: is_vector
//sellector: vector_ref
//setter: vector_set
/////////////////////////////////////////////////////////
cellpoint make_vector(int num, cellpoint fill)
{
	if (!memory_enough(num/2 + 1)){
		//store the args
		car_set(allocons, fill);
		cdr_set(allocons, NIL);
		//call garbage collection
		garbage_collection();
		//restore the args
		fill = car(allocons);
	}

    cellpoint cpv = make_atom(ATOM_BIT|VECTOR_BIT, num);
    int i;
	
    for (i=0; i < num; i = i+2){
        if (i+1 == num){
            cons(fill, NIL);
        } else{
            cons(fill, fill);
        }
    }
    return cpv;
}
cellpoint is_vector(cellpoint point)
{
    if (is_atom(point) && (atom_type(point) & VECTOR_BIT)){
		return a_true;
	}else {
		return a_false;
	}
}
int vector_len(cellpoint vec)
{
	return cdr(vec);
}
cellpoint vector_ref(cellpoint vec, int ind)
{
    if (ind < 0 || ind >= vector_len(vec)){
        printf("Error: the index %d out of the range. The length of vector is %d.\n", ind, vector_len(vec));
		error_handler();
    }
    cellpoint v = vec + ind/2 + 1;
    if (ind % 2 == 0){
        return car(v);
    } else{
		return cdr(v);
    }
}
void vector_set(cellpoint vec, int ind, cellpoint np)
{
    if (ind < 0 || ind >= vector_len(vec)){
        printf("Error: the index %d out of the range. The length of vector is %d.\n", ind, vector_len(vec));
		error_handler();
    }
    cellpoint v = vec + ind/2 + 1;
    if (ind % 2 == 0){
        car_set(v, np);
    } else{
        cdr_set(v, np);
    }
}

////////////////////////////////////////////////////////////////////////
//primitive procedure
//maker: make_prim_proc
//predicate: is_prim_proc
//selector: prim_proc_obj
////////////////////////////////////////////////////////////////////////
cellpoint make_prim_proc(cellpoint pname, prim_proc_t pp)
{
	if (!memory_enough(1)){
		//store the args
		car_set(allocons, pname);
		cdr_set(allocons, NIL);
		//calls garbage collection
		garbage_collection();
		//restore the args
		pname = car(allocons);
	}
	return make_atom(ATOM_BIT|PRIM_PROC_BIT, cons(pname, (uint)pp));
}
cellpoint is_prim_proc(cellpoint obj)
{
	if (is_atom(obj) && (atom_type(obj) & PRIM_PROC_BIT)){
		return a_true;
	}else {
		return a_false;
	}
}
prim_proc_t prim_proc_obj(cellpoint obj)
{
	return (prim_proc_t)cdr(cdr(obj));
}

////////////////////////////////////////////////////////////////////////
//compound procedure
//maker: make_procedure
//predicate: is_compound_proc
////////////////////////////////////////////////////////////////////////

//three args: args, body & env
cellpoint make_procedure(void)
{
	reg = cons(args_ref(3), NIL);
	reg = cons(args_ref(2), reg);
	reg = cons(args_ref(1), reg);
	reg = cons(NIL, reg);
	if (!memory_enough(1)){
		//calls garbage collection
		garbage_collection();
	}
	reg = make_atom(ATOM_BIT|COMP_PROC_BIT, reg);
	args_pop(3);
	return reg;
}
cellpoint is_compound_proc(cellpoint obj)
{
	if (is_atom(obj) && (atom_type(obj) & COMP_PROC_BIT)){
		return a_true;
	}else {
		return a_false;
	}
}
