#include "GarbageCollector.h"
#include "CommonFileFunc.h"

#include <fstream>

garbage::GarbageCollector::GarbageCollector()
{
    this->pos = -1;
    for (int i = 0; i < 20; i++)
        this->record_numbers[i] = -1;
}
void garbage::GarbageCollector::add(int to_add)
{
    if (pos == 19)
    {
        std::cout << "Garbage collector overflow\n\n";
        return;
    }
    this->pos++;
    this->record_numbers[this->pos] = to_add;
}
int garbage::GarbageCollector::getLastRecordNumber()
{
    if (this->pos == -1) return -1;
    int result = this->record_numbers[this->pos];
    this->record_numbers[this->pos] = -1;
    this->pos--;
    return result;
}

void garbage::addRecordNumberToGarbage(GarbageCollector& collector, int record_number, char* GARBAGE_FILE_NAME, int option)
{
    // option - to which file add record number
    // 0: master-index
    // 1: slave
    collector.add(record_number);
    writeToFileStructure<GarbageCollector>(collector, GARBAGE_FILE_NAME, option);
    return;
}
void garbage::garbageCollectorInitilialization(char* FILE_NAME)
{
    GarbageCollector collector;
    std::ofstream in(FILE_NAME, std::ofstream::binary | std::ofstream::app);
    in.write((char*)&collector, sizeof(collector)); // 0: master-index (lecturer-index)
    in.write((char*)&collector, sizeof(collector)); // 1: slave (scientific publication)
    in.close();
    return;
}

int garbage::getGarbageCollectorLastRecord(char* GARBAGE_FILE_NAME, int option)
{
    // option - to which file add record number
    // 0: master-index
    // 1: slave
    garbage::GarbageCollector temp = readFromFileStructure<garbage::GarbageCollector>(GARBAGE_FILE_NAME, option);
    return temp.getLastRecordNumber();
}

