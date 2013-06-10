
# date of git snapshot
%define snapshot .20130610git

Summary: 	Tango device for power supplies from Delta Elektronika
Name:    	tangods-deltaps
Version: 	0.2.0
# post-release
# see http://fedoraproject.org/wiki/Packaging:NamingGuidelines#Non-Numeric_Version_in_Release
# 
Release:	1%{?snapshot}%{?dist}.maxlab
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

%files
%defattr (-,root,root,755)
%{_bindir}/*

%changelog
* Mon Jun 10 2013 Mirjam Lindberg <mirjam.lindberg@maxlab.lu.se> 0.2.0-1.20130610git
- Calculate tolerance as a percentage of the power supply max current. The percentage is a new property of the device.
- Max source voltage is a new attribute. Default value is the factory setting max voltage.
- SendCommand command added. Sends a generic SCPI command to the powersupply.
- Added functionality to read attributes Max_voltage and Max_current.

* Mon Jun 03 2013 Andreas Persson <andreas_g.persson@maxlab.lu.se> 0.1.0-2.20130603git
- disable AutoReqProv

* Mon Jun 03 2013 Andreas Persson <andreas_g.persson@maxlab.lu.se> 0.1.0-1.20130603git
- initial package
