/*
 *  application.h
 *
 *  Date: June 19th 2022
 *  Author: Paul Mauviel
 */

#pragma once

#include <cstdint>
#include <abcu_course.h>
#include <tuple>

/**
 * Main Application Class
 */
class Application {
public:
    /**
     * Main Application Loop
     */
    void Run();

private:
    /**
     * Prints a greeting
     */
    void printGreeting();

    /**
     * Prints farewell message
     */
    void printFarewell();

    /**
     * Prints the menu
     */
    void printMenu();

    /**
     * Gets a filepath from input, converts to absolute path if necessary
     * @return Absolute path to file specified by user
     * @throws Runtime exception if file not found
     */
    Path getFilePathFromUser();

    /**
     * Gets a course number from user input
     * @return course number requested
     */
    std::string getCourseNumberFromUser();

    /**
     * Shuts down the main application loop
     */
    void endApplication();

private:
    bool _isRunning { false };
    std::unordered_map<std::string, ABCUCourse> courses {};
};
