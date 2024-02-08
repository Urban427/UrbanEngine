Target = IOSystem

include ../makefilePatterns/${platform}.mk

windowsApi = Windows/
androidApi = Android/
folders += ${bin}${windowsApi} ${bin}${androidApi}

SCR += ${wildcard ${${platform}Api}*.cpp}

IFlags += -I ${windowsApi}
IFlags += -I ${androidApi}

include ../makefilePatterns/pattern.mk