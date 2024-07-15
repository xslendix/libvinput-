#include <libvinput++/Events.hpp>

namespace VInput {

bool KeyboardEvent::Modifiers::pressed_except_shift(void) {
	return this->left_control || this->right_control || this->left_alt || this->right_alt
	    || this->left_meta || this->right_meta || this->left_super || this->right_super
	    || this->left_hyper || this->right_hyper;
}

} // namespace VInput
