# Multithread WebCrawler (C++)

這是一個基於 C++ 實作的高效能網路爬蟲專案。本專案採用 **Producer-Consumer 模型**，並結合 `pthread` 與 `libcurl` 函式庫，實現了具備執行緒安全（Thread-safe）任務分發與 URL 去重功能的併發爬取系統。


執行緒安全任務佇列 (Thread-safe Queue)**：使用 `pthread_mutex` 與 `pthread_cond_t` 實作條件變數同步，確保多個執行緒在存取任務時不會發生 Race Condition。
URL 去重機制 (Deduplication)**：利用 `std::set` 搭配互斥鎖（Mutex）實作 `VisitedList`，保證同一網址在單次執行中僅會被爬取一次。
高效能併發爬取**：主程式支援建立多個工作執行緒（Worker Threads），利用 `libcurl` 同時進行網路請求與網頁內容下載。
正則表達式解析**：使用 `std::regex` 從 HTML 原始碼中精準提取 `http/https` 連結並自動加入任務清單。

環境

執行此專案前，請確保您的環境已安裝以下組件：
* **Compiler**: GCC (支援 C++11 或更新版本)
* **Libraries**: 
    * `libcurl` (用於網路請求)
    * `pthread` (用於多執行緒管理)

安裝 libcurl (以 Ubuntu 為例):
Bash
sudo apt-get update
sudo apt-get install libcurl4-openssl-dev

編譯專案:
Bash
g++ src/main.cpp -Iinclude -lcurl -lpthread -o crawler

執行:
Bash
./crawler
