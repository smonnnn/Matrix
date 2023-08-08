#!/bin/bash
name="matrix"
bash ./compile.sh ./
gcc test.c -o executable -L./libs/ -l:"$name".a
./executable
rm executable