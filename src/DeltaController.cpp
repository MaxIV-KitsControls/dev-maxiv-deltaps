/*----- PROTECTED REGION ID(DeltaController.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        DeltaController.cpp
//
// description : C++ source for the DeltaController and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               DeltaController are implemented in this file.
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


#include <DeltaController.h>
#include <DeltaControllerClass.h>

#include <yat/Exception.h>
/*----- PROTECTED REGION END -----*/


/**
 *	DeltaController class description:
 *	Device server to control all groups of Delta power supplies
 */

//================================================================
//
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//----------------------------------------------------------------
//  State         |  dev_state
//  Status        |  dev_status
//  On            |  on
//  Off           |  off
//  Reset         |  reset
//================================================================
//	Attributes managed are:
//	Current:	
//	Voltage:	
//	Impedance:	
//	Vlim:	
//	MaxCurrent:	
//	MaxVoltage:	




namespace DeltaController_ns
{
	/*----- PROTECTED REGION ID(DeltaController::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	DeltaController::namespace_starting



//--------------------------------------------------------
/**
 *	Method      : DeltaController::DeltaController()
 *	Description : Constructors for a Tango device
 *	              implementing the class DeltaController
 */
//--------------------------------------------------------
DeltaController::DeltaController(Tango::DeviceClass *cl, string &s)
 	: Tango::Device_4Impl(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(DeltaController::constructor_1) ENABLED START -----*/

    init_device();

    /*----- PROTECTED REGION END -----*/	//	DeltaController::constructor_1
}
//--------------------------------------------------------
DeltaController::DeltaController(Tango::DeviceClass *cl, const char *s)
 	: Tango::Device_4Impl(cl, s)
{
	/*----- PROTECTED REGION ID(DeltaController::constructor_2) ENABLED START -----*/

    init_device();

    /*----- PROTECTED REGION END -----*/	//	DeltaController::constructor_2
}
//--------------------------------------------------------
DeltaController::DeltaController(Tango::DeviceClass *cl, const char *s, const char *d)
 	: Tango::Device_4Impl(cl, s, d)
{
	/*----- PROTECTED REGION ID(DeltaController::constructor_3) ENABLED START -----*/

    init_device();

    /*----- PROTECTED REGION END -----*/	//	DeltaController::constructor_3
}


//--------------------------------------------------------
/**
 *	Method      : DeltaController::delete_device()()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void DeltaController::delete_device()
{
	DEBUG_STREAM << "DeltaController::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(DeltaController::delete_device) ENABLED START -----*/

    //	Delete device allocated objects
    if (powersupply > 0)
    {
        delete powersupply;
    }
    powersupply = 0;
    delete attr_Current_read;
    attr_Current_read = 0;
    delete attr_Voltage_read;
    attr_Voltage_read = 0;
    delete attr_Impedance_read;
    attr_Impedance_read = 0;
    delete attr_Voltage_read;
    attr_Voltage_read = 0;

    /*----- PROTECTED REGION END -----*/	//	DeltaController::delete_device
	delete[] attr_MaxCurrent_read;
	delete[] attr_MaxVoltage_read;
	
	
}


//--------------------------------------------------------
/**
 *	Method      : DeltaController::init_device()
 *	Description : //	will be called at device initialization.
 */
