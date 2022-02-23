#pragma once

#include <functional>
#include <string>

namespace minmd
{

class file_watcher
{
public:
	file_watcher(const std::string& t_path, std::function<void()> t_callback);
	~file_watcher();
	
private:
	bool file_is_modified(int t_file_descriptor);
	int m_file_descriptor;
	int m_watch_descriptor;
};

} //namespace minmd
