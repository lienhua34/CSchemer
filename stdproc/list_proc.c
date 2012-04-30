#include "common.h"
#include "argcheck.h"

///////////////////////////////////////////////////////////////
//list standard procedure
///////////////////////////////////////////////////////////////

///null?
cellpoint null_proc(cellpoint arglst)
{
	check_arglst_len_eq("null?", 1, arglst);

	return is_null(car(arglst));
}
///list?
cellpoint list_pred_proc(cellpoint arglst)
{
	check_arglst_len_eq("list?", 1, arglst);

	return is_list(car(arglst));
}
///list
cellpoint list_proc(cellpoint arglst)
{
	args_push(arglst);
	return list();
}
///length
cellpoint length_proc(cellpoint arglst)
{
	check_arglst_len_eq("length", 1, arglst);
	check_arg_type("length", "first", car(arglst), LIST_T);

	args_push(car(arglst));
	return list_len();
}
///append
cellpoint append_proc(cellpoint arglst)
{
	args_push(arglst);
	return append();
}
///reverse
cellpoint reverse_proc(cellpoint arglst)
{
	check_arglst_len_eq("reverse", 1, arglst);
	check_arg_type("reverse", "first", car(arglst), LIST_T);

	args_push(car(arglst));
	return reverse();
}
///list-tail
cellpoint list_tail_proc(cellpoint arglst)
{
	check_arglst_len_eq("list-tail", 2, arglst);
	check_arg_type("list-tail", "first", car(arglst), LIST_T);
	check_arg_type("list-tail", "second", car(cdr(arglst)), INTEGER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return list_tail();
}
///list-ref
cellpoint list_ref_proc(cellpoint arglst)
{
	check_arglst_len_eq("list-ref", 2, arglst);
	check_arg_type("list-ref", "first", car(arglst), LIST_T);
	check_arg_type("list-ref", "second", car(cdr(arglst)), INTEGER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return list_ref();
}
///memq
cellpoint memq_proc(cellpoint arglst)
{
	check_arglst_len_eq("memq", 2, arglst);
	check_arg_type("memq", "second", car(cdr(arglst)), LIST_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return member(eq);
}
///memv
cellpoint memv_proc(cellpoint arglst)
{
	check_arglst_len_eq("memv", 2, arglst);
	check_arg_type("memv", "second", car(cdr(arglst)), LIST_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return member(eqv);
}
///member
cellpoint member_proc(cellpoint arglst)
{
	check_arglst_len_eq("member", 2, arglst);
	check_arg_type("member", "second", car(cdr(arglst)), LIST_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return member(equal);
}
///assq
cellpoint assq_proc(cellpoint arglst)
{
	check_arglst_len_eq("assq", 2, arglst);
	check_arg_type("assq", "second", car(cdr(arglst)), LIST_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return assoc(eq);
}
///assv
cellpoint assv_proc(cellpoint arglst)
{
	check_arglst_len_eq("assv", 2, arglst);
	check_arg_type("assv", "second", car(cdr(arglst)), LIST_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return assoc(eqv);
}
///assoc
cellpoint assoc_proc(cellpoint arglst)
{
	check_arglst_len_eq("assoc", 2, arglst);
	check_arg_type("assoc", "second", car(cdr(arglst)), LIST_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return assoc(equal);
}
