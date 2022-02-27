import 'card.dart';
import 'dart:math';

const int DECKSIZE = 52;
const int SUITSIZE = 13;
const int NUMSUITS = 4;

class Deck {
  List<Card> _available = Deck.newDeckOrder();
  List<Card> _unavailable = <Card>[];
  Card? _cut;

  Random _rand = Random();

  void reset() {
    _available = Deck.newDeckOrder();
    _unavailable.clear();
    _cut = null;
  }

  void shuffle() {
    reset();
    for (int i = 0; i < DECKSIZE; i++) {
      _swap(i, _rand.nextInt(DECKSIZE));
    }
  }

  Card cut() {
    int i = _rand.nextInt(_available.length);
    Card cut = _available[i];
    _cut = cut;
    _makeUnavailable(i);
    return cut;
  }

  void _swap(int i, int j) {
    Card tmp = _available[i];
    _available[i] = _available[j];
    _available[j] = tmp;
  }

  void _makeUnavailable(int i) {
    Card tmp = _available[i];
    _available.removeAt(i);
    _unavailable.add(tmp);
  }

  static List<Card> newDeckOrder() {
    List<Card> list = <Card>[];
    for (int i = 0; i < NUMSUITS; i++) {
      for (int j = 0; j < SUITSIZE; j++) {
        Suit suit;
        switch (i) {
          case 0:
            suit = Suit.clubs;
            break;
          case 1:
            suit = Suit.diamonds;
            break;
          case 2:
            suit = Suit.hearts;
            break;
          case 3:
            suit = Suit.spades;
            break;
        }
        int indx = j;
        if (i == 2 || i == 3) {
          indx = SUITSIZE - j - 1;
        } // reverse if in second half
        list.add(Card(Value.values[i], Suit.values[indx]));
      }
    }

    return list;
  }
}
