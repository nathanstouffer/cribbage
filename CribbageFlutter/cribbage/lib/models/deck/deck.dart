// ignore_for_file: constant_identifier_names

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

  List<List<Card>> deal() {
    List<Card> first = <Card>[];
    List<Card> second = <Card>[];
    for (int i = 0; i < 6; i++) {
      // deal six cards, one to each player
      first.add(_available[0]);
      _makeUnavailable(0);

      second.add(_available[0]);
      _makeUnavailable(0);
    }
    return [first, second];
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
    for (int s = 0; s < NUMSUITS; s++) {
      for (int i = 0; i < SUITSIZE; i++) {
        int v = i;
        if (s == 2 || s == 3) {
          v = SUITSIZE - i - 1;
        } // reverse if in second half
        list.add(Card(Value.values[v], Suit.values[s]));
      }
    }

    return list;
  }
}
