#!/bin/bash
name="matrix"
flags=""
bash ./compile.sh ./
gcc $flags test.c -o executable -L./libs/ -l:"$name".a
./executable
rm executable