#include <stdlib.h>
#include <sqlite3.h>
#include "connector.h"

static double inf_dist_buf, inf_cost_buf;
static sqlite3 *conn;

int connector_initialize(void) {
    int ret = sqlite3_open("data/data.db", &conn);
    if (ret) {
        return 1;
    }
    return 0;
}

int connector_finalize(void) {
    sqlite3_close(conn);
}

int row_cnt_handler(void *out, int ncol, char **data, char **cols) {
    *(unsigned long*)out = atoll(*data);
    return 0;
}

int cities_handler(void *out, int ncol, char **data, char **cols) {
    struct List **cur = (struct List**)out;
    if (list_initialize(*cur, *data, atof(data[1]), atof(data[2]))) {
        return 1;
    }
    ++(*cur);
    return 0;
}

int adjacency_list_handler(void *out, int ncol, char **data, char **cols) {
    struct List *cur = (struct List*)out;
    unsigned long from_idx = atoll(*data);
    unsigned long to_idx = atoll(data[1]);
    double dist = calc_dist(cur[from_idx].longitude,
                            cur[from_idx].latitude,
                            cur[to_idx].longitude,
                            cur[to_idx].latitude);
    double cost = atof(data[2]);
    if (list_push_back(cur + from_idx,
                       to_idx,
                       dist,
                       cost)) {
        return 1;
    }
    if (list_push_back(cur + to_idx,
                       from_idx,
                       dist,
                       cost)) {
        return 1;
    }
    inf_dist_buf += dist;
    inf_cost_buf += cost;
    return 0;
}

int connector_read(unsigned long *size,
                   double *inf,
                   struct List **adjacency_list) {
    if (!adjacency_list || !size || !inf) {
        return 1;
    }
    unsigned long nrows = 0;
    int ret = sqlite3_exec(conn, "SELECT COUNT(*) FROM cities",
                           row_cnt_handler, &nrows, 0);
    if (ret) {
        return 2;
    }
    *size = nrows;
    *adjacency_list = malloc(sizeof(struct List) * nrows);
    struct List *adjacency_list_iter = *adjacency_list;
    if (!(adjacency_list_iter)) {
        return 3;
    }
    ret = sqlite3_exec(conn, "SELECT * FROM cities",
                       cities_handler, &adjacency_list_iter, 0);
    if (ret) {
        return 4;
    }
    inf_dist_buf = 0;
    inf_cost_buf = 0;
    ret = sqlite3_exec(conn, "SELECT * FROM adjacency_list",
                       adjacency_list_handler, *adjacency_list, 0);
    if (ret) {
        return 5;
    }
    *inf = inf_dist_buf > inf_cost_buf ? inf_dist_buf : inf_cost_buf;
    return 0;
}
