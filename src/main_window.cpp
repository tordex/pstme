#include "main_window.h"


main_window::main_window(std::shared_ptr<chunks> _bookmarks) : m_chunks(_bookmarks), m_list(1), m_b_include_return(true)
{
	init();
}

main_window::~main_window()
{

}

bool main_window::on_key_press_event(GdkEventKey *key_event)
{
	if (key_event->keyval == GDK_KEY_Escape)
	{
		on_cancel_clicked();
		return true;
	}
	return Gtk::Window::on_key_press_event(key_event);
}

void main_window::init()
{
	set_titlebar(m_header);
	m_header.show();
	m_header.set_title(m_chunks->get_name());

	m_header.pack_start(m_btn_cancel);
	m_btn_cancel.set_label("Cancel");
	m_btn_cancel.show();
	m_btn_cancel.signal_clicked().connect( sigc::mem_fun(*this, &main_window::on_cancel_clicked) );

	m_header.pack_end(m_btn_ok);
	m_btn_ok.set_label("OK");
	m_btn_ok.show();
	m_btn_ok.signal_clicked().connect( sigc::mem_fun(*this, &main_window::on_ok_clicked) );
	m_btn_ok.set_can_default(true);
	set_default(m_btn_ok);

	add(m_vbox);
	m_vbox.set_margin_left(16);
	m_vbox.set_margin_right(16);
	m_vbox.set_margin_top(16);
	m_vbox.set_margin_bottom(16);
	m_vbox.set_spacing(8);
	m_vbox.show();

	m_vbox.pack_start(m_search_box, Gtk::PACK_SHRINK);
	m_search_box.set_icon_from_icon_name("search-symbolic");
	m_search_box.set_activates_default(true);
	m_search_box.signal_changed().connect( sigc::mem_fun(*this, &main_window::on_text_changed) );
	m_search_box.show();

	m_vbox.pack_start(m_scrolled_wnd, Gtk::PACK_EXPAND_WIDGET);
	m_scrolled_wnd.show();
	m_scrolled_wnd.add(m_list);
	m_list.set_headers_visible(false);
	m_list.signal_row_activated().connect( sigc::mem_fun(*this, &main_window::on_list_row_activated) );
	m_list.show();

	m_vbox.pack_start(m_include_return, Gtk::PACK_SHRINK);
	m_include_return.set_label("Include return character with bookmark");
	m_include_return.set_active(true);
	m_include_return.show();

	set_default_size(0, 300);

	search_chunks("");
}

void main_window::on_cancel_clicked()
{
	this->close();
}

void main_window::on_ok_clicked()
{
	auto selection = m_list.get_selected();
	if(selection.empty()) return;
	if(selection.front() >= 0 && selection.front() < (int) m_current_chunks.size())
	{
		m_b_include_return = m_include_return.get_active();
		m_selected_chunk = m_current_chunks[selection.front()];
		this->close();
	}
}

void main_window::on_text_changed()
{
	std::string text = m_search_box.get_text();
	search_chunks(text);
}

void main_window::search_chunks(const std::string &text)
{
	m_current_chunks = m_chunks->find_bookmarks(text);
	m_list.clear_items();
	for(const auto& b : m_current_chunks)
	{
		m_list.append(b->get_name());
	}

	// Select first list item
	Gtk::TreePath path("0");
	m_list.set_cursor(path);
}

void main_window::on_list_row_activated(const Gtk::TreePath &, Gtk::TreeViewColumn *)
{
	on_ok_clicked();
}

