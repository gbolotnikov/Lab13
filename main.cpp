#include <iostream>
#include <fstream>
#include <float.h>
#include "linreg_predictor.h"

#include "helpers.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <.csv> <model>" << endl;
        return EXIT_FAILURE;
    }

    std::ifstream istream{argv[2]};
    auto vectors = read_vector(istream);
    istream.close();

    size_t id = 0;
    std::ifstream istreamD{argv[1]};
    auto features = Predictor::features{};
    double maxProbability = -DBL_MAX;
    size_t supposedId = 0;
    size_t positive = 0, negative = 0;
    while (read_features(istreamD, features, id)) {
        for (size_t i = 0; i < vectors.size(); ++i) {
            LinregPredictor predictor(vectors[i]);
            auto probability = predictor.predict(features);
            if (probability > maxProbability) {
                maxProbability = probability;
                supposedId = i;
            }
        }
        if (supposedId == id) {
            ++positive;
        } else {
            ++negative;
        }
        features.clear();
        maxProbability = -DBL_MAX;
    }
    istreamD.close();
    double result = (double)positive / (positive + negative);
    std::cout<< result << std::endl;
}