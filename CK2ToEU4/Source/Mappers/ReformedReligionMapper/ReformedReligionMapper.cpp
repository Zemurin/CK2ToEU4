#include "ReformedReligionMapper.h"
#include "CommonRegexes.h"
#include "Log.h"
#include <iomanip>

void mappers::ReformedReligionMapper::initReformedReligionMapper(const std::filesystem::path& path)
{
	Log(LogLevel::Info) << "-> Parsing Reformed Religion mappings";
	registerKeys();
	std::filesystem::path dirPath = "configurables";
	if (!path.empty())
	{
		Log(LogLevel::Info) << "Reformed Religions Mapper override: " << path.string();
		dirPath = dirPath / path;
	}
	parseFile(dirPath / "reformed_religions_mappings.txt");
	parseFile(dirPath / "pagan_religions.txt");
	clearRegisteredKeywords();
	Log(LogLevel::Info) << "<> " << religionEntries.size() << " religions mapped.";
}

void mappers::ReformedReligionMapper::initReformedReligionMapper(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void mappers::ReformedReligionMapper::registerKeys()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& doctrine, std::istream& theStream) {
		ReformedReligionMapping newMapping(theStream);
		newMapping.setName(doctrine);
		religionEntries.insert(std::pair(doctrine, newMapping));
	});
}
