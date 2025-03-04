#!/bin/bash

while ./data > in.txt && ./a < in.txt > out.txt && ./std < in.txt > std.txt && diff out.txt std.txt; do
    echo "no problem meow!"
done