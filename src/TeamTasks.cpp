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

/*
enum class TaskStatus
{
  NEW, IN_PROGRESS, TESTING, DONE
};

using TasksInfo = map<TaskStatus, int>;
*/

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
    TasksInfo oldTasks = personTasks.at(person);
    for (; task_count > 0; task_count--)
      {
    	if (personTasks.at (person).at (TaskStatus::NEW) > 0)
    	  {
    	    personTasks.at (person).at (TaskStatus::NEW)--;
    	    personTasks.at (person)[TaskStatus::IN_PROGRESS]++;
    
    	    oldTasks.at (TaskStatus::NEW) --;
    	    newTasks[TaskStatus::IN_PROGRESS]++;
    	  }
    	else if (personTasks.at (person).at (TaskStatus::IN_PROGRESS) > 0)
    	  {
    	    personTasks.at (person).erase(TaskStatus::NEW);
    	    
    	    personTasks.at (person).at (TaskStatus::IN_PROGRESS)--;
    	    personTasks.at (person)[TaskStatus::TESTING]++;
    
    	    oldTasks.at (TaskStatus::IN_PROGRESS) --;
    	    newTasks[TaskStatus::TESTING]++;
    	  }
    	else if (personTasks.at (person).at (TaskStatus::TESTING) > 0)
    	  {
    	    personTasks.at (person).erase(TaskStatus::IN_PROGRESS);
    	      
    	    personTasks.at (person).at (TaskStatus::TESTING)--;
    	    personTasks.at (person)[TaskStatus::DONE]++;
    
    	    oldTasks.at (TaskStatus::TESTING) --;
    	    newTasks[TaskStatus::DONE]++;
    
    	  }
    	else {
    	    personTasks.at (person).erase(TaskStatus::TESTING);
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

/*
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
*/
