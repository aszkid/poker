#include "net.h"
#include "utils.h"

extern void do_connect();

void _net_handle_open()
{
    log_debug("Open connection!");
}

void _net_handle_close()
{
    log_debug("Close connection");
}

int connect()
{
    do_connect();
}