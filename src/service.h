/**
  * @file: service.h
  * @brief: structure to create linux service
  * @date: Aug 2015
  * @version: 1
  * @author: <a href="mailto:aref.moqadam@gmail.com">Aref Moqadam</a>
  */

#ifndef SERVICE_H
#define SERVICE_H

#include <stdlib.h>

#define CREATE_SERVICE(func, intv) \
    class _Service : public GSRC::Service { \
    private: void update() { func } \
    } _service; _service.start(intv); \
    exit(EXIT_SUCCESS);


namespace GSRC
{
    /**
     * @brief: change the Seassion ID of the current process after forking
     * @return: new Session ID
     */
    pid_t _changeSID();

    /**
     * @brief: Fork from parent process
     */
    void  _forkTheProcess();

    /**
     * @brief: Change the Current Directory to '/' for the process
     */
    void  _changeDirectory();

    /**
     * @brief: Close standard input and output (std::cin, std::cout and std::cerr)
     */
    void  _closeStdIO();

    /**
     * @brief: Run deamon required functions
     * @param shouldFork: Should fork from parent or stay in the same process
     * @param shouldUnMask: Should un-mask the file session
     * @param shouldChangeDir: Should change the current directory to root
     * @param shouldCloseStdIO: Should hide every standard input/output
     */
    void  run(bool shouldFork = true, bool shouldUnMask = true, bool shouldChangeDir = true, bool shouldCloseStdIO = true);

    /**
     * @class: Service
     * @brief: Class containing deamon requirements
     */
    class Service
    {
    public:
        /**
         * @brief: Default Constructor
         * @param shouldFork: Should fork from parent or stay in the same process
         * @param shouldUnMask: Should un-mask the file session
         * @param shouldChangeDir: Should change the current directory to root
         * @param shouldCloseStdIO: Should hide every standard input/output
         */
        Service(bool shouldFork = true, bool shouldUnMask = true, bool shouldChangeDir = true, bool shouldCloseStdIO = true);

        /**
         * @brief: Start main loop for the service
         * @param Interval: interval between each cycle in milliseconds
         * @note: Note that this function lockes the process. In the other words
         *        program flow stops by calling this function until the service
         *        call stop function.
         */
        void start(float Interval=100);

        /**
         * @brief: Stop the service
         */
        void stop();

        /**
         * @return whether the service is running or not
         */
        bool isRunning() const;

        /**
         * @return the interval between each cycle
         */
        float interval() const;

        /**
         * @brief: Set interval between each cycle. This function can be called anywhere in the program
         * @param Interval in milliseconds
         */
        void setInterval(float Interval);

    protected:
        /**
         * @brief: virtual update function that is called on each cycle
         */
        virtual void update() {}

    private:
        pid_t _pid;
        bool _isRunning;
        float _interval;
    };
}

#endif // SERVICE_H
