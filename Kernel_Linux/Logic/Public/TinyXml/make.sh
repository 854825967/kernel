#!/bin/sh
CHILD_PATH=

for child in $CHILD_PATH
do
make -C $child $1
if [ $? -eq 0 ] 
then
	echo -e "\033[33m===================== @_@ : Oh ye, make $child ok =====================\033[0m"
else
	echo -e "\033[31m================ {{{>_<}}} : Oh fuck, make $child fail ================\033[0m"
fi
done

