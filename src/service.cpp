/**
  * @file: service.cpp
  * @brief: structure to create linux service
  * @date: Aug 2015
  * @version: 1
  * @author: <a href="mailto:aref.moqadam@gmail.com">Aref Moqadam</a>
  */

#include "service.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdexcept>

void GSRC::_forkTheProcess()
{
    pid_t pid = fork();

    if (pid < 0) //-- On failure
        throw(std::runtime_error("Failed to fork the process..."));

    if (pid > 0) //-- On parental
        exit(EXIT_SUCCESS);
}

pid_t GSRC::_changeSID()
{
    pid_t sid = setsid();
    if (sid < 0)
        throw(std::runtime_error("Failed to set the Session ID (SID)..."));
    return sid;
}

void GSRC::_changeDirectory()
{
    if (chdir("/") < 0)
        throw(std::runtime_error("Failed to change process directory..."));
}

void GSRC::_closeStdIO()
{
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void GSRC::_run(bool shouldFork, bool shouldUnMask, bool shouldChangeDir, bool shouldCloseStdIO)
{
    //-- Fork off the parent process
    if (shouldFork)
        _forkTheProcess();

    //-- Change the file mode mask
    if (shouldUnMask)
        umask(0);

    if (shouldChangeDir)
        _changeDirectory();

    /* Open any logs here */

    //-- Create a new SID for the child process
    if (shouldFork)
        _changeSID();

    //-- Close out the standard file descriptors
    if (shouldCloseStdIO)
        _closeStdIO();
}


GSRC::Service::Service(bool shouldFork, bool shouldUnMask, bool shouldChangeDir, bool shouldCloseStdIO)
{
    run(shouldFork, shouldUnMask, shouldChangeDir, shouldCloseStdIO);
}

void GSRC::Service::start(float Interval)
{
    _interval = Interval;
    _isRunning = true;

    while (_isRunning)
    {
        update();
        usleep(_interval * 1000);
    }
}

void GSRC::Service::stop()
{
    _isRunning = false;
}

bool GSRC::Service::isRunning() const
{
    return _isRunning;
}

float GSRC::Service::interval() const
{
    return _interval;
}

void GSRC::Service::setInterval(float Interval)
{
    _interval = Interval;
}
