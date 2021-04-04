#include <iostream>
#include <memory>

using namespace std;
class Car
{
    public:
        virtual void turnSignalOn() = 0;
        virtual void turnSignalOff() = 0;
        virtual void wiperOn() = 0;
        virtual void wiperOff() = 0;
        virtual ~Car() {}
};
// Existing class
class USCar : public Car
{
    public:
        virtual void turnSignalOn() { cout << "left level on " << endl; oLeftLevel = true; }
        virtual void turnSignalOff() { cout << "left level off " << endl; oLeftLevel = false; }
        virtual void wiperOn() { cout << "right level on " << endl; oRightLevel = true; }
        virtual void wiperOff() { cout << "right level off " << endl; oRightLevel = false; }
        USCar() {}
        USCar(const USCar&) = delete;
        USCar& operator=(const USCar&) = delete;
        virtual ~USCar() {}
    private:
        bool oLeftLevel = false; // Turn signal
        bool oRightLevel = false; // Wiper control
};
class Driver
{
    public:
        Driver(unique_ptr<USCar> car) : oCar{move(car)} {}
        void changeLane() noexcept
        {
            oCar->turnSignalOn();
            oCar->turnSignalOff();
        }
        void cleanWindow() noexcept
        {
            oCar->wiperOn();
            oCar->wiperOff();
        }
    private:
        unique_ptr<USCar> oCar;
};

// New class
class AUCar : public Car
{
    public:
        void turnSignalOn() { cout << "right level on " << endl; oRightLevel = true; }
        void turnSignalOff() { cout << "right level off " << endl; oRightLevel = false; }
        void wiperOn() { cout << "left level on " << endl; oLeftLevel = true; }
        void wiperOff() { cout << "left level off " << endl; oLeftLevel = false; }
        AUCar() {}
        AUCar(const AUCar&) = delete;
        AUCar& operator=(const AUCar&) = delete;
    private:
        bool oLeftLevel = false; //  Wiper control
        bool oRightLevel = false; // Turn signal
};
class CarAdapterForAUCar: public USCar
{
    public:
        void turnSignalOn() { oCar.turnSignalOn(); }
        void turnSignalOff() { oCar.turnSignalOff(); }
        void wiperOn() { oCar.wiperOn(); }
        void wiperOff() { oCar.wiperOff(); }
    private:
        AUCar oCar;
};

int main()
{
    Driver d(make_unique<USCar>());
    d.changeLane();
    d.cleanWindow();

    // Compile error
    // Driver d2(make_unique<AUCar>());
    Driver d2(make_unique<CarAdapterForAUCar>());
    d2.changeLane();
    d2.cleanWindow();
    
}