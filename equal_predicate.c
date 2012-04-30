#include "common.h"

/*************************************************************
 *This file provides three equivalence predicate:
 *    eq?, eqv? & equal?
 *************************************************************/

//two args: obj1 & obj2
cellpoint eq(void)
{
	if (args_ref(1) == args_ref(2)){
		reg = a_true;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: obj1 & obj2
cellpoint eqv(void)
{
    if (is_true(is_boolean(args_ref(1))) && 
		is_true(is_boolean(args_ref(2)))){
        reg = (args_ref(1) == args_ref(2)) ? a_true : a_false;
    }else if (is_true(is_symbol(args_ref(1))) && 
			  is_true(is_symbol(args_ref(2)))){
		reg = (args_ref(1) == args_ref(2)) ? a_true : a_false;
    }else if (is_true(is_number(args_ref(1))) && 
			  is_true(is_number(args_ref(2)))){
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = number_eq();
    }else if (is_true(is_char(args_ref(1))) && 
			  is_true(is_char(args_ref(2)))){
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = char_eq();
    }else if (is_true(is_null(args_ref(1))) && 
			  is_true(is_null(args_ref(2)))){
        reg = a_true;
    }else if (is_true(is_pair(args_ref(1))) && 
			  is_true(is_pair(args_ref(2)))){
		reg = (args_ref(1) == args_ref(2)) ? a_true : a_false;
    }else if (is_true(is_string(args_ref(1))) && 
			  is_true(is_string(args_ref(2)))){
		reg = (args_ref(1) == args_ref(2)) ? a_true : a_false;
    }else if (is_true(is_vector(args_ref(1))) && 
			  is_true(is_vector(args_ref(2)))){
        reg = (args_ref(1) == args_ref(2)) ? a_true : a_false;
    }else if (is_true(is_procedure(args_ref(1))) && 
			  is_true(is_procedure(args_ref(2)))){
		reg = (args_ref(1) == args_ref(2)) ? a_true : a_false;
	}else {
		reg = a_false;
	}
	args_pop(2);
	return reg;
}
//two args: obj1 & obj2
cellpoint equal(void)
{
    if (is_true(is_string(args_ref(1))) && 
		is_true(is_string(args_ref(2)))){
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = string_eq();
    }else if (is_true(is_vector(args_ref(1))) && 
			  is_true(is_vector(args_ref(2)))){
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = vector_eq();
    }else if (is_true(is_list(args_ref(1))) && 
			  is_true(is_list(args_ref(2)))){
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = list_eq();
	}else {
		reg = args_ref(1);
		args_push(args_ref(2));
		args_push(reg);
		reg = eqv();
	}
	args_pop(2);
	return reg;
}
