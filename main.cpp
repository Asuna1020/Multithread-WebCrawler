#include <bits/stdc++.h>
#include <pthread.h>
#include <regex>
#include <curl/curl.h>
#include "visited.hpp"
#include "Queue.hpp"
using namespace std;
VisitedList v;
size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *userp)
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

string download_url(string url)
{
    CURL *curl;
    string readbuffer;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readbuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readbuffer;
}
void *work(void *arg)
{
    Queue *task = (Queue *)arg;
    regex url_pattern("href=\"(https?://[^\"]+)\"");
    string url;
    while (task->pop(url))
    {
        if (v.checkAndAdd(url))
        {
            string html = download_url(url);

            smatch match;
            string::const_iterator searchStart(html.cbegin());
            while (regex_search(searchStart, html.cend(), match, url_pattern))
            {
                task->push(match[1]);
                searchStart = match.suffix().first;
            }
            cout << "Thread " << pthread_self() << " 完成爬取: " << url << endl;
        }
    }
    return NULL;
}

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
    Queue task;
    task.push("https://www.csie.ncu.edu.tw/");
    pthread_t thread[4];
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&thread[i], NULL, work, &task);
    }
    sleep(5);
    task.setdone();
    for (int i = 0; i < 4; i++)
    {
        pthread_join(thread[i], NULL);
    }
    curl_global_cleanup();

    return 0;
}
