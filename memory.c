#include "common.h"

//the memory
#define MEMORY 0x100000
//#define MEMORY 0x800
struct cons_cell *the_cons_cells;
struct cons_cell *free_cons_cells;
cellpoint free_point = 1;

//memory init
void memory_init(void)
{
    the_cons_cells = (struct cons_cell *)malloc(sizeof(struct cons_cell) * MEMORY);
	if (the_cons_cells == NULL){
		printf("Error: malloc error. -- INITIAL.\n");
		exit(-1);
	}
	
	free_cons_cells = (struct cons_cell *)malloc(sizeof(struct cons_cell) * MEMORY);
	if (free_cons_cells == NULL){
		printf("Error: malloc error. -- INITIAL.\n");
		exit(-1);
	}
}
boolean memory_enough(int k)
{
	return (free_point + k) < MEMORY;
}
//basic operation: cons
cellpoint cons(uint addr, uint decre)
{
    if(!memory_enough(1)){
		//store the args
		car_set(allocons, addr);
		cdr_set(allocons, decre);
		//call garbage collection
        garbage_collection();
		//restore the args
		addr = car(allocons);
		decre = cdr(allocons);
    }
	the_cons_cells[free_point].car = addr;
	the_cons_cells[free_point].cdr = decre;
//	printf("%d\n", free_point);
    return free_point++;
}
//basic operation: car
uint car(cellpoint cp)
{
    return the_cons_cells[cp].car;
}
//basic operation: cdr
uint cdr(cellpoint cp)
{
    return the_cons_cells[cp].cdr;
}
//basic operation: car_set!
void car_set(cellpoint cp, uint ele)
{
	the_cons_cells[cp].car = ele;
}
//basic operation: cdr_set!
void cdr_set(cellpoint cp, uint ele)
{
	the_cons_cells[cp].cdr = ele;
}


