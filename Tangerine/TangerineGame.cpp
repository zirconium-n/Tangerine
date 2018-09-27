#include <sgk/general/Game.h>
#include <sgk/tangerine/Map.h>
#include <fstream>

int main() {
	std::ifstream clover{ "field_clover.fld" };
	sgk::tangerine::Map clover_map{ 11, 11, clover };
	nlohmann::json clover_json{ {"map", clover_map } };
	std::cout << clover_json.dump() << std::endl;
	system("pause");
	return 0;
}