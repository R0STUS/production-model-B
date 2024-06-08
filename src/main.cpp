#include "main.h"

double sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

struct Neuron {
    std::vector<double> weights;
    double bias = 0.0;
};

double activation(double x) {
    if (std::isfinite(x)) {
        return x;
    }
    else {
        return 0.0;
    }
}

double output(const std::vector<double>& inputs, const std::vector<Neuron>& network) {
    double sum = 0.0;
    for (size_t i = 0; i < network.size(); i++) {
        double dot_product = 0.0;
        for (size_t j = 0; j < inputs.size(); j++) {
            dot_product += inputs[j] * network[i].weights[j];
        }
        sum += activation(dot_product + network[i].bias);
    }
    return sum;
}

void save_network(const std::vector<Neuron>& network, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&network[0]), sizeof(Neuron) * network.size());
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

void load_network(std::vector<Neuron>& network, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&network[0]), sizeof(Neuron) * network.size());
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    double learning_rate = 0.1;
    double weights1 = 38.9831;
    double weights2 = -13.1807;
    std::string line;
    double bias = -0.404941;
    std::vector<double> weights = { weights1, weights2 };
    std::vector<double> inputs = { 75, 180 };
    double weight = 75;
    double height = 180;
    double rating = 0;
    double target = 0;

    std::vector<Neuron> network = {
        { {weights1, weights2}, bias },
    };
    /*
    if (std::ifstream("network.bin")) {
        load_network(network, "network.bin");
    }
    */
    while (true) {
        std::cout << std::endl << network[0].weights[0] << " " << network[0].weights[1] << " " << network[0].bias << std::endl;
        std::cout << "Enter weight of human (kg):  ";
        std::cin >> weight;
        std::cout << "Enter height of human (cm):  ";
        std::cin >> height;
        inputs = { weight, height };

        double out = output(inputs, network);
        double output = sigmoid(out);

        std::cout << "The person is " << output << " (0 - not an adult, 1 - adult)" << std::endl;

        std::cout << "The person is adult? (0 or 1):  ";
        std::cin >> target;
        double diff = output - target;

        std::cout << "Rating:  ";
        if (output < target + 0.1 && output > target - 0.1) {
            rating = 1;
        }
        else
            rating = 0;
        std::cout << rating;
        double grad_w0 = (output - target) * inputs[0];
        double grad_w1 = (output - target) * inputs[1];
        double grad_b = output - target;

        network[0].weights[0] -= learning_rate * grad_w0;
        network[0].weights[1] -= learning_rate * grad_w1;
        network[0].bias -= learning_rate * grad_b;

        save_network(network, "network.bin");
    }
    return 0;
}