#include "company_classes.h"
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
//bool CompareTechnologiesByValue::operator()(const Technology* lhs, const Technology* rhs) const
//{
//	return *lhs == *rhs;
//}

void Project::addDeveloper(Developer* dev)
{
	developers.push_back(dev);
	for (auto& technology : dev->getTechnologies())
		unfulfiled_technologies.erase(technology);
}

bool Project::eligibleToWork(Developer* dev)
{
	for (auto& technology : dev->getTechnologies())
		if (unfulfiled_technologies.find(technology) != unfulfiled_technologies.end())
			return true;
	return false;
}

double ProgrammingTechnologyTimeChangeStrategy::getTimeChange(int command_size)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	double chances[] = { chance_unresolved_compiler_bug, chance_rare_bug, chance_data_lost };
	double influences[] = { unresolved_compiler_error_influence, rare_bug_influence, data_lost_influence };
	double cur_chances[] = { dist(mt) ,dist(mt) ,dist(mt) };
	double project_influence = 0;
	for (int i = 0; i < 3; i++)
	{
		if (cur_chances[i] < chances[i])
			project_influence += influences[i];
	}
	return project_influence;
}

double ManagingTechnologyTimeChangeStrategy::getTimeChange(int command_size)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	
	double project_influence = 0;

	double cur_chances[] = { dist(mt) ,dist(mt) ,dist(mt) , dist(mt) };
	
	double incompatibility_chance = team_imcompatibility_chance + 0.04 * (command_size - 8);
	if (cur_chances[0] < incompatibility_chance)
	{
		project_influence += team_imcompatibility_influence;
	}

	double spirit_chance = small_team_spirit_boost_chance + 0.05 * (8 - command_size);

	if (cur_chances[1] < spirit_chance)
	{
		project_influence -= small_team_spirit_boost_influence;
	}
	
	double team_member_ill = team_member_ill_chance + 0.01 * (command_size);

	if (cur_chances[2] < team_member_ill)
		project_influence += team_member_ill_influence;

	double good_management = perfect_managment_chance - 0.02 * (command_size);

	if (cur_chances[3] < good_management)
		project_influence -= perfect_managment_chance;

	return project_influence;
}

void ProjectManager::simulate()
{
	vector<ProjectWithState> projects_status = vector<ProjectWithState>();
	projects_status.reserve(projects.size());
	for (Project* project : projects)
		projects_status.push_back(ProjectWithState(project));

	bool all_projects_finished = false;
	vector<unsigned char> developers_used(developers.size());
	std::fill(developers_used.begin(), developers_used.end(), 0);

	while (!all_projects_finished)
	{
		all_projects_finished = true;
		for (auto& cur_project_status : projects_status)
		{
			if (cur_project_status.state == ProjectState::kProcessing)
			{
				--cur_project_status.time_left;
				if (cur_project_status.time_left == 0)
				{
					cur_project_status.state = ProjectState::kFinished;
					cout << "Project " << cur_project_status.project->getName() << " is finished\n";
					for (int i : cur_project_status.developers_used)
						developers_used[i] = 0;
				}
				else
					all_projects_finished = false;
			}
			else if (cur_project_status.state != ProjectState::kFinished)
				all_projects_finished = false;
		}

		if (all_projects_finished)
		{
			cout << "All projects are finished\n";
			break;
		}

		for (auto& cur_project_status : projects_status)
		{
			if (cur_project_status.state != ProjectState::kAssigningDevelopers)
				continue;
			auto project = cur_project_status.project;
			int i = 0;
			for (auto developer : developers)
			{
				if (developers_used[i] != 0)
				{
					++i;
					continue;
				}
					
				if (cur_project_status.project->eligibleToWork(developer))
				{
					cur_project_status.developers_used.push_back(i);
					project->addDeveloper(developer);
					developers_used[i] = 1;
					cout << "Developer " << developer->getName() << " added to project " << project->getName() << endl;
				}
				if (project->finishedAssigning())
				{
					cur_project_status.state = ProjectState::kProcessing;
					cur_project_status.time_left = project->getDevelopmentTime();
					cout << "The project " << project->getName() << " started. " << cur_project_status.time_left << " hours to finish.\n";
					break;
				}
				++i;
			}
		}
	}
}

int MediumProjectTimeAssesmentStrategy::assessTime(Project* project)
{
	int initial_time = project->getDifficulty() * 100;
	double command_improvement_ratio = 0;
	for (auto& developer : project->getDevelopers())
		command_improvement_ratio += developer->getEfficiency();

	command_improvement_ratio /= 1.25; // command interactions slowdown
	initial_time /= command_improvement_ratio;

	double technologies_influence = 0;
	for (auto& techology : project->getTechnologies())
	{
		technologies_influence += techology->getTimeChange(project->getDevelopers().size());
	}

	initial_time = (1 + technologies_influence) * initial_time;
	return initial_time;
}

int LargeProjectTimeAssesmentStrategy::assessTime(Project* project)
{
	int initial_time = project->getDifficulty() * 300;
	double command_improvement_ratio = 0;
	for (auto& developer : project->getDevelopers())
		command_improvement_ratio += developer->getEfficiency() * 0.75;

	command_improvement_ratio /= 1.75; // command interactions slowdown
	initial_time /= command_improvement_ratio;

	double technologies_influence = 0;
	for (auto& techology : project->getTechnologies())
	{
		technologies_influence += techology->getTimeChange(project->getDevelopers().size()) * 1.5;
	}

	initial_time = (1 + technologies_influence) * initial_time;
	return initial_time;
}
