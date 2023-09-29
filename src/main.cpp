// By José Antonio Rosales
#include <iostream>
#include <string>
#include "../utils/crud.cpp"

using namespace std;

void menu(int user_id)
{
  do
  {
    system("clear");
    cout << "¡Welcome to TaskManager!" << endl;
    cout << "           :)           " << endl;
    cout << endl;
    cout << "Select an option:" << endl;
    cout << "1.Check my tasks\n2.New task\n3.Edit task\n4.Delete task" << endl;
    cout << "To stop the program just type anything else." << endl;

    string opt;
    cout << "\n>";
    getline(cin, opt);

    switch (stoi(opt))
    {
    case 1:
      read_todo(user_id);
      break;
    case 2:
      insert_todo(user_id);
      break;
    case 3:
      update_todo(user_id);
      break;
    case 4:
      delete_todo(user_id);
      break;

    default:
      exit(0);
    }
  } while (true);
}

int main(int argc, char const *argv[])
{
  int user_id = 1;
  menu(user_id);
  return 0;
}
