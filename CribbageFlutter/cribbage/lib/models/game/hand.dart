import '../deck/card.dart';

class Hand {
  List<Card> _cards;
  Card _cut;
  bool _isCrib;

  Hand(this._cards, this._cut, this._isCrib);

  int score() {
    int score = 0;
    score += pairScore();
    score += fifteenScore();
    score += runScore();
    score += flushScore();
    score += nobsScore();
    return score;
  }

  int pairScore() {
    int numPairs = 0;
    for (int i = 0; i < 4; i++) // iterate over all 5 choose 2 pairs of cards
    {
      for (int j = i + 1; j < 5; j++) {
        Card card1 = _cards[i];
        Card card2;
        if (i == 4) {
          card2 = _cut;
        } else {
          card2 = _cards[j];
        }

        if (card1.getValue() == card2.getValue()) {
          numPairs++;
        }
      }
    }

    return 2 * numPairs;
  }

  int fifteenScore() {
    List<Card> subset = [];
    for (int c = 0; c < 4; c++) // test set of five cards add to fifteen
    {
      subset.add(_cards[c]);
    }
    subset.add(_cut);
    if (Hand.sum(subset) == 15) {
      return 2;
    }

    int numFifteens = 0;

    for (int i = 0; i < 5; i++) // check if sets of four cards add to fifteen
    {
      subset.clear();
      for (int c = 0; c < 4; c++) {
        if (c != i) {
          subset.add(_cards[c]);
        }
      }
      if (i != 4) {
        subset.add(_cut);
      }
      if (Hand.sum(subset) == 15) {
        numFifteens++;
      }
    }

    for (int i = 0; i < 4; i++) // check if sets of three cards add to fifteen
    {
      for (int j = i + 1; j < 5; j++) {
        subset.clear();
        for (int c = 0; c < 4; c++) {
          if (c != i && c != j) {
            subset.add(_cards[c]);
          }
        }
        if (j != 4) {
          subset.add(_cut);
        }
        if (Hand.sum(subset) == 15) {
          numFifteens++;
        }
      }
    }

    for (int i = 0; i < 4; i++) // check if sets of two cards add to fifteen
    {
      for (int j = i + 1; j < 5; j++) {
        subset.clear();
        for (int c = 0; c < 4; c++) {
          if (c == i || c == j) {
            subset.add(_cards[c]);
          }
        }
        if (j == 4) {
          subset.add(_cut);
        }
        if (Hand.sum(subset) == 15) {
          numFifteens++;
        }
      }
    }

    return 2 * numFifteens;
  }

  int runScore() {
    List<Card> subset = [];
    for (int c = 0; c < 4; c++) // check if all five form a run
    {
      subset.add(_cards[c]);
    }
    subset.add(_cut);
    if (Hand.isRun(subset)) {
      return 5;
    }

    int numRuns = 0;

    for (int i = 0; i < 5; i++) // check if sets of four cards are runs
    {
      subset.clear();
      for (int c = 0; c < 4; c++) {
        if (c != i) {
          subset.add(_cards[c]);
        }
      }
      if (i != 4) {
        subset.add(_cut);
      }
      if (Hand.isRun(subset)) {
        numRuns++;
      }
    }
    if (numRuns != 0) {
      return 4 * numRuns;
    }

    for (int i = 0; i < 4; i++) // check if sets of three cards are runs
    {
      for (int j = i + 1; j < 5; j++) {
        subset.clear();
        for (int c = 0; c < 4; c++) {
          if (c != i && c != j) {
            subset.add(_cards[c]);
          }
        }
        if (j != 4) {
          subset.add(_cut);
        }
        if (Hand.isRun(subset)) {
          numRuns++;
        }
      }
    }
    if (numRuns != 0) {
      return 3 * numRuns;
    }

    return 0;
  }

  int flushScore() {
    Map<Suit, int> counts = {};
    for (int c = 0; c < 4; c++) {
      Suit suit = _cards[c].getSuit();
      int count = counts[suit] ?? 0;
      counts[suit] = count + 1;
    }

    for (Suit suit in counts.keys) {
      int count = counts[suit] ?? 0;
      if (count == 4) {
        if (suit == _cut.getSuit()) {
          return 5;
        } // if the cut matches, no questions asked

        if (_isCrib) {
          return 0;
        } // cut doesn't match, so no flush in the crib
        else {
          return 4;
        }
      }
    }
    return 0;
  }

  int nobsScore() {
    for (int c = 0; c < 4; c++) {
      if (_cards[c].getValue() == Value.jack) {
        if (_cards[c].getSuit() == _cut.getSuit()) {
          return 1;
        }
      }
    }

    return 0;
  }

  static int sum(List<Card> cards) {
    int sum = 0;
    for (Card card in cards) {
      sum += card.pips();
    }
    return sum;
  }

  static bool isRun(List<Card> cards) {
    cards.sort((a, b) => a.getValue().index.compareTo(b.getValue().index));

    int expectedIndex = cards[0].getValue().index;
    for (int c = 0; c < cards.length; c++) // iterate over sorted cards
    {
      if (cards[c].getValue().index !=
          expectedIndex++) // check if index is different than it should be
      {
        return false;
      }
    }

    return true;
  }
}
