## Process this file with automake to produce Makefile.in

## Copyright (C) 2005-2013 Red Hat, Inc.
##
## This library is free software; you can redistribute it and/or
## modify it under the terms of the GNU Lesser General Public
## License as published by the Free Software Foundation; either
## version 2.1 of the License, or (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public
## License along with this library.  If not, see
## <http://www.gnu.org/licenses/>.

LCOV = lcov
GENHTML = genhtml

SUBDIRS = . gnulib/lib include/libvirt src tools docs gnulib/tests \
  tests po examples

XZ_OPT ?= -v -T0
export XZ_OPT

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
  config-post.h \
  ChangeLog-old \
  libvirt.spec libvirt.spec.in \
  mingw-libvirt.spec.in \
  libvirt.pc.in \
  libvirt-qemu.pc.in \
  libvirt-lxc.pc.in \
  libvirt-admin.pc.in \
  Makefile.nonreentrant \
  autogen.sh \
  cfg.mk \
  run.in \
  README.md \
  AUTHORS.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libvirt.pc libvirt-qemu.pc libvirt-lxc.pc libvirt-admin.pc

NEWS: \
	  $(srcdir)/docs/news.xml \
	  $(srcdir)/docs/news-ascii.xsl \
	  $(srcdir)/docs/reformat-news.py
	$(AM_V_GEN) \
	if [ -x $(XSLTPROC) ]; then \
	  $(XSLTPROC) --nonet \
	    $(srcdir)/docs/news-ascii.xsl \
	    $(srcdir)/docs/news.xml \
	  >$@-tmp \
	    || { rm -f $@-tmp; exit 1; }; \
	  $(PYTHON) $(srcdir)/docs/reformat-news.py $@-tmp >$@ \
	    || { rm -f $@-tmp; exit 1; }; \
	  rm -f $@-tmp; \
	fi
EXTRA_DIST += \
	$(srcdir)/docs/news.xml \
	$(srcdir)/docs/news-ascii.xsl \
	$(srcdir)/docs/reformat-news.py

rpm: clean
	@(unset CDPATH ; $(MAKE) dist && rpmbuild -ta $(distdir).tar.xz)

srpm: clean
	@(unset CDPATH ; $(MAKE) dist && rpmbuild -ts $(distdir).tar.xz)

check-local: all tests

check-access:
	@($(MAKE) $(AM_MAKEFLAGS) -C tests check-access)

cov: clean-cov
	$(MKDIR_P) $(top_builddir)/coverage
	$(LCOV) -c -o $(top_builddir)/coverage/libvirt.info.tmp \
	  -d $(top_builddir)/src  -d $(top_builddir)/daemon \
	  -d $(top_builddir)/tests
	$(LCOV) -r $(top_builddir)/coverage/libvirt.info.tmp \
	  -o $(top_builddir)/coverage/libvirt.info
	rm $(top_builddir)/coverage/libvirt.info.tmp
	$(GENHTML) --show-details -t "libvirt" -o $(top_builddir)/coverage \
	  --legend $(top_builddir)/coverage/libvirt.info

clean-cov:
	rm -rf $(top_builddir)/coverage

MAINTAINERCLEANFILES = .git-module-status

dist-hook: gen-ChangeLog gen-AUTHORS

# Generate the ChangeLog file (with all entries since the switch to git)
# and insert it into the directory we're about to use to create a tarball.
gen_start_date = 2009-07-04
.PHONY: gen-ChangeLog
gen-ChangeLog:
	$(AM_V_GEN)if test -d .git; then \
	  $(top_srcdir)/build-aux/gitlog-to-changelog \
	    --since=$(gen_start_date) > $(distdir)/cl-t; \
	  rm -f $(distdir)/ChangeLog; \
	  mv $(distdir)/cl-t $(distdir)/ChangeLog; \
	fi

.PHONY: gen-AUTHORS
gen-AUTHORS:
	$(AM_V_GEN)\
	if test -d $(srcdir)/.git; then \
	  ( \
	    cd $(srcdir) && \
	    git log --pretty=format:'%aN <%aE>' | sort -u \
	  ) > all.list && \
	  sort -u $(srcdir)/AUTHORS.in > maint.list && \
	  comm -23 all.list maint.list > contrib.list && \
	  contrib="`cat contrib.list`" && \
	  perl -p -e "s/#contributorslist#// and print '$$contrib'" \
	    < $(srcdir)/AUTHORS.in > $(distdir)/AUTHORS-tmp && \
	  mv -f $(distdir)/AUTHORS-tmp $(distdir)/AUTHORS && \
	  rm -f all.list maint.list contrib.list; \
	fi
