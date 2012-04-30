#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

extern cellpoint string(void);
extern cellpoint string_eq(void);
extern cellpoint string_eq_ci(void);
extern cellpoint string_less(void);
extern cellpoint string_less_ci(void);
extern cellpoint string_greater(void);
extern cellpoint string_greater_ci(void);
extern cellpoint string_less_eq(void);
extern cellpoint string_less_eq_ci(void);
extern cellpoint string_greater_eq(void);
extern cellpoint string_greater_eq_ci(void);
extern cellpoint substring(void);
extern cellpoint string_append(void);
extern cellpoint string_2_list(void);
extern cellpoint list_2_string(void);
extern cellpoint string_copy(void);
extern void string_fill(void);

#endif // STRING_H_INCLUDED