//--------------------------------------------------------
void DeltaController::init_device()
{
	DEBUG_STREAM << "DeltaController::init_device() create device " << device_name << endl;
	

	/*----- PROTECTED REGION ID(DeltaController::init_device_before) ENABLED START -----*/

    //	Initialization before get_device_property() call        
    attr_Current_read = new Tango::DevDouble();
    attr_Voltage_read = new Tango::DevDouble();
    attr_Impedance_read = new Tango::DevDouble();
    attr_Vlim_read = new Tango::DevDouble();

    this->vlim = 0;
    this->impedance = 0;

    /*----- PROTECTED REGION END -----*/	//	DeltaController::init_device_before
	
	//	Get the device properties (if any) from database
	get_device_property();
	if (mandatoryNotDefined)
		return;
	
	attr_MaxCurrent_read = new Tango::DevDouble[1];
	attr_MaxVoltage_read = new Tango::DevDouble[1];
	
	/*----- PROTECTED REGION ID(DeltaController::init_device) ENABLED START -----*/

    //	Initialize device
    this->set_state(Tango::INIT);
    try
    {
        DEBUG_STREAM << "Configure a new power supply with IP " << this->iPAddress << std::endl;
        
        if(this->groupNumber<1 || this->groupNumber>4){
            this->set_state(Tango::FAULT);
            this->set_status("Wrong groupNumber");
            powersupply = new PSC_ETH(iPAddress, groupNumber);
        }
        else{
            powersupply = new PSC_ETH(iPAddress, groupNumber);
            this->set_state(Tango::ON);
            this->set_status("Communication OK");
        }
    }
    catch (const yat::Exception &e)
    {
        std::stringstream message;
        for (unsigned int i = 0; i < e.errors.size(); i++)
        {
            message << e.errors[i].reason << " , " << e.errors[i].desc << " , " << e.errors[i].origin << " , " << e.errors[i].code << std::endl;
        }
        this->set_state(Tango::FAULT);
        this->set_status(message.str());
    }
    catch (...)
    {
        ERROR_STREAM << "UNKNOWN KNOWN ERRRRRRROR" << std::endl;
        this->set_state(Tango::UNKNOWN);
    }

    /*----- PROTECTED REGION END -----*/	//	DeltaController::init_device
}



//--------------------------------------------------------
/**
 *	Method      : DeltaController::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void DeltaController::get_device_property()
{
	/*----- PROTECTED REGION ID(DeltaController::get_device_property_before) ENABLED START -----*/

    //	Initialize property data members

    /*----- PROTECTED REGION END -----*/	//	DeltaController::get_device_property_before

	mandatoryNotDefined = false;
	set_status("Initializing....");

	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("IPAddress"));
	dev_prop.push_back(Tango::DbDatum("GroupNumber"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on DeltaControllerClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		DeltaControllerClass	*ds_class =
			(static_cast<DeltaControllerClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize IPAddress from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  iPAddress;
		else {
			//	Try to initialize IPAddress from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  iPAddress;
		}
		//	And try to extract IPAddress value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  iPAddress;

		//	Try to initialize GroupNumber from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  groupNumber;
		else {
			//	Try to initialize GroupNumber from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  groupNumber;
		}
		//	And try to extract GroupNumber value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  groupNumber;
		//	Property GroupNumber is mandatory, check if has been defined in database.
		check_mandatory_property(cl_prop, dev_prop[i]);


	}
	/*----- PROTECTED REGION ID(DeltaController::get_device_property_after) ENABLED START -----*/

    //	Check device property data members init

    /*----- PROTECTED REGION END -----*/	//	DeltaController::get_device_property_after

}
//--------------------------------------------------------
/**
 *	Method      : DeltaController::check_mandatory_property()
 *	Description : For mandatory properties check if defined in database.
 */
//--------------------------------------------------------
void DeltaController::check_mandatory_property(Tango::DbDatum &class_prop, Tango::DbDatum &dev_prop)
{
	//	Check if all properties are empty
	if (class_prop.is_empty() && dev_prop.is_empty())
	{
		TangoSys_OMemStream	tms;
		tms << endl <<"Property \'" << dev_prop.name;
		if (Tango::Util::instance()->_UseDb==true)
			tms << "\' is mandatory but not defined in database";
		else
			tms << "\' is mandatory but cannot be defined without database";
		string	status(get_status());
		status += tms.str();
		set_status(status);
		mandatoryNotDefined = true;
	/*----- PROTECTED REGION ID(DeltaController::check_mandatory_property) ENABLED START -----*/

        cerr << tms.str() << " for " << device_name << endl;

        /*----- PROTECTED REGION END -----*/	//	DeltaController::check_mandatory_property

	}
}


//--------------------------------------------------------
/**
 *	Method      : DeltaController::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void DeltaController::always_executed_hook()
{
	INFO_STREAM << "DeltaController::always_executed_hook()  " << device_name << endl;
	 
	if (mandatoryNotDefined)
	{
		string	status(get_status());
		Tango::Except::throw_exception(
					(const char *)"PROPERTY_NOT_SET",
					status.c_str(),
					(const char *)"DeltaController::always_executed_hook()");
	}

	/*----- PROTECTED REGION ID(DeltaController::always_executed_hook) ENABLED START -----*/

    //	code always executed before all requests

    /*----- PROTECTED REGION END -----*/	//	DeltaController::always_executed_hook
}




