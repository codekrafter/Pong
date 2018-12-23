#!/bin/bash

clang++ *.cpp -o pong -lsfml-window -lsfml-system -lsfml-graphics
rc=$?
echo

if [ $rc -ne 0 ]; then
echo Failed To Build, Exiting
exit $rc
fi

./pong
