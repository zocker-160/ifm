/* Output driver definitions */

#ifndef DRIVER_H
#define DRIVER_H

/* Driver structs */
typedef struct mapfuncs_st {
    void (*map_start)(void);
    void (*map_section)(vhash *sect);
    void (*map_room)(vhash *room);
    void (*map_link)(vhash *link);
    void (*map_join)(vhash *join);
    void (*map_endsection)(void);
    void (*map_finish)(void);
} mapfuncs;

typedef struct itemfuncs_st {
    void (*item_start)(void);
    void (*item_entry)(vhash *item);
    void (*item_finish)(void);
} itemfuncs;

typedef struct taskfuncs_st {
    void (*task_start)(void);
    void (*task_entry)(vhash *task);
    void (*task_finish)(void);
} taskfuncs;

typedef struct errfuncs_st {
    void (*warning)(char *file, int line, char *msg);
    void (*error)(char *file, int line, char *msg);
} errfuncs;

#endif
