#include <libvinput++/VInput.hpp>

#include <cctype>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <memory>

char g_word_buffer[128] = { 0 };
int  g_word_len = 0;

std::unique_ptr<VInput::EventListener> g_listener;

void commit_word(void) {
	if (g_word_len)
		std::printf("Word introduced: %.*s\n", g_word_len, g_word_buffer);
	g_word_len = 0;
}

void keyboard_callback(VInput::KeyboardEvent evt) {
	if (!evt.pressed)
		return;

	if (std::isdigit(evt.keychar)) {
		g_word_len = 0;
		return;
	}

	if (evt.keychar == '\b') {
		g_word_len--;
		if (g_word_len < 0)
			g_word_len = 0;
		return;
	}

	if (evt.keychar == '\n' || evt.keychar == '\r')
		commit_word();

	if (!std::isprint(evt.keychar))
		return;

	if (!std::isalpha(evt.keychar) || std::isspace(evt.keychar)
	    || evt.modifiers.pressed_except_shift()) { // New word
		commit_word();
	} else {
		if (g_word_len > (int)(sizeof(g_word_buffer) / sizeof(char)))
			g_word_len = 0;
		g_word_buffer[g_word_len++] = evt.keychar;
	}
}

void mouse_button_callback(VInput::MouseButtonEvent evt) {
	(void)evt;
	commit_word();
}

void mouse_move_callback(VInput::MouseMoveEvent evt) {
	(void)evt;
	commit_word();
}

void signal_handler(int sig) {
	printf("Signal %d received, exiting...\n", sig);
	g_listener->destroy();
	std::exit(0);
}

int main(void) {
	std::signal(SIGINT, signal_handler);
	g_listener = std::make_unique<VInput::EventListener>(true, true, true);
	g_listener->start(&keyboard_callback, &mouse_button_callback, &mouse_move_callback);
}
