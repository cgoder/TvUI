
# **********************************************
# _BIG_ENDIAN Macro for big endian cpu
# **********************************************

LIBNAME  = liblorewalker

CROSS_TOOL_PREFIX = arm-none-linux-gnueabi-
CXX = $(CROSS_TOOL_PREFIX)g++
CC  = $(CROSS_TOOL_PREFIX)g++
AR  = $(CROSS_TOOL_PREFIX)ar
LD  = $(CROSS_TOOL_PREFIX)ld
RANLIB  = $(CROSS_TOOL_PREFIX)ranlib

C_OPTS := -DSKYWORTH_LINUXTV
CC_OPTS := -DSKYWORTH_LINUXTV

C_OPTS += $(CFLAGS)
CC_OPTS += $(CFLAGS)

C_OPTS += -DCOCOS2D_DEBUG=1 -g -Wall -Wextra -std=c99
CC_OPTS += -DCOCOS2D_DEBUG=1 -D_GLIBCXX_USE_NANOSLEEP  -g -Wall -Wextra -std=c++11 -Wno-deprecated-declarations -Wno-reorder

SRCDIR += ./
SRCDIR += ./AutoTuning
SRCDIR += ./ChannelEdit
SRCDIR += ./ChannelList
SRCDIR += ./common
SRCDIR += ./epg/GridView
SRCDIR += ./ManualScan
SRCDIR += ./pf
SRCDIR += ./skyscanapi
#SRCDIR += ./tvplayer
SRCDIR += ./tvreminder
SRCDIR += ./sources
SRCDIR += ./menu
SRCDIR += ./menu/PictureMenu
SRCDIR += ./menu/SoundMenu
SRCDIR += ./epg
SRCDIR += ./localMedia
SRCDIR += ./rec
SRCDIR += ./guide
SRCDIR += ./eventdispacher
SRC_C += $(foreach dir,$(SRCDIR), $(wildcard $(dir)/*.c))
SRC_CPP += $(foreach dir, $(SRCDIR), $(wildcard $(dir)/*.cpp))

INCDIR += ./
INCDIR += ./AutoTuning
INCDIR += ./ChannelEdit
INCDIR += ./ChannelList
INCDIR += ./common
INCDIR += ./epg/GridView
INCDIR += ./ManualScan
INCDIR += ./pf
INCDIR += ./skyscanapi
INCDIR += ./tvplayer
INCDIR += ./setting/include
INCDIR += ./tvreminder
INCDIR += ./sources
INCDIR += ./menu
INCDIR += ./epg
INCDIR += ./localMedia
INCDIR += ./rec
INCDIR += ./guide
INCDIR += ./eventdispacher
INCDIR += ../libcocos2dx-3.10
INCDIR += ../libcocos2dx-3.10/cocos
INCDIR += ../libcocos2dx-3.10/cocos/2d
INCDIR += ../libcocos2dx-3.10/cocos/3d
INCDIR += ../libcocos2dx-3.10/cocos/base
INCDIR += ../libcocos2dx-3.10/cocos/base/allocator
INCDIR += ../libcocos2dx-3.10/cocos/deprecated
INCDIR += ../libcocos2dx-3.10/cocos/math
INCDIR += ../libcocos2dx-3.10/cocos/network
INCDIR += ../libcocos2dx-3.10/cocos/platform
INCDIR += ../libcocos2dx-3.10/cocos/platform/LinuxTV
INCDIR += ../libcocos2dx-3.10/cocos/renderer
INCDIR += ../libcocos2dx-3.10/cocos/storage
INCDIR += ../libcocos2dx-3.10/cocos/ui
INCDIR += ../libcocos2dx-3.10/cocos/editor-support

INCDIR += ../libcocos2dx-3.10/extensions
INCDIR += ../libcocos2dx-3.10/external
INCDIR += ../libcocos2dx-3.10/external/poly2tri
INCDIR += ../libcocos2dx-3.10/external/edtaa3func
INCDIR += ../libcocos2dx-3.10/external/unzip
INCDIR += ../libcocos2dx-3.10/external/tinyxml2
INCDIR += ../libcocos2dx-3.10/external/ConvertUTF
INCDIR += ../libcocos2dx-3.10/external/xxhash
INCDIR += ../libcocos2dx-3.10/external/xxtea
INCDIR += ../libcocos2dx-3.10/external/flatbuffers
INCLUDE = $(foreach dir,$(INCDIR), -I$(dir))


STATIC_OBJ_C0  = $(patsubst %.c, %.o, $(SRC_C))
STATIC_OBJ_C1  = $(patsubst %.cpp, %.o, $(SRC_CPP))

STATIC_OBJ_C  = $(foreach file, $(STATIC_OBJ_C0), $(file) )
STATIC_OBJ_CPP = $(foreach file, $(STATIC_OBJ_C1), $(file))


# **********************************************
libs: $(STATIC_OBJ_C) $(STATIC_OBJ_CPP)
#	@$(AR) cru $(LIBNAME).a $(STATIC_OBJ_C) $(STATIC_OBJ_CPP)
	@$(CXX) $(STATIC_OBJ_C) $(STATIC_OBJ_CPP) $(CC_OPTS) -fPIC -shared -o $(LIBNAME).so
#	@$(CXX) $(STATIC_OBJ_C) $(STATIC_OBJ_CPP) -o $(LIBNAME)
#	@echo "make lorewalker ok ......."

$(STATIC_OBJ_C) : %.o : %.c
	@echo "begin compiling for c file $< ........."
	@$(CC) $(INCLUDE) $(C_OPTS) -c $< -o $@
	@echo "make c file obj ok....."

$(STATIC_OBJ_CPP) : %.o : %.cpp
	@echo "begin compiling for cpp file $<....."
	@$(CXX) $(INCLUDE) $(CC_OPTS) -c $< -o $@
	@echo "make cpp file objs ok...."

clean :
	@rm -f $(STATIC_OBJ_C)
	@rm -f $(STATIC_OBJ_CPP)
	@rm -rf $(LIBNAME)

