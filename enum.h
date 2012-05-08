#ifndef ENUM_H
#define ENUM_H

enum StartParam {ReadFromFile = 2, LoadOneDevice = 4};
enum StatusOfWork{DevNotSet = 1, Work = 0, Error = 2};
enum Options{HELP = 'h', TANGO_HOST = 't', DEVICE = 'd', ATTRIBUTE = 'a', FILE_NAME = 'f', COMMAND = 'c', UNKNOWN_SYMBOL = '?'};
enum VideoSettingsWinValue{BRIGHTNESS_SNAPSHOT = 0, CONTRAST_SNAPSHOT = 1, GAMMA_SNAPSHOT = 2, ROTATION_SNAPSHOT = 3, SCALE_SNAPSHOT = 4,
                           BRIGHTNESS_REALTIME = 5, CONTRAST_REALTIME = 6, GAMMA_REALTIME = 7, ROTATION_REALTIME = 8, SCALE_REALTIME = 9};
#endif // ENUM_H
