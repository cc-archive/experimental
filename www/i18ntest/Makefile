srcdir = .
localedir =  locale/default

POTFILE = messages.pot
PO_NAME = LC_MESSAGES/messages.po
MO_NAME = LC_MESSAGES/messages.mo
POFILES = \
	$(localedir)/en_US/$(PO_NAME) \
	$(localedir)/de_DE/$(PO_NAME) \
	$(localedir)/zh_CN/$(PO_NAME)

POTFILES = \
	index.php \
	test1.php


CATALOGS = \
	$(localedir)/de_DE/$(MO_NAME) \
	$(localedir)/zh_CN/$(MO_NAME)


INSTALL = /usr/bin/install -c
INSTALL_DATA = $(INSTALL) -m 644

GMSGFMT = /usr/bin/gmsgfmt
MSGFMT = /usr/bin/msgfmt
XGETTEXT = /usr/bin/xgettext -n

UPDATE_PO_SCRIPT = ./update_po_files.sh

all: $(POTFILE) $(POFILES) $(CATALOGS)

clean:
	rm -f $(CATALOGS)
	rm -f $(POTFILE)
	@# do not delete POFILES (only the main POTFILE which is generated)

clean-all: clean-mo
	@#find . -depth -name "*.mo" -type f -exec rm -Rf {} \;
	@#find . -depth -name "*.gmo" -type f -exec rm -Rf {} \;

clean-mo:
	rm -f $(CATALOGS)

$(POTFILE):
	$(XGETTEXT) $(POTFILES) -o messages.pot

$(POFILES):
	$(UPDATE_PO_SCRIPT)	

$(CATALOGS):
	$(MSGFMT) `dirname $@`/`basename $@ mo`po -o $@ 

#.po.gmo:
#	file=`echo $* | sed 's,.*/,,'`.gmo \
#	  && rm -f $$file && $(GMSGFMT) -o $$file $<

#.SUFFIXES:
#.SUFFIXES: .po .mo .gmo


#$(POTFILES):
#	$(XGETTEXT) *.php

# POTFILES is created from POTFILES.in by stripping comments, empty lines
# and Intltool tags (enclosed in square brackets), and appending a full
# relative path to them
#POTFILES: POTFILES.in
#	( posrcprefix='$(top_srcdir)/'; \
#	  rm -f $@-t $@ \
#	    && (sed -e '/^#/d' 					\
#		    -e 's/^[[].*] *//' 				\
#		    -e '/^[ 	]*$$/d' 			\
#		    -e "s@^@	$$posrcprefix@" $(srcdir)/$@.in	\
#		| sed -e '$$!s/$$/ \\/') > $@-t \
#	    && chmod a-w $@-t \
#	    && mv $@-t $@ )

.po.mo:
	$(MSGFMT) -o $@ $<


