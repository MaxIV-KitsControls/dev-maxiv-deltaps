import PyTango
from symbol import try_stmt
import unittest
import time
import exceptions
import math

class Itest2811ChannelTestCase(unittest.TestCase):

    POWERSUPPLIES = ( { "DEVICE" : "test/itest/2811-A-1",
                        "IP" : "192.168.150.107",
                        "CHANNEL" : 1
                      }, 
                      { "DEVICE" : "test/itest/2811-A-2",
                        "IP" : "192.168.150.101",
                        "CHANNEL" : 1
                      }) 

    CURRENT_TOLERANCE = 0.01
    
    def setUp(self):
        print "In method", self._testMethodName
        for ps in self.POWERSUPPLIES:
            proxy = PyTango.DeviceProxy(ps["DEVICE"])
            proxy.put_property({"IP":ps["IP"]})
            proxy.put_property({"Channel":ps["CHANNEL"]})
            proxy.init()
            ps["PROXY"]=proxy

    def tearDown(self):
        for ps in self.POWERSUPPLIES:
            proxy = ps["PROXY"]
            proxy.reset()
            self.waitState(proxy, PyTango.DevState.MOVING, PyTango.DevState.ON)
            proxy.off()
        
    def testInit(self):
        not_expected = PyTango.DevState.FAULT
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            "when:"
            device.init()
            actual = device.State()

            "then:"
            self.assertNotEquals(not_expected, actual, "Not the expected state after changing with the good properties  : %s (not expected : %s)" % (actual, not_expected))
            
    def testWrongIP(self):
        expected = PyTango.DevState.FAULT
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]

            "when: Set the wrong IP"
            device.put_property({"IP":"127.0.0.1"}) #hope the device doesn't run on the device itself ;-)

            device.init()
            actual = device.State()

            "then:"
            self.assertEquals(expected, actual, "The state is not correctly set after changing the IP address  : %s (expected : %s)" % (actual, expected))
            
            "when: Restore the good IP"
            device.put_property({"IP":ps["IP"]})
            device.init()
            actual = device.State()

            "then:"
            self.assertNotEquals(expected, actual, "Not the expected state after changing with the good properties  : %s (not expected : %s)" % (actual, expected))

    def testWrongChannel(self):
        expected = PyTango.DevState.FAULT
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            
            "when: Set the wrong Channel"
            device.put_property({"Channel":-1})

            device.init()
            actual = device.State()

            "then:"
            self.assertEquals(expected, actual, "The state is not correctly set in case of a wrong channel number : %s (expected : %s)" % (actual, expected))
            
            "when: Restore the good Channel"
            device.put_property({"Channel":ps["CHANNEL"]})
            device.init()
            actual = device.State()

            "then:"
            self.assertNotEquals(expected, actual, "Not the expected state after changing with the good properties  : %s (not expected : %s)" % (actual, expected))

    def testReset(self):
        expected = 0.0
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            device.On()
            
            "when :"
            device.Current = .5
            device.Reset()
            self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)
            actual = device.Current

            "then :"
            self.assertMoreOrLessEquals(expected, actual, self.CURRENT_TOLERANCE,"**ERROR** Reset has no effect : %s   (expected %s)" % (actual, expected) )

    def testStateMoving(self):
        expected = PyTango.DevState.MOVING
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            
            "setup:"
            device.On()
            device.Current = 0.0
            self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)
            
            "when:"
            device.Current = 3.0
            actual = device.state()
            
            "then:"
            self.assertEquals(expected, actual, "The state is not correctly set after setting a long action : %s (expected : %s)" % (actual, expected))
            self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)


    def testStateOn(self):
        expected = PyTango.DevState.ON
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            
            "when:"
            device.On()
            self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)
            actual = device.state()

            "then:"
            self.assertEquals(expected, actual, "The state is not correctly set after the On command  : %s (expected : %s)" % (actual, expected))

    def testStateOff(self):
        expected = PyTango.DevState.OFF
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            
            "when:"
            device.Off()
            actual = device.state()

            "then:"
            self.assertEquals(expected, actual, "The state is not correctly set after the Off command  : %s (expected : %s)" % (actual, expected))
    
    def testTwiceOn(self):
        expected = 1.3
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            
            "setup:"
            if device.state()==PyTango.DevState.ON :
                device.Off()

            "when: On command is call twice"
            device.On()
            self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)

            device.Current = expected
            self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)

            "then: No effect"
            try:
               device.On()
               self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)

            except PyTango.DevFailed:
               self.fail("On() raised Pytango.DevFailed after called twice!")
            
            actual = device.Current 
            self.assertMoreOrLessEquals(expected, actual, self.CURRENT_TOLERANCE,"When execute On() twice it change the current !!!:%s (expected:%s)" % (actual, expected))


    def testTwiceOff(self):
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            
            "setup:"
            if device.state()==PyTango.DevState.OFF :
                device.On()

            "when: Off command is call twice"
            device.Off()

            "then: No effect"
            try:
               device.Off()
            except PyTango.DevFailed:
               self.fail("Off() raised Pytango.DevFailed after called twice!")
            
    def testCurrent(self):
        attribute = "Current"
        # Absolute random valuess
        values = [-2.0, -0.45, 0.0, 1.38, 2.0]
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            device.On()
            self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)
            
            for expected in values :
                self._write_wait_read_test(device, attribute, expected, self.CURRENT_TOLERANCE)


    def testWrongCurrent(self):
        attribute = "Current"
        wrong_values = [-20.0, 5.01]
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            
            for wrong in wrong_values :
                "when:"
                self.assertRaises(PyTango.DevFailed, lambda : device.write_attribute(attribute, wrong) )


    def testVoltageAndImpedance(self):
        attribute = "Voltage"
        # Absolute random valuess
        values = [-2.0, -0.45, 1.38, 2.0]
        for ps in self.POWERSUPPLIES:
            device = ps["PROXY"]
            device.On()
            
            for value in values :
                "when:"
                device.Current = value
                self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)

                "then:"
                actual = device.Voltage
                expected = 0.0
                self.assertNotEquals(expected, actual, "The voltage (or Impedance) doesn't correspond to the current : %s (NOT expected : %s)" % (actual, expected))

                actual = device.Impedance
                expected = 0.0
                self.assertNotEquals(expected, actual, "The voltage (or Impedance) doesn't correspond to the current : %s (NOT expected : %s)" % (actual, expected))
                # Considering only the resistance of impedance ?
               
                actual = device.Voltage
                expected = device.Impedance * device.Current

                "then:"
                self.assertMoreOrLessEquals(expected, actual, self.CURRENT_TOLERANCE, "The voltage (or Impedance) doesn't correspond to the current : %s (expected : %s)" % (actual, expected))