//--------------------------------------------------------
/**
 *	Method      : DeltaController::read_attr_hardware()
 *	Description : Hardware acquisition for attributes.
 */
//--------------------------------------------------------
void DeltaController::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "DeltaController::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(DeltaController::read_attr_hardware) ENABLED START -----*/

    //	Add your own code

    /*----- PROTECTED REGION END -----*/	//	DeltaController::read_attr_hardware

}


//--------------------------------------------------------
/**
 *	Read Current attribute
 *	Description: The DC current of the selected pole.
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------
void DeltaController::read_Current(Tango::Attribute &attr)
{
	DEBUG_STREAM << "DeltaController::read_Current(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(DeltaController::read_Current) ENABLED START -----*/


    //	Set the attribute value
    *attr_Current_read = powersupply->get_measure_current();
    attr.set_value(attr_Current_read);

    /*----- PROTECTED REGION END -----*/	//	DeltaController::read_Current
}
	
//--------------------------------------------------------
/**
 *	Write Current attribute values to hardware.
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------	
void DeltaController::write_Current(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "DeltaController::write_Current(Tango::Attribute &attr) entering... " << endl;
	
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	
	/*----- PROTECTED REGION ID(DeltaController::write_Current) ENABLED START -----*/

    powersupply->set_current(w_val);

    /*----- PROTECTED REGION END -----*/	//	DeltaController::write_Current
}

//--------------------------------------------------------
/**
 *	Read Voltage attribute
 *	Description: The measured voltage of the magnet. 
 *	             The Delta power supplies operate in voltage mode which means that an output voltage must be set before setting the output current. 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------
void DeltaController::read_Voltage(Tango::Attribute &attr)
{
	DEBUG_STREAM << "DeltaController::read_Voltage(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(DeltaController::read_Voltage) ENABLED START -----*/

    //	Set the attribute value
    *attr_Voltage_read = powersupply->get_measure_voltage();
    attr.set_value(attr_Voltage_read);

    /*----- PROTECTED REGION END -----*/	//	DeltaController::read_Voltage
}
	
//--------------------------------------------------------
/**
 *	Write Voltage attribute values to hardware.
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------	
void DeltaController::write_Voltage(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "DeltaController::write_Voltage(Tango::Attribute &attr) entering... " << endl;
	
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	
	/*----- PROTECTED REGION ID(DeltaController::write_Voltage) ENABLED START -----*/

    powersupply->set_voltage(w_val);

    /*----- PROTECTED REGION END -----*/	//	DeltaController::write_Voltage
}

//--------------------------------------------------------
/**
 *	Read Impedance attribute
 *	Description: Set impedance of load to correctly set voltage of combined power supply (group 4)
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------
void DeltaController::read_Impedance(Tango::Attribute &attr)
{
	DEBUG_STREAM << "DeltaController::read_Impedance(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(DeltaController::read_Impedance) ENABLED START -----*/

    *attr_Impedance_read = this->impedance;
    //	Set the attribute value
    attr.set_value(attr_Impedance_read);

    /*----- PROTECTED REGION END -----*/	//	DeltaController::read_Impedance
}
	
