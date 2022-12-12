## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = gestionelection

gestionelection_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	bureau_de_vote.c bureau_de_vote.h bv_stats.c bv_stats.h\
	election.c election.h election_calcul.c election_calcul.h\
	user.c user.h\
	liste_electorale.c liste_electorale.h le_stats.c

gestionelection_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

