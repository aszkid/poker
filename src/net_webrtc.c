#include "net.h"
#include "utils.h"

// Javascript glue functions
extern void js_init();
extern void js_connect(const char *server_id);

// Javascript callbacks
void _net_handle_message(const char *message)
{
    log_info("Received message: %s", message);
}

////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////

int net_init()
{
    js_init();
    return NET_OK;
}

int net_connect(const char *server_id)
{
    js_connect(server_id);
}

int net_recv(int fd, void (*callback)(const char *))
{
}

int net_send(int fd, const char *message)
{
}
