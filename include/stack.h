#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef cellpoint t_stack;
extern void stack_init(t_stack *);
extern boolean stack_is_empty(t_stack *);
extern void stack_push(t_stack *, cellpoint);
extern cellpoint stack_pop(t_stack *);
extern cellpoint stack_top(t_stack *);

#endif // STACK_H_INCLUDED
