/*
 *  abcu_course.h
 *
 *  Date: June 19th 2022
 *  Author: Paul Mauviel
 */

#pragma once


#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <fmt/format.h>

using Path = std::filesystem::path;

/**
 * Main Course Structure
 */
struct ABCUCourse {
    std::string Number {};
    std::string Name {};
    std::vector<std::string> Prerequisites {};

    std::string GetShortDescription() {
        return fmt::format("{}, {}", Number, Name);
    }

    std::string GetDescription() {
        auto shortDesc = GetShortDescription();


        if (Prerequisites.empty()) {
            return fmt::format("{}\nNo Prerequisites.", shortDesc);
        } else {
            std::string prereqs{};

            for (const auto &prereq: Prerequisites) {
                if (prereqs.empty()) {
                    prereqs = fmt::format("{}", prereq);
                } else {
                    prereqs = fmt::format("{}, {}", prereqs, prereq);
                }
            }
            return fmt::format("{}\nPrerequisites: {}", shortDesc, prereqs);
        }
    }
};

/**
 * Loads Courses From File
 * @return unordered map of ABCUCourse with ABCUCourse::Number as key
 */
std::unordered_map<std::string, ABCUCourse> LoadCoursesFromFile(const Path&);
