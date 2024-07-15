#ifndef _VINPUT_EVENT_EMULATOR
#define _VINPUT_EVENT_EMULATOR

#include <cstdint>
#include <string_view>
#include <vector>

namespace VInput {

class EventEmulator {
public:
	EventEmulator(void);
	~EventEmulator(void);

	EventEmulator(EventEmulator const &) = delete;
	EventEmulator &operator=(EventEmulator const &) = delete;

	void destroy(void);

	std::vector<int> keyboard_state_get(void);
	void             keyboard_state_clear(void);
	void             keyboard_state_set(std::vector<int> states);

	void keyboard_press(std::uint16_t keysym);
	void keyboard_release(std::uint16_t keysym);

	void keyboard_typec(char ch);
	void keyboard_types(std::string_view text);
	void keyboard_types(char *text);
	void keyboard_types(char *text, std::size_t len);

private:
	void *m_event_emulator; // INTERNAL
};

} // namespace VInput

#endif // _VINPUT_EVENT_EMULATOR
