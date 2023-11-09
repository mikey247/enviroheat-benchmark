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

    bool isTmaxReached() const;
    std::string getPumpStatus() const;
    std::string getResistanceStatus() const;

private:
};


#endif