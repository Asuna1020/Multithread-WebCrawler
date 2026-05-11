#ifndef VISITED_HPP
#define VISITED_HPP

#include <set>
#include <string>
#include <pthread.h>
using namespace std;
class VisitedList
{
    set<string> visited_urls;
    pthread_mutex_t mtx;

public:
    VisitedList()
    {
        pthread_mutex_init(&mtx, NULL);
    }

    ~VisitedList()
    {
        pthread_mutex_destroy(&mtx);
    }

    bool checkAndAdd(string url)
    {
        pthread_mutex_lock(&mtx);

        if (visited_urls.find(url) == visited_urls.end())
        {
            visited_urls.insert(url);
            pthread_mutex_unlock(&mtx);
            return true;
        }

        pthread_mutex_unlock(&mtx);
        return false;
    }
};

#endif