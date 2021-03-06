#!/bin/sh

rados -p data load-gen \
    --num-objects 10240 \
    --min-object-size 1048576 \
    --max-object-size 25600000 \
    --min-ops 4 \
    --max-ops 1024 \
    --max-backlog 1024 \
    --percent 50 \
    --run-length 1200
