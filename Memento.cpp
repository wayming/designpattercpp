#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <iterator>

using namespace std;

class Memento
{
    public:
        virtual void  restore() const noexcept = 0;
};
class Originator
{
    public:
        virtual shared_ptr<Memento> save() noexcept = 0;
        virtual void dumpState() const noexcept = 0;
};

class AutoVehicle : public Originator
{
    public:
        shared_ptr<Memento> save() noexcept;
        const unsigned int getSpeed() { return oSpeed; }
        const bool isCruiseEnabled() { return oCruiseEnabled; }
        void setSpeed(unsigned int speed) { oSpeed = speed; }
        void setCruise(bool cruise) { oCruiseEnabled = cruise; } 

        void dumpState() const noexcept
        {
            cout << "Speed " << oSpeed << endl;
            if (oCruiseEnabled) {
                cout << "Cruise control activated" << endl;
            }
        }
    private:
        unsigned int oSpeed;
        bool oCruiseEnabled;
};

class ManualVehicle : public Originator
{
    public:
        shared_ptr<Memento> save() noexcept;
        const unsigned int getSpeed() { return oSpeed; }
        bool isCruiseEnabled() { return oCruiseEnabled; }
        const unsigned int getGear() { return oGear; }
        void setSpeed(unsigned int speed) { oSpeed = speed; }
        void setCruise(bool cruise) { oCruiseEnabled = cruise; } 
        void setGear(unsigned int gear) { oGear = gear; }

        void dumpState() const noexcept
        {
            cout << "Speed " << oSpeed << endl;
            cout << "Gear " << oGear << endl;
            if (oCruiseEnabled) {
                cout << "Cruise control activated" << endl;
            }
        }
    private:
        unsigned int oSpeed;
        bool oCruiseEnabled;
        unsigned int oGear;
};

class AutoVehicleMemento : public Memento
{
    public:
        AutoVehicleMemento(AutoVehicle& orginator) :
            oVehicle(orginator),
            oSpeed(orginator.getSpeed()),
            oCruiseEnabled(orginator.isCruiseEnabled()) {}
        void restore() const noexcept
        {
            oVehicle.setSpeed(oSpeed);
            oVehicle.setCruise(oCruiseEnabled);
        }
    private:
        unsigned int oSpeed;
        bool oCruiseEnabled;
        AutoVehicle& oVehicle;
};

class ManualVehicleMemento : public Memento
{
    public:
        ManualVehicleMemento(ManualVehicle& orginator) :
            oVehicle(orginator),
            oSpeed(orginator.getSpeed()),
            oCruiseEnabled(orginator.isCruiseEnabled()),
            oGear(orginator.getGear()) {}
        void restore() const noexcept
        {
            oVehicle.setSpeed(oSpeed);
            oVehicle.setCruise(oCruiseEnabled);
            oVehicle.setGear(oGear);
        }
    private:
        unsigned int oSpeed;
        bool oCruiseEnabled;
        unsigned int oGear;
        ManualVehicle& oVehicle;
};


shared_ptr<Memento> AutoVehicle::save() noexcept
{
    return make_shared<AutoVehicleMemento>(*this);
}

shared_ptr<Memento> ManualVehicle::save() noexcept
{
    return make_shared<ManualVehicleMemento>(*this);
}

int main()
{
    vector<shared_ptr<Memento>> historyAuto;
    vector<shared_ptr<Memento>> historyManual;

    AutoVehicle autoV;
    autoV.setSpeed(120);
    autoV.setCruise(true);
    historyAuto.push_back(autoV.save());
    autoV.setSpeed(80);
    autoV.setCruise(false);

    ManualVehicle manualV;
    manualV.setSpeed(30);
    manualV.setCruise(false);
    manualV.setGear(1);
    historyManual.push_back(manualV.save());
    manualV.setSpeed(60);
    manualV.setCruise(false);
    manualV.setGear(2);

    (*historyAuto.crbegin())->restore();
    historyAuto.pop_back();
    autoV.dumpState();

    (*historyManual.crbegin())->restore();
    historyManual.pop_back();
    manualV.dumpState();
    return 1;
}