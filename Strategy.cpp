#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <iterator>
#include <atomic>
#include <chrono>

using namespace std;
using namespace std::literals::chrono_literals;

class Vehicle
{
    public:
        Vehicle(string model, unsigned int buildYear, unsigned int engineSize, unsigned int price) :
            oModel(model), oBuildYear(buildYear), oEngineSize(engineSize), oPrice(price) {}

        void dump()
        {
            cout << oModel << " built on "
                 << oBuildYear << ". Engine "
                 << oEngineSize << "cc, price "
                 << oPrice << endl;
        }
        const unsigned int getBuildyear() const { return oBuildYear; }
        const unsigned int getEngineSize() const { return oEngineSize; }
        const unsigned int getPrice() const { return oPrice; }
    private:
        string oModel;
        unsigned int oBuildYear;
        unsigned int oEngineSize;
        unsigned int oPrice;
};


class Strategy
{
    public:
        virtual void execute(vector<Vehicle>& vehicles) const = 0;
};

class SortByBuildYear : public Strategy
{
    public:
    void execute(vector<Vehicle>& vehicles) const
    {
        sort(vehicles.begin(), vehicles.end(),
            [](const Vehicle& a, const Vehicle& b) -> bool {
                return a.getBuildyear() < b.getBuildyear();
            }
        );
    }
};
class SortByEngineSize : public Strategy
{
    public:
    void execute(vector<Vehicle>& vehicles) const
    {
        sort(vehicles.begin(), vehicles.end(),
            [](const Vehicle& a, const Vehicle& b) -> bool {
                return a.getEngineSize() < b.getEngineSize();
            }
        );
    }
};
class SortByPrice : public Strategy
{
    public:
    void execute(vector<Vehicle>& vehicles) const
    {
        sort(vehicles.begin(), vehicles.end(),
            [](const Vehicle& a, const Vehicle& b) -> bool {
                return a.getPrice() < b.getPrice();
            }
        );
    }
};

class Context
{
    public:
        Context(unique_ptr<Strategy> s) : oStrategy(move(s)) {};
        void setStrategy(unique_ptr<Strategy> s) { oStrategy = move(s); }
        void sort(vector<Vehicle>& vehicles) { oStrategy->execute(vehicles); }
    private:
        unique_ptr<Strategy> oStrategy;
};

void dumpVehicles(vector<Vehicle>& vehicles)
{
    auto iter = vehicles.begin();
    while (iter != vehicles.end()) {
        iter->dump();
        iter++;
    }
}

int main()
{
    vector<Vehicle> vehicles;
    vehicles.emplace_back(string("RAV4"), 2020, 2000, 30000);
    vehicles.emplace_back(string("RAV4"), 2010, 2500, 4000);
    vehicles.emplace_back(string("CX5"), 2018, 2500, 28000);
    vehicles.emplace_back(string("CX5"), 2019, 2500, 30000);
    vehicles.emplace_back(string("Forester"), 2019, 2500, 30000);
    vehicles.emplace_back(string("Forester"), 2019, 2500, 29000);

    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Original" << endl;
    dumpVehicles(vehicles);

    Context c(make_unique<SortByBuildYear>());
    c.sort(vehicles);
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SortByBuildYear" << endl;
    dumpVehicles(vehicles);

    c.setStrategy(make_unique<SortByEngineSize>());
    c.sort(vehicles);
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SortByEngineSize" << endl;
    dumpVehicles(vehicles);


    c.setStrategy(make_unique<SortByPrice>());
    c.sort(vehicles);
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SortByPrice" << endl;
    dumpVehicles(vehicles);

}