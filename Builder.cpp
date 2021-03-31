#include <iostream>
#include <map>
#include <memory>
using namespace std;

enum class BodyType
{
    SUV,
    Sedan
};
map<BodyType, string> BodyTypeStrings = {
    {BodyType::SUV, "SUV"},
    {BodyType::Sedan, "Sedan"}
};

enum class Engine
{
    Petrol,
    Diesel
};
map<Engine, string> EngineStrings = {
    {Engine::Petrol, "Petrol"},
    {Engine::Diesel, "Diesel"}
};

enum class Transmission
{
    Auto,
    Manual,
    CVT
};
map<Transmission, string> TransmissionStrings = {
    {Transmission::Auto, "Auto"},
    {Transmission::Manual, "Manual"},
    {Transmission::CVT, "CVT"}
};

enum class Color
{
    White,
    Blue,
    Grey,
    Pearl
};
map<Color, string> ColorStrings = {
    {Color::White, "White"},
    {Color::Blue, "Blue"},
    {Color::Grey, "Grey"},
    {Color::Pearl, "Pearl"},
};


class Car
{
    public:
        void whoAmI()
        {
            cout << BodyTypeStrings[oBodyType]
                 << "-" << EngineStrings[oEngine]
                 << "-" << TransmissionStrings[oTransmission]
                 << "-" << ColorStrings[oColor]
                 << endl;
        }
        BodyType oBodyType;
        Engine oEngine;
        Transmission oTransmission;
        Color oColor;
};

class CarBuilder
{
    public:
        virtual void reset() = 0;
        virtual void setBodyType() = 0;
        virtual void setEngine() = 0;
        virtual void setTransmission() = 0;
        virtual void setColor() = 0;
        virtual unique_ptr<Car> getCar() = 0;
};

class PerformanceCarBuilder : public CarBuilder{
    public:
        void reset()            { oCar = make_unique<Car>(); }
        void setBodyType()      { oCar->oBodyType = BodyType::Sedan; };
        void setEngine()        { oCar->oEngine = Engine::Diesel; };
        void setTransmission()  { oCar->oTransmission = Transmission::Manual; };
        void setColor()         { oCar->oColor = Color::Blue; };
        unique_ptr<Car> getCar(){ return move(oCar); }
    
    private:
        unique_ptr<Car> oCar;
};

class FamilyCarBuilder : public CarBuilder{
    public:
        void reset()            { oCar = make_unique<Car>(); }
        void setBodyType()      { oCar->oBodyType = BodyType::SUV; };
        void setEngine()        { oCar->oEngine = Engine::Petrol; };
        void setTransmission()  { oCar->oTransmission = Transmission::Auto; };
        void setColor()         { oCar->oColor = Color::Pearl; };
        unique_ptr<Car> getCar(){ return move(oCar); }
    
    private:
        unique_ptr<Car> oCar;
};

class Director
{
    public:
        void setBuilder(unique_ptr<CarBuilder> builder) { oBuilder = move(builder); }
        unique_ptr<Car> buildCar()
        {
            oBuilder->reset();
            oBuilder->setBodyType();
            oBuilder->setEngine();
            oBuilder->setTransmission();
            oBuilder->setColor();
            return oBuilder->getCar();
        }
    
    private:
        unique_ptr<CarBuilder> oBuilder;
    
};

int main() {
    Director d;
    d.setBuilder(make_unique<PerformanceCarBuilder>());
    d.buildCar()->whoAmI();

    d.setBuilder(make_unique<FamilyCarBuilder>());
    d.buildCar()->whoAmI();
}