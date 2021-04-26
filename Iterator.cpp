#include <iostream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <iterator>

using namespace std;

enum class BodyType {
    Sedan,
    SUV
};
using VehicleCollection = map<string, map<BodyType, vector<string>>>;

VehicleCollection japanVehicleCollection {
    {"Toyota",
        {
            {BodyType::Sedan, {"Camry", "Corolla"}},
            {BodyType::SUV, {"RAV4", "LandCrusier"}}
        }
    },
    {"Subaru",
        {
            {BodyType::Sedan, {"Impreza", "Liberty"}},
            {BodyType::SUV, {"Outback", "Forester"}}
        }
    },
    {"Mazda",
        {
            {BodyType::Sedan, {"Mazda3", "Mazda6"}},
            {BodyType::SUV, {"CX5", "CX9"}}
        }
    }
};

class VehicleIterator
{
    public:
        VehicleIterator(VehicleCollection& collection) : oCollection(collection)
        {
            for(auto const iter : oCollection) {
                oMakes.push_back(iter.first);
            }
            oThisMake = oMakes.begin();
        }
        virtual string getNext() = 0;
        virtual bool hasMore() = 0;
    
    protected:
        VehicleCollection& oCollection;
        vector<string> oMakes;
        vector<string>::const_iterator oThisMake;
};

template <typename T>
class ModelIterator : public VehicleIterator
{
    public:
        ModelIterator(VehicleCollection& collection, const T& bodyType) :
            VehicleIterator(collection),
            oBodyType(bodyType),
            oModelsOfThisMake(oCollection.at(*oThisMake)[bodyType]),
            oThisModel(oModelsOfThisMake.begin()),
            oEnd(false) {}

        string getNext()
        {
            if (oEnd) {
                cout << "None" << endl;
            }

            string vehicleName = *oThisModel;

            advance(oThisModel, 1);
            if (oThisModel == oModelsOfThisMake.end()) {
                // Check for next make
                advance(oThisMake, 1);
                while(oThisMake != oMakes.end()) {
                    oModelsOfThisMake = oCollection.at(*oThisMake)[oBodyType];
                    if (oModelsOfThisMake.size() > 0) {
                        // Found models from the next make
                        oThisModel = oModelsOfThisMake.begin();
                        break;
                    }
                }

                if (oThisMake == oMakes.end()) {
                    oEnd = true;
                }
            }

            return vehicleName;
        }

        // Look for the next vehicle
        // Update oNextModel and oNextMake
        bool hasMore() { return !oEnd; }

    private:
        T oBodyType;
        vector<string>& oModelsOfThisMake;
        vector<string>::const_iterator oThisModel;
        bool oEnd;
};

int main()
{
    unique_ptr<VehicleIterator> suvIter = make_unique<ModelIterator<BodyType>>(japanVehicleCollection, BodyType::SUV);
    while(suvIter->hasMore()) {
        cout << "++" << suvIter->getNext() << endl;;
    }

    unique_ptr<VehicleIterator> sedanIter = make_unique<ModelIterator<BodyType>>(japanVehicleCollection, BodyType::Sedan);
    while(sedanIter->hasMore()) {
        cout << "--" << sedanIter->getNext() << endl;;
    }
}