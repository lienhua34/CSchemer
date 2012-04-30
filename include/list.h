#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

extern cellpoint is_list(cellpoint);
extern cellpoint list_eq(void);
extern cellpoint list(void);
extern cellpoint list_len(void);
extern cellpoint append(void);
extern cellpoint reverse(void);
extern cellpoint list_tail(void);
extern cellpoint list_ref(void);
extern cellpoint member(cellpoint (*)(void));
extern cellpoint assoc(cellpoint (*)(void));


#endif // LIST_H_INCLUDED