//--------------------------------------------------------
/**
 *	Write Impedance attribute values to hardware.
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------	
void DeltaController::write_Impedance(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "DeltaController::write_Impedance(Tango::Attribute &attr) entering... " << endl;
	
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	
	/*----- PROTECTED REGION ID(DeltaController::write_Impedance) ENABLED START -----*/


    this->impedance = w_val;
    /*----- PROTECTED REGION END -----*/	//	DeltaController::write_Impedance
}

//--------------------------------------------------------
/**
 *	Read Vlim attribute
 *	Description: Set Vlim to correctly set voltage of combined power supply (group 4)
 *	             If set current is I, V = Vlim*I*Impedance
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------
void DeltaController::read_Vlim(Tango::Attribute &attr)
{
	DEBUG_STREAM << "DeltaController::read_Vlim(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(DeltaController::read_Vlim) ENABLED START -----*/
    *attr_Vlim_read = this->vlim;
    //	Set the attribute value
    attr.set_value(attr_Vlim_read);

    /*----- PROTECTED REGION END -----*/	//	DeltaController::read_Vlim
}
	
//--------------------------------------------------------
/**
 *	Write Vlim attribute values to hardware.
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------	
void DeltaController::write_Vlim(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "DeltaController::write_Vlim(Tango::Attribute &attr) entering... " << endl;
	
	//	Retrieve write value
	Tango::DevDouble	w_val;
	attr.get_write_value(w_val);
	
	/*----- PROTECTED REGION ID(DeltaController::write_Vlim) ENABLED START -----*/

    this->vlim = w_val;

    /*----- PROTECTED REGION END -----*/	//	DeltaController::write_Vlim
}

//--------------------------------------------------------
/**
 *	Read MaxCurrent attribute
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------
void DeltaController::read_MaxCurrent(Tango::Attribute &attr)
{
	DEBUG_STREAM << "DeltaController::read_MaxCurrent(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(DeltaController::read_MaxCurrent) ENABLED START -----*/

	//	Set the attribute value
	attr.set_value(attr_MaxCurrent_read);

	/*----- PROTECTED REGION END -----*/	//	DeltaController::read_MaxCurrent
}

//--------------------------------------------------------
/**
 *	Read MaxVoltage attribute
 *	Description: 
 *
 *	Data type:	Tango::DevDouble
 *	Attr type:	Scalar 
 */
//--------------------------------------------------------
void DeltaController::read_MaxVoltage(Tango::Attribute &attr)
{
	DEBUG_STREAM << "DeltaController::read_MaxVoltage(Tango::Attribute &attr) entering... " << endl;
	/*----- PROTECTED REGION ID(DeltaController::read_MaxVoltage) ENABLED START -----*/

	//	Set the attribute value
	attr.set_value(attr_MaxVoltage_read);

	/*----- PROTECTED REGION END -----*/	//	DeltaController::read_MaxVoltage
}



//--------------------------------------------------------
/**
 *	Method      : DeltaController::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any at server startup
 *	              for specified device.
 */
//--------------------------------------------------------
void DeltaController::add_dynamic_attributes()
{
	
	/*----- PROTECTED REGION ID(DeltaController::add_dynamic_attributes) ENABLED START -----*/

    //	Add your own code to create and add dynamic attributes if any

    /*----- PROTECTED REGION END -----*/	//	DeltaController::add_dynamic_attributes()
}



//========================================================
//	Command execution methods
//========================================================

//--------------------------------------------------------
/**
 *	Execute the State command:
 *	Description: This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 *	@param argin none.
 *	@returns State Code
 */
