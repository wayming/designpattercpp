#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

class CarTypeFactor
{
    public:
        virtual double getFactor() const = 0;
};
class SmallCar : public CarTypeFactor
{
    public:
        double getFactor() const { return 1.0; }
};
class MediumCar : public CarTypeFactor
{
    public:
        double getFactor() const { return 1.2; }
};
class LargeCar : public CarTypeFactor
{
    public:
        double getFactor() const { return 1.5; }
};
class LuxuryCar : public CarTypeFactor
{
    public:
        double getFactor() const { return 2.2; }
};


class Vericle
{
    public:
        virtual unsigned int getValue() const = 0;
        virtual ~Vericle() {};
};
class Sedan : public Vericle
{
    public:
        Sedan(CarTypeFactor &type) : oCarTypeFactor{type} {}
        ~Sedan() {}
        unsigned int getValue() const
        {
            return (unsigned int)oStandardPrice * oCarTypeFactor.getFactor();
        }
    private:
        unsigned int oStandardPrice { 30000 };
        CarTypeFactor &oCarTypeFactor;
};
class SUV : public Vericle
{
    public:
        SUV(CarTypeFactor &type) : oCarTypeFactor{type} {}
        ~SUV() {}
        unsigned int getValue() const
        {
            return (unsigned int)oStandardPrice * oCarTypeFactor.getFactor();
        }
    private:
        unsigned int oStandardPrice { 50000 };
        CarTypeFactor &oCarTypeFactor;
};
class VericleFleet : public Vericle
{
    public:
        VericleFleet() {}
        ~VericleFleet() {}
        void add(shared_ptr<Vericle> &&v) { oVericles.push_back(move(v)); }
        unsigned int getValue() const
        {
            unsigned int value = 0; 
            auto calValue = [&value](const shared_ptr<Vericle> &v) {
                unsigned int currVal = v->getValue();
                cout << "Add " << currVal << endl;
                value += currVal;
            };
            for_each(oVericles.begin(), oVericles.end(), calValue);
            cout << "Subtotal " << value << endl;
            return value;
        }
    private:
        vector<shared_ptr<Vericle>> oVericles;
};

int main()
{
    SmallCar small;
    MediumCar medium;
    LargeCar large;
    LuxuryCar luxury;

    VericleFleet *bneVFleet = new VericleFleet();
    bneVFleet->add(make_unique<SUV>(small));
    bneVFleet->add(make_unique<SUV>(small));
    bneVFleet->add(make_unique<SUV>(small));

    VericleFleet *qldVFleet = new VericleFleet();
    qldVFleet->add(make_unique<Sedan>(small));
    qldVFleet->add(make_unique<Sedan>(small));
    qldVFleet->add(make_unique<Sedan>(small));
    qldVFleet->add(shared_ptr<Vericle>(bneVFleet));

    VericleFleet *melVFleet = new VericleFleet();
    melVFleet->add(make_unique<SUV>(small));
    melVFleet->add(make_unique<SUV>(medium));
    melVFleet->add(make_unique<SUV>(medium));

    VericleFleet *vicVFleet = new VericleFleet();
    vicVFleet->add(make_unique<Sedan>(small));
    vicVFleet->add(make_unique<Sedan>(medium));
    vicVFleet->add(make_unique<Sedan>(medium));
    vicVFleet->add(shared_ptr<Vericle>(melVFleet));

    VericleFleet *nswVFleet = new VericleFleet();
    nswVFleet->add(make_unique<Sedan>(large));
    nswVFleet->add(make_unique<Sedan>(large));
    nswVFleet->add(make_unique<Sedan>(luxury));
    nswVFleet->add(make_unique<SUV>(large));
    nswVFleet->add(make_unique<SUV>(large));
    nswVFleet->add(make_unique<SUV>(luxury));

    VericleFleet *ausVFleet = new VericleFleet();
    ausVFleet->add(shared_ptr<Vericle>(qldVFleet));
    ausVFleet->add(shared_ptr<Vericle>(vicVFleet));
    ausVFleet->add(shared_ptr<Vericle>(nswVFleet));

    shared_ptr<Vericle> root = shared_ptr<Vericle>(ausVFleet);
    unsigned int total = root->getValue();
    cout << "Total value " << total << endl;
    return 0;
}