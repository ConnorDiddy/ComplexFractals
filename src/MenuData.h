#ifndef MENU_DATA_H
#define MENU_DATA_H

#include <iostream>
#include <vector>
#include <map>
#include "ActionData.h"

typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData {
public:
    MenuData();
    void addAction(const std::string& name, ActionFunctionType func, const std::string& description);
    const std::vector<std::string>& getNames() const;
    ActionFunctionType getFunction(const std::string& name);
    const std::string& getDescription(const std::string& name);

private:
    std::vector<std::string> mCommands;
    std::map<std::string, ActionFunctionType> mCommandActionMap;
    std::map<std::string, std::string> mCommandDescriptionMap;
};

#endif