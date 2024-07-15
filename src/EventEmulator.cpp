#include <libvinput++/EventEmulator.hpp>

#include <cstring>
#include <stdexcept>

#include <libvinput.h>

namespace VInput {

EventEmulator::EventEmulator(void) {
	m_event_emulator = new ::EventEmulator;
	auto err = EventEmulator_create(reinterpret_cast<::EventEmulator *>(m_event_emulator));
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

EventEmulator::~EventEmulator(void) {
	this->destroy();
	delete reinterpret_cast<::EventEmulator *>(m_event_emulator);
}

void EventEmulator::destroy(void) {
	if (!m_event_emulator)
		return;

	auto err = EventEmulator_free(reinterpret_cast<::EventEmulator *>(m_event_emulator));
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

std::vector<int> EventEmulator::keyboard_state_get(void) {
	int *state;
	int  nstate;
	auto err = EventEmulator_keyboard_state_get(
	    reinterpret_cast<::EventEmulator *>(m_event_emulator), &state, &nstate);
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));

	std::vector<int> state_vec(state, state + nstate);

	free(state);

	return state_vec;
}

void EventEmulator::keyboard_state_clear(void) {
	auto err
	    = EventEmulator_keyboard_state_clear(reinterpret_cast<::EventEmulator *>(m_event_emulator));
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

void EventEmulator::keyboard_state_set(std::vector<int> states) {
	auto err = EventEmulator_keyboard_state_set(
	    reinterpret_cast<::EventEmulator *>(m_event_emulator), states.data(), states.size());
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

void EventEmulator::keyboard_press(std::uint16_t keysym) {
	auto err = EventEmulator_press(reinterpret_cast<::EventEmulator *>(m_event_emulator), keysym);
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

void EventEmulator::keyboard_release(std::uint16_t keysym) {
	auto err = EventEmulator_release(reinterpret_cast<::EventEmulator *>(m_event_emulator), keysym);
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

void EventEmulator::keyboard_typec(char ch) {
	auto err = EventEmulator_typec(reinterpret_cast<::EventEmulator *>(m_event_emulator), ch);
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

void EventEmulator::keyboard_types(std::string_view text) {
	auto err = EventEmulator_types(reinterpret_cast<::EventEmulator *>(m_event_emulator),
	    const_cast<char *>(text.data()), text.size());
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

void EventEmulator::keyboard_types(char *text) {
	auto err = EventEmulator_types(
	    reinterpret_cast<::EventEmulator *>(m_event_emulator), text, strlen(text));
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

void EventEmulator::keyboard_types(char *text, std::size_t len) {
	auto err
	    = EventEmulator_types(reinterpret_cast<::EventEmulator *>(m_event_emulator), text, len);
	if (err != VINPUT_OK)
		throw std::runtime_error(VInput_error_get_message(err));
}

} // namespace VInput
