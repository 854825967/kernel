#!/bin/sh

LOGIC_MAKEDIR="Chat"

CXX=g++
CC=gcc

buildLogic()
{
	echo -e "args1:build as \033[31mDEBUG\033[0m or \033[31mRELEASE\033[0m, DEBUG as default"
	for dir in $LOGIC_MAKEDIR
	do
		make -C $dir mode=$1
		if [ "$?" -eq "0" ]
		then 
			echo "===================== @_@ : Oh ye, make $dir ok ====================="
		else
			echo -e "\033[31m================ {{{>_<}}} : Oh fuck, make $dir fail ================\033[0m"
		fi
	done
}

buildLogic $1

