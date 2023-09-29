// By José Antonio Rosales
#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

using namespace std;
using namespace sql;

Connection *sql_conn()
{
  Connection *con;
  mysql::MySQL_Driver *driver;

  driver = mysql::get_mysql_driver_instance();
  con = driver->connect("127.0.0.1:3306", "root", "");

  if (con->isValid())
    return con;
  else
    exit(0);
}

void read_todo(int id)
{
  int todo_id;
  string todo_name, todo_desc, todo_date;
  bool is_done;

  Connection *con = sql_conn();
  Statement *stmt = con->createStatement();
  stmt->execute("USE todo_app");
  ResultSet *res = stmt->executeQuery("SELECT * FROM todo WHERE todo_user = \"" + to_string(id) + "\"");

  system("clear");
  while (res->next())
  {
    todo_id = res->getInt(1);
    todo_name = res->getString(2);
    todo_desc = res->getString(3);
    is_done = res->getBoolean(4);
    todo_date = res->getString(5);

    cout << "----------" << endl;
    cout << "ID:" << todo_id << endl;
    cout << todo_name << endl;
    cout << todo_desc << endl;
    (is_done) ? cout << "Task done." << endl : cout << "Task pending" << endl;
    cout << "Deadline on " << todo_date << "." << endl;
  }
  cout << "Enter anything to continue..." << endl;
  string s;
  getline(cin, s);

  delete con;
  delete stmt;
  delete res;
}

void insert_todo(int user_id)
{
  string in_name, in_desc, in_date;

  system("clear");
  cout << "Insert new task" << endl;
  cout << "Name: ";
  getline(cin, in_name);
  cout << "Description: ";
  getline(cin, in_desc);
  cout << "Deadline: ";
  getline(cin, in_date);

  sql::Connection *con = sql_conn();
  sql::Statement *stmt = con->createStatement();

  stmt->execute("USE todo_app");
  stmt->execute("INSERT INTO todo (todo_name, todo_desc, todo_date, todo_user) VALUE (\"" + in_name + "\", \"" + in_desc + "\", \"" + in_date + "\", " + to_string(user_id) + ");");

  delete con;
  delete stmt;

  system("clear");
  cout << "Task created succesfully..." << endl;
  string s;
  getline(cin, s);
}

void update_todo(int user_id)
{
  string in_name, in_desc, task_id;

  system("clear");
  cout << "Edit task" << endl;
  cout << "Task ID: ";
  getline(cin, task_id);
  cout << "Name: ";
  getline(cin, in_name);
  cout << "Description: ";
  getline(cin, in_desc);

  sql::Connection *con = sql_conn();
  sql::Statement *stmt = con->createStatement();

  stmt->execute("USE todo_app");
  stmt->execute("UPDATE todo SET todo_name = '" + in_name + "', todo_desc = '" + in_desc + "' WHERE todo_id = " + task_id + " AND todo_user = " + to_string(user_id));

  delete con;
  delete stmt;

  system("clear");
  cout << "Task updated succesfully..." << endl;
  string s;
  getline(cin, s);
}

void delete_todo(int user_id)
{
  string task_id;
  string confirmation;

  system("clear");
  cout << "Delete task" << endl;
  cout << "Task ID: ";
  getline(cin, task_id);
  cout << "Are you sure?! (yes/no)" << endl;
  getline(cin, confirmation);

  if (confirmation == "yes")
  {
    sql::Connection *con = sql_conn();
    sql::Statement *stmt = con->createStatement();

    stmt->execute("USE todo_app");
    stmt->execute("DELETE FROM todo WHERE todo_id = " + task_id + " AND todo_user = " + to_string(user_id));

    delete con;
    delete stmt;

    system("clear");
    cout << "Task deleted succesfully..." << endl;
    string s;
    getline(cin, s);
  }
  else
  {
    system("clear");
    cout << "Operation aborted..." << endl;
    string s;
    getline(cin, s);
  }
}
