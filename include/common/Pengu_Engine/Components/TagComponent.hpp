#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP 1
#include <string>

struct TagComponent {

	std::string tag;
	TagComponent() = default;
	TagComponent(const std::string& t) : tag(t) {};
};

#endif // !TAGCOMPONENT_HPP
