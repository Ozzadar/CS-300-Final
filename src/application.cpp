/*
 *  application.cpp
 *
 *  Date: June 19th 2022
 *  Author: Paul Mauviel
 */

// Application-defined headers
#include <application.h>
#include <utils.h>

// STL Headers
#include <iostream>
#include <cassert>

void Application::Run() {
    _isRunning = true;

    printGreeting();

    while (_isRunning) {
        std::cout << "What would you like to do? \n";
        printMenu();

        switch (auto selection = getValidIntegerFromUser()) {
            case 1: {
                try {
                    auto fileName = getFilePathFromUser();
                    courses = LoadCoursesFromFile(fileName);

                } catch (const std::runtime_error& e) {
                    std::cerr << fmt::format("Error: {}", e.what()) << std::endl;
                }
                break;
            }
            case 2: {
                if (courses.empty()) {
                    std::cerr << "Course list not loaded! Use option 1 first!" << std::endl;
                    break;
                }

                std::cout << "Here is a sample schedule: \n";

                // Get the list of keys from the map
                std::vector<std::string> keys(courses.size());
                std::transform(courses.begin(), courses.end(), keys.begin(), [](auto kv_pair) {
                    return kv_pair.first;
                });

                // sort the keys
                std::sort(keys.begin(), keys.end());

                // Print the courses by their short description in sorted order
                for (const auto& key : keys) {
                    std::cout << courses[key].GetShortDescription() << "\n";
                }
                std::cout << std::endl;
                break;
            }
            case 3: {
                if (courses.empty()) {
                    std::cerr << "Course list not loaded! Use option 1 first!" << std::endl;
                    break;
                }

                auto courseNumber = getCourseNumberFromUser();

                // unordered maps dont have a constant-time function for checking if a key exists
                // this will initialize an empty object at that key if it doesnt exist so we can check
                // for an empty course number.
                // this wouldn't be a good way to do it in a long-running application as it would lead to a build up
                // of empty objects if there are a lot of queries for things that don't exist but for our use-case it
                // will be good enough.
                // NOTE: C++ 20 adds a .contains(key) function that is constant time on average but im using C++17
                // standard here Ref: https://en.cppreference.com/w/cpp/container/unordered_map/contains
                if (courses[courseNumber].Number.empty()) {
                    std::cerr << fmt::format("Course {} not in catalogue!\n", courseNumber) << std::endl;
                    break;
                }

                std::cout << courses[courseNumber].GetDescription() << "\n\n";

                break;
            }

            case 9: {
                endApplication();
                break;
            }

            default: {
                std::cerr << fmt::format("{} is not a valid option.", std::to_string(selection)) << std::endl;
            }
        }

        // Flush the output buffer to ensure everything has been printed.
        std::flush(std::cout);
    }

    printFarewell();
}

void Application::printGreeting() {
    std::cout << "Welcome to the course planner." << std::endl;
}

void Application::printFarewell() {
    std::cout << "Thank you for using the course planner!" << std::endl;
}

void Application::printMenu() {
    std::cout << "1. Load Data Structure.\n";
    std::cout << "2. Print Course List. \n";
    std::cout << "3. Print Course.\n";
    std::cout << "9. Exit" << std::endl;
}

Path Application::getFilePathFromUser() {
    std::cout << "Which file would you like to load? (absolute or relative paths accepted)" << std::endl;

    std::string userSpecifiedPath;
    std::getline(std::cin, userSpecifiedPath);

    // Ensure that slashes are in the operating system's correct format
    auto path = Path(userSpecifiedPath).make_preferred();

    // convert to absolute path if path supplied is relative
    if (path.is_relative()) {
        path = std::filesystem::current_path() / path;
    }

    // Conversion to absolute path was unsuccessful if this assert is thrown
    assert(path.is_absolute() && "Path is not absolute!");

    if (!std::filesystem::exists(path)) {
        throw std::runtime_error(fmt::format("File doesn't exist: {}\n", path.string()));
    }

    return path;
}

std::string Application::getCourseNumberFromUser() {
    std::cout << "What course do you want to know about?";

    std::string courseNumber;
    std::getline(std::cin, courseNumber);
    return courseNumber;
}

void Application::endApplication() {
    _isRunning = false;
}




