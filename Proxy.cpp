#include <iostream>
#include <algorithm>
#include <memory>
#include <map>

using namespace std;

enum class Badge
{
    Standard,
    LClass,
    Premium,
    SClass
};

class IForester
{
    public:
    virtual const string getDescription(const Badge b) = 0;
};
class Forester : public IForester
{
    public:
    const string getDescription(const Badge b) {
        string ret;
        switch (b) {
            case Badge::Standard:
                ret = "Forester Standard";
                break;
            case Badge::LClass:
                ret = "Forester L";
                break;
            case Badge::Premium:
                ret = "Forester Premium";
                break;
            case Badge::SClass:
                ret = "Forester S";
                break;
            default:
                ret = "Unknown";
                break;
        }
        return ret;
    }
};
class Proxy : public IForester
{
    public:
    Proxy(IForester& f) : oForester(f) {}
    const string getDescription(const Badge b) {
        if (oCache.find(b) == oCache.end()) {
            oCache.emplace(b, oForester.getDescription(b));
        }

        return oCache.at(b);
    }

    private:
    IForester& oForester;
    map<Badge, const string> oCache;
};

int main()
{
    Forester f;
    Proxy p(f);

    cout << p.getDescription(Badge::Standard) << endl;
    cout << p.getDescription(Badge::Premium) << endl;

    cout << p.getDescription(Badge::Standard) << endl;
    cout << p.getDescription(Badge::Premium) << endl;
    
    return 0;
}