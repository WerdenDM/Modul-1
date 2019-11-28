// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "company_classes.h"
int main()
{
	ProgrammingTechnologyTimeChangeStrategy programming_strategy = ProgrammingTechnologyTimeChangeStrategy(0.2, 0.1, 0.15, 0.1, 0.05, 0.07);
	ManagingTechnologyTimeChangeStrategy managing_strategy = ManagingTechnologyTimeChangeStrategy(0.1, 0.4, 0.5, 0.2, 0.2, 0.2, 0.1, 0.3);
	Technology python = Technology("python", &programming_strategy);
	Technology c_plus_plus = Technology("c++", &programming_strategy);
	Technology web = Technology("web", &programming_strategy);
	Technology js = Technology("js", &programming_strategy);

	Technology managing = Technology("managing", &managing_strategy);
	Technology pm = Technology("PM", &managing_strategy);

	Developer developer1 = Developer("WEB BB", 0.8);
	developer1.addTechnology(python);
	developer1.addTechnology(js);

	developer1.addTechnology(web);

	Developer developer2("C++ BB", 0.8);
	developer2.addTechnology(c_plus_plus);
	//developer1.addTechnology(js);

	//developer1.addTechnology(web);
	Developer manager1("MM BB", 0.6);
	manager1.addTechnology(managing);
	manager1.addTechnology(pm);

	LargeProjectTimeAssesmentStrategy large_strategy = LargeProjectTimeAssesmentStrategy();
	MediumProjectTimeAssesmentStrategy medium_strategy = MediumProjectTimeAssesmentStrategy();

	Project web_project = Project("Web project", 6, &large_strategy);

	web_project.addTechnology(python);
	web_project.addTechnology(web);
	web_project.addTechnology(js);
	web_project.addTechnology(managing);
	web_project.addTechnology(pm);

	Project native_project = Project("Native project", 6, &medium_strategy);

	native_project.addTechnology(c_plus_plus);
	native_project.addTechnology(managing);
	native_project.addTechnology(pm);

	ProjectManager project_manager;
	project_manager.addDeveloper(developer1);
	project_manager.addDeveloper(developer2);
	project_manager.addDeveloper(manager1);

	project_manager.addProject(web_project);
	project_manager.addProject(native_project);

	project_manager.simulate();





}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
