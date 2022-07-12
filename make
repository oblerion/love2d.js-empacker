#!/bin/bash
DSRC="src/"
NEXEC="main"

CC=clang
CFLAGS=" -g -Wall -Werror -lm -static-libgcc"
INC=" -Iinclude" 
EXEC=$NEXEC
DOBJ="obj/"

CC2=i686-w64-mingw32-gcc
#CFLAGS2="-g -Wall -lm -L${RAYLIBWIN}/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -static-libgcc"
CFLAGS2=" -g -Wall -lm -lgdi32 -lwinmm -mwindows -static-libgcc"
INC2=" -Iinclude"
#-I/usr/i696-w64-mingw32/include -lgdi32 -lwinmm
EXEC2=""
DOBJ2="build/obj/"

TCC="";
TCFLAGS="";
TINC="";
TEXEC="";
TLINK=" ";
TDOBJ=" ";

function init()
{
	TCC="$1";#compilo
	TINC="$2";#inlcude dir
	TCFLAGS="$3";#flag/ lib dir
	TEXEC="$4";#out exec
	TDOBJ="$5";#obj dir 
}
function comp(){
	local out;
	if [ "$CC"="clang" ] || [ "$CC"="gcc" ];then
        out="$TDOBJ${1:0:-2}.o"
	elif [ "$CC"="clang++" ] || [ "$CC"="g++" ];then
        out="$TDOBJ${1:0:-4}.o"
	fi
	rm -f $out;
	echo rm -f $out;
	command $TCC -c $DSRC$1 $TINC -g -Wall -o $out;
	echo $TCC -c $DSRC$1 $TINC -o $out;
	TLINK="$TLINK $out";
}
function link(){
	command $TCC $TLINK $TCFLAGS "-o" $TEXEC; 
	echo $TCC $TLINK $TCFLAGS "-o" $TEXEC;
}

if [ $# -eq 0 ];then 
# default
    rm -f $EXEC
	init "$CC" "$INC" "$CFLAGS" "$EXEC" "$DOBJ";
	for n in $DSRC*.c ; do
        	comp ${n:${#DSRC}};
	done
	link;
elif [ "$1" == "w" ];then
    rm -f $EXEC2
	init "$CC2" "$INC2" "$CFLAGS2" "$EXEC2" "$DOBJ2";
    	for n in src/*.c ; do
        	comp ${n:4};
	done
	link;
fi
