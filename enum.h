#ifndef ENUM_H
#define ENUM_H

enum StartParam {ReadFromFile = 2, LoadOneDevice = 4};
enum StatusOfWork{DevNotSet = 1, Work = 0, Error = 2};
enum Options{HELP = 'h', TANGO_HOST = 't', DEVICE = 'd', ATTRIBUTE = 'a', FILE_NAME = 'f', COMMAND = 'c', UNKNOWN_SYMBOL = '?'};
#endif // ENUM_H
