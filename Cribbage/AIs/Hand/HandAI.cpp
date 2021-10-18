#include "HandAI.h"

std::string HandAI::enumToString(HandAIEnum handAIType)
{
    switch (handAIType)
    {
        case HandAIEnum::RandomH:               return "RandomH";                   break;
        case HandAIEnum::RetainedEVH:           return "RetainedEVH";               break;
        case HandAIEnum::GrossHalfCribEVH:      return "GrossHalfCribEVH";          break;
        case HandAIEnum::RelativeHalfCribEVH:   return "RelativeHalfCribEVH";       break;
        case HandAIEnum::GrossFullCribEVH:      return "GrossFullCribEVH";          break;
        case HandAIEnum::RelativeFullCribEVH:   return "RelativeFullCribEVH";       break;
        default:                                return "No Hand AI";
    }
}

HandAIEnum HandAI::stringToEnum(std::string str)
{
    if (str == "RandomH")                   { return HandAIEnum::RandomH; }
    if (str == "RetainedEVH")               { return HandAIEnum::RetainedEVH; }
    if (str == "GrossHalfCribEVH")          { return HandAIEnum::GrossHalfCribEVH; }
    if (str == "RelativeHalfCribEVH")       { return HandAIEnum::RelativeHalfCribEVH; }
    if (str == "GrossFullCribEVH")          { return HandAIEnum::GrossFullCribEVH; }
    if (str == "RelativeFullCribEVH")       { return HandAIEnum::RelativeFullCribEVH; }
    std::cerr << "should not be here in HandAI::stringToEnum()" << std::endl;
    return HandAIEnum::RandomH;
}
