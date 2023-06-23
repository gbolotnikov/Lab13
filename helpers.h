#pragma once

#include <istream>
#include <vector>

#include "predictor.h"

bool read_features(std::istream& stream, Predictor::features& features, size_t& id);

std::vector<std::vector<double>> read_vector(std::istream&);