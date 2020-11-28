#ifndef _CORE_H_
#define _CORE_H_

#include <stdio.h>

int core_initialize(void);
int core_finalize(void);
int core_idx_to_str(unsigned long idx, const char **out);
int core_find_path(unsigned long from,
                   unsigned long to,
                   char dist,
                   double *val,
                   unsigned long *steps,
                   unsigned long **path);
int core_log(FILE *fout);
int core_free_path(unsigned long *path);
int core_log_path(unsigned long steps, unsigned long *path, FILE *fout);

#endif
