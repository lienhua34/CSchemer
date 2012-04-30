#include "common.h"
#include "argcheck.h"

/////////////////////////////////////////////////////////////////////////////////
//string interface
/////////////////////////////////////////////////////////////////////////////////
///string?
cellpoint string_pred_proc(cellpoint arglst)
{
    check_arglst_len_eq("string?", 1, arglst);

    return is_string(car(arglst));
}
///make-string
cellpoint make_string_proc(cellpoint arglst)
{
	int len;
	args_push(arglst);
	len = get_integer(list_len());
	if (len == 1){
		reg = make_char('\0');
	}else if (len == 2){
		reg = car(cdr(arglst));
	}else {
		printf("Error: procedure \"make-string\" expects one or two arguments, but given %d.\n", len);
		error_handler();
	}
		   
	check_arg_type("make-string", "first", car(arglst), INTEGER_T);
	check_arg_type("make-string", "second", reg, CHARACTER_T);

	return make_string(get_integer(car(arglst)), reg);
}
///string
cellpoint string_proc(cellpoint arglst)
{
	reg = arglst;
	while (is_false(is_null(reg))){
		if (is_false(is_char(car(reg)))){
			printf("Error: procedure \"string\" requires its arguments must be a list of characters.\n");
			error_handler();
		}
		reg = cdr(reg);
	}
	args_push(arglst);
	return string();
}
///string-length
cellpoint string_length_proc(cellpoint arglst)
{
    check_arglst_len_eq("string-length",1,arglst);
	check_arg_type("string-length", "first", car(arglst), STRING_T);

    return make_integer(string_len(car(arglst)));
}
///string-ref
cellpoint string_ref_proc(cellpoint arglst)
{
    check_arglst_len_eq("string-ref", 2, arglst);
	check_arg_type("string-ref", "first", car(arglst), STRING_T);
	check_arg_type("string-ref", "second", car(cdr(arglst)), INTEGER_T);

    return string_ref(car(arglst), get_integer(car(cdr(arglst))));
}
///string-set
cellpoint string_set_proc(cellpoint arglst)
{
    check_arglst_len_eq("string-set!", 3, arglst);
    cellpoint farg = car(arglst);
    cellpoint sarg = car(cdr(arglst));
    cellpoint targ = car(cdr(cdr(arglst)));
	check_arg_type("string-set!", "first", farg, STRING_T);
	check_arg_type("string-set!", "second", sarg, INTEGER_T);
	check_arg_type("string-set!", "third", targ, CHARACTER_T);

    string_set(farg, get_integer(sarg), targ);
	return make_symbol("ok");
}
///string=?
cellpoint string_eq_proc(cellpoint arglst)
{
    check_arglst_len_eq("string=?", 2, arglst);
    check_arg_type("string=?", "first", car(arglst), STRING_T);
	check_arg_type("string=?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_eq();
}
///string-ci=?
cellpoint string_eq_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("string-ci=?", 2, arglst);
	check_arg_type("string-ci=?", "first", car(arglst), STRING_T);
	check_arg_type("string-ci=?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_eq_ci();
}
///string<?
cellpoint string_less_proc(cellpoint arglst)
{
	check_arglst_len_eq("string<?", 2, arglst);
	check_arg_type("string<?", "first", car(arglst), STRING_T);
	check_arg_type("string<?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_less();
}
///string>?
cellpoint string_greater_proc(cellpoint arglst)
{
	check_arglst_len_eq("string>?", 2, arglst);
	check_arg_type("string>?", "first", car(arglst), STRING_T);
	check_arg_type("string>?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_greater();
}
///string<=?
cellpoint string_less_eq_proc(cellpoint arglst)
{
	check_arglst_len_eq("string<=?", 2, arglst);
	check_arg_type("string<=?", "first", car(arglst), STRING_T);
	check_arg_type("string<=?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_less_eq();
}
///string>=?
cellpoint string_greater_eq_proc(cellpoint arglst)
{
	check_arglst_len_eq("string>=?", 2, arglst);
	check_arg_type("string>=?", "first", car(arglst), STRING_T);
	check_arg_type("string>=?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_greater_eq();
}
///string-ci<?
cellpoint string_less_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("string-ci<?", 2, arglst);
	check_arg_type("string-ci<?", "first", car(arglst), STRING_T);
	check_arg_type("string-ci<?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_less_ci();
}
///string-ci>?
cellpoint string_greater_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("string-ci>?", 2, arglst);
	check_arg_type("string-ci>?", "first", car(arglst), STRING_T);
	check_arg_type("string-ci>?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_greater_ci();
}
///string-ci<=?
cellpoint string_less_eq_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("string-ci<=?", 2, arglst);
	check_arg_type("string-ci<=?", "first", car(arglst), STRING_T);
	check_arg_type("string-ci<=?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_less_eq_ci();
}
///string-ci>=?
cellpoint string_greater_eq_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("string-ci>=?", 2, arglst);
	check_arg_type("string-ci>=?", "first", car(arglst), STRING_T);
	check_arg_type("string-ci>=?", "second", car(cdr(arglst)), STRING_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return string_greater_eq_ci();
}
///substring
cellpoint substring_proc(cellpoint arglst)
{
	check_arglst_len_eq("substring", 3, arglst);
	check_arg_type("substring", "first", car(arglst), STRING_T);
	check_arg_type("substring", "second", car(cdr(arglst)), INTEGER_T);
	check_arg_type("substring", "third", car(cdr(cdr(arglst))), INTEGER_T);

	args_push(car(cdr(cdr(arglst))));
	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return substring();
}
///string-append
cellpoint string_append_proc(cellpoint arglst)
{
	args_push(arglst);
	return string_append();
}
///string->list
cellpoint string_2_list_proc(cellpoint arglst)
{
	check_arglst_len_eq("string->list", 1, arglst);
	check_arg_type("string->list", "first", car(arglst), STRING_T);

	args_push(car(arglst));
	return string_2_list();
}
///list->string
cellpoint list_2_string_proc(cellpoint arglst)
{
	check_arglst_len_eq("list->string", 1 ,arglst);
	reg = car(arglst);
	check_arg_type("list->string", "first", reg, LIST_T);

	while (is_false(is_null(reg))){
		if (is_false(is_char(car(reg)))){
			printf("Error: procedure \"list->string\" requires a list of characters.\n");
			error_handler();
		}
		reg = cdr(reg);
	}
	args_push(car(arglst));
	return list_2_string();
}
///string-copy
cellpoint string_copy_proc(cellpoint arglst)
{
	check_arglst_len_eq("string-copy", 1, arglst);
	check_arg_type("string-copy", "first", car(arglst), STRING_T);

	args_push(car(arglst));
	return string_copy();
}
///string-fill
cellpoint string_fill_proc(cellpoint arglst)
{
	check_arglst_len_eq("string-fill", 2, arglst);
	check_arg_type("string-fill", "first", car(arglst), STRING_T);
	check_arg_type("string-fill", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	string_fill();
	return make_symbol("ok");
}
