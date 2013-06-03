
# date of git snapshot
%define snapshot .20130603git

Summary: 	Tango device for power supplies from Delta Elektronika
Name:    	tangods-deltaps
Version: 	0.1.0
# post-release
# see http://fedoraproject.org/wiki/Packaging:NamingGuidelines#Non-Numeric_Version_in_Release
# 
Release:	2%{?snapshot}%{?dist}.maxlab
License: 	GPL
URL:		http://www.maxlab.lu.se
Group:		System Environment/Daemons
Source: 	%{name}-%{version}.tar.gz
Requires:	libdeltaps
Requires:	libtango8
BuildRequires: libdeltaps-devel
BuildRequires: libtango8-devel
# for pogo Makefile templates:
BuildRequires: tango-java
# todo: find out why this is needed: 
AutoReqProv: no

%description
Tango device for power supplies from Delta Elektronika
via ethernet

%prep
%setup -q

%build
make -C src \
	RELEASE_TYPE=OPTIMIZED \
	OUTPUT_TYPE=DEVICE \
	MAKE_ENV=%{_datadir}/pogo/preferences \
	all

%install
[ -z %{buildroot} ] || rm -rf %{buildroot}
mkdir -p %{buildroot}%{_bindir}
make -C src \
	RELEASE_TYPE=OPTIMIZED \
	OUTPUT_TYPE=DEVICE \
	MAKE_ENV=%{_datadir}/pogo/preferences \
	INSTALL_DIR=%{buildroot}%{_bindir} \
	install

%clean
[ -z %{buildroot} ] || rm -rf %{buildroot}

%post

%postun

# main package includes libraries and copyright info
%files
%defattr (-,root,root,755)
%{_bindir}/*

%changelog
* Mon Jun 03 2013 Andreas Persson <andreas_g.persson@maxlab.lu.se> 0.1.0-2.20130603git
- disable AutoReqProv

* Mon Jun 03 2013 Andreas Persson <andreas_g.persson@maxlab.lu.se> 0.1.0-1.20130603git
- initial package
