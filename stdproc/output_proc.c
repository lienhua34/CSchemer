#include "common.h"
#include "argcheck.h"

//////////////////////////////////////////////////////////
//This file contains the output procedures
//////////////////////////////////////////////////////////

//write
cellpoint write_proc(cellpoint arglst)
{
	check_arglst_len_eq("write", 1, arglst);
	write(car(arglst));
	return make_symbol("ok");
}
//display
cellpoint display_proc(cellpoint arglst)
{
	check_arglst_len_eq("display", 1, arglst);
	display(car(arglst));
	return make_symbol("ok");
}
//newline
cellpoint newline_proc(cellpoint arglst)
{
	check_arglst_len_eq("newline", 0, arglst);
	newline();
	return make_symbol("ok");
}
//write-char
cellpoint write_char_proc(cellpoint arglst)
{
	check_arglst_len_eq("write-char", 1, arglst);
	check_arg_type("write-char", "first", car(arglst), CHARACTER_T);
	display(car(arglst));
	return make_symbol("ok");
}
