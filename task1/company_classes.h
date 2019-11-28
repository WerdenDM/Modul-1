#pragma once
#include <string>
#include <vector>
#include <set>
#include <list>
#include <random>
using std::list;
using std::vector;
using std::string;
using std::set;

class Technology;
class Project;

//class CompareTechnologiesByValue
//{
//	bool operator()(const Technology* lhs, const Technology* rhs) const;
//};

class Developer
{
private:
	string full_name;
	
	double efficiency; // from 0 to 1

	set<Technology*> technologies;
public:
	Developer(const string& fname, double eff) :full_name(fname), efficiency(eff) {}
	void setTechnogies(const set<Technology*>& techn) { technologies = techn; }
	void addTechnology(Technology& tech) { technologies.insert(&tech); }
	set<Technology*> getTechnologies() const { return technologies; }
	double getEfficiency() const { return efficiency; }
	const string& getName() const { return full_name; }
};

class TechnologyTimeChangeStrategy
{
public:
	virtual double getTimeChange(int command_size) = 0;
};


class ProgrammingTechnologyTimeChangeStrategy:public TechnologyTimeChangeStrategy
{
private:
	double chance_unresolved_compiler_bug; // change from 0 to 1 to prolong or shorten the overall project time
	double chance_rare_bug;
	double chance_data_lost;
	
	
	double unresolved_compiler_error_influence; // from -1 to 1, where -1 mean that the project time is prolonged by 100%, 1 - shortend by 100%
	double rare_bug_influence;
	bool data_lost_influence;
public:
	ProgrammingTechnologyTimeChangeStrategy(double c_u_c_b, double c_r_b, double c_d_l, double u_c_e_i, double r_b_i, double d_l_i) :
		chance_unresolved_compiler_bug(c_u_c_b),
		chance_rare_bug(c_r_b),
		chance_data_lost(c_d_l),
		unresolved_compiler_error_influence(u_c_e_i),
		rare_bug_influence(r_b_i),
		data_lost_influence(d_l_i) {}

	virtual double getTimeChange(int command_size);
};

class ManagingTechnologyTimeChangeStrategy :public TechnologyTimeChangeStrategy
{
private:
	double team_imcompatibility_chance; // change from 0 to 1 to prolong or shorten the overall project time
	double small_team_spirit_boost_chance;
	double team_member_ill_chance;
	double perfect_managment_chance;


	double team_imcompatibility_influence; // from -1 to 1, where -1 mean that the project time is prolonged by 100%, 1 - shortend by 100%
	double small_team_spirit_boost_influence;
	double team_member_ill_influence;
	double perfect_managment_influence;

public:
	ManagingTechnologyTimeChangeStrategy(double t_i_c, double s_m_s_b_c, double t_m_i_c, double p_m_c, double t_i_i, double s_t_s_b_i, double t_m_i_i, double p_m_i) :
		team_imcompatibility_chance(t_i_c),
		small_team_spirit_boost_chance(s_t_s_b_i),
		team_member_ill_chance(t_m_i_c),
		perfect_managment_chance(p_m_c),
		team_imcompatibility_influence(t_i_i),
		small_team_spirit_boost_influence(s_t_s_b_i),
		team_member_ill_influence(t_m_i_i),
		perfect_managment_influence(p_m_i) {}

	virtual double getTimeChange(int command_size);
};


class Technology
{
private:
	string name;
	TechnologyTimeChangeStrategy* strategy;

public:
	Technology(const string& name, TechnologyTimeChangeStrategy* str) :
		name(name), strategy(str) {}

	double getTimeChange(int command_size) { return strategy->getTimeChange(command_size); }
};

class ProjectTimeAssesmentStrategy
{
public:
	virtual int assessTime(Project* project) = 0;
};

class MediumProjectTimeAssesmentStrategy: public ProjectTimeAssesmentStrategy
{
public:
	virtual int assessTime(Project* project) override;
};

class LargeProjectTimeAssesmentStrategy: public ProjectTimeAssesmentStrategy
{
public:
	virtual int assessTime(Project* project) override;
};


class Project
{
private:
	string name;
	set<Technology*> technologies;
	set<Technology*> unfulfiled_technologies;
	vector<Developer*> developers;
	int difficulty; // from 1 to 10, all inclusive

	ProjectTimeAssesmentStrategy* strategy;
public:
	Project(const string& name, int dif, ProjectTimeAssesmentStrategy* str) :name(name), difficulty(dif), strategy(str) {}

	void setTechnogies(set<Technology*>& techn) { technologies = techn; unfulfiled_technologies = techn; }
	void addTechnology(Technology& tech) { technologies.insert(&tech); unfulfiled_technologies.insert(&tech); }

	//void setDevelopers(vector<Developer*>& devs) { developers = devs; }
	void addDeveloper(Developer* dev);

	bool eligibleToWork(Developer* dev);
	bool finishedAssigning() { return unfulfiled_technologies.empty(); }

	int getDevelopmentTime() { return strategy->assessTime(this); }

	int getDifficulty() const { return difficulty; }
	const vector<Developer*>& getDevelopers() const { return developers; }
	const set<Technology*>& getTechnologies() const { return technologies; }
	const string& getName() const { return name; }

};
enum class ProjectState
{
	kAssigningDevelopers,kProcessing, kFinished 
};

struct ProjectWithState
{
public:
	Project* project;
	ProjectState state = ProjectState::kAssigningDevelopers;
	vector<int> developers_used;
	int time_left;
	ProjectWithState(Project* pr) :project(pr), time_left(0) {}

	ProjectWithState() :ProjectWithState(nullptr) {}
};

class ProjectManager
{
private:
	vector<Project*> projects;
	vector<Developer*> developers;
public:

	void setProjects(vector<Project*>& pr) { projects = pr; }
	void addProject(Project& pr) { projects.push_back(&pr); }

	void setDevelopers(vector<Developer*>& devs) { developers = devs; }
	void addDeveloper(Developer& dev) { developers.push_back(&dev); }

	void simulate();
};