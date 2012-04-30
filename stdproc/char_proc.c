#include "common.h"
#include "argcheck.h"

//////////////////////////////////////////////////////////////////
//character interface
//////////////////////////////////////////////////////////////////

///character?
cellpoint char_pred_proc(cellpoint arglst)
{
    check_arglst_len_eq("character?", 1, arglst);

    return is_char(car(arglst));
}
///char=?
cellpoint char_eq_proc(cellpoint arglst)
{
    check_arglst_len_eq("char=?", 2, arglst);
	check_arg_type("char=?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char=?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
    return char_eq();
}
///char<?
cellpoint char_less_proc(cellpoint arglst)
{
	check_arglst_len_eq("char<?", 2, arglst);
	check_arg_type("char<?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char<?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_less();
}
///char>?
cellpoint char_greater_proc(cellpoint arglst)
{
	check_arglst_len_eq("char>?", 2, arglst);
	check_arg_type("char>?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char>?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_greater();
}
///char<=?
cellpoint char_less_eq_proc(cellpoint arglst)
{
	check_arglst_len_eq("char<=?", 2, arglst);
	check_arg_type("char<=?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char<=?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_less_eq();
}
///char>=?
cellpoint char_greater_eq_proc(cellpoint arglst)
{
	check_arglst_len_eq("char>=?", 2, arglst);
	check_arg_type("char>=?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char>=?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_greater_eq();
}
///char-ci=?
cellpoint char_eq_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-ci=?", 2, arglst);
	check_arg_type("char-ci=?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char-ci=?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_eq_ci();
}
///char-ci<?
cellpoint char_less_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-ci<?", 2, arglst);
	check_arg_type("char-ci<?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char-ci<?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_less_ci();
}
///char-ci>?
cellpoint char_greater_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-ci>?", 2, arglst);
	check_arg_type("char-ci>?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char-ci>?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_greater_ci();
}
///char-ci<=?
cellpoint char_less_eq_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-ci<=?", 2, arglst);
	check_arg_type("char-ci<=?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char-ci<=?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_less_eq_ci();
}
///char-ci>=?
cellpoint char_greater_eq_ci_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-ci>=?", 2, arglst);
	check_arg_type("char-ci>=?", "first", car(arglst), CHARACTER_T);
	check_arg_type("char-ci>=?", "second", car(cdr(arglst)), CHARACTER_T);

	args_push(car(cdr(arglst)));
	args_push(car(arglst));
	return char_greater_eq_ci();
}
///char-upper-case?
cellpoint char_upper_case_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-upper-case?", 1, arglst);
	check_arg_type("char-upper-case?", "first", car(arglst), CHARACTER_T);

	args_push(car(arglst));
	return char_is_upcase();
}
///char-lower-case?
cellpoint char_lower_case_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-lower-case?", 1, arglst);
	check_arg_type("char-lower-case?", "first", car(arglst), CHARACTER_T);

	args_push(car(arglst));
	return char_is_lowercase();
}
///char-alphabetic?
cellpoint char_alphabetic_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-alphabetic?", 1, arglst);
	check_arg_type("char-alphabetic?", "first", car(arglst), CHARACTER_T);

	args_push(car(arglst));
	return char_is_alphabetic();
}
///char-numeric?
cellpoint char_numeric_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-numeric?", 1, arglst);
	check_arg_type("char-numeric?", "first", car(arglst), CHARACTER_T);

	args_push(car(arglst));
	return char_is_numeric();
}
///char-whitespace?
cellpoint char_whitespace_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-whitespace?", 1, arglst);
	check_arg_type("char-whitespace?", "first", car(arglst), CHARACTER_T);

	args_push(car(arglst));
	return char_is_whitespace();
}
///char->integer
cellpoint char_2_integer_proc(cellpoint arglst)
{
	check_arglst_len_eq("char->integer", 1, arglst);
	check_arg_type("char->integer", "first", car(arglst), CHARACTER_T);

	args_push(car(arglst));
	return char_2_integer();
}
///integer->char
cellpoint integer_2_char_proc(cellpoint arglst)
{
	check_arglst_len_eq("integer->char", 1, arglst);
	check_arg_type("integer->char", "first", car(arglst), INTEGER_T);

	args_push(car(arglst));
	return integer_2_char();
}
///char-upcase
cellpoint char_upcase_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-upcase", 1, arglst);
	check_arg_type("char-upcase", "first", car(arglst), CHARACTER_T);

	args_push(car(arglst));
	return char_upcase();
}
///char-downcase
cellpoint char_downcase_proc(cellpoint arglst)
{
	check_arglst_len_eq("char-downcase", 1, arglst);
	check_arg_type("char-downcase", "first", car(arglst), CHARACTER_T);

	args_push(car(arglst));
	return char_downcase();
}
 
