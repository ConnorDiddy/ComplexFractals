#include "image_menu.h"

std::string getString( ActionData& action_data, const std::string& prompt ) {
  std::string result;
  action_data.getOS() << prompt;
  action_data.getIS() >> result;

  return result;
}

int getInteger( ActionData& action_data, const std::string& prompt ) {
  int result;
  action_data.getOS() << prompt;
  action_data.getIS() >> result;

  return result;
}

double getDouble( ActionData& action_data, const std::string& prompt ) {
  double result;
  action_data.getOS() << prompt;
  action_data.getIS() >> result;

  return result;
}

int askQuestions3(ActionData& action_data) {
  std::string favColor;
  int favInt;
  double favFloat;

  favColor = getString(action_data, "What is your favorite color? ");
  favInt = getInteger(action_data, "What is your favorite integer? ");
  favFloat = getDouble(action_data, "What is your favorite number? ");
  
  for (int i = 1; i <= favInt; i++) {
    action_data.getOS() << i << ' ' <<  favColor << ' ' << favFloat << std::endl;
  };
  
 return favInt;
}

std::string getChoice( ActionData& action_data ) {
  std::string choice;

  choice = getString(action_data, "Choice? ");

  return choice;
}

#include "ActionData.h" // Include the necessary header file

void commentLine(ActionData& action_data) {
    char ch;
    action_data.getIS().read(&ch, 1);
    if (ch == '\n') {
        return; // Return if the first character is a newline character
    }

    while (action_data.getIS().read(&ch, 1)) {
        // If the character read is not a newline character, continue reading
        if (ch != '\n' && action_data.getIS().good()) {
            continue;
        } else {
            return; // Return if a newline character is read
        }
    }
}

void quit( ActionData& action_data ) {
  action_data.setDone();
}