#Utilities
    def waitState(self, device, running_state, expected_state, timeout=10):
        start = time.clock()
      
        while time.clock()-start < timeout:
           current = device.state()
           if current == expected_state or current != running_state:
              break;
           else :
              time.sleep(.2)

#TEST UTILITIES
    def _write_wait_read_test(self, device, attribute, expected, tolerance=0.0 ):
            "when:"
            print "%s %s %s" % (device.name(), attribute, expected)
            #setattr(device, attribute, expected)
            device.write_attribute(attribute, expected)
            self.waitState(device, PyTango.DevState.MOVING, PyTango.DevState.ON)
            actual = getattr(device, attribute)

            "then:"
            if tolerance==0.0 :
               self.assertEquals(expected, actual, "%s is not set correctly : %s (expected : %s)" % (attribute, actual, expected))
            else:
               self.assertMoreOrLessEquals(expected, actual, tolerance, "The attribute %s is not in the expected tolerance(%s): %s (expected %s)" % (attribute, tolerance, actual, expected))

    def assertMoreOrLessEquals(self, expected, actual, tolerance, message):
        diff = math.fabs(expected - actual)
        self.assertTrue( diff<=tolerance, message)

if __name__ == '__main__':
    suiteFew = unittest.TestSuite()
    suiteFew.addTest(Itest2811ChannelTestCase("testWrongIP"))
    unittest.TextTestRunner(verbosity=2).run(suiteFew)
    #unittest.TextTestRunner(verbosity=2).run(unittest.makeSuite(Itest2811ChannelTestCase))

