#include "common.h"
#include "argcheck.h"

////////////////////////////////////////////////////////////////
//vector standard procedure
////////////////////////////////////////////////////////////////

///vector?
cellpoint vector_pred_proc(cellpoint arglst)
{
	check_arglst_len_eq("vector?", 1, arglst);

	return is_vector(car(arglst));
}
///make-vector
cellpoint make_vector_proc(cellpoint arglst)
{
	int len;
	args_push(arglst);
	len = get_integer(list_len());
	if (len == 1){
		reg = NIL;
	}else if (len == 2){
		reg = car(cdr(arglst));
	}else {
		printf("Error: procedure \"make-vector\" expects one or two arguments, but given %d.\n", len);
		error_handler();
	}

	check_arg_type("make-vector", "first", car(arglst), INTEGER_T);
	
	return make_vector(get_integer(car(arglst)), reg);
}
///vector
cellpoint vector_proc(cellpoint arglst)
{
	args_push(arglst);
	return vector();
}
///vector-length
cellpoint vector_length_proc(cellpoint arglst)
{
	check_arglst_len_eq("vector-length", 1, arglst);
	check_arg_type("vector-length", "first", car(arglst), VECTOR_T);

	return make_integer(vector_len(car(arglst)));
}
///vector-ref
cellpoint vector_ref_proc(cellpoint arglst)
{
	check_arglst_len_eq("vector-ref", 2, arglst);
	cellpoint farg = car(arglst);
	cellpoint sarg = car(cdr(arglst));
	check_arg_type("vector-ref", "first", farg, VECTOR_T);
	check_arg_type("vector-ref", "first", sarg, INTEGER_T);
	
	return vector_ref(farg, get_integer(sarg));
}
///vector-set!
cellpoint vector_set_proc(cellpoint arglst)
{
	check_arglst_len_eq("vector-set!", 3, arglst);
	cellpoint farg = car(arglst);
	cellpoint sarg = car(cdr(arglst));
	cellpoint targ = car(cdr(cdr(arglst)));
	check_arg_type("vector-set!", "first", farg, VECTOR_T);
	check_arg_type("vector-set!", "second", sarg, INTEGER_T);

	vector_set(farg, get_integer(sarg), targ);
	return make_symbol("ok");
}
///vector->list
cellpoint vector_2_list_proc(cellpoint arglst)
{
	check_arglst_len_eq("vector->list", 1, arglst);
	check_arg_type("vector->list", "first", car(arglst), VECTOR_T);

	args_push(car(arglst));
	return vector_2_list();
}
///list->vector
cellpoint list_2_vector_proc(cellpoint arglst)
{
	check_arglst_len_eq("list->vector", 1, arglst);
	check_arg_type("list->vector", "first", car(arglst), LIST_T);

	args_push(car(arglst));
	return list_2_vector();
}
///vector-fill!
cellpoint vector_fill_proc(cellpoint arglst)
{
	check_arglst_len_eq("vector-fill!", 2, arglst);
	check_arg_type("vector-fill!", "first", car(arglst), VECTOR_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	vector_fill();
	return make_symbol("ok");
}
