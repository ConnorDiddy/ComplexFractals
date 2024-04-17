#include "image_menu.h"

MenuData::MenuData () 
    : mCommands(), mCommandActionMap(), mCommandDescriptionMap() {
    }

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
    mCommands.push_back(name);
    mCommandDescriptionMap[name] = description;
    mCommandActionMap[name] = func;
}

const std::vector<std::string>& MenuData::getNames() const {
    return mCommands;
}

ActionFunctionType MenuData::getFunction(const std::string& name) {
    // Check if name exists in command function map
    if (mCommandActionMap.find(name) != mCommandActionMap.end()) {
        return mCommandActionMap[name];
    }
    else {
        return 0;
    }
}

const std::string& MenuData::getDescription( const std::string& name ) {
    static std::string emptyString;

     if (mCommandDescriptionMap.find(name) != mCommandDescriptionMap.end()) {
        return mCommandDescriptionMap[name];
    }
    else {
        return emptyString;
    }
}