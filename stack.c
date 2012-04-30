#include "common.h"

/*************************************************************
 *This file implements stack data struct with list.
 *************************************************************/

void stack_init(t_stack *st)
{
    *st = NIL;
}
boolean stack_is_empty(t_stack *st)
{
    return *st == NIL;
}
void stack_push(t_stack *st, cellpoint ele)
{
    *st = cons(ele, *st);
}
cellpoint stack_pop(t_stack *st)
{
    if (stack_is_empty(st)){
        perror("Error: the stack is empty. --STACK_POP\n");
		error_handler();
    }
    cellpoint top = car(*st);
    *st = cdr(*st);
    return top;
}
cellpoint stack_top(t_stack *st)
{
    if (stack_is_empty(st)){
        perror("Error: the stack is empty. --STACK_TOP\n");
		error_handler();
    }
    return car(*st);
}

