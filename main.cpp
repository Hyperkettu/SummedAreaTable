#include "pch.h"

std::vector<uint8_t> inputData = { 
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 5, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

size_t SAT_WIDTH = 10;
size_t SAT_HEIGHT = 10;

int main() {
    try {

        VulkanGraphicsAPI api;
        SummedAreaTable sat;

        sat.generateTable(api, inputData, SAT_WIDTH, SAT_HEIGHT);
      
        uint32_t sumOverArea = sat.getRectangleSum(1, 1, 3, 3);

        std::cout << "Sum over Area is " << sumOverArea << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

