#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <iterator>
#include <atomic>

using namespace std;

class Vehicle;
class IModel;
class LModel;
class PModel;
class SModel;
class Visitor
{
    public:
        virtual void visitIModel(Vehicle& v) = 0;
        virtual void visitLModel(Vehicle& v) = 0;
        virtual void visitPModel(Vehicle& v) = 0;
        virtual void visitSModel(Vehicle& v) = 0;
};
class Vehicle
{
    public:
        Vehicle(const unsigned int price, const unsigned int warranty) :
            oPrice(price), oWarranty(warranty), oCashBack(0) {}
        
        virtual void accept(Visitor& v) = 0;
        void dump()
        {
            cout << "Sell price " << oPrice << " with " << oWarranty << " years warranty" << endl;
            if (oCashBack > 0) {
                cout << "$" << oCashBack << " cash rewards" << endl;
            }
        }
        void setPrice(const unsigned int price) { oPrice = price; }
        void setWarranty(const unsigned int warranty) { oWarranty = warranty; }
        void setCashBack(const unsigned int cashback) { oCashBack = cashback; }
        const unsigned int getPrice() const { return oPrice; }
        const unsigned int getWarranty() const { return oWarranty; }
        const unsigned int getCashBack() const { return oCashBack; }


    protected:
        unsigned int oPrice;
        unsigned int oWarranty;
        unsigned int oCashBack;
};


class IModel : public Vehicle
{
    public:
        IModel() : Vehicle(33000, 5) {}
        void accept(Visitor& v)
        {
            v.visitIModel(*this);
        }
};


class LModel : public Vehicle
{
    public:
        LModel() : Vehicle(36000, 5) {}
        void accept(Visitor& v)
        {
            v.visitLModel(*this);
        }
};

class PModel : public Vehicle
{
    public:
        PModel() : Vehicle(39000, 5) {}
        void accept(Visitor& v)
        {
            v.visitPModel(*this);
        }
};

class SModel : public Vehicle
{
    public:
        SModel() : Vehicle(43000, 7) {}
        void accept(Visitor& v)
        {
            v.visitSModel(*this);
        }
};


class PromotitionVisitor : public Visitor
{
    public:
        void visitIModel(Vehicle& vehicle)
        {
            vehicle.setPrice(0.95 * vehicle.getPrice());
        }
        void visitLModel(Vehicle& vehicle)
        {
            vehicle.setPrice(0.94 * vehicle.getPrice());
        }
        void visitPModel(Vehicle& vehicle)
        {
            vehicle.setWarranty(vehicle.getWarranty() + 2);
        }
        void visitSModel(Vehicle& vehicle)
        {
            vehicle.setCashBack(1000);
        }
};

int main()
{
    vector<shared_ptr<Vehicle>> vehicles = {
        make_shared<IModel>(),
        make_shared<LModel>(),
        make_shared<PModel>(),
        make_shared<SModel>()};
    
    auto iter = vehicles.begin();
    PromotitionVisitor promotion;
    while(iter != vehicles.end()) {
        (*iter)->accept(promotion);
        (*iter)->dump();
        iter++;
    }
}