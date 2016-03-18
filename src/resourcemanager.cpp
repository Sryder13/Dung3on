#include "resourcemanager.hpp"

void resourcemanager::deleteResource(std::string filename)
{
	std::cout << "deleting resource: " << filename << std::endl;
	delete resourceList.find(filename)->second; // delete the object
	resourceList.erase(filename); // remove it from the list
}

void resourcemanager::clearResources()
{
	std::cout << "deleting resources" << std::endl;
	for (std::map<std::string, resource *>::iterator resourceList_iter = resourceList.begin(); resourceList_iter != resourceList.end(); ++resourceList_iter)
	{
		// loop through the list
		std::cout << "deleting: " << resourceList_iter->first << std::endl;
		delete resourceList_iter->second; // delete the object
	}
	resourceList.clear(); // clear the list
}
