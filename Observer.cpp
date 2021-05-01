#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <iterator>
#include <atomic>

using namespace std;
enum class Event
{
    POWER_ON,
    POWER_OFF,
    DRIVER_ASSITENT_ON,
    DRIVER_ASSITENT_OFF,
    HIGH_BEAM_ON,
    HIGH_BEAM_OFF,
};

class Subscriber
{
    public:
        virtual void update(Event e) = 0;
        unsigned int getSubId() { return oSubId; }
    protected:
        unsigned int getNextid()
        {
            auto id = oSubscriberId.load();
            oSubscriberId.store(id+1);
            cout << oSubscriberId.load() << endl;
            return id;
        }

    public:
        static atomic<unsigned int> oSubscriberId;

    protected:
        unsigned int oSubId{0};
};
atomic<unsigned int> Subscriber::oSubscriberId = 0;

class Publisher
{
    public:
        virtual void subscribe(shared_ptr<Subscriber> s) = 0;
        virtual void unsubscribe(shared_ptr<Subscriber> s) = 0;
        virtual void notify(Event e) = 0;
};

class VehicleControlPanel : public Publisher
{
    public:
        void subscribe(shared_ptr<Subscriber> s)
        {
            oSubscribers[s->getSubId()] = s;
        }
        void unsubscribe(shared_ptr<Subscriber> s)
        {
            oSubscribers.erase(s->getSubId());
        }
        void notify(Event e)
        {
            auto iter = oSubscribers.begin();
            for (iter; iter != oSubscribers.end(); iter++) {
                iter->second->update(e);
            }
        }
    private:
        map<unsigned int, shared_ptr<Subscriber>> oSubscribers;

};

class Engine : public Subscriber
{
    public:
        Engine() { oSubId = getNextid(); }
        void update(Event e)
        {
            switch (e) {
                case Event::POWER_ON:
                    cout << "Engine Started" << endl;
                    break;
                case Event::POWER_OFF:
                    cout << "Engine Stopped" << endl;
                    break;
            }

        }
};

class HeadLight : public Subscriber
{
    public:
        HeadLight() { oSubId = getNextid(); }
        void update(Event e)
        {
            switch (e) {
                case Event::POWER_ON:
                    cout << "HeadLight On" << endl;
                    break;
                case Event::POWER_OFF:
                    cout << "HeadLight Off" << endl;
                    break;
                case Event::HIGH_BEAM_ON:
                    cout << "High Beam On" << endl;
                    break;
                case Event::HIGH_BEAM_OFF:
                    cout << "High Beam Off" << endl;
                    break;
            }
        }
};


class DriverAssistance : public Subscriber
{
    public:
        DriverAssistance() { oSubId = getNextid(); }
        void update(Event e)
        {
            switch (e) {
                case Event::POWER_ON:
                case Event::DRIVER_ASSITENT_ON:
                    cout << "DriverAssistance On" << endl;
                    break;
                case Event::POWER_OFF:
                case Event::DRIVER_ASSITENT_OFF:
                    cout << "DriverAssistance Off" << endl;
                    break;
            }
        }
};


int main()
{
    VehicleControlPanel panel;
    
    auto e = make_shared<Engine>();
    auto h = make_shared<HeadLight>();
    auto d = make_shared<DriverAssistance>();
    panel.subscribe(e);
    panel.subscribe(h);
    panel.subscribe(d);

    panel.notify(Event::POWER_ON);
    panel.notify(Event::HIGH_BEAM_ON);
    panel.notify(Event::DRIVER_ASSITENT_OFF);
    panel.notify(Event::POWER_OFF);

    panel.unsubscribe(h);
    panel.unsubscribe(d);
    panel.notify(Event::POWER_ON);
    panel.notify(Event::HIGH_BEAM_ON);
    panel.notify(Event::DRIVER_ASSITENT_OFF);
    panel.notify(Event::POWER_OFF);    
}