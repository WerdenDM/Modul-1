#include "base_classes.h"
int S = 15;
int Base::N = 1;
int Alpha::N_alpha = 1;
int Beta::N_beta = 1;
int Gamma::N_gamma = 1;

std::list<Base*> Base::instances = std::list<Base*>();

int predictSValue(const std::list<Base*>& base_classes, int start_value)
{
	
	for (auto iter = base_classes.rbegin(); iter != base_classes.rend(); ++iter)
	{
		start_value = (*iter)->get_new_value(start_value);
	}
	return start_value;
}
