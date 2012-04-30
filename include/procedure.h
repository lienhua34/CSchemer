#ifndef PROCEDURE_H_INCLUDED
#define PROCEDURE_H_INCLUDED

//primitive procedure

extern cellpoint apply_prim_proc(void);

//compound procedure
extern cellpoint procedure_parameters(void);
extern cellpoint procedure_body(void);
extern cellpoint procedure_env(void);

//procedure common functions
extern cellpoint is_procedure(cellpoint);
extern cellpoint procedure_name(void);
extern void procedure_name_set(void);


#endif //PROCEDURE_H_INCLUDED
