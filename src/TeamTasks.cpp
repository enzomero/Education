/*
 * TeamTasks.cpp
 *
 *  Created on: 4 ���. 2018 �.
 *      Author: Raus
 */
#include <iostream>
#include <string>
#include <map>
#include <tuple>

using namespace std;

enum class TaskStatus
{
  NEW, IN_PROGRESS, TESTING, DONE
};

using TasksInfo = map<TaskStatus, int>;

class TeamTasks
{
public:
  const TasksInfo&
  GetPersonTasksInfo (const string& person) const
  {
    return personTasks.at (person);
  }

  void
  AddNewTask (const string& person)
  {
    personTasks[person][TaskStatus::NEW]++;
  }

  tuple<TasksInfo, TasksInfo>
  PerformPersonTasks (const string& person, int task_count)
  {
    TasksInfo newTasks;
    TasksInfo oldTasks;
    int diff = 0;
    for (auto taskInfo : personTasks.at (person))
      {
	if (taskInfo.first != TaskStatus::NEW)
	  {
	    taskInfo.second += task_count;
	    newTasks[taskInfo.first] = task_count;
	    task_count = diff;
	    diff = 0;
	  }

	if (taskInfo.second < task_count)
	  {
	    diff = task_count - taskInfo.second;
	    taskInfo.second = 0;
	  }
	else if (taskInfo.second > task_count)
	  {
	    taskInfo.second -= task_count;
	    oldTasks[taskInfo.first] = taskInfo.second;
	  }
	else
	  {
	    oldTasks[taskInfo.first] = taskInfo.second;
	  }
      }

    return tie (newTasks, oldTasks);
  }
private:
  map<string, map<TaskStatus, int>> personTasks;
};

bool
operator< (TaskStatus& lhs, TaskStatus& rhs)
{
  if (lhs == TaskStatus::NEW and rhs == TaskStatus::IN_PROGRESS)
    return true;
  if (lhs == TaskStatus::IN_PROGRESS and rhs == TaskStatus::TESTING)
    return true;
  if (lhs == TaskStatus::TESTING and rhs == TaskStatus::DONE)
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
  for (int i = 0; i < 3; ++i)
    {
      tasks.AddNewTask ("Ivan");
    }

  cout << "Ivan's tasks: ";
  PrintTasksInfo (tasks.GetPersonTasksInfo ("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie (updated_tasks, untouched_tasks) = tasks.PerformPersonTasks ("Ivan", 4);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo (updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo (untouched_tasks);

  return 0;
}
