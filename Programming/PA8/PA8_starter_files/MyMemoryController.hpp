/* 
 * MyMemoryController.hpp
 * 
 * Done for you. You should not modify this file.
*/


#ifndef MY_MEMORY_CONTROLLER_HPP
#define MY_MEMORY_CONTROLLER_HPP

#include "BaseMemoryController.hpp"

class MyMemoryController : public BaseMemoryController
{
    private:

    public:
        MyMemoryController(uint32_t base_address, uint32_t total_bytes);
        ~MyMemoryController();

};

#endif