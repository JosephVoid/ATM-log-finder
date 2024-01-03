#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

std::string getFile(std::string terminal, std::string date) {
  std::string full_dir; std::stringstream ss;
  ss << "cd " << terminal <<"&& dir /b /s *.* | findstr /i " << date <<"";
  full_dir = exec(ss.str().c_str());
  return full_dir.substr(full_dir.find_last_of('\\') + 1);
}

int getRecordNoLine(std::string file_path, int record_no) 
{
    std::string line; int lineCount; bool found = false;
    std::ifstream file (file_path);
    if (file.is_open())
    {
      while ( getline (file,line) )
      {
        lineCount += 1;
        if (line.find(std::to_string(record_no)) != std::string::npos && line.find("RECORD NO.") != std::string::npos) {
          found = true;
          break;
        }
      }
      file.close();
    }
    else std::cout << ">> (*) UNABLE TO OPEN FILE";

    return found ? lineCount : -1;
}

std::vector<std::string> getSurroundingText(std::string file_path, int record_no, int record_line) {
  std::ifstream file (file_path); 
  int lineCount = 0, upperBound = 0, lowerBound = 0;
  int lower_rec_num = record_no, upper_rec_num = record_no;
  std::string line; std::vector<std::string> text;
  
  if (record_line == -1) {
    // decrease RN by 1 until an EJ is found
    for (size_t i = 0; i < 7; i++)
    {
      lower_rec_num -= 1;
      if (getRecordNoLine(file_path, lower_rec_num) != -1){

        lowerBound = getRecordNoLine(file_path, lower_rec_num);
        break;
      }
    }
    
    // increase RN by 1 until an EJ is found
    for (size_t i = 0; i < 7; i++)
    {
      upper_rec_num += 1;
      if (getRecordNoLine(file_path, upper_rec_num) != -1){

        upperBound = getRecordNoLine(file_path, upper_rec_num);
        break;
      }
    }
    
    if (lowerBound != 0 && upperBound != 0){
      // get the lines and read from tope EJ + 20 to bottom EJ -15
      if (file.is_open())
      {
        while ( getline (file,line) )
        {
          lineCount += 1;
          if (lineCount > lowerBound - 20 && lineCount < upperBound + 15) {
            text.push_back(line + '\n');
          }
        }
        file.close();
      }
      else std::cout << ">> (*) UNABLE TO OPEN FILE";
      }
      else {
        text.push_back(">> (*) RECORD_NO NOT FOUND!");
        return text;
      }
    
  }
  
  else {
    if (file.is_open())
    {
      while ( getline (file,line) )
      {
        lineCount += 1;
        if (lineCount > record_line - 15 && lineCount < record_line + 20) {
          text.push_back(line + '\n');
        }
      }
      file.close();
    }
    else std::cout << ">> (*) UNABLE TO OPEN FILE";
  }

  return text;
}