#include <iostream>
#include <yaml-cpp/yaml.h>

struct YoloConfig {
    std::string trainFolder;
    std::string testFolder;
    std::string valFolder;
    int numClasses;
    std::vector<std::string> classNames;
};

YoloConfig readYoloConfig(const std::string& filename) {
    YoloConfig config;

    try {
        YAML::Node root = YAML::LoadFile(filename);

        config.trainFolder = root["train"].as<std::string>();
        config.testFolder = root["test"].as<std::string>();
        config.valFolder = root["val"].as<std::string>();
        config.numClasses = root["nc"].as<int>();

        const YAML::Node& classNamesNode = root["names"];
        for (const auto& className : classNamesNode) {
            config.classNames.push_back(className.as<std::string>());
        }
    } catch (const YAML::Exception& e) {
        std::cerr << "Error parsing YAML: " << e.what() << std::endl;
    }

    return config;
}

int main() {
    std::string filename = "data.yaml";
    YoloConfig config = readYoloConfig(filename);

    std::cout << "Train Folder: " << config.trainFolder << std::endl;
    std::cout << "Test Folder: " << config.testFolder << std::endl;
    std::cout << "Validation Folder: " << config.valFolder << std::endl;
    std::cout << "Number of Classes: " << config.numClasses << std::endl;
    std::cout << "Class Names:" << std::endl;
    for (const auto& className : config.classNames) {
        std::cout << "- " << className << std::endl;
    }

    return 0;
}
