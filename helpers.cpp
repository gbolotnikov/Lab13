#include "helpers.h"
#include "utils.h"
#include <string>
#include <sstream>
#include <iterator>

static std::vector<std::vector<double>> split(std::vector<double> model) {
    std::vector<std::vector<double>> result{NumModel};
    auto begin = model.begin();
    auto end = begin;
    for(auto& res: result) {
        std::advance(end, NumCoeff);
        std::copy(begin, end, std::back_inserter(res));
        begin = end;
    }
    return result;
}

bool read_features(std::istream& stream, Predictor::features& features, size_t& id) {
    std::string line;
    std::getline(stream, line);
    if(line.length() == 0) {
        return false;
    }
    std::stringstream test(line);
    std::string byte; 
    std::getline(test, byte, ',');
    id = stoi(byte);
    while(std::getline(test, byte, ',')) {
        features.push_back(stoi(byte));
    }
    return true;
}

std::vector<std::vector<double>> read_vector(std::istream& stream) {
    std::vector<double> result;

    std::copy(std::istream_iterator<double>(stream),
              std::istream_iterator<double>(),
              std::back_inserter(result));

    return split(std::move(result));
}



