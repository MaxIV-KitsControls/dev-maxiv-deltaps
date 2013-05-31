/*----- PROTECTED REGION ID(DeltaControllerClass.h) ENABLED START -----*/
//=============================================================================
//
// file :        DeltaControllerClass.h
//
// description : Include for the DeltaControllerClass root class.
//               This class is the singleton class for.
//               the DeltaController device class..
//               It contains all properties and methods which the .
//               DeltaController requires only once e.g. the commands.
//
// project :     Delta power supply.
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL:  $
//
// CVS only:
// $Source:  $
// $Log:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#ifndef DELTACONTROLLERCLASS_H
#define DELTACONTROLLERCLASS_H

#include <tango.h>
#include <DeltaController.h>

/*----- PROTECTED REGION END -----*/

namespace DeltaController_ns
{
	/*----- PROTECTED REGION ID(DeltaController::classes for dynamic creation) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	DeltaController::classes for dynamic creation



//=========================================
//	Define classes for attributes
//=========================================
//	Attribute Current class definition
class CurrentAttrib: public Tango::Attr
{
public:
	CurrentAttrib():Attr("Current",
	                   Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~CurrentAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<DeltaController *>(dev))->read_Current(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<DeltaController *>(dev))->write_Current(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<DeltaController *>(dev))->is_Current_allowed(ty);}
};

//	Attribute Voltage class definition
class VoltageAttrib: public Tango::Attr
{
public:
	VoltageAttrib():Attr("Voltage",
	                   Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~VoltageAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<DeltaController *>(dev))->read_Voltage(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<DeltaController *>(dev))->write_Voltage(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<DeltaController *>(dev))->is_Voltage_allowed(ty);}
};

//	Attribute Impedance class definition
class ImpedanceAttrib: public Tango::Attr
{
public:
	ImpedanceAttrib():Attr("Impedance",
	                   Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~ImpedanceAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<DeltaController *>(dev))->read_Impedance(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<DeltaController *>(dev))->write_Impedance(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<DeltaController *>(dev))->is_Impedance_allowed(ty);}
};

//	Attribute Vlim class definition
class VlimAttrib: public Tango::Attr
{
public:
	VlimAttrib():Attr("Vlim",
	                   Tango::DEV_DOUBLE, Tango::READ_WRITE) {};
	~VlimAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<DeltaController *>(dev))->read_Vlim(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
		{(static_cast<DeltaController *>(dev))->write_Vlim(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<DeltaController *>(dev))->is_Vlim_allowed(ty);}
};

//	Attribute MaxCurrent class definition
class MaxCurrentAttrib: public Tango::Attr
{
public:
	MaxCurrentAttrib():Attr("MaxCurrent",
	                   Tango::DEV_DOUBLE, Tango::READ) {};
	~MaxCurrentAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<DeltaController *>(dev))->read_MaxCurrent(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<DeltaController *>(dev))->is_MaxCurrent_allowed(ty);}
};

//	Attribute MaxVoltage class definition
class MaxVoltageAttrib: public Tango::Attr
{
public:
	MaxVoltageAttrib():Attr("MaxVoltage",
	                   Tango::DEV_DOUBLE, Tango::READ) {};
	~MaxVoltageAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
		{(static_cast<DeltaController *>(dev))->read_MaxVoltage(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
		{return (static_cast<DeltaController *>(dev))->is_MaxVoltage_allowed(ty);}
};






//=========================================
//	Define classes for commands
//=========================================
//	Command On class definition
class OnClass : public Tango::Command
{
public:
	OnClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	OnClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~OnClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<DeltaController *>(dev))->is_On_allowed(any);}
};

//	Command Off class definition
class OffClass : public Tango::Command
{
public:
	OffClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	OffClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~OffClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<DeltaController *>(dev))->is_Off_allowed(any);}
};

//	Command Reset class definition
class ResetClass : public Tango::Command
{
public:
	ResetClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	ResetClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~ResetClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<DeltaController *>(dev))->is_Reset_allowed(any);}
};





/**
 *	The TemplateDevServClass singleton definition
 */

class
#ifdef _TG_WINDOWS_
	__declspec(dllexport)
#endif
	DeltaControllerClass : public Tango::DeviceClass
{
	/*----- PROTECTED REGION ID(DeltaController::Additionnal DServer data members) ENABLED START -----*/

	/*----- PROTECTED REGION END -----*/	//	DeltaController::Additionnal DServer data members



public:
//	write class properties data members
	Tango::DbData	cl_prop;
	Tango::DbData	cl_def_prop;
	Tango::DbData	dev_def_prop;

//	Method prototypes
	static DeltaControllerClass *init(const char *);
	static DeltaControllerClass *instance();
	~DeltaControllerClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	DeltaControllerClass(string &);
	static DeltaControllerClass *_instance;
	void command_factory();
	void attribute_factory(vector<Tango::Attr *> &);
	void write_class_property();
	void set_default_property();
	void get_class_property();
	string get_cvstag();
	string get_cvsroot();

private:
	void device_factory(const Tango::DevVarStringArray *);
	void create_static_attribute_list(vector<Tango::Attr *> &);
	void erase_dynamic_attributes(const Tango::DevVarStringArray *,vector<Tango::Attr *> &);
	vector<string>	defaultAttList;
	Tango::Attr *get_attr_object_by_name(vector<Tango::Attr *> &att_list, string attname);


};

}	//	namespace

#endif	//	DELTACONTROLLERCLASS_H

