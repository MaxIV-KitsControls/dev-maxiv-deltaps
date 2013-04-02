/*----- PROTECTED REGION ID(Itest2811Channel.h) ENABLED START -----*/
//=============================================================================
//
// file :        Itest2811Channel.h
//
// description : Include for the Itest2811Channel class.
//
// project :     BILT channel interface.
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


#ifndef ITEST2811CHANNEL_H
#define ITEST2811CHANNEL_H


#include <tango.h>

/*----- PROTECTED REGION END -----*/


/**
 *	Itest2811Channel class Description:
 *	The Bilt multi channel power supply has three individual channels. This class offers an interface to an individual channel of the power supply.
 */

namespace Itest2811Channel_ns
{
	/*----- PROTECTED REGION ID(Itest2811Channel::Additional Class Declarations) ENABLED START -----*/

		//		Additional Class Declarations

	/*----- PROTECTED REGION END -----*/	//	Itest2811Channel::Additional Class Declarations


class Itest2811Channel : public Tango::Device_4Impl
{


	/*----- PROTECTED REGION ID(Itest2811Channel::Data Members) ENABLED START -----*/

	//		Add your own data members

	/*----- PROTECTED REGION END -----*/	//	Itest2811Channel::Data Members


//	Device property data members
public:		//	Magnet:	Name of the Magnet
	string	magnet;
	//	Pole:	The number of the channel or Pole of the Bilt power supply [1-5]
	Tango::DevShort	pole;
	//	IP:	
	string	iP;
	
//	Attribute data members
public:
	Tango::DevDouble	*attr_Current_read;
	Tango::DevDouble	*attr_Voltage_read;
	Tango::DevDouble	*attr_Impedance_read;



//	Constructors and destructors
public:
	/**
	 * Constructs a newly allocated Command object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	Itest2811Channel(Tango::DeviceClass *cl,string &s);
	/**
	 * Constructs a newly allocated Command object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device Name
	 */
	Itest2811Channel(Tango::DeviceClass *cl,const char *s);
	/**
	 * Constructs a newly allocated Command object.
	 *
	 *	@param cl	Class.
	 *	@param s 	Device name
	 *	@param d	Device description.
	 */
	Itest2811Channel(Tango::DeviceClass *cl,const char *s,const char *d);
	/**
	 * The object destructor.
	 */	
	~Itest2811Channel() {delete_device();};



//	Miscellaneous methods
public:
	/**
	 *	will be called at device destruction or at init command.
	 */
	void delete_device();
	/**
	 *	Initialize the device
	 */
	virtual void init_device();
	/**
	 *	Read the device properties from database
	 */
	 void get_device_property();
	/**
	 *	Always executed method before execution command method.
	 */
	virtual void always_executed_hook();


//	Attribute methods
public:
	/**
	 *	Method      : Itest2811Channel::read_attr_hardware()
	 *	Description : Hardware acquisition for attributes.
	 */
	virtual void read_attr_hardware(vector<long> &attr_list);


	/**
	 *	Current attribute related methods.
	 *	Description: The DC current of the selected pole.
	 *
	 *	Data type:	Tango::DevDouble
	 *	Attr type:	Scalar 
	 */
	virtual void read_Current(Tango::Attribute &attr);
	virtual void write_Current(Tango::WAttribute &attr);
	virtual bool is_Current_allowed(Tango::AttReqType type);



	/**
	 *	Voltage attribute related methods.
	 *	Description: The measured voltage of the selected pole.
	 *
	 *	Data type:	Tango::DevDouble
	 *	Attr type:	Scalar 
	 */
	virtual void read_Voltage(Tango::Attribute &attr);
	virtual bool is_Voltage_allowed(Tango::AttReqType type);



	/**
	 *	Impedance attribute related methods.
	 *	Description: Calculated impedance of the selected pole.
	 *
	 *	Data type:	Tango::DevDouble
	 *	Attr type:	Scalar 
	 */
	virtual void read_Impedance(Tango::Attribute &attr);
	virtual bool is_Impedance_allowed(Tango::AttReqType type);




	/**
	 *	Method      : Itest2811Channel::add_dynamic_attributes()
	 *	Description : Add dynamic attributes if any.
	 */
	void add_dynamic_attributes();

//	Command related methods
public: 
	/**
	 *	Command State related methods.
	 */
	virtual Tango::DevState dev_state();

	/**
	 *	Command Status related methods.
	 */
	virtual Tango::ConstDevString dev_status();

	/**
	 *	Command On related methods.
	 */
	virtual void on();
	virtual bool is_On_allowed(const CORBA::Any &any);

	/**
	 *	Command Off related methods.
	 */
	virtual void off();
	virtual bool is_Off_allowed(const CORBA::Any &any);

	/**
	 *	Command Reset related methods.
	 */
	virtual void reset();
	virtual bool is_Reset_allowed(const CORBA::Any &any);



	/*----- PROTECTED REGION ID(Itest2811Channel::Additional Method prototypes) ENABLED START -----*/

	//	Additional Method prototypes

	/*----- PROTECTED REGION END -----*/	//	Itest2811Channel::Additional Method prototypes

};

	/*----- PROTECTED REGION ID(Itest2811Channel::Additional Classes Definitions) ENABLED START -----*/

	//	Additional Classes definitions

	/*----- PROTECTED REGION END -----*/	//	Itest2811Channel::Additional Classes Definitions

} //	namespace

#endif	//	ITEST2811CHANNEL_H