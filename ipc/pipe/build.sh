#!/bin/bash

gcc pipe_server.c -o server -lpthread
gcc pipe_client.c -o client -lpthread
