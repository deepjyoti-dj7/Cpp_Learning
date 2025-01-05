#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class Logger {
private:
    static int counter;
    static Logger* loggerInstance;
    static std::mutex mtx;
    
    // Private constructor
    Logger() {
        counter++;
        std::cout << "Instance created, number of instances: " << counter << std::endl;
    }

public:
    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Static method to get the logger instance
    static Logger* getLogger() {
        if (loggerInstance == nullptr) {
            std::lock_guard<std::mutex> lock(mtx); // Thread-safe
            if (loggerInstance == nullptr) {
                loggerInstance = new Logger();
            }
        }
        return loggerInstance;
    }

    // Logging method
    void Log(const std::string& message) {
        std::cout << message << std::endl;
    }
};

// Static member initialization
int Logger::counter = 0;
Logger* Logger::loggerInstance = nullptr;
std::mutex Logger::mtx;

// Logging functions for different users
void user1Logs() {
    Logger* logger1 = Logger::getLogger();
    logger1->Log("This message is from client1");
}

void user2Logs() {
    Logger* logger2 = Logger::getLogger();
    logger2->Log("This message is from client2");
}

int main() {
    std::thread t1(user1Logs);
    std::thread t2(user2Logs);

    t1.join();
    t2.join();

    return 0;
}
