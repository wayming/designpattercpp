#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Car {
    public:
        virtual void whoAmI() = 0;
};

class ToyotaMake : public Car {
    public:
        void whoAmI() { cout << "Made by Toyota" << endl; }
        ToyotaMake() {}
        ToyotaMake(ToyotaMake&& make) = delete;
        ToyotaMake& operator=(ToyotaMake&& make) = delete;
        ToyotaMake(const ToyotaMake&) = delete;
        ToyotaMake& operator=(const ToyotaMake&) = delete;
    
    private:
        vector<string> models { "camery", "yaris", "Rav4" };
        
};

class VolvoMake : public Car {
    public:
        void whoAmI() { cout << "Made by Volvo" << endl;}
        VolvoMake() {}
        VolvoMake(VolvoMake&& make) = delete;
        VolvoMake& operator=(VolvoMake&& make) = delete;
        VolvoMake(const VolvoMake&) = delete;
        VolvoMake& operator=(const VolvoMake&) = delete;
    
    private:
        vector<string> models { "xc40", "xc60", "xc90" };
};

class CarFactory {
    public:
        virtual unique_ptr<Car> newCar() = 0;
};

class ToyotaFactory : public CarFactory {
    public:
        unique_ptr<Car> newCar()
        {
            return make_unique<ToyotaMake>();
        }
};

class VolvoFactory : public CarFactory {
    public:
        unique_ptr<Car> newCar()
        {
            return make_unique<VolvoMake>();
        }
};

class App {
    public:
        App(CarFactory &l_factory) : oFactory(l_factory) {}
        void run()
        {
            auto c = oFactory.newCar();
            c->whoAmI();
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