#
# This is a sample Makfile for generating necessary infrastructure for 
# languages. It is not necessarily the most pretty thing you have ever
# seen and I'm sure there are a gazillion better ways to do all of this.
#
# Copyright 2006, Creative Commons.
# Copyright 2006, Jon Phillips.
#
#
#
srcdir = .
localedir =  locale/default
testlocaledir = locale/testsite.org
ccexplocaledir = locale/ccexperimental.localhost


POTFILE = messages.pot
PO_NAME = LC_MESSAGES/messages.po
MO_NAME = LC_MESSAGES/messages.mo
POFILES = \
	$(localedir)/en_US/$(PO_NAME) \
	$(localedir)/de_DE/$(PO_NAME) \
	$(localedir)/zh_CN/$(PO_NAME) \
	$(testlocaledir)/en_US/$(PO_NAME) \
	$(testlocaledir)/de_DE/$(PO_NAME) \
	$(testlocaledir)/zh_CN/$(PO_NAME) \
	$(ccexplocaledir)/en_US/$(PO_NAME) \
	$(ccexplocaledir)/de_DE/$(PO_NAME) \
	$(ccexplocaledir)/zh_CN/$(PO_NAME)
	
POTFILES = \
	index.php \
	test1.php


CATALOGS = \
	$(localedir)/en_US/$(MO_NAME) \
	$(localedir)/de_DE/$(MO_NAME) \
	$(localedir)/zh_CN/$(MO_NAME) \
	$(testlocaledir)/en_US/$(MO_NAME) \
	$(testlocaledir)/de_DE/$(MO_NAME) \
	$(testlocaledir)/zh_CN/$(MO_NAME) \
	$(ccexplocaledir)/en_US/$(MO_NAME) \
	$(ccexplocaledir)/de_DE/$(MO_NAME) \
	$(ccexplocaledir)/zh_CN/$(MO_NAME)

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

.po.mo:
	$(MSGFMT) -o $@ $<


