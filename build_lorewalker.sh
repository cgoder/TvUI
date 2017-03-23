#!/bin/bash
###############################################
#1、脚本需要放置在source code根目录下运行
#
###############################################
#指定需要下载COCOS2Dx版本
COCOS2DX="3.10"
COCOS2DX_Branche="master"

#执行脚本参数数目
PARAM_NUM="5"
#机芯、机型需要手动设置默机芯为MS100机型为M1
SKYMODEL="MS100"
SKYTYPE="M1"
MANUFACTURER="MSTAR"
PLATFORM="mstar6586"
WORKSPACE=`pwd`

info_show(){
  echo -e "\033[37;42m < $@ > \033[0m"
}
show_cmd(){
  info_show $@
			$@
}

#编译版本
COCOS2DX_DIR="../libcocos2dx-3.10"

if [ "$1" != "" ]; then
    temp=$1
	else
		read -p "Target Device: -MS100)MS100 M1  -MS200)MS200 M2" temp
	fi
	
case $temp in
	MS100)
	SKYMODEL="MS100"
	SKYTYPE="M1"
	echo "SKYMODEL=MS100 SKYTYPE=M1"
	;;
	MS200)
	SKYMODEL="MS200"
	SKYTYPE="M2"
	echo "SKYMODEL=MS200 SKYTYPE=M2"
	;;
	*)
	echo "please first input MS100 or MS200"
	exit 0
	;;
esac
	
if [ "$2" != "" ]; then
    COMPILEMODE=$2
	else
		read -p "Target Device: debug)debug  release)release" COMPILEMODE
	fi
	
#编译报错退出
function make_error_exit(){
		if [ "`echo $?`" != "0" ]; then  #在make clean;make如果失败，则走到这一步，即可在下面进行打印或操作；
			echo -e "\033[1;41m The compile lorewalker fail!!!!oh I'm sorry!!! \033[0m"
			exit 1
		fi 
}

function error_force_exit(){
		echo -e "\033[1;41m There is a error or do something fail ,force exit!!!! oh I'm sorry! \033[0m"
		exit
}

#初始化环境变量svn jdk
function init_complier_env() {
		#初始化环境变量
        source java7_openjdk_svn_1_7
}

## 检测编译参数
function check_param_number() {
	PARAM_NUM=$2
	if [ $1 -lt $PARAM_NUM ];then
		echo -e "\033[41;33;4;5m>>>>>> Error >>>>>> input param invalid >>>>>>" 
		echo -e "\033[0m "
		help
		exit 0
	fi
}

#addflags mstar6586 include and lib
function compile_liblorewalker() {
	#cocos2dx
	COCOS2DX_LIB=$COCOS2DX_DIR/

	#mslib
	MS_LIB=$COCOS2DX_DIR/external/$PLATFORM/lib/mslib
	MSUTO_LIB=$COCOS2DX_DIR/external/$PLATFORM/lib/mslib/utopia
	echo "$MS_LIB"
	# opengles
	GL_INC=$COCOS2DX_DIR/external/$PLATFORM/include/OpenGL
	GL_LIB=$COCOS2DX_DIR/external/$PLATFORM/lib/opengl
	#freetype	
	FREETYPE_INC=$COCOS2DX_DIR/external/$PLATFORM/include/freetype2
#FREETYPE_LIB
	#json
	#JSON_INC="$COCOS2DX_DIR/external/$PLATFORM/include/libjson/include""$COCOS2DX_DIR/external/$PLATFORM/include/json"
	JSON_INC=$COCOS2DX_DIR/external/$PLATFORM/include
#	JSON_LIB
	#zlib
	ZLIB_INC=$COCOS2DX_DIR/external/$PLATFORM/include/zlib
#	ZLIB_LIB
	#dfb
	DFB_INC=$COCOS2DX_DIR/external/$PLATFORM/include/dfb/target/directfb
#	DFB_LIB
	#CURL
	CURL_INC=$COCOS2DX_DIR/external/$PLATFORM/include
#	CURL_LIB
	#websocket
	#WEBST_INC
	#png
	PNG_INC=$COCOS2DX_DIR/external/$PLATFORM/include/png

	#jpeg
	JPEG_INC=$COCOS2DX_DIR/external/$PLATFORM/include/jpeg/include
	#fontconfig
	FONT_INC=$COCOS2DX_DIR/external/$PLATFORM/include/fontconfig
	#sqlite
	SQL_INC=$COCOS2DX_DIR/external/$PLATFORM/include/sqlite
	# show_cmd make CFLAGS="-I$GL_INC -I$FREETYPE_INC -I$JSON_INC \
	# -I$ZLIB_INC -I$DFB_INC \
	# -I$CURL_INC -I$PNG_INC \
	# -I$JPEG_INC -I$FONT_INC -I$SQL_INC \
	# -L$MS_LIB -L$COCOS2DX_LIB"

	#show_cmd `
	make CFLAGS="-I$GL_INC -I$FREETYPE_INC -I$JSON_INC \
	-I$ZLIB_INC -I$DFB_INC \
	-I$CURL_INC -I$PNG_INC \
	-I$JPEG_INC -I$FONT_INC -I$SQL_INC \
	-L$GL_LIB -L$MS_LIB -L$MSUTO_LIB -L$COCOS2DX_LIB"
	#`
	make_error_exit
}

function help() {
  show_cmd "
   Note1:  \n                                                    										
   Note2:  \n                                                          									
   Note4:  \n                                         													
    -help :help\n							           
	-6586 :make 6586\n"
	exit 0
}


while true;
do
	case "$3" in
	-6586)
		echo "Compile liblorewalker"
		#todo
		compile_liblorewalker
		echo "Successful compile liblorewalker"
		echo "###########################################"
		exit 0
		;;
	esac
	help
done
