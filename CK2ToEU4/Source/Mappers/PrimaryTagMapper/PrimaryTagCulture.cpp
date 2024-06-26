#include "PrimaryTagCulture.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"

mappers::PrimaryTagCulture::PrimaryTagCulture(std::istream& theStream)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void mappers::PrimaryTagCulture::registerKeys()
{
	registerKeyword("primary", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString tagStr(theStream);
		tag = tagStr.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}

std::optional<std::string> mappers::PrimaryTagCulture::getTag() const
{
	if (!tag.empty())
		return tag;
	return std::nullopt;
}
