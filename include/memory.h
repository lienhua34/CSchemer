#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

//variables
extern struct cons_cell *the_cons_cells;
extern struct cons_cell *free_cons_cells;
extern cellpoint free_point;
extern cellpoint cons_args;

//functions
extern void memory_init(void);
extern boolean memory_enough(int);
extern cellpoint cons(uint, uint);
extern uint car(cellpoint);
extern uint cdr(cellpoint);
extern void car_set(cellpoint, uint);
extern void cdr_set(cellpoint, uint);

#endif //MEMORY_H_INCLUDED
