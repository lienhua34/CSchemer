#include "common.h"
#include "stdproc.h"

/*************************************************************
 *This file provides procedures operating environment
 *************************************************************/

////////////////////////////////////////////////////////
//frame
////////////////////////////////////////////////////////

//two args: vars & vals
static cellpoint make_frame(void)
{
	reg = cons(args_ref(1), args_ref(2));
	args_pop(2);
	return reg;
}
//one arg: frame
static cellpoint frame_variables(void)
{
	reg = car(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: frame
static cellpoint frame_values(void)
{
	reg = cdr(args_ref(1));
	args_pop(1);
	return reg;
}
//three args: var, val & frame
static cellpoint add_binding_to_frame(void)
{
	//add var
	args_push(args_ref(3));
	reg = frame_variables();
	reg = cons(args_ref(1), reg);
	car_set(args_ref(3), reg);
	//add val
	args_push(args_ref(3));
	reg = frame_values();
	reg = cons(args_ref(2), reg);
	cdr_set(args_ref(3), reg);
	
	args_pop(3);
	return args_ref(3);
}

////////////////////////////////////////////////////////
//environment
////////////////////////////////////////////////////////
static cellpoint the_empty_env = NIL;

//one arg: env
static cellpoint first_frame(void)
{
	reg = car(args_ref(1));
	args_pop(1);
	return reg;
}
//one arg: env
static cellpoint enclosing_env(void)
{
	reg = cdr(args_ref(1));
	args_pop(1);
	return reg;
}
//there args: vars, vals & base_env
cellpoint extend_env(void)
{
	int len1, len2;
	//vars length
	args_push(args_ref(1));
	reg = list_len();
	len1 = get_integer(reg);
	//vals length
	args_push(args_ref(2));
	reg = list_len();
	len2 = get_integer(reg);
	if (len1 != len2){
		printf("Error: the length of vars(%d) not equal the lengths of vals(%d). --EXTEND_ENV\n", len1, len2);
		error_handler();
	}else {
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = make_frame();
		reg = cons(reg, args_ref(3));
	}
	args_pop(3);
	return reg;
}
//two args: var & env
cellpoint lookup_var_val(void)
{
	//push env
	stack_push(&vars_stack, args_ref(2));
	while (stack_top(&vars_stack) != the_empty_env){
		args_push(stack_top(&vars_stack));
		reg = first_frame();
		stack_push(&vars_stack, reg);
		//get vals
		args_push(stack_top(&vars_stack));
		reg = frame_values();
		//get vars
		args_push(stack_pop(&vars_stack));
		stack_push(&vars_stack, reg);
		reg = frame_variables();
		while (reg != NIL){
			stack_push(&vars_stack, reg);
			args_push(args_ref(1));
			args_push(car(stack_top(&vars_stack)));
			reg = eq();
			if (is_true(reg)){
				stack_pop(&vars_stack);
				//get the car of vals
				reg = car(stack_pop(&vars_stack));
				//pop env
				stack_pop(&vars_stack);
				args_pop(2);
				return reg;
			}
			//renew the vars
			reg = cdr(stack_pop(&vars_stack));
			//renew the vals
			stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
		}
		//pop vals
		stack_pop(&vars_stack);
		//renew env
		args_push(stack_pop(&vars_stack));
		reg = enclosing_env();
		stack_push(&vars_stack, reg);
	}
	printf("Error: unknown variables ");
	display(args_ref(1));
	newline();
	error_handler();
	args_pop(2);
	return NIL;
}
//three args: var, val & env
void define_var(void)
{
	//get first frame
	args_push(args_ref(3));
	reg = first_frame();
	stack_push(&vars_stack, reg);
	//get vals
	args_push(stack_top(&vars_stack));
	reg = frame_values();
	//get vars
	args_push(stack_pop(&vars_stack));
	stack_push(&vars_stack, reg);
	reg = frame_variables();
	while (reg != NIL){
		//push vars
		stack_push(&vars_stack, reg);
		args_push(args_ref(1));
		args_push(car(stack_top(&vars_stack)));
		reg = eq();
		if (is_true(reg)){
			//pop vars
			stack_pop(&vars_stack);
			//set new val
			reg = stack_pop(&vars_stack);
			car_set(reg, args_ref(2));
			args_pop(3);
			return;
		}
		//renew vars
		reg = cdr(stack_pop(&vars_stack));
		//renew vals
		stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
	}
	//pop vals
	stack_pop(&vars_stack);
	//add binding the the first frame
	args_push(args_ref(3));
	reg = first_frame();
	stack_push(&vars_stack, args_ref(1));
	stack_push(&vars_stack, args_ref(2));
	args_push(reg);
	args_push(stack_pop(&vars_stack)); 
	args_push(stack_pop(&vars_stack)); 
	add_binding_to_frame();
	//if the val is a compound procedure, then sets its name
	if (is_true(is_compound_proc(args_ref(2)))){
		//checks whether the procedure has a name
		args_push(args_ref(2));
		reg = procedure_name();
		if (is_true(is_null(reg))){
			reg = args_ref(2);
			args_push(args_ref(1));
			args_push(reg);
			procedure_name_set();
		}
	}
	args_pop(3);
}
//three args: var, val & env
void set_var_val(void)
{
	//push env
	stack_push(&vars_stack, args_ref(3));
	while (stack_top(&vars_stack) != the_empty_env){
		//get first frame
		args_push(stack_top(&vars_stack));
		reg = first_frame();
		stack_push(&vars_stack, reg);
		//get vals
		args_push(stack_top(&vars_stack));
		reg = frame_values();
		//get vars
		args_push(stack_pop(&vars_stack));
		stack_push(&vars_stack, reg);
		reg = frame_variables();
		while (reg != NIL){
			//push vars
			stack_push(&vars_stack, reg);
			args_push(args_ref(1));
			args_push(car(stack_top(&vars_stack)));
			reg = eq();
			if (is_true(reg)){
				//pop vars
				stack_pop(&vars_stack);
				//set new val
				reg = stack_pop(&vars_stack);
				car_set(reg, args_ref(2));
				//pop env
				stack_pop(&vars_stack);
				args_pop(3);
				return;
			}
			//renew vars
			reg = cdr(stack_pop(&vars_stack));
			//renew vals
			stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
		}
		//pop vals
		stack_pop(&vars_stack);
		//renew env
		args_push(stack_pop(&vars_stack));
		reg = enclosing_env();
		stack_push(&vars_stack, reg);
	}
	printf("Error: unknown variable ");
	display(args_ref(1));
	newline();
	error_handler();
	//pop env
	stack_pop(&vars_stack);
	args_pop(3);
}

///////////////////////////////////////////////////////
//setup environment
///////////////////////////////////////////////////////
struct prim_proc_pair{
	char *name;
	prim_proc_t func;
};
static struct prim_proc_pair pparray[] = {
	//pair procedure
	{"pair?", pair_pred_proc},
	{"cons", cons_proc},
	{"car", car_proc},
	{"cdr", cdr_proc},
	{"car-set!", car_set_proc},
	{"cdr-set!", cdr_set_proc},

	//equivalence predicate procedure
	{"eq?", eq_proc},
	{"eqv?", eqv_proc},
	{"equal?", equal_proc},

	//list procedure
	{"null?", null_proc},
	{"list?", list_pred_proc},
	{"list", list_proc},
	{"length", length_proc},
	{"append", append_proc},
	{"reverse", reverse_proc},
	{"list-tail", list_tail_proc},
	{"list-ref", list_ref_proc},
	{"memq", memq_proc},
	{"memv", memv_proc},
	{"member", member_proc},
	{"assq", assq_proc},
	{"assv", assv_proc},
	{"assoc", assoc_proc},
	
	//boolean procedure
	{"boolean?", boolean_pred_proc},
	{"not", boolean_not_proc},

	//character procedure
	{"char?", char_pred_proc},
	{"char=?", char_eq_proc},
	{"char<?", char_less_proc},
	{"char>?", char_greater_proc},
	{"char<=?", char_less_eq_proc},
	{"char>=?", char_greater_eq_proc},
	{"char-ci=?", char_eq_ci_proc},
	{"char-ci<?", char_less_ci_proc},
	{"char-ci>?", char_greater_ci_proc},
	{"char-ci<=?", char_less_eq_ci_proc},
	{"char-ci>=?", char_greater_eq_ci_proc},
	{"char-upper-case?", char_upper_case_proc},
	{"char-lower-case?", char_lower_case_proc},
	{"char-alphabetic?", char_alphabetic_proc},
	{"char-numeric?", char_numeric_proc},
	{"char-whitespace?", char_whitespace_proc},
	{"char->integer", char_2_integer_proc},
	{"integer->char", integer_2_char_proc},
	{"char-upcase", char_upcase_proc},
	{"char-downcase", char_downcase_proc},

	//symbol procedure
	{"symbol?", symbol_pred_proc},
	{"symbol->string", symbol_2_string_proc},
	{"string->symbol", string_2_symbol_proc},
	
	//string procedure
	{"string?", string_pred_proc},
	{"make-string", make_string_proc},
	{"string", string_proc},
	{"string-length", string_length_proc},
	{"string-ref", string_ref_proc},
	{"string-set!", string_set_proc},
	{"string=?", string_eq_proc},
	{"string<?", string_less_proc},
	{"string>?", string_greater_proc},
	{"string<=?", string_less_eq_proc},
	{"string>=?", string_greater_eq_proc},
	{"string-ci=?", string_eq_ci_proc},
	{"string-ci<?", string_less_ci_proc},
	{"string-ci>?", string_greater_ci_proc},
	{"string-ci<=?", string_less_eq_ci_proc},
	{"string-ci>=?", string_greater_eq_ci_proc},
	{"substring", substring_proc},
	{"string-append", string_append_proc},
	{"string->list", string_2_list_proc},
	{"list->string", list_2_string_proc},
	{"string-copy", string_copy_proc},
	{"string-fill!", string_fill_proc},

	//number procedure
	{"integer?", integer_pred_proc},
	{"number?", number_pred_proc},
	{"=", number_eq_proc},
	{"<", number_less_proc},
	{">", number_greater_proc},
	{"<=", number_less_eq_proc},
	{">=", number_greater_eq_proc},
	{"+", add_proc},
	{"-", sub_proc},
	{"*", mul_proc},
	{"/", div_proc},
	{"remainder", remainder_proc},

	//vector procedure
	{"vector?", vector_pred_proc},
	{"make-vector", make_vector_proc},
	{"vector", vector_proc},
	{"vector-length", vector_length_proc},
	{"vector-ref", vector_ref_proc},
	{"vector-set!", vector_set_proc},
	{"vector->list", vector_2_list_proc},
	{"list->vector", list_2_vector_proc},
	{"vector-fill!", vector_fill_proc},

	//output procedures
	{"write", write_proc},
	{"display", display_proc},
	{"newline", newline_proc},
	{"write-char", write_char_proc},
	
	//control procedures
	{"procedure?", proc_pred_proc},
	{"apply", apply_proc}
};

static cellpoint prim_proc_names(void)
{
	int len = sizeof(pparray) / sizeof(struct prim_proc_pair);
	int i;
	reg = NIL;
	for (i=len-1; i >= 0; --i){
		reg = cons(make_symbol(pparray[i].name), reg);
	}
	return reg;
}
static cellpoint prim_proc_objs(void)
{
	int len = sizeof(pparray) / sizeof(struct prim_proc_pair);
	int i;
	reg = NIL;
	for (i = len-1; i >= 0; --i){
		stack_push(&vars_stack, reg);
		reg = make_prim_proc(make_symbol(pparray[i].name), pparray[i].func);
		reg = cons(reg, stack_pop(&vars_stack));
	}
	return reg;
}
cellpoint setup_environment(void)
{
	args_push(the_empty_env);
	args_push(prim_proc_objs());
	args_push(prim_proc_names());
	reg = extend_env();
	return reg;
}
