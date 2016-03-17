#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include<iostream>
#include<map>

class resource // resource type, inherited by the resources
{
	public:
		resource() {}
		virtual ~resource() {}
		virtual void load(const std::string filename) {}
};

class resourcemanager
{
	public:
		// This makes this class a "singleton". a single static declaration of the resourcemanager is made that
		// is gotten with resourcemanager::getResourceManager
		static resourcemanager *getResourceManager() {static resourcemanager rManager; return &rManager;}

		// templated so we distinguish between different resources when loading
		template <class T>
		T *getResource(const std::string &filename)
		{
			if (resourceList.find(filename) != resourceList.end()) // check the resource does not already exist
			{
				return dynamic_cast<T *>(resourceList[filename]); // it does exist so just return the right thing
			}

			T *newT = new T(); // does not exist so create new one

			newT->load(filename); // load
			resourceList[filename] = newT; // add to resourceList
			return newT; // return the new one
		}
		void deleteResource(std::string filename)
		{
            std::cout << "deleting resource: " << filename << std::endl;
            delete resourceList.find(filename)->second; // delete the object
            resourceList.erase(filename); // remove it from the list
		}
		void clearResources()
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
	protected:
	private:
		resourcemanager() {}
		resourcemanager(resourcemanager const&); // make sure these cannot be accessed by "deleting " them
		void operator=(resourcemanager const&); // make sure these cannot be accessed by "deleting " them

		std::map <std::string, resource *> resourceList; // the resource list is a map with the key being a string of the filename
};

#endif // RESOURCEMANAGER_H
