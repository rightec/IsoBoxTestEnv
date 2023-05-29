#include "isolatedBox_dataentryqueue.h"

using namespace std;

int main()
{
    cout << "Hello Isolated Box CMake. Main Test Running" << endl;


    MonitoringDataQueue g_DataQueue;
    ISO_DataEntryQueue g_dataEntryQueue(&g_DataQueue);
    ISO_DataEntryQueue::setStopConsumerFlag(true);
    ISO_DataEntryQueue::setStopProducerFlag(true);

    std::thread l_consumer_t(&ISO_DataEntryQueue::thread_consumer, &g_dataEntryQueue);
    std::thread l_producer_t(&ISO_DataEntryQueue::thread_producer, &g_dataEntryQueue);

    l_producer_t.join();
    l_consumer_t.join();

    return 0;
}