#include <libvinput++/EventListener.hpp>

#include <stdexcept>
#include <thread>

#include <libvinput.h>

namespace VInput {

EventListener::EventListener(
    bool listen_keyboard, bool listen_mouse_button, bool listen_mouse_move) {
	m_this_id = std::this_thread::get_id();
	m_event_listener = new ::EventListener;

	auto err = EventListener2_create(reinterpret_cast<::EventListener *>(m_event_listener),
	    listen_keyboard, listen_mouse_button, listen_mouse_move);
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

EventListener::~EventListener(void) {
	this->destroy();
	delete reinterpret_cast<::EventListener *>(m_event_listener);
}

void EventListener::start(void (*keyboard_callback)(KeyboardEvent),
    void (*mouse_button_callback)(MouseButtonEvent), void (*mouse_move_callback)(MouseMoveEvent)) {
	if (m_this_id != std::this_thread::get_id())
		throw std::runtime_error("Event listener not created on the same thread "
		                         "the start function is on.");

	auto err = EventListener2_start((::EventListener *)m_event_listener,
	    reinterpret_cast<void (*)(::KeyboardEvent)>(keyboard_callback),
	    reinterpret_cast<void (*)(::MouseButtonEvent)>(mouse_button_callback),
	    reinterpret_cast<void (*)(::MouseMoveEvent)>(mouse_move_callback));

	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

void EventListener::destroy(void) {
	if (!m_event_listener)
		return;

	auto err = EventListener_free(reinterpret_cast<::EventListener *>(m_event_listener));
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

} // namespace VInput
