#include "common.h"

/*************************************************************
 *This file provides procedures operating vector objects.
 *************************************************************/

//one arg: arglst
cellpoint vector(void)
{
    int len, i=0;
	
	args_push(args_ref(1));
	len = get_integer(list_len());
    reg = make_vector(len, NIL);
	stack_push(&vars_stack, args_ref(1));
    while (is_false(is_null(stack_top(&vars_stack)))){
		vector_set(reg, i, car(stack_top(&vars_stack)));
		++i;
		stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
    }
	stack_pop(&vars_stack);
	args_pop(1);
    return reg;
}
//two args: vec1 & vec2
cellpoint vector_eq(void)
{
    int len1 = vector_len(args_ref(1));
    int len2 = vector_len(args_ref(2));
    int i;

    if (args_ref(1) == args_ref(2)){
		args_pop(2);
        return a_true;
    }

    if (len1 != len2){
		args_pop(2);
        return a_false;
    }

    for (i=0; i < len1; ++i){
		reg = vector_ref(args_ref(1), i);
		args_push(vector_ref(args_ref(2), i));
		args_push(reg);
		reg = equal();
        if (is_false(reg)){
            args_pop(2);
			return a_false;
        }
    }
	args_pop(2);
    return a_true;
}
//one arg: vec
cellpoint vector_2_list(void)
{
	int i, len = vector_len(args_ref(1));
	
	reg = NIL;
	for (i=len-1; i >= 0; --i){
		reg = cons(vector_ref(args_ref(1), i), reg);
	}
	args_pop(1);
	return reg;
}
//one arg: lst
cellpoint list_2_vector(void)
{
	args_push(args_ref(1));
	reg = vector();
	args_pop(1);
	return reg;
}
//two args: vec & fill
void vector_fill(void)
{
	int i, len;
	
	reg = args_ref(1);
	len = vector_len(reg);
	for (i=0; i < len; ++i){
		vector_set(reg, i, args_ref(2));
	}
	args_pop(1);
}
