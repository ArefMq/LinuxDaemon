#include <iostream>
#include <stdexcept>

#include "../src/service.h"

class MyService : public GSRC::Service
{
private:
    void update()
    {
        //-- Sample code:
        static int i=0;
        if (i++ > 10)
            stop();
        std::cout << "i = " << i << "\n";
    }
};

int main()
{
    try
    {
        MyService myService; //-- Do the required service stuff; such as forking, etc.
        myService.start(1000); //-- Run the service iteratively and lock the process flow.

        //-- When the flow of the program reaches here, it means
        //   that the service has stopped successfully.
        return 0;
    }
    catch (std::runtime_error& ex)
    {
        std::cerr << "Service terminated because:\n\t" << ex.what() << "\n\n";
        return -1;
    }
    catch (std::exception& ex)
    {
        std::cerr << "Service terminated because:\n\t" << ex.what() << "\n\n";
        return -1;
    }
    catch (...)
    {
        std::cerr << "Service terminated duo to some unknown reasons...\n\n";
        return -1;
    }

    return 0; //-- Technically no need for this! :D
}
