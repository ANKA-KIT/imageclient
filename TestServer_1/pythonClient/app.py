import sys
from PyTango.device_proxy import DeviceProxy
from PyTango.device_proxy import DevFailed
import time
import datetime

if __name__ == "__main__":
  dev = DeviceProxy("anka-tango3.ka.fzk.de:10000/sys/tg_test/mytest");
 #dev.command_inout("StartRecording");
  
  start = time.time();
 # data = dev.read_attribute("ScalarStr");
 #str = dev.command_inout("MyReadScalarCommand")
  data = dev.read_attribute("ScalarStr");
  print time.time() - start;

#  import time
#millis = int(round(time.time() * 1000))
#print millis
#Quick'n'easy. Thanks all, sorry for the brain fart.

  
  #dev.command_inout("StopRecording");
  print data.value;
  