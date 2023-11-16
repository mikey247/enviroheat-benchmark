#ifndef SYSTEM_TEST
#define SYSTEM_TEST
#include <string>


class SystemTest{
public:
    SystemTest();
    void warmUp();
    void idling();
    void drainage();
    void v40();

    bool isTmaxReached();
    std::string getPumpStatus();
    std::string getResistanceStatus();
private:
};


#endif