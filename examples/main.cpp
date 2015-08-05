#include <iostream>
#include <stdexcept>

#include "../src/service.h"

int main()
{   
    try
    {
        CREATE_SERVICE({


           //-- Sample code:
           static int i=0;
           if (i++ > 10)
               stop();
           std::cout << "i = " << i << "\n";


        }, 1000);
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

    return 0;
}
