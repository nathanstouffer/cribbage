import '../../deck/card.dart';

const double CUT_PROB = 1.0 / 46.0; // probability that a given card is cut
const double THROW_PROB = 2.0 /
    (45.0 * 44.0); // probability that the two cards are thrown into the crib
const int SIX_CHOOSE_TWO = 15; // value of 6 choose 2

enum HandAIEnum { Random, RetainedEV, GrossHalfCribEV, RelativeHalfCribEV }

abstract class HandAI {
  List<Card> select(List<Card> dealt, bool isMyCrib);
}
