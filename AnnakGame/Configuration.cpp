#include "Configuration.h"
#include "json.hpp"
#include <fstream>
#include <stdexcept>
using json = nlohmann::json;

map<int, string> Configuration::_tileCategories;
map<string, int> Configuration::_startingResources;
vector<string> Configuration::_resourceTypes;
map<string, vector<int>> Configuration::_costs;
map<string, vector<int>> Configuration::_capacities;
map<string, pair<int, int>> Configuration::_sizes;
map<string, double> Configuration::_speeds;
map<string, int> Configuration::_rains;
map<string, string> Configuration::_categoryToResource;

void Configuration::loadConfiguration(const string& config_file) {
    std::ifstream ifs(config_file);
    if (!ifs.is_open())
        throw runtime_error("Failed to open configuration file: " + config_file);

    json config;
    ifs >> config;

    for (const auto& entry : config["Tiles"].items())
        _tileCategories[entry.value()] = entry.key();

    for (const auto& entry : config["StartingResources"].items())
        _startingResources[entry.key()] = entry.value();

    _resourceTypes = config["ResourceTypes"].get<vector<string>>();

    for (const auto& entry : config["Costs"].items())
        _costs[entry.key()] = entry.value().get<vector<int>>();

    for (const auto& entry : config["Capacities"].items())
        _capacities[entry.key()] = entry.value().get<vector<int>>();

    for (const auto& entry : config["Sizes"].items()) {
        auto size_vec = entry.value().get<vector<int>>();
        if (size_vec.size() == 2)
            _sizes[entry.key()] = make_pair(size_vec[0], size_vec[1]);
        else
            throw runtime_error("Invalid size format in configuration file for key: " + entry.key());
    }

    for (const auto& entry : config["Speeds"].items())
        _speeds[entry.key()] = entry.value();

    for (const auto& entry : config["Rains"].items())
        _rains[entry.key()] = entry.value();
    _categoryToResource = {
      {"Forest", "Wood"},
      {"Field", "Wool"},
      {"IronMine", "Iron"},
      {"BlocksMine", "Blocks"}
    };

    ifs.close();
}