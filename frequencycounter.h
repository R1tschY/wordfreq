#ifndef FREQUENCYCOUNTER_H
#define FREQUENCYCOUNTER_H

#include <string>
#include <vector>
#include <unordered_map>

class FrequencyCounter {
public:
  FrequencyCounter();

  void addWordsInFile(const char *filename);
  void print(bool sorted = false) const;
  void saveCSV(const char *filename, bool sorted = false) const;

private:
  typedef std::unordered_map<std::string, int> Table;
  typedef std::vector<std::pair<std::string, int> > SortableTable;
  
  SortableTable sort() const;

  Table table_;
};

#endif // FREQUENCYCOUNTER_H
