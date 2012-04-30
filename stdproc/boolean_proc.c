#include "common.h"
#include "argcheck.h"

///////////////////////////////////////////////////////////////////////
//boolean standar procedure
///////////////////////////////////////////////////////////////////////

///boolean?
cellpoint boolean_pred_proc(cellpoint arglst)
{
    check_arglst_len_eq("boolean?",1,arglst);

    return is_boolean(car(arglst));
}
///not
cellpoint boolean_not_proc(cellpoint arglst)
{
	check_arglst_len_eq("not", 1, arglst);

	args_push(car(arglst)); 
    return boolean_not();
}
