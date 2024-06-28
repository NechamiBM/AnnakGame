#pragma once
#include <vector>
#include <map>
#include <string>
using namespace std;

class Configuration
{
private:
	static map<int, string> _tileCategories;
	static map<string, int> _startingResources;
	static vector<string> _resourceTypes;
	static map<string, vector<int>> _costs;
	static map<string, vector<int>> _capacities;
	static map<string, pair<int, int>> _sizes;
	static map<string, double> _speeds;
	static map<string, int> _rains;
	static map<string, string> _categoryToResource;

public:
	static const map<int, string>& tileCategories() { return _tileCategories; }
	static const map<string, int>& startingResources() { return _startingResources; }
	static const vector<string>& resourceTypes() { return _resourceTypes; }
	static const map<string, vector<int>>& costs() { return _costs; }
	static const map<string, vector<int>>& capacities() { return _capacities; }
	static const map<string, pair<int, int>>& sizes() { return _sizes; }
	static const map<string, double>& speeds() { return _speeds; }
	static const map<string, int>& rains() { return _rains; }
	static const map<string, string>& categoryToResource() { return _categoryToResource; }
	static void loadConfiguration(const string& config_file);
};