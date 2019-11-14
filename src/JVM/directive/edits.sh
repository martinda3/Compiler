#!/bin/bash

#            echo $f
#done

for f in *.java; do
    sed s/compilers.toyc.// < $f > ~/javaprogs/compilers/tmp/$f
done
