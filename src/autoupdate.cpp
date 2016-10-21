#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>

#include <unistd.h> // getcwd
#include <libgen.h> // basename

#define VERSION "1.3"

#define MAXPATHLEN 1024

std::string get_working_path()
{
   char temp[MAXPATHLEN];
   return ( getcwd(temp, MAXPATHLEN) ? std::string( temp ) : std::string("") );
}

int main(int argc, char* argv[])
{
    bool running = true;
    std::mutex running_mutex;

    std::cout << "Version: " << VERSION << "\n";

    //std::thread t;
    auto t = std::thread([&]() { 
            std::string binpath(get_working_path() + '/' + basename(argv[0]));
            std::cout << "opening: " << binpath << "\n";
            
            // Wait for the main loop to settle
            running_mutex.lock();
            running = false;
            running_mutex.unlock();

            std::fstream fs;
            fs.open(binpath, std::fstream::out|std::fstream::trunc);
            fs << "Test";
            fs.close();
        });

    for ( ;; )
    {
        running_mutex.lock();
        if ( !running )
        {
            std::cout << "terminating\n";
            running_mutex.unlock();
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        running_mutex.unlock();
    }

    t.join();

    return 0;
}
