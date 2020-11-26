#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_

#include "../util/util.h"

int connector_initialize(void);
int connector_read(unsigned long *size, struct List **adjacency_list);
int connector_finalize(void);

#endif
