#ifndef _VINPUT_EVENTS
#define _VINPUT_EVENTS

#include <cstdint>

namespace VInput {

struct KeyboardEvent {
	struct Modifiers {
		bool left_control : 1;
		bool right_control : 1;
		bool left_shift : 1;
		bool right_shift : 1;
		bool left_alt : 1; // On Mac, this is the Option key
		bool right_alt : 1; // On Mac, this is the Option key
		bool left_meta : 1; // On Mac, this is the Command key
		bool right_meta : 1; // On Mac, this is the Command key
		bool left_super : 1; // On Mac, this is the Fn key
		bool right_super : 1; // On Mac, this is the Fn key
		bool left_hyper : 1;
		bool right_hyper : 1;

		bool pressed_except_shift(void);
	};

	bool          pressed;
	char          keychar; // The ASCII character of the key, 0 if unavailable
	std::uint16_t keycode;
	std::uint16_t keysym; // On X11, the KeySym, on Windows, the Virtual Key code

	Modifiers modifiers;

	std::size_t timestamp; // Timestamp of event, in milliseconds
};

struct MouseButtonEvent {
	enum class Button {
		Left = 0,
		Right,
		Middle,
	};

	enum class Kind {
		Press,
		Release,
	};

	Button button;
	Kind   kind;
};

struct MouseMoveEvent {
	unsigned int x, y;
	float        velocity_x, velocity_y, velocity;
};

} // namespace VInput

#endif // _VINPUT_EVENTS
