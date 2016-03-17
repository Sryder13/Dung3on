#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include<iostream>
#include<map>

class resource
{
	public:
		resource() {}
		virtual ~resource() {}
		virtual void load(const std::string filename) {}
};

class resourcemanager
{
	public:
		static resourcemanager *getResourceManager() {static resourcemanager rManager; return &rManager;}

		template <class T>
		T *getResource(const std::string &filename)
		{
			if (resourceList.find(filename) != resourceList.end())
			{
				return dynamic_cast<T *>(resourceList[filename]);
			}

			T *newT = new T();

			newT->load(filename);
			resourceList[filename] = newT;
			return newT;
		}
		void clearResources()
		{
			std::cout << "deleting resources" << std::endl;
			for (std::map<std::string, resource *>::iterator resourceList_iter = resourceList.begin(); resourceList_iter != resourceList.end(); ++resourceList_iter)
			{
				std::cout << "deleting " << resourceList_iter->first << std::endl;
				delete resourceList_iter->second;
			}
			resourceList.clear();
		}
	protected:
	private:
		resourcemanager() {}
		resourcemanager(resourcemanager const&);
		void operator=(resourcemanager const&);

		std::map <std::string, resource *> resourceList;
};

#endif // RESOURCEMANAGER_H