//--------------------------------------------------------
Tango::DevState DeltaController::dev_state()
{
	DEBUG_STREAM << "DeltaController::State()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DeltaController::dev_state) ENABLED START -----*/

    Tango::DevState argout = DeviceImpl::dev_state();

    if (Tango::FAULT != argout && Tango::UNKNOWN != argout && this->groupNumber >= 1 && this->groupNumber <= 4)
    {
        try
        {
            if (powersupply->get_output_state() == MAGNET_OFF)
            {
                argout = Tango::OFF;
            }
            else // it's a boolean if (channel->get_state() == MAGNET_ON) {
                if (powersupply->is_current_moving())
            {
                argout = Tango::MOVING;
            }
            else
            {   //Group 1 PS do not have any output on/off function
                if(this->groupNumber == 1 && this->isDeviceOn!=true) {argout = Tango::OFF;}
                else{ argout = Tango::ON;} 
            }
        }
        catch (yat::Exception &e)
        {
            std::stringstream message;
            for (unsigned int i = 0; i < e.errors.size(); i++)
            {
                message << e.errors[i].reason << " , " << e.errors[i].desc << " , " << e.errors[i].origin << " , " << e.errors[i].code << std::endl;
            }
            argout = Tango::FAULT;
            this->set_status(message.str());
        }
        catch (...)
        {
            ERROR_STREAM << "ERRRRRRROR" << std::endl;
            argout = Tango::UNKNOWN;
        }
    }

    /*----- PROTECTED REGION END -----*/	//	DeltaController::dev_state

	set_state(argout);    // Give the state to Tango.
	if (argout!=Tango::ALARM)
		DeviceImpl::dev_state();
	return get_state();  // Return it after Tango management.

}

//--------------------------------------------------------
/**
 *	Execute the Status command:
 *	Description: This command gets the device status (stored in its <i>device_status</i> data member) and returns it to the caller.
 *
 *	@param argin none.
 *	@returns Status description
 */
//--------------------------------------------------------
Tango::ConstDevString DeltaController::dev_status()
{
	DEBUG_STREAM << "DeltaController::Status()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DeltaController::dev_status) ENABLED START -----*/

    string status = DeviceImpl::dev_status();
    //	Add your own status management

    /*----- PROTECTED REGION END -----*/	//	DeltaController::dev_status

	set_status(status);               // Give the status to Tango.
	return DeviceImpl::dev_status();  // Return it.

}

//--------------------------------------------------------
/**
 *	Execute the On command:
 *	Description: Turns on power supply output.
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
void DeltaController::on()
{
	DEBUG_STREAM << "DeltaController::On()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DeltaController::on) ENABLED START -----*/
    // TODO: add status text depending on group
    //	Add your own code
    if (powersupply->get_output_state() == MAGNET_OFF)
    {
        powersupply->set_output_state(MAGNET_ON);
    }
    if(this->groupNumber == 1) this->isDeviceOn = true;
    
    /*----- PROTECTED REGION END -----*/	//	DeltaController::on

}

//--------------------------------------------------------
/**
 *	Execute the Off command:
 *	Description: Turns off power supply output.
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
void DeltaController::off()
{
	DEBUG_STREAM << "DeltaController::Off()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DeltaController::off) ENABLED START -----*/

    //	Add your own code
    // TODO: add status text depending on group
    if (powersupply->get_output_state() == MAGNET_ON)
    {
        powersupply->set_output_state(MAGNET_OFF);
    }

    if(this->groupNumber == 1) this->isDeviceOn = false;

    /*----- PROTECTED REGION END -----*/	//	DeltaController::off

}

//--------------------------------------------------------
/**
 *	Execute the Reset command:
 *	Description: Reset faults and alarms
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
void DeltaController::reset()
{
	DEBUG_STREAM << "DeltaController::Reset()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(DeltaController::reset) ENABLED START -----*/

    //	Add your own code
    powersupply->clear_all_err();
    powersupply->set_current(0.0);
    powersupply->set_voltage(0.0);

    /*----- PROTECTED REGION END -----*/	//	DeltaController::reset

}


	/*----- PROTECTED REGION ID(DeltaController::namespace_ending) ENABLED START -----*/

//	Additional Methods


/*----- PROTECTED REGION END -----*/	//	DeltaController::namespace_ending
} //	namespace
