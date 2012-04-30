#include "common.h"
#include "argcheck.h"

///////////////////////////////////////////////////////////////////////
//number standard procedure
///////////////////////////////////////////////////////////////////////
///integer?
cellpoint integer_pred_proc(cellpoint arglst)
{
    check_arglst_len_eq("integer?", 1, arglst);

	return is_integer(car(arglst));
}
///number?
cellpoint number_pred_proc(cellpoint arglst)
{
    check_arglst_len_eq("number?", 1, arglst);

	return is_number(car(arglst));
}
///=
cellpoint number_eq_proc(cellpoint arglst)
{
    check_arglst_len_eq("=", 2, arglst);
	check_arg_type("=", "first", car(arglst), NUMBER_T);
	check_arg_type("=", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return number_eq();
}
///<
cellpoint number_less_proc(cellpoint arglst)
{
	check_arglst_len_eq("<", 2, arglst);
	check_arg_type("<", "first", car(arglst), NUMBER_T);
	check_arg_type("<", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return number_less();
}
///>
cellpoint number_greater_proc(cellpoint arglst)
{
	check_arglst_len_eq(">", 2, arglst);
	check_arg_type(">", "first", car(arglst), NUMBER_T);
	check_arg_type(">", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return number_greater();
}
///<=
cellpoint number_less_eq_proc(cellpoint arglst)
{
 	check_arglst_len_eq("<=", 2, arglst);
	check_arg_type("<=", "first", car(arglst), NUMBER_T);
	check_arg_type("<=", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return number_less_eq();
}
///>=
cellpoint number_greater_eq_proc(cellpoint arglst)
{
	check_arglst_len_eq(">=", 2, arglst);
	check_arg_type(">=", "first", car(arglst), NUMBER_T);
	check_arg_type(">=", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return number_greater_eq();
}
///+
cellpoint add_proc(cellpoint arglst)
{
	check_arglst_len_eq("+", 2, arglst);
	check_arg_type("+", "first", car(arglst), NUMBER_T);
	check_arg_type("+", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return add();
}
///-
cellpoint sub_proc(cellpoint arglst)
{
	check_arglst_len_eq("-", 2, arglst);
	check_arg_type("-", "first", car(arglst), NUMBER_T);
	check_arg_type("-", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return sub();
}
///*
cellpoint mul_proc(cellpoint arglst)
{
	check_arglst_len_eq("*", 2, arglst);
	check_arg_type("*", "first", car(arglst), NUMBER_T);
	check_arg_type("*", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return mul();
}
///divide
cellpoint div_proc(cellpoint arglst)
{
	check_arglst_len_eq("/", 2, arglst);
	check_arg_type("/", "first", car(arglst), NUMBER_T);
	check_arg_type("/", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return mdiv();
}
///remainder
cellpoint remainder_proc(cellpoint arglst)
{
	check_arglst_len_eq("remainder", 2, arglst);
	check_arg_type("remainder", "first", car(arglst), NUMBER_T);
	check_arg_type("remainder", "second", car(cdr(arglst)), NUMBER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return mremainder();
}
