#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <iterator>
#include <atomic>

using namespace std;


class State
{
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void accelerate() = 0;
        virtual void brake() = 0;
};
class BaseState : public State
{
    void start()
    {
        cout << "No transistion" << endl;
    }
    void stop()
    {
        cout << "No transistion" << endl;
    }
    void accelerate()
    {
        cout << "No transistion" << endl;
    }
    void brake()
    {
        cout << "No transistion" << endl;
    } 
};
class Vehicle;
class Started;
class Stopped;
class HighSpeedMode;
class LowSpeedMode;

class Vehicle
{
    public:
        Vehicle();

        void transit(unique_ptr<State> state)
        {
            oState = move(state);
        }
        void start()
        {
            oSpeed = 0;
            oState->start();
        }
        void stop()
        {
            oSpeed = 0;
            oState->stop();
        }
        void accelerate()
        {
            oSpeed += 20;
            oState->accelerate();
        }
        void brake()
        {
            oSpeed -= 20;
            oState->brake();
        }
        unsigned int getSpeed() { return oSpeed; }
    private:
        unsigned int oSpeed;
        unique_ptr<State> oState;

};

class Stopped : public BaseState
{
    public:
        Stopped(Vehicle& v) : oVehicle(v) {}
        void start();

    private:
        Vehicle& oVehicle;

};

class Started : public BaseState
{
    public:
        Started(Vehicle& v) : oVehicle(v) {}
        void stop();
        void accelerate();
    private:
        Vehicle& oVehicle;

};

class HighSpeedMode : public BaseState
{
    public:
        HighSpeedMode(Vehicle& v) : oVehicle(v) {}
        void brake();

    private:
        Vehicle& oVehicle;
};

class LowSpeedMode : public BaseState
{
    public:
        LowSpeedMode(Vehicle& v) : oVehicle(v) {}
        void accelerate();
        void brake();
        void stop();

    private:
        Vehicle& oVehicle;

};

Vehicle::Vehicle() : oSpeed(0)
{
    oState = make_unique<Stopped>(*this);
}

void Stopped::start()
{
    cout << "Transit to start" << endl;
    oVehicle.transit(make_unique<Started>(oVehicle));
}
void Started::stop()
{
    cout << "Transit to stop" << endl;
    oVehicle.transit(make_unique<Stopped>(oVehicle));
}
void Started::accelerate()
{
    if (oVehicle.getSpeed() > 60) {
        cout << "Transit to high speed mode" << endl;
        oVehicle.transit(make_unique<HighSpeedMode>(oVehicle));
    } else if (oVehicle.getSpeed() > 0) {
        cout << "Transit to low speed mode" << endl;
        oVehicle.transit(make_unique<LowSpeedMode>(oVehicle));
    }

}
void HighSpeedMode::brake()
{
    if (oVehicle.getSpeed() <= 60) {
        cout << "Transit to low speed mode" << endl;
        oVehicle.transit(make_unique<LowSpeedMode>(oVehicle));
    }
}
void LowSpeedMode::accelerate()
{
    if (oVehicle.getSpeed() > 60) {
        cout << "Transit to high speed mode" << endl;
        oVehicle.transit(make_unique<HighSpeedMode>(oVehicle));
    }
}
void LowSpeedMode::brake()
{
    if (oVehicle.getSpeed() == 0) {
        cout << "Transit to stopped" << endl;
        oVehicle.transit(make_unique<Stopped>(oVehicle));
    }
}
void LowSpeedMode::stop()
{
    cout << "Transit to stopped" << endl;
    oVehicle.transit(make_unique<Stopped>(oVehicle));
}
int main()
{
    Vehicle v;
    v.start();
    v.accelerate();
    v.accelerate();
    v.accelerate();
    v.accelerate();
    v.brake();
    v.brake();
    v.stop();
}