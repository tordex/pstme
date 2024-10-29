#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "chunks.h"

class main_window : public Gtk::Window
{
	std::shared_ptr<chunks> m_chunks;
	std::vector<std::shared_ptr<chunk>> m_current_chunks;
	std::shared_ptr<chunk> m_selected_chunk;
	bool m_b_include_return;
public:
	main_window(std::shared_ptr<chunks> _bookmarks);
	~main_window();

	std::shared_ptr<chunk> get_selected() const { return m_selected_chunk; }
	bool get_include_return() const { return m_b_include_return; }
	bool on_key_press_event(GdkEventKey* key_event) override;

private:
	void init();
	void on_cancel_clicked();
	void on_ok_clicked();
	void on_text_changed();
	void search_chunks(const std::string& text);
	void on_list_row_activated(const Gtk::TreePath&, Gtk::TreeViewColumn*);

private:
	Gtk::Button			m_btn_cancel;
	Gtk::Button			m_btn_ok;
	Gtk::Entry			m_search_box;
	Gtk::ListViewText	m_list;
	Gtk::CheckButton	m_include_return;
	Gtk::HeaderBar		m_header;
	Gtk::VBox			m_vbox;
	Gtk::ScrolledWindow m_scrolled_wnd;
};

#endif // MAIN_WINDOW_H
