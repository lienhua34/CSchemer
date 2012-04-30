#include "common.h"
#include "argcheck.h"

//////////////////////////////////////////////////////////////////
//This file contains various primitive procedures which control 
//the flow of program execution in special ways.
//////////////////////////////////////////////////////////////////

//procedure?
cellpoint proc_pred_proc(cellpoint arglst)
{
	check_arglst_len_eq("procedure?", 1, arglst);
	return is_procedure(car(arglst));
}

//apply
static cellpoint combine_args(cellpoint arglst)
{
	if (is_true(is_null(cdr(arglst)))){
		cellpoint last_arg = car(arglst);
		if (is_false(is_list(last_arg))){
			printf("Error: the procedure \"apply\" expects the last argument must be a list, but given: ");
			write(last_arg);
			newline();
			error_handler();
		}
		return last_arg;
	}else {
		return cons(car(arglst), combine_args(cdr(arglst)));
	}
}
cellpoint apply_proc(cellpoint arglst)
{
	int len;
	args_push(arglst);
	len = get_integer(list_len());
	if (len < 2){
		printf("Error: the procedure \"apply\" expects at least 2 arguments.\n");
		error_handler();
	}
	check_arg_type("apply", "first", car(arglst), PROCEDURE_T);

	args_push(a_false);
	args_push(combine_args(cdr(arglst)));
	args_push(car(arglst));
	return apply();
}



