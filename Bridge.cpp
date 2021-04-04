#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

class Car
{
    public:
        void engineOn() { cout << "Turn on engine" << endl; }
        void engineOff() { cout << "Turn off engine" << endl; }
        void rightSignalOn() { cout << "Turn on right signal" << endl; }
        void rightSignalOff() { cout << "Turn off right signal" << endl; }
        void leftSignalOn() { cout << "Turn on left signal" << endl; }
        void leftSignalOff() { cout << "Turn off left signal" << endl; }
        void handBrakeOn() { cout << "Turn on handBrake" << endl; }
        void handBrakeOff() { cout << "Turn off handBrake" << endl; }
        void brake() { cout << "Brake" << endl; }
        void wheelLeft() { cout << "Left turn wheel" << endl; }
        void wheelRight() { cout << "Right turn wheel" << endl; }
        void wheelStright() { cout << "Stright wheel" << endl; }
        virtual void accelerate() = 0;
        virtual void decelerate() = 0;
};

class Pedal
{
    public:
        virtual void depress() = 0;
        virtual void release() = 0;
};
class ClutchPedal : public Pedal
{
    public:
        void depress() { cout << "Clutch Pedal Depressed" << endl; }
        void release() { cout << "Clutch Pedal Released" << endl; }
};
class AcceleratorPedal : public Pedal
{
    public:
        void depress() { cout << "Accelerator Pedal Depressed" << endl; }
        void release() { cout << "Accelerator Pedal Released" << endl; }
};
class Gear
{
    public:
        void low() { cout << "Low Gear" << endl; }
        void high() { cout << "High Gear" << endl; }
};
class ManualCar : public Car
{
    public:
        void accelerate()
        {
            oClutch.depress();
            oAccelerator.depress();
            oGear.high();
            oClutch.release();
        }
        void decelerate()
        {
            oClutch.depress();
            oAccelerator.release();
            oGear.low();
            oClutch.release();
        }
    private:
        ClutchPedal oClutch;
        AcceleratorPedal oAccelerator;
        Gear oGear;

};
class AutoCar : public Car
{
    public:
        void accelerate()
        {
            oAccelerator.depress();
        }
        void decelerate()
        {
            oAccelerator.release();
        }
    private:
        AcceleratorPedal oAccelerator;
};

class CarFactory
{
    public:
        virtual unique_ptr<Car> NewCar() = 0;
};

class ManualCarFactory : public CarFactory
{
    public:
        unique_ptr<Car> NewCar()
        {
            return make_unique<ManualCar>();
        }
};
class AutoCarFactory : public CarFactory
{
    public:
        unique_ptr<Car> NewCar()
        {
            return make_unique<AutoCar>();
        }
};


class Driver {
    public:
        Driver(CarFactory& carFactory) { oCar = carFactory.NewCar(); }
        void start()
        {
            oCar->engineOn();
            oCar->handBrakeOff();
            oCar->accelerate();
        }
        void stop()
        {
            oCar->decelerate();
            oCar->handBrakeOn();
            oCar->engineOff();
        }
        void changeToRightLane()
        {
            oCar->rightSignalOn();
            oCar->wheelRight();
            oCar->wheelStright();
            oCar->rightSignalOff();
        }
        void changeToLeftLane()
        {
            oCar->leftSignalOn();
            oCar->wheelRight();
            oCar->wheelStright();
            oCar->leftSignalOff();
        }
    private:
        unique_ptr<Car> oCar;
};

int main()
{
    ManualCarFactory manualFactory;
    AutoCarFactory autoFactory;
    
    Driver d1(autoFactory);
    d1.start();
    d1.changeToRightLane();
    d1.changeToLeftLane();
    d1.stop();

    Driver d2(manualFactory);
    d2.start();
    d2.changeToRightLane();
    d2.changeToLeftLane();
    d2.stop();

}