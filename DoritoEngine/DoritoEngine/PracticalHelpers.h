#pragma once
#include "DoritoPCH.h"
#include "json.hpp"

using json = nlohmann::json;

namespace DoritoHelpers
{
	inline json ReadJson(const std::string& jsonFile)
	{
		json j;
		auto fullPath = "../Resources/" + jsonFile;

		std::ifstream file(fullPath);

		if (file.is_open())
		{
			file >> j;
			file.close();

			return j;
		}
		else
		{
			throw std::runtime_error(std::string("Failed to open Json: " + fullPath));
		}
	}

}