#!/bin/sh

KERNEL_MAKEDIR="Public Public/TinyXml Public/simpleini Kernel/CallBackSystem Kernel/Config Kernel/ConnectPool Kernel/LogicManage Kernel/MemaryPool Kernel/NetSystem Kernel"

CXX=g++
CC=gcc

buildKernel()
{
	for dir in $KERNEL_MAKEDIR
	do
		make -C $dir mode=$1
		if [ "$?" -eq "0" ]
		then 
			echo "===================== @_@ : Oh ye, make $dir ok ====================="
		else
			echo -e "\033[31m================ {{{>_<}}} : Oh fuck, make $dir fail ================\033[0m"
		fi
	done

	if [ "$1" = "RELEASE" ]
	then
		$CXX  -Wall -D __LINUX_64__ -ldl -O ./Release/*.o -o ./Kernel_R
	else
		$CXX  -Wall -D __LINUX_64__ -ldl -D _DEBUG -g -pg ./Debug/*.o -o ./Kernel_D
	fi
}

error_noargs()
{
	echo -e "{{{>_<}}} : Oh fuck"
	echo -e "args1:build \033[31mkernel\033[0m or \033[31mlogic\033[0m, also u can \033[31mclean\033[0m"
	echo -e "args2:as \033[31mDEBUG\033[0m or \033[31mRELEASE\033[0m, DEBUG as default"
}

if [ $# -lt 1 ]
then
	error_noargs
else
	if [ "$1" = "kernel" ]
	then
		buildKernel $2
	elif [ "$1" = "logic" ]
	then
		echo "logic to be continue"
	elif [ "$1" = "clean" ]
	then
		find ./ -name *.o | xargs rm -f
		find ./ -name *.a | xargs rm -f
		rm -f ./Kernel_*
	else
		error_noargs
	fi
fi


