#include <iostream>
#include <algorithm>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>

using namespace std;

mutex commandQueueMutex;
enum class CommandType {
    START,
    STOP,
    ACCELERATE,
    BRAKE
};
class Car
{
    public:
        void start() { cout << "Car start" << endl; }
        void stop() { cout << "Car stop" << endl; }
        void accelerate() { cout << "Car accelerate" << endl; }
        void brake() { cout << "Car brake" << endl; }
};
class Command
{
    public:
        virtual void execute() = 0;
};
class CarCommand : public Command
{
    public:
        CarCommand(Car& c) : oCar(c) {}

    protected:
        Car& oCar;
};
class StartCommand : public CarCommand
{
    public:
        StartCommand(Car& c) : CarCommand(c) {}
        void execute() { oCar.start(); }
};
class StopCommand : public CarCommand
{
    public:
        StopCommand(Car& c) : CarCommand(c) {}
        void execute() { oCar.stop(); }
};
class AccelerateCommand : public CarCommand
{
    public:
        AccelerateCommand(Car& c) : CarCommand(c) {}
        void execute() { oCar.accelerate(); }
};
class BrakeCommand : public CarCommand
{
    public:
        BrakeCommand(Car& c) : CarCommand(c) {}
        void execute() { oCar.brake(); }
};
int main()
{
    queue<unique_ptr<Command>> commandQueue;
    Car c;
    auto recvShutdown = false;
    auto processedCommands = 0;

    auto recvFunc = [&commandQueue, &recvShutdown, &processedCommands]()->void {
        while (true) {
            if (recvShutdown) break;
            if (commandQueue.size() > 0) {
                lock_guard<mutex> lock(commandQueueMutex);
                if (commandQueue.size() > 0) {
                    commandQueue.front()->execute();
                    commandQueue.pop();
                    processedCommands++;
                    cout << processedCommands << endl;
                }
            }
        }

    };
    thread reciver(recvFunc);

    auto sendFunc = [&commandQueue, &c](int numOfCommands, CommandType type)->void {
        auto idx = 0;
        while (idx++ < numOfCommands) {
            lock_guard<mutex> lock(commandQueueMutex);
            switch (type) {
                case CommandType::START :
                    commandQueue.push(make_unique<StartCommand>(c));
                    break;
                case CommandType::STOP :
                    commandQueue.push(make_unique<StopCommand>(c));
                    break;
                case CommandType::ACCELERATE :
                    commandQueue.push(make_unique<AccelerateCommand>(c));
                    break;
                case CommandType::BRAKE :
                    commandQueue.push(make_unique<BrakeCommand>(c));
                    break;
                default:
                    cout << "Unknown command type" << endl;
                    break;
            }
        }
    };
    vector<thread> sendThreads;
    auto numPerThread = 10000;
    auto numThread = 100;
    for (auto i=0; i < numThread; i++) {
        auto remainder = i % 4;
        switch (remainder) {
            case 0 :
                sendThreads.emplace_back(sendFunc, numPerThread, CommandType::START);
                break;
            case 1 :
                sendThreads.emplace_back(sendFunc, numPerThread, CommandType::STOP);
                break;
            case 2 :
                sendThreads.emplace_back(sendFunc, numPerThread, CommandType::ACCELERATE);
                break;
            case 3 :
                sendThreads.emplace_back(sendFunc, numPerThread, CommandType::BRAKE);
                break;
       }
    }

    for (auto& sender : sendThreads) sender.join();

    while (processedCommands < numPerThread * numThread) {
        this_thread::sleep_for (chrono::seconds(1));
    }

    recvShutdown = true;
    reciver.join();

    return 0;
}