void execute(void (*function)(void *p), void *p);
void pool_init(void);
void pool_shutdown(void);
void pool_submit(void (*somefunction)(void *p), void *p);
void *worker();