#include "file_watcher.h"

#include <glibmm/main.h>
#include <sys/inotify.h>
#include <unistd.h>


minmd::file_watcher::file_watcher(const std::string& t_path, std::function<void()> t_callback)
{
	//inotify
	this->m_file_descriptor = inotify_init1(IN_NONBLOCK);
	this->m_watch_descriptor = inotify_add_watch(this->m_file_descriptor, t_path.c_str(), IN_MODIFY);

	//timeout
	Glib::signal_timeout().connect([t_callback, this](){
		if (file_is_modified(this->m_file_descriptor))
		{
			t_callback();
		}
		return true;
	}, 1000);
}




minmd::file_watcher::~file_watcher()
{
	inotify_rm_watch(this->m_file_descriptor, this->m_watch_descriptor);
}




constexpr static const std::size_t max_path_length = 512;
constexpr static const std::size_t event_size = sizeof(inotify_event);
constexpr static const std::size_t buffer_length = event_size + max_path_length;

bool minmd::file_watcher::file_is_modified(int t_file_descriptor)
{
	char buffer[buffer_length];
	auto num_bytes = read(t_file_descriptor, buffer, buffer_length);
	
	return num_bytes != -1;
}	
