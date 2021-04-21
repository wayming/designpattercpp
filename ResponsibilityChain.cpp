#include <iostream>
#include <algorithm>
#include <memory>
#include <map>

using namespace std;

class Car
{
    public:
        bool EngineCheck()
        {
            cout << "Engine works fine." << endl;
            return true;
        }

        bool TransmissionCheck()
        {
            cout << "Transmission works fine." << endl;
            return true;
        }

        bool ComputerCheck()
        {
            cout << "Computer works fine." << endl;
            return true;
        }
};

class Handler
{
    public:
        virtual void setNext(Handler* h) = 0;
        virtual bool handle(Car& c) = 0;
};
class CarDiagnoser : public Handler
{
    public:
        void setNext(Handler* h) { oNext = h; };
        bool handle(Car& c)
        {
            if (oNext != NULL) {
                return oNext->handle(c);
            }
            return true;
        }
    
    private:
        Handler* oNext{NULL};

};
class EngineDiagnoser : public CarDiagnoser
{
    public:
        bool handle(Car& c)
        {
            if (c.EngineCheck()) {
               return  CarDiagnoser::handle(c);
            } else {
                return false;
            }
        }
};
class TransmissionDiagnoser : public CarDiagnoser
{
    public:
        bool handle(Car& c)
        {
            if (c.TransmissionCheck()) {
                return CarDiagnoser::handle(c);
            } else {
                return false;
            }
        }
};
class ComputerDiagnoser : public CarDiagnoser
{
    public:
        bool handle(Car& c)
        {
            if (c.ComputerCheck()) {
                return CarDiagnoser::handle(c);
            } else {
                return false;
            }
        }
};

int main()
{
    Car c;

    CarDiagnoser diag;
    EngineDiagnoser eDiag;
    TransmissionDiagnoser tDiag;
    ComputerDiagnoser cDiag;
    
    tDiag.setNext(&cDiag);
    eDiag.setNext(&tDiag);
    diag.setNext(&eDiag);

    diag.handle(c);
}