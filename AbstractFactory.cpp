#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class AutoTransmission {
    public:
        virtual void whoAmI() = 0;
};

class ManualTransmission {
    public:
        virtual void whoAmI() = 0;
};


class AutoToyotaMake : public AutoTransmission{
    public:
        void whoAmI() { cout << "Auto Transmission car made by Toyota" << endl; }
};

class AutoVolvoMake : public AutoTransmission{
    public:
        void whoAmI() { cout << "Auto Transmission car made by Volvo" << endl; }
};

class ManualToyotaMake : public ManualTransmission{
    public:
        void whoAmI() { cout << "Manual Transmission car made by Toyota" << endl; }
};

class ManualVolvoMake : public ManualTransmission{
    public:
        void whoAmI() { cout << "Manual Transmission car made by Volvo" << endl; }
};


class CarFactory {
    public:
        virtual unique_ptr<AutoTransmission> newAutoTransmissionCar() = 0;
        virtual unique_ptr<ManualTransmission> newManualTransmissionCar() = 0;
};

class ToyotaFactory : public CarFactory {
    public:
        unique_ptr<AutoTransmission> newAutoTransmissionCar()
        {
            return make_unique<AutoToyotaMake>();
        }
        unique_ptr<ManualTransmission> newManualTransmissionCar()
        {
            return make_unique<ManualToyotaMake>();
        }
};

class VolvoFactory : public CarFactory {
    public:
        unique_ptr<AutoTransmission> newAutoTransmissionCar()
        {
            return make_unique<AutoVolvoMake>();
        }
        unique_ptr<ManualTransmission> newManualTransmissionCar()
        {
            return make_unique<ManualVolvoMake>();
        }
};

class App {
    public:
        App(CarFactory &l_factory) : oFactory(l_factory) {}
        void run()
        {
            auto tCar = oFactory.newAutoTransmissionCar();
            tCar->whoAmI();

            auto mCar = oFactory.newManualTransmissionCar();
            mCar->whoAmI();
        }
    private:
        CarFactory& oFactory;
};

int main() {
    ToyotaFactory tFactory;
    VolvoFactory vFactory;

    App a(tFactory);
    a.run();
    
    App b(vFactory);
    b.run();
}