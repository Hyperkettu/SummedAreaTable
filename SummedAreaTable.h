#pragma once

class SummedAreaTable {

private:
    uint32_t width = 0;
    uint32_t height = 0;

    std::vector<uint8_t> summedAreaTable;


public:

    SummedAreaTable() = default;

    void generateTable(VulkanGraphicsAPI& api, std::vector<uint8_t>& inputData, uint32_t width, uint32_t height) {

        this->width = width;
        this->height = height;

        uint32_t elementCount = inputData.size();

        api.initVulkan(inputData, this->width, this->height);
        std::cout << "Vulkan initialized with compute SAT setup.\n";

        api.recordCommandBuffer(this->width, this->height);
        api.submitCommandBuffer();

        api.waitForGpu();

        summedAreaTable = std::vector<uint8_t>(elementCount);
        api.retrievePrefixSum(summedAreaTable, elementCount);

        std::cout << "Generated SAT from GPU: ";

        int row = 0;

        std::cout << std::endl;

        for (uint8_t prefix : summedAreaTable) {
            std::cout << static_cast<uint32_t>(prefix) << " ";
            row++;

            if (row % this->width == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    uint8_t get(uint32_t x, uint32_t y) {
        return summedAreaTable[this->width * y + x];
    }

    uint8_t getRectangleSum(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {

        if (x0 >= this->width || x1 >= this->width || y0 >= this->height || y1 >= this->height) {
            return 0;
        }

        uint32_t upperLeftCornerX = x0;
        uint32_t upperleftCornerY = y0;

        uint32_t lowerLeftCornerX = x0;
        uint32_t lowerleftCornerY = y1;

        uint32_t upperRightCornerX = x1;
        uint32_t upperRightCornerY = y0;

        uint32_t lowerRightCornerX = x1;
        uint32_t lowerRightCornerY = y1;

        return get(upperLeftCornerX, upperleftCornerY) + get(lowerRightCornerX, lowerRightCornerY) - 
            get(upperRightCornerX, upperRightCornerY) - get(lowerLeftCornerX, lowerleftCornerY);
    }
};