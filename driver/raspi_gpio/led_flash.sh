#!/bin/bash

for ((i = 0; i < 10; i ++)) do
    echo 1 > /sys/class/gpio/gpio21/value
    sleep 2
    echo 0 > /sys/class/gpio/gpio21/value
    sleep 2
done

