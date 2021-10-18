#include "RandomHandAI.h"

#include <vector>
#include <algorithm>

#include "../../Utils/Card.h"
#include "../../Utils/Random.h"

std::vector<Card> RandomHandAI::select(const std::vector<Card>& dealt, bool isMyCrib)
{
    std::vector<Card> keep;

    while (keep.size() < 4)
    {
        int i = Random::Instance()->randInt() % 6;
        if (std::find(keep.begin(), keep.end(), dealt[i]) == keep.end())
        {
            keep.push_back(dealt[i]);
        }
    }

    return keep;
}
