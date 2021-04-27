#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <iterator>

using namespace std;
enum class ComponentState
{
    ON,
    OFF
};
class Vehicle;
class VehicleComponent
{
    public:
        VehicleComponent(const Vehicle& v) : oVehicle(v) {}
        virtual void trigger(ComponentState state) = 0;
    protected:
        const Vehicle& oVehicle;
};
class BrakePaddle : public VehicleComponent
{
    public:
        BrakePaddle(const Vehicle& v) : VehicleComponent(v) {}
        void trigger(ComponentState state);
};
class SignalLeveler : public VehicleComponent
{
    public:
        SignalLeveler(const Vehicle& v) : VehicleComponent(v) {}
        void trigger(ComponentState state);
};
class PowerButton : public VehicleComponent
{
    public:
        PowerButton(const Vehicle& v) : VehicleComponent(v) {}
        void trigger(ComponentState state);
};
class Engine : public VehicleComponent
{
    public:
        Engine(const Vehicle& v) : VehicleComponent(v) {}
        void trigger(ComponentState state);
};
class BrakeLight : public VehicleComponent
{
    public:
        BrakeLight(const Vehicle& v) : VehicleComponent(v) {}
        void trigger(ComponentState state);
};
class TurnLight : public VehicleComponent
{
    public:
        TurnLight(const Vehicle& v) : VehicleComponent(v) {}
        void trigger(ComponentState state);
};
class HeadLight : public VehicleComponent
{
    public:
        HeadLight(const Vehicle& v) : VehicleComponent(v) {}
        void trigger(ComponentState state);
};


class Mediator
{
    public:
        virtual void notify(const VehicleComponent* const sender, ComponentState state) const = 0;
};

class Vehicle : public Mediator
{
    public:
        Vehicle()
        {
            oBrakePaddle = make_shared<BrakePaddle>(*this);
            oSignalLeveler = make_shared<SignalLeveler>(*this);
            oPowerButton = make_shared<PowerButton>(*this);
            oEngine = make_shared<Engine>(*this);
            oBrakeLight = make_shared<BrakeLight>(*this);
            oTurnLight = make_shared<TurnLight>(*this);
            oHeadLight = make_shared<HeadLight>(*this); 
        }
        void notify(const VehicleComponent* const sender, ComponentState state) const
        {
            if (sender == oBrakePaddle.get()) {
                oBrakeLight->trigger(state);
            } else if (sender == oSignalLeveler.get()) {
                oTurnLight->trigger(state);
            } else if (sender == oPowerButton.get()) {
                oEngine->trigger(state);
                oHeadLight->trigger(state);
            }
        }
        void start()
        {
            oBrakePaddle->trigger(ComponentState::ON);
            oPowerButton->trigger(ComponentState::ON);
            oSignalLeveler->trigger(ComponentState::ON);
            oBrakePaddle->trigger(ComponentState::OFF);
            oSignalLeveler->trigger(ComponentState::OFF);
        }
    private:
        shared_ptr<BrakePaddle> oBrakePaddle;
        shared_ptr<SignalLeveler> oSignalLeveler;
        shared_ptr<PowerButton> oPowerButton;
        shared_ptr<Engine> oEngine;
        shared_ptr<BrakeLight> oBrakeLight;
        shared_ptr<TurnLight> oTurnLight;
        shared_ptr<HeadLight> oHeadLight;
};

void BrakePaddle::trigger(ComponentState state)
{
    if (state == ComponentState::ON) {
        cout << "BrakePaddle pushed" << endl;
    } else if (state == ComponentState::OFF) {
        cout << "BrakePaddle released" << endl;
    }
    oVehicle.notify(this, state);
}

void SignalLeveler::trigger(ComponentState state)
{
    if (state == ComponentState::ON) {
        cout << "SignalLeveler pushed" << endl;
    } else if (state == ComponentState::OFF) {
        cout << "SignalLeveler released" << endl;
    }
    oVehicle.notify(this, state);
}

void PowerButton::trigger(ComponentState state)
{
    if (state == ComponentState::ON) {
        cout << "PowerButton pressed" << endl;
    } else if (state == ComponentState::OFF) {
        cout << "PowerButton released" << endl;
    }
    oVehicle.notify(this, state);
}

void Engine::trigger(ComponentState state)
{
    if (state == ComponentState::ON) {
        cout << "Engine on" << endl;
    } else if (state == ComponentState::OFF) {
        cout << "Engine off" << endl;
    }
}

void BrakeLight::trigger(ComponentState state)
{
    if (state == ComponentState::ON) {
        cout << "BrakeLight on" << endl;
    } else if (state == ComponentState::OFF) {
        cout << "BrakeLight off" << endl;
    }
}

void TurnLight::trigger(ComponentState state)
{
    if (state == ComponentState::ON) {
        cout << "TurnLight on" << endl;
    } else if (state == ComponentState::OFF) {
        cout << "TurnLight off" << endl;
    }
}

void HeadLight::trigger(ComponentState state)
{
    if (state == ComponentState::ON) {
        cout << "HeadLight on" << endl;
    } else if (state == ComponentState::OFF) {
        cout << "HeadLight off" << endl;
    }
}


int main()
{
    Vehicle v;
    v.start();
}