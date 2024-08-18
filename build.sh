#! /bin/bash

if [ -z $1 ]
then
    echo "Please input Chapter files C[chapter_number_file]"
    exit 1
fi

(cd build && cmake -Wno-dev "../$1" && make && ./bin/main)
rm -r build && mkdir build
