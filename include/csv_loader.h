#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include<string>
#include<unordered_map>
#include<vector>

class DataFrame{
  private:
    Table table_;

  public:
    using Column = std::vector<double>;
    using Table = std::unordered_map<std::string, Column>;

    bool load_csv(const std::string& filename);

    const Table& data() const {return table_;}
    const Column& column(const std::string& name) const {return table_.at(name); }
    std::vector<std::string> columns() const;
}

#endif