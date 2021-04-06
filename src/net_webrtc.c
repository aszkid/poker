#include "net.h"
#include "utils.h"

extern void do_connect();

void _net_handle_open()
{
    log_info("Open connection!");
}

void _net_handle_foo(char *foo)
{
    log_debug("net foo: %s", foo);
    do_connect();
}

int alert()
{
    do_connect();
}