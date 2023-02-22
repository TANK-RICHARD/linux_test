#!/bin/bash

gcc fifo_server.c -o server -lpthread
gcc fifo_client.c -o client -lpthread
