#include "common.h"
#include <string.h>

/*************************************************************
 *This file provides procedures operating symbol objects.
 *************************************************************/

//one arg: sym
cellpoint symbol_2_string(void)
{
	reg = chars_2_string(get_symbol(args_ref(1)));
	args_pop(1);
	return reg;
}
//one arg: str
cellpoint string_2_symbol(void)
{
	char *s = get_string(args_ref(1));
	reg = make_symbol(s);
	free(s);
	args_pop(1);
	return reg;
}


