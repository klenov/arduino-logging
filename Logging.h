#ifndef LOGGING_H
#define LOGGING_H
#include <inttypes.h>
#include <stdarg.h>
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
//#include "pins_arduino.h"
extern "C" {
  #include <avr/io.h>
}


#define LOG_LEVEL_NOOUTPUT 0
#define LOG_LEVEL_ERRORS 1
#define LOG_LEVEL_INFOS 2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_VERBOSE 4

// default loglevel if nothing is set from user
#define LOGLEVEL LOG_LEVEL_DEBUG


#define CR "\n"
#define LOGGING_VERSION 1

/*!
* Logging is a helper class to output informations over
* RS232. If you know log4j or log4net, this logging class
* is more or less similar ;-)
* Different loglevels can be used to extend or reduce output
* All methods are able to handle any number of output parameters.
* All methods print out a formated string (like printf).
* To reduce output and program size, reduce loglevel.
*
* Output format string can contain below wildcards. Every wildcard
* must be start with percent sign (\%)
*
*/
class Logging {
private:
    int _level;
    long _baud;
    Print* _printer;
public:
    /*!
	 * default Constructor
	 */
    Logging()
      : _level(LOG_LEVEL_NOOUTPUT),
        _baud(0),
        _printer(NULL) {}

    /*
    * You need to initialize the baud rate
    * yourself, if printer happens to be a serial port.
    * \param level - logging levels <= this will be logged.
    * \param printer - place that logging output will be sent to.
    * \return void
    *
    */
    void Init(int level, Print *printer);

    /**
	* Output an error message. Output message contains
	* ERROR: followed by original msg
	* Error messages are printed out, at every loglevel
	* except 0 ;-)
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/
    void Error(const char* msg, ...);

    /**
	* Output an info message. Output message contains
	* Info messages are printed out at l
	* loglevels >= LOG_LEVEL_INFOS
	*
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/

   void Info(const char* msg, ...);

    /**
	* Output an debug message. Output message contains
	* Debug messages are printed out at l
	* loglevels >= LOG_LEVEL_DEBUG
	*
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/

    void Debug(const char* msg, ...);

    /**
	* Output an verbose message. Output message contains
	* Debug messages are printed out at l
	* loglevels >= LOG_LEVEL_VERBOSE
	*
	* \param msg format string to output
	* \param ... any number of variables
	* \return void
	*/

    void Verbose(const char* msg, ...);


private:
    void print(const char *format, va_list args);
};

extern Logging Log;
#endif
