#!/usr/bin/env bash
./compiler $1 > a.cpp
if [ -z "$2" ]; then
  OUTPUT=a.out
else
  OUTPUT=$2
fi
g++ a.cpp -o $OUTPUT
rm a.cpp
chmod +x $OUTPUT
