#include "common.h"

/*************************************************************
 *This file provides procedures operating on boolean objects
 *************************************************************/

//one arg: cp
cellpoint boolean_not(void)
{
    if (is_false(args_ref(1))){
        reg = a_true;
    }else {
        reg = a_false;
    }
	args_pop(1);
	return reg;
}
