#include <gtkmm.h>
#include "main_window.h"
#include "load_chunks.h"

int on_cmd(const Glib::RefPtr<Gio::ApplicationCommandLine> &, Glib::RefPtr<Gtk::Application> &app)
{
	app->activate();
	return 0;
}

int main (int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "tordex.pstme", Gio::APPLICATION_HANDLES_COMMAND_LINE);

	app->signal_command_line().connect(
		sigc::bind(sigc::ptr_fun(on_cmd), app), false);

	std::string settings_file;
	if(argc > 1)
	{
		settings_file = argv[1];
	} else
	{
		Gtk::MessageDialog dialog("ERROR: Settings file expected as argument", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
		dialog.run();
		return -1;
	}

	auto _chunks = load_bookmarks_from_file(settings_file);
	if(_chunks)
	{
		main_window win(_chunks);
		auto ret = app->run(win);
		auto sel_b = win.get_selected();
		if(sel_b)
		{
			bool first = true;
			for(const auto& b : sel_b->get_lines())
			{
				if(!first) printf("\n");
				printf("%s", b.c_str());
				first = false;
			}
			if(win.get_include_return())
			{
				printf("\n");
			}
		}
		return ret;
	}
	Gtk::MessageDialog dialog("ERROR: Loading settings from " + settings_file, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
	dialog.run();

	return -1;
}
