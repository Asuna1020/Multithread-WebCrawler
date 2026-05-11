#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <bits/stdc++.h>
#include <pthread.h>
#include <string>
using namespace std;
class Queue
{
    queue<string> q;
    pthread_mutex_t mtx;
    pthread_cond_t cond;
    bool done = false;

public:
    Queue()
    {
        pthread_mutex_init(&mtx, NULL);
        pthread_cond_init(&cond, NULL);
    }
    void setdone()
    {
        pthread_mutex_lock(&mtx);
        done = true;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mtx);
    }
    void push(string url)
    {
        pthread_mutex_lock(&mtx);
        q.push(url);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);
    }
    bool pop(string &val)
    {
        pthread_mutex_lock(&mtx);
        while (q.empty() && !done)
        {
            pthread_cond_wait(&cond, &mtx);
        }
        if (q.empty())
        {
            pthread_mutex_unlock(&mtx);
            return false;
        }
        val = q.front();
        q.pop();
        pthread_mutex_unlock(&mtx);
        return true;
    }
};
#endif
