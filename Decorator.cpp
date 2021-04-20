#include <iostream>
#include <memory>
using namespace std;

class Forester
{
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
};

class ForesterBasic : public Forester
{
    public:
        void start() { cout << "Start Engine" << endl; }
        void stop() { cout << "Stop Engine" << endl; }

};

class PackageDecorator : public Forester
{
    public:
        PackageDecorator(unique_ptr<Forester> f) : oForester(move(f)) {}
        virtual void start() { oForester->start(); }
        virtual void stop() { oForester->stop(); }
    public:
        unique_ptr<Forester> oForester;
};

class EyeSightDecorator : public PackageDecorator
{
    public:
        EyeSightDecorator(unique_ptr<Forester> f) : PackageDecorator(move(f)) {}
        void start()
        {
            cout << "Start EyeSight" << endl;
            oForester->start();
        }
        void stop()
        { 
            cout << "Stop EyeSight" << endl;
            oForester->stop();
        }
};

class SeatMemoryDecorator : public PackageDecorator
{
    public:
        SeatMemoryDecorator(unique_ptr<Forester> f) : PackageDecorator(move(f)) {}
        void start()
        {
            cout << "Seat Memory Init" << endl;
            oForester->start();
        }
        void stop()
        { 
            oForester->stop();
        }
};

int main()
{
    unique_ptr<Forester> f = make_unique<ForesterBasic>();
    unique_ptr<Forester> e = make_unique<EyeSightDecorator>(move(f));
    unique_ptr<Forester> s = make_unique<SeatMemoryDecorator>(move(e));

    s->start();
    s->stop();

}