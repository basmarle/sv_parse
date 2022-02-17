//
// Created by encya on 17-02-22.
//

#ifndef SV_PARSE_MODULE_H
#define SV_PARSE_MODULE_H


#include <string>
#include <vector>

class Module {
public:
    Module(const std::string& name);

    std::vector<std::string> ports;
    std::string name;

    Module();
};


#endif //SV_PARSE_MODULE_H
