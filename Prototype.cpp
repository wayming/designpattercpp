#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class Car
{
    public:
        Car() noexcept {}
        virtual ~Car() noexcept {}
        Car(const Car& c) noexcept
        {
            cout << "Copy Construct Car" << endl;
            oSeats = c.oSeats;
            oEngine = c.oEngine;
            oPrice = c.oPrice;
            oMake = c.oMake;
        }
        Car& operator=(const Car& c) noexcept
        {
            cout << "Assign Construct Car" << endl;
            oSeats = c.oSeats;
            oEngine = c.oEngine;
            oPrice = c.oPrice;
            oMake = c.oMake;
            return *this;
        }

        virtual shared_ptr<Car> clone() noexcept = 0;
        void whoAmI()
        {
            cout << oSeats << " seats, "
                 << oEngine << "L, price "
                 << oPrice << ", made by "
                 << oMake << ", build from "
                 << oBuild << ", the " << oIndex
                 << "th." << endl;
        }
        void setBuild(const string& build) { oBuild = build; }
    protected:
        int oSeats{4};
        double oEngine{2.0};
        int oPrice{10000};
        string oMake;
        string oBuild;
        int oIndex{0};
};

class ToyotaCar : public Car
{
    public:
        ToyotaCar() 
        {
            oSeats = 4;
            oEngine = 2.0;
            oPrice = 35000;
            oMake = "Toyota";
            oIndex = sIndex++;
        }
        shared_ptr<Car> clone() noexcept
        {
            shared_ptr<Car> c = make_shared<ToyotaCar>();
            c->setBuild("clone toyota car");
            return c;
        }
    private:
        static int sIndex;
};
int ToyotaCar::sIndex = 0;

class VolvoCar : public Car
{
    public:
        VolvoCar() 
        {
            oSeats = 7;
            oEngine = 2.5;
            oPrice = 65000;
            oMake = "Volvo";
            oIndex = sIndex++;
        }
        shared_ptr<Car> clone() noexcept
        {
            shared_ptr<Car> c = make_shared<VolvoCar>();
            c->setBuild("clone Volvo car");
            return c;
        }
    private:
        static int sIndex;
};
int VolvoCar::sIndex = 0;

class App
{
    public:
        void timesCars(shared_ptr<Car> c, const int t)
        {
            auto k = 0;
            while(k++ < t) {
                oCars.push_back(c->clone());
            } 
        }

        void dumpAllCars()
        {
            for(const auto c : oCars) {
                c->whoAmI();
            }
        }
    private:
        vector<shared_ptr<Car>> oCars;
};

int main()
{
    App app;

    shared_ptr<Car> tCar = make_shared<ToyotaCar>();
    shared_ptr<Car> vCar = make_shared<VolvoCar>();

    app.timesCars(tCar, 5);
    app.timesCars(vCar, 8);
    app.timesCars(tCar, 2);
    app.timesCars(vCar, 3);
    app.dumpAllCars();
}