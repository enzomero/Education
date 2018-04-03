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

class TeamTasks {
public:
	const TasksInfo&
		GetPersonTasksInfo(const string& person) const {
		return personTasks.at(person);
	}

	void AddNewTask(const string& person) {
		personTasks[person][TaskStatus::NEW]++;
	}

	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person,
		int task_count) {
		const TasksInfo origin = personTasks.at(person);

		TasksInfo newTasks;
		TasksInfo oldTasks;
		int count = task_count;

		for (int i = 0 ; i < 3 ; i++) {
			TaskStatus now = static_cast<TaskStatus>(i);
			TaskStatus next = static_cast<TaskStatus>(i + 1);
			if (count == 0)
				break;
			IteratorOfTasks(person, count, newTasks, oldTasks, now, next);
		}

		const TasksInfo finaled = personTasks.at(person);

		Comparator(origin, finaled, newTasks, oldTasks, task_count);
		return tie(newTasks, oldTasks);
	}
private:
	map<string, map<TaskStatus, int>> personTasks;

	void IteratorOfTasks(const string& person, int& task_count, TasksInfo& newTasks, TasksInfo& oldTasks, TaskStatus now, TaskStatus next) {
		int diff = personTasks.at(person)[now] - task_count;
		if (diff <= 0) {
			personTasks.at(person)[next] += personTasks.at(person)[now];
			personTasks.at(person).erase(now);

			task_count = diff * (-1);
		}
		else {
			personTasks.at(person)[next] += task_count;
			personTasks.at(person)[now] = diff;

			task_count = 0;
		}
	}

	void Comparator(TasksInfo origin, TasksInfo finaled, TasksInfo& newTasks, TasksInfo& oldTasks, int task_count) {
		for (int i = 0; i < 3; i++) {
			TaskStatus now = static_cast<TaskStatus>(i);
			TaskStatus next = static_cast<TaskStatus>(i + 1);
			int diff = origin[now] - finaled[now];
			if (diff < 0) {
				newTasks[next] = task_count;
				break;
			} 
			newTasks[next] = diff;
			task_count -= diff;
		}

		for (int i = 0; i < 3; i++) {
			TaskStatus now = static_cast<TaskStatus>(i);
			TaskStatus next = static_cast<TaskStatus>(i + 1);
			int oldDiff = finaled[now] - newTasks[now];
			if (oldDiff < 0)
				oldTasks[now] = oldDiff * (-1);
			else
				oldTasks[now] = oldDiff;
		}

		oldTasks.erase(TaskStatus::DONE);
	}
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
