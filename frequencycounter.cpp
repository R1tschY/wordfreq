#include <fstream>
#include <cctype>
#include <boost/algorithm/string/split.hpp>

#include "frequencycounter.h"

FrequencyCounter::FrequencyCounter() {

}

void FrequencyCounter::addWordsInFile(const char* filename) {
  std::ifstream fin(filename);

  if (!fin) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return;
  }

  std::string line;
  std::vector<std::string> words_in_line;

  line.reserve(1024);
  words_in_line.reserve(250);
  while (std::getline(fin, line)) {
    words_in_line.clear();
    boost::split(words_in_line, line,
                 [] (int c) { return !std::isalpha(c); },
                 boost::token_compress_on);
    for (const auto& word : words_in_line) {
      if (!word.empty()) {
        table_[word]++;
      }
    }
  }
}

void FrequencyCounter::print(bool sorted) const {
  if (sorted) {
    for (const auto& key_val : sort()) {
      printf("%15s: %3d\n", key_val.first.c_str(), key_val.second);
    }
    
  } else {
    for (const auto& key_val : table_) {
      printf("%15s: %3d\n", key_val.first.c_str(), key_val.second);
    }
  }
}

FrequencyCounter::SortableTable FrequencyCounter::sort() const {
  SortableTable sorted_table(table_.cbegin(), table_.cend());
  
  std::sort(sorted_table.begin(), sorted_table.end(),
    [] (const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      return a.second > b.second;
    }
  );
  
  return sorted_table;
}

void FrequencyCounter::saveCSV(const char *filename, bool sorted) const {
  std::ofstream fout(filename, std::ios_base::out | std::ios_base::trunc);

  if (!fout) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return;
  }

  if (sorted) {
    for (const auto& key_val : sort()) {
      fout << key_val.first << ',' << key_val.second << std::endl;
    }
    
  } else {
    for (const auto& key_val : table_) {
      fout << key_val.first << ',' << key_val.second << std::endl;
    }
  }
}
