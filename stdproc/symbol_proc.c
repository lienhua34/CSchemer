#include "common.h"
#include "argcheck.h"


//////////////////////////////////////////////////////////////
//symbol interface
//////////////////////////////////////////////////////////////
///symbol?
cellpoint symbol_pred_proc(cellpoint arglst)
{
    check_arglst_len_eq("symbol?", 1, arglst);

    return is_symbol(car(arglst));
}
///symbol->string
cellpoint symbol_2_string_proc(cellpoint arglst)
{
    check_arglst_len_eq("symbol->string",1,arglst);
	check_arg_type("symbol->string", "first", car(arglst), SYMBOL_T);

	args_push(car(arglst));
    return symbol_2_string();
}
///string->symbol
cellpoint string_2_symbol_proc(cellpoint arglst)
{
	check_arglst_len_eq("string->symbol", 1, arglst);
	check_arg_type("string->symbol", "first", car(arglst), STRING_T);

	args_push(car(arglst));
	return string_2_symbol();
}
