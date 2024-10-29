#pragma once

#define VK_CHECK_RESULT(f) { VkResult res = (f); if (res != VK_SUCCESS) { \
    std::cout << "Fatal : VkResult is \"" << res << "\" in " << __FILE__ << " at line " << __LINE__ << "\n"; \
    exit(1); } }

class VulkanGraphicsAPI {

public:

    struct UniformBufferObject {
        uint32_t width;
        uint32_t height;
    };

    VulkanGraphicsAPI() = default;
    ~VulkanGraphicsAPI() { 
        clean();
    }

private:

    VkInstance instance;
    VkDevice device;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkQueue computeQueue;
    VkPipeline computePipeline;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkBuffer ssbo;
    VkDeviceMemory ssboMemory;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    uint32_t computeQueueFamilyIndex;

    VkBuffer outputSsbo;
    VkDeviceMemory outputSsboMemory;

    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;

public:

    void createInstance();
    void pickPhysicalDevice();

    void findComputeQueueFamily();
    void createLogicalDevice();
    std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createSSBO(std::vector<uint8_t>& inputData);
    void createOutputSSBO(uint32_t dataSize);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void createComputePipeline();
    void updateUniformBuffer(uint32_t width, uint32_t height);
    void createDescriptorSets();
    void createCommandPool();
    void recordCommandBuffer(uint32_t width, uint32_t height);
    void retrievePrefixSum(std::vector<uint8_t>& outputData, uint32_t elementCount);
    void submitCommandBuffer();
    void allocateCommandBuffer();

    void cleanupCommandPool() {
        vkDestroyCommandPool(device, commandPool, nullptr);
    }

    void initVulkan(std::vector<uint8_t>& inputData, uint32_t width, uint32_t height);

    void waitForGpu() {
        vkDeviceWaitIdle(device);
    }

    void clean();
};