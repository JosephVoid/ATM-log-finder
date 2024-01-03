#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>

#include "helpers.h"


using namespace std;

int main () {
  string terminal, date, ej_dir, d_str, m_str;
  std::stringstream ssd, ssf;
  int record_no, month, day;

  cout<<"                   **\n";
  cout<<"                   ** \n";
  cout<<"                *  **  *\n";
  cout<<"              ***  **  ***\n";
  cout<<"            *****  **  *****\n";
  cout<<"          *******  **  *******\n";
  cout<<"        *****    * ** *    *****\n";
  cout<<"      ******       **       ******\n";
  cout<<"    *******        **        *******\n";
  cout<<"  **********     * ** *     *********\n";
  cout<<"***************************************\n";

  cout<<"\n\t\tDASHEN BANK\n";
  cout<<"\t\tEJ FINDER\n\n\n";
  
  for (;;)
  { 
    // Terminal input check
    term:
    cout<<"TERMINAL: ", cin>>terminal;
    if ( !(terminal.rfind("PATM", 0) == 0) || !(terminal.length() == 8) ) {
      cout<<">> (*) WRONG TERMINAL FORMAT!\n";
      goto term;
    }

    // Month input check
    mnth:
    cout<<"MONTH: ";
    while(!(cin >> month)) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << ">> (*) MONTH MUST BE AN INTEGER!\n";
      cout<<"MONTH:\n";
    }

    if (month > 12 || month < 1) {
      cout<<">> (*) MONTH MUST BE BETWEEN 1 AND 12!\n";
      goto mnth;
    }

    if (month < 10)
    {
      m_str = to_string(month);
      m_str.insert(0, 1 ,'0');
    } else {
      m_str = to_string(month);
    }

    // Day input check
    dy:
    cout<<"DAY: ";
    while(!(cin >> day)) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << ">> (*) DAY MUST BE AN INTEGER!\n";
      cout<<"DAY:";
    }

    if (day > 31 || day < 1) {
      cout<<">> (*) DAY MUST BE BETWEEN 1 AND 31!"<<endl;
      goto dy;
    }

    if (day < 10)
    {
      d_str = to_string(day);
      d_str.insert(0, 1 ,'0');
    } else {
      d_str = to_string(day);
    }
    

    // Record number input check
    cout<<"RECORD_NO:";
    while(!(cin >> record_no)) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << ">> (*) RECORD NUMBER MUST BE AN INTEGER!\n";
      cout<<"RECORD_NO:";
    }

    cout<<"\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout<<"\n";

    ssd.str(std::string()); ssf.str(std::string());
    ssd << "2022-" << m_str << "-" << d_str;
    ssf <<terminal<<"/"<<getFile(terminal,ssd.str());
    string fin_dir = ssf.str();
    fin_dir.erase(fin_dir.find_last_not_of(" \n\r\t")+1);

    for (auto &&i : getSurroundingText(fin_dir, record_no, getRecordNoLine(fin_dir, record_no)))
    {
      cout<< i;
    }  

    cout<<"\n";
    cout<<"\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
  }  
  return 0;
}

// MISSION RECOVERY
// exec(string cmd)
// getFile(string terminal, string date)
// getRecordNoLine(string file_path, int record_no)
// getSurroundingText(string file_path, int record_no, int record_line)
