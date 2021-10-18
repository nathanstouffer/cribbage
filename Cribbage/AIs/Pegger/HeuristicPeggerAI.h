#ifndef __HEURISTIC_PEGGER_AI_H__
#define __HEURISTIC_PEGGER_AI_H__

#include "PeggerAI.h"

class HeuristicPeggerAI : public PeggerAI
{
public:

    Card select(const std::vector<Card>& played, const std::vector<Card>& avail);

};

#endif
