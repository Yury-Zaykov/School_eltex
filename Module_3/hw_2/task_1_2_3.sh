#!/usr/bin/bash

var=$(ipcs -m | grep 128 | awk '{print $2}')

ipcrm shm ${var}


#play /home/yury/Downloads/adele_hello.mp3

