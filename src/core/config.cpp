#include "config.h"
#include "json.h"

#include <fstream>

using json = nlohmann::json;

void configuration::Save() noexcept
{
	std::ifstream f("example.json");
	json data = json::parse(f);
	json ex3 = {
		{"happy", true},
		{"pi", 3.141},
	};
}