#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Car;
class Bycicle;
class Transport
{
public:
    virtual void info() = 0;
};

namespace Internal
{

class Car : public Transport
{
public:
    void info() override { std::cout << "Car" << std::endl; }
};

class Bycicle : public Transport
{
public:
    void info() override { std::cout << "Bycicle" << std::endl; }
};
} // namespace Internal

class TransportFabric
{
public:
    virtual std::unique_ptr<Transport> createTransport() const = 0;
};

class BycicleFabric : public TransportFabric
{
public:
    std::unique_ptr<Transport> createTransport() const override
    {
        return std::make_unique<Internal::Car>();
    }
};

class CarFabric : public TransportFabric
{
public:
    std::unique_ptr<Transport> createTransport() const override
    {
        return std::make_unique<Internal::Bycicle>();
    }
};

int main()
{
    CarFabric *carFab = new CarFabric;
    BycicleFabric *bikeFab = new BycicleFabric;

    std::vector<std::unique_ptr<Transport>> transports;
    transports.push_back(carFab->createTransport());
    transports.push_back(bikeFab->createTransport());

    for (auto &transport : transports)
        transport->info();

    return 0;
}
