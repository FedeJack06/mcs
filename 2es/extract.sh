#!/bin/bash
echo " " > fileInput
for pl in $*
do
    grep "/\* $pl" SolarSysData.h | awk '{print $1}' >> fileInput
    grep -A6 "// $pl" SolarSysData.h | grep -v "// $pl" >> fileInput
    echo " " >> fileInput
done
