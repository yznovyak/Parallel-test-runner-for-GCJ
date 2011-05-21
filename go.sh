#!/bin/sh
SOURCE=`grep -e '#include \".*\.cpp\"' runner.cpp  | sed 's/#include //g' | sed 's/\"//g'`
rm -f submission.zip
zip submission runner.cpp $SOURCE
g++ -pthread runner.cpp && ./a.out