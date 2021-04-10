#pragma once

enum { NET_OK };

/**
 * Initializes networking subsystem. Must be called before using any other functions here.
 */
int net_init();

/**
 * Connect to a server room.
 * Returns a unique file descriptor handle for this connection.
 */
int net_connect(const char *server_id);

/**
 * Listen to messages from the connection represented by the file descriptor `fd`.
 * Upon receiving.
 */
int net_recv(int fd, void (*callback)(const char *));

/**
 * Send `message` to the connection represented by the file descriptor `fd`.
 */
int net_send(int fd, const char *message);
