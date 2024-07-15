#ifndef _VINPUT_EVENT_LISTENER
#define _VINPUT_EVENT_LISTENER

#include <thread>

#include <libvinput++/Events.hpp>

namespace VInput {

class EventListener {
public:
	EventListener(bool listen_keyboard = false, bool listen_mouse_button = false,
	    bool listen_mouse_move = false);
	~EventListener(void);

	EventListener(EventListener const &) = delete;
	EventListener &operator=(EventListener const &) = delete;

	void start(void (*keyboard_callback)(KeyboardEvent),
	    void (*mouse_button_callback)(MouseButtonEvent),
	    void (*mouse_move_callback)(MouseMoveEvent));
	void destroy();

private:
	std::thread::id m_this_id;
	void           *m_event_listener; // INTERNAL
};

} // namespace VInput

#endif // _VINPUT_EVENT_LISTENER
