#include "common.h"

/*************************************************************
 *This file provides procedures operating list objects
 *************************************************************/

cellpoint is_list(cellpoint point)
{
    if (is_true(is_null(point))){
        return a_true;
    }else if (is_true(is_pair(point))){
		while (is_true(is_pair(point))){
			point = cdr(point);
		}
		if (is_true(is_null(point))){
			return a_true;
		}else {
			return a_false;
		}
	}else {
        return a_false;
    }
}
//two args: lst1 & lst2
cellpoint list_eq(void)
{
    if (args_ref(1) == args_ref(2)){
		args_pop(2);
        return a_true;
    }

	stack_push(&vars_stack, args_ref(1));
	reg = args_ref(2);
    while (is_false(is_null(stack_top(&vars_stack))) && 
		   is_false(is_null(reg))){
		//compare the car of lst1 & lst2
		args_push(car(reg));
		args_push(car(stack_top(&vars_stack)));
		stack_push(&vars_stack, reg);
		reg = equal();
        if (is_false(reg)){
			reg = stack_pop(&vars_stack);
			break;
        }
        reg = cdr(stack_pop(&vars_stack));
		stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
    }
    if (is_true(is_null(stack_pop(&vars_stack))) && 
		is_true(is_null(reg))){
		reg = a_true;
    }else {
		reg = a_false;
    }
	args_pop(2);
	return reg;
}
//one arg: arglst
cellpoint list(void)
{
	reg = args_ref(1);
	stack_push(&vars_stack, NIL);
	while (is_false(is_null(reg))){
		stack_push(&vars_stack, cons(car(reg), stack_pop(&vars_stack)));
		reg = cdr(reg);
	}
	reg = stack_pop(&vars_stack);
	args_push(reg);
	reg = reverse();
	args_pop(1);
	return reg;
}
//one arg: lst
cellpoint list_len(void)
{
    int len = 0;
	reg = args_ref(1);
	while (is_false(is_null(reg))){
		++len;
		reg = cdr(reg);
	}
	args_pop(1);
    return make_integer(len);
}
//one arg: arglst
cellpoint append(void)
{
	reg = args_ref(1);
	if (is_true(is_null(reg))){
		reg = args_ref(1);
	}else if (is_true(is_null(cdr(reg)))){
		reg = car(args_ref(1));
	}else {
		//computes the reverse of the first list
		reg = car(args_ref(1));
		if (is_false(is_list(reg))){
			printf("Error: procedure \"append\" requires its arguments must be a list. but give a argument ");
			write(reg);
			error_handler();
			args_pop(1);
			return NIL;
		}
		args_push(reg);
		reg = reverse();
		stack_push(&vars_stack, reg);
		//appends the rest lists
		args_push(cdr(args_ref(1)));
		reg = append();
		//appends the the reversed first list to the rest lists 
		while (is_false(is_null(stack_top(&vars_stack)))){
			reg = cons(car(stack_top(&vars_stack)), reg);
			stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
		}
		stack_pop(&vars_stack);
	}
	args_pop(1);
	return reg;
}
//one args: lst
cellpoint reverse(void)
{
	stack_push(&vars_stack, NIL);
	reg = args_ref(1);
	while (is_false(is_null(reg))){
		stack_push(&vars_stack, cons(car(reg), stack_pop(&vars_stack)));
		reg = cdr(reg);
	}
	reg = stack_pop(&vars_stack);
	args_pop(1);
	return reg;
}
//two args: lst & k
cellpoint list_tail(void)
{
    int count = get_integer(args_ref(2));
	reg = args_ref(1);
    while (count > 0){
        if (is_true(is_null(reg))){
            printf("Error:the parameter list has fewer than %d elements. --LIST-TAIL\n", get_integer(args_ref(2)));
			error_handler();
        }
		reg = cdr(reg);
        --count;
    }
	args_pop(2);
    return reg;
}
//two args: lst & k
cellpoint list_ref(void)
{
    int count = get_integer(args_ref(2));
	reg = args_ref(1);
    while (count > 0){
        if (is_true(is_null(reg))){
            printf("Error:the parameter list has fewer than %d elements. --LIST-REF\n", get_integer(args_ref(2)));
			error_handler();
        }
        reg = cdr(reg);
        --count;
    }
	args_pop(2);
    return car(reg);
}
//two args: obj & lst
cellpoint member(cellpoint (*eqfunc)(void))
{
	stack_push(&vars_stack, args_ref(2));
	while (is_false(is_null(stack_top(&vars_stack)))){
		//compares the obj & the car of reg
		reg = args_ref(1);
		args_push(car(stack_top(&vars_stack)));
		args_push(reg);
		reg = eqfunc();
		if (is_true(reg)){
			args_pop(2);
			return stack_pop(&vars_stack);
		}
		stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
	}
	stack_pop(&vars_stack);
	args_pop(2);
	return a_false;
}
//two args: obj & alist
cellpoint assoc(cellpoint (*eqfunc)(void))
{
	stack_push(&vars_stack, args_ref(2));
	while (is_false(is_null(stack_top(&vars_stack)))){
		//compares the obj & the car of the car of reg
		reg = args_ref(1);
		args_push(car(car(stack_top(&vars_stack))));
		args_push(reg);
		reg = eqfunc();
		if (is_true(reg)){
			args_pop(2);
			return car(stack_pop(&vars_stack));
		}
		stack_push(&vars_stack, cdr(stack_pop(&vars_stack)));
	}
	stack_pop(&vars_stack);
	args_pop(2);
	return a_false;
}

