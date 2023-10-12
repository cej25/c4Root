USE_LMD_INPUT=1
CXXFLAGS+=-DCONTROL_INCLUDE -Wfatal-errors -std=c++11
OBJS += unpack_aida.o
OBJS += unpack_germanium_febex.o
OBJS += unpack_fatima_vme.o
OBJS += unpack_fatima_tamex.o
OBJS += unpack_plastic_tamex.o
OBJS += unpack_bplast_twinpeaks.o
OBJS += unpack_frs.o
#OBJS += raw_user.o
