/*
 *  abcu_course.cpp
 *
 *  Date: June 19th 2022
 *  Author: Paul Mauviel
 */

#include <abcu_course.h>
#include <fstream>
#include <tuple>

std::pair<std::string, uint32_t> GetNextTokenFromStringWithDelimiter(const std::string& theString, char delimiter, uint32_t startPosition) {
    if (startPosition > theString.size()) return {"", theString.size() + 1};
    std::string token {};

    // Reserve 10 characters to reduce number of resizes
    token.reserve(10);

    for (auto i = startPosition; i < theString.size(); i++) {

        auto character = theString[i];

        if (character == delimiter) {
            return {theString.substr(startPosition, i - startPosition), i+1};
        }
    }

    return {theString.substr(startPosition, theString.size() - startPosition), theString.size() + 1};
}

std::unordered_map<std::string, ABCUCourse> LoadCoursesFromFile(const Path& filePath) {
    std::unordered_map<std::string, ABCUCourse> courses {};

    std::ifstream inputFile {filePath};

    std::string line;
    while (std::getline(inputFile, line)) {
        ABCUCourse newCourse {};

        // By tokenizing the string like this, we prevent looping over the string multiple times
        // If we first split the string, and then filled the structure, that would be looping over things twice.
        // NOTE: This same concept could be applied to reading through the file. We could have read everything a token at
        // a time from the file, creating a new course structure every time we reached a new line -- this would also
        // reduce some redundant time spent looping over the input data.
        // The performance gains are negligible though I opted to not do it.
        auto result = GetNextTokenFromStringWithDelimiter(line, ',', 0);
        uint8_t i { 0 };
        while (!result.first.empty()) {
            auto token = result.first;

            switch (i) {
                case 0: {
                    newCourse.Number = token;
                    break;
                }
                case 1: {
                    newCourse.Name = token;
                    break;
                }
                default: {
                    newCourse.Prerequisites.push_back(token);
                }
            }

            i++;
            result = GetNextTokenFromStringWithDelimiter(line, ',', result.second);
        }

        // Add course to map
        courses[newCourse.Number] = newCourse;
    }

    inputFile.close();
    return courses;
}