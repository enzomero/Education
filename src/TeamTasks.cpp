/*
 * TeamTasks.cpp
 *
 *  Created on: 4 мар. 2018 г.
 *      Author: Raus
 */
#include <iostream>
#include <string>
#include <map>
#include <tuple>

using namespace std;

enum class TaskStatus
{
  NEW,          // нова€
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// ќбъ€вл€ем тип-синоним дл€ map<TaskStatus, int>,
// позвол€ющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks
{
public:
  // ѕолучить статистику по статусам задач конкретного разработчика
  const TasksInfo&
  GetPersonTasksInfo (const string& person) const;


  // ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
  void
  AddNewTask (const string& person)
  {
    TasksInfo data = {{TaskStatus::NEW , 1}};
    personTasks.insert({{person, data}});
  }

  // ќбновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo>
  PerformPersonTasks (const string& person, int task_count)
  {
    TasksInfo taskPerson = personTasks.at(person);
    if (true){

    }
    return tie(taskPerson, taskPerson);
  }
private:
  map<string, map<TaskStatus, int>> personTasks;
};

bool operator<( TaskStatus& lhs,  TaskStatus& rhs){
  if ( lhs == TaskStatus::NEW and rhs == TaskStatus::IN_PROGRESS )
    return true;
  if ( lhs == TaskStatus::IN_PROGRESS and rhs == TaskStatus::TESTING )
      return true;
  if ( lhs == TaskStatus::TESTING and rhs == TaskStatus::DONE )
      return true;
  return false;
}

void
PrintTasksInfo (TasksInfo tasks_info)
{
  cout << tasks_info[TaskStatus::NEW] << " new tasks" << ", "
      << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" << ", "
      << tasks_info[TaskStatus::TESTING] << " tasks are being tested" << ", "
      << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int
main ()
{
  TeamTasks tasks;
  tasks.AddNewTask ("Ilia");
  for (int i = 0; i < 3; ++i)
    {
      tasks.AddNewTask ("Ivan");
    }
  cout << "Ilia's tasks: ";
  PrintTasksInfo (tasks.GetPersonTasksInfo ("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo (tasks.GetPersonTasksInfo ("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie (updated_tasks, untouched_tasks) = tasks.PerformPersonTasks ("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo (updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo (untouched_tasks);

  tie (updated_tasks, untouched_tasks) = tasks.PerformPersonTasks ("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo (updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo (untouched_tasks);

  return 0;
}
