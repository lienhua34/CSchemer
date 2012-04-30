#include "common.h"

/*************************************************************
 *This file implements garbage collection mechanism.
 *two global functions:
 *  gc_init: inits the root list to hold the major variables
 *  garbage_collection: activates garbage collection mechanism
 *the main variable: 
 *  root: a list, holds the major variables. When garbage collection
 *mechanism is activated, we can reach all usable objects with car & cdr 
 *operators starting from root.
 *************************************************************/

extern struct cons_cell *the_cons_cells;
extern struct cons_cell *free_cons_cells;
extern cellpoint free_point;

#define BROKEN_HEART 0xFFFFFFF
static cellpoint root = NIL;
static cellpoint scan;

void gc_init(void)
{
	//preallocate a list of gc and set it to root
	root = cons(a_false, NIL);
	root = cons(a_true, root);
	root = cons(reg, root);
	root = cons(obarray, root);
	root = cons(state_constants, root);
	root = cons(current_state, root);
	root = cons(state_stack, root);
	root = cons(parser_stack, root);
	root = cons(vars_stack, root);
	root = cons(args_stack, root);
	root = cons(env_stack, root);
	root = cons(current_env, root);
	root = cons(allocons, root);
	root = cons(the_global_env, root);
}
static cellpoint cons_infree(cellpoint addr, cellpoint decre)
{
	free_cons_cells[free_point].car = addr;
	free_cons_cells[free_point].cdr = decre;
//	printf("cons_infree:%d\n", free_point);
	return free_point++;
}
static cellpoint car_infree(cellpoint p)
{
	return free_cons_cells[p].car;
}
static cellpoint cdr_infree(cellpoint p)
{
	return free_cons_cells[p].cdr;
}
static void car_set_infree(cellpoint p, cellpoint n)
{
	free_cons_cells[p].car = n;
}
static void cdr_set_infree(cellpoint p, cellpoint n)
{
	free_cons_cells[p].cdr = n;
}
static boolean is_broken_heart(uint p)
{
	return (p == BROKEN_HEART) ? true : false;
}
static boolean gc_finished(void)
{
	return (scan >= free_point) ? true : false;
}
static cellpoint relocate_string(cellpoint old)
{
	int len = string_len(old);
	int i;
	cellpoint fp = cons_infree(car(old), cdr(old));
	//copy the characters sequence
	for (i=0; i < len; i += 2){
		if (i+1 == len){
			cons_infree(string_ref(old,i), NIL);
		}else {
			cons_infree(string_ref(old,i), string_ref(old, i+1));
		}
	}
	//set broken heart
	car_set(old, BROKEN_HEART);
	//set forward point
	cdr_set(old, fp);
	return fp;
}
static cellpoint relocate_vector(cellpoint old)
{
	int len = vector_len(old);
	int i;
	cellpoint fp = cons_infree(car(old), cdr(old));
	
	for (i=0; i < len; i += 2){
		if (i+1 == len){
			cons_infree(vector_ref(old,i), NIL);
		}else {
			cons_infree(vector_ref(old,i), vector_ref(old, i+1));
		}
	}
	//set broken heart
	car_set(old, BROKEN_HEART);
	//set forward point
	cdr_set(old, fp);
	return fp;
}
static cellpoint relocate_procedure(cellpoint old)
{
	cellpoint fp, p;
	fp = cons_infree(car(old), cdr(old));
	p = cons_infree(car(cdr(old)), cdr(cdr(old)));
	cdr_set_infree(fp, p);
	//set broken heart
	car_set(old, BROKEN_HEART);
	//set forward point
	cdr_set(old, fp);
	return fp;
}
static cellpoint relocate_cell(cellpoint old)
{
	if (is_true(is_null(old))){
		return NIL;
	}
	if (is_broken_heart(car(old))){
		return cdr(old);
	}else {
		cellpoint fp = NIL;
		if (is_true(is_pair(old))){
			fp = cons_infree(car(old), cdr(old));
			//set broken-heart
			car_set(old, BROKEN_HEART);
			//set forward point
			cdr_set(old, fp);
			return fp;
		}else {
			if (is_true(is_string(old))){
				return relocate_string(old);
			}else if (is_true(is_vector(old))){
				return relocate_vector(old);
			}else if (is_true(is_procedure(old))){
				return relocate_procedure(old);
			}else {
				fp = cons_infree(car(old), cdr(old));
				//set broken heart
				car_set(old, BROKEN_HEART);
				//set forward point
				cdr_set(old, fp);
				return fp;
			}
		}
	}
}
static void set_root(void)
{
	cellpoint r = root;
	//set the_global_env
	car_set(r, the_global_env);
	//set allocons
	r = cdr(r);
	car_set(r, allocons);
	//set current_env
	r = cdr(r);
	car_set(r, current_env);
	//set env_stack
	r = cdr(r);
	car_set(r, env_stack);
	//set args_stack
	r = cdr(r);
	car_set(r, args_stack);
	//set vars_stack
	r = cdr(r);
	car_set(r, vars_stack);
	//set parser_stack
	r = cdr(r);
	car_set(r, parser_stack);
	//set state_stack
	r = cdr(r);
	car_set(r, state_stack);
	//set current_state
	r = cdr(r);
	car_set(r, current_state);
	//set state_constants
	r = cdr(r);
	car_set(r, state_constants);
	//set obarray
	r = cdr(r);
	car_set(r, obarray);
	//set reg
	r = cdr(r);
	car_set(r, reg);
	//set a_true
	r = cdr(r);
	car_set(r, a_true);
	//set a_false
	r = cdr(r);
	car_set(r, a_false);
}
static void reassign_root(void)
{
	root = relocate_cell(root);
}
static void gc_flip(void)
{
	cellpoint r;
	//exchange the working memory and the free memory
	struct cons_cell *tmp = the_cons_cells;
	the_cons_cells = free_cons_cells;
	free_cons_cells = tmp;
	if (!memory_enough(1)){
		printf("Error: run out of memory!\n");
		exit(-1);
	}

	//restore the_global_env
	r = root;
	the_global_env = car(r);
	//restore allocons
	r = cdr(r);
	allocons = car(r);
	//restore current_env
	r = cdr(r);
	current_env = car(r);
	//restore env_stack
	r = cdr(r);
	env_stack = car(r);
	//restore args_stack
	r = cdr(r);
	args_stack = car(r);
	//restore vars_stack
	r = cdr(r);
	vars_stack = car(r);
	//restore parser_stack
	r = cdr(r);
	parser_stack = car(r);
	//restore state_stack
	r = cdr(r);
	state_stack = car(r);
	//restore current_state
	r = cdr(r);
	current_state = car(r);
	//restore state_constants
	r = cdr(r);
	state_constants = car(r);
	set_state_constants();
	//restore obarray
	r = cdr(r);
	obarray = car(r);
	//restore reg
	r = cdr(r);
	reg = car(r);
	//restore a_true
	r = cdr(r);
	a_true = car(r);
	//restore a_false
	r = cdr(r);
	a_false = car(r);
}
void garbage_collection(void)
{
	printf("gc starting.\n");
	set_root();
	//reassign the root in the free memory
	free_point = 1;
	reassign_root();
	scan = root;
	while (!gc_finished()){
		if (car_infree(scan) & ATOM_BIT){
			if (car_infree(scan) & PRIM_PROC_BIT){
				//if the scan is a primitive procedure, copy its name
				++scan;
				car_set_infree(scan, relocate_cell(car_infree(scan)));
			}
		}else {
			cellpoint fp = NIL;
			fp = relocate_cell(car_infree(scan));
			car_set_infree(scan, fp);
			fp = relocate_cell(cdr_infree(scan));
			cdr_set_infree(scan, fp);
		}
		++scan;
	}
	gc_flip();
	printf("gc finished\n");
}
