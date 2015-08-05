#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include "../src/service.h"

int main()
{
    try
    {
        GSRC::run(true, true, true, false); //-- Run the service stuff manually.

        for (;;)
        {
            //-- Sample code:
            static int i=0;
            if (i++ > 10)
                break;
            std::cout << "i = " << i << "\n";

        }

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

