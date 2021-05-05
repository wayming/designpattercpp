#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <iterator>
#include <atomic>

using namespace std;

class PriceCalc
{
    public:
        const unsigned int totalPrice() {
            return enginePrice() + bodyPrice() + tyrePrice() + entertainmentSystemPrice();
        };
        virtual unsigned int enginePrice() { return 5000; };
        virtual unsigned int bodyPrice() { return 6000; };
        virtual unsigned int tyrePrice() { return 1000; };
        virtual unsigned int entertainmentSystemPrice() { return 3000; };
};

class IModelPrice : public PriceCalc
{
};

class LModelPrice : public PriceCalc
{
    public:
        unsigned int tyrePrice()
        {
            return 2000;
        }
};


class PModelPrice : public PriceCalc
{
    public:
        unsigned int tyrePrice()
        {
            return 2000;
        }
        unsigned int entertainmentSystemPrice()
        {
            return 4000;
        }
};

class SModelPrice : public PriceCalc
{
    public:
        unsigned int tyrePrice()
        {
            return 2000;
        }
        unsigned int entertainmentSystemPrice()
        {
            return 5000;
        }
};

int main()
{
    cout << IModelPrice().totalPrice() << endl;
    cout << LModelPrice().totalPrice() << endl;
    cout << PModelPrice().totalPrice() << endl;
    cout << SModelPrice().totalPrice() << endl;
}