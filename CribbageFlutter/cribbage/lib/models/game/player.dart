import 'package:cribbage/models/deck/card.dart';

// TODO figure out if we will use this struct... not really sure how
// to organize everything just yet
class Player {
  int score = 0;

  List<Card> _pegged = [];
  List<Card> _notPegged = [];

  void markPegged(Card toMark) {
    for (Card card in _notPegged) {
      if (toMark == card) {
        _pegged.add(card);
        _notPegged.remove(card);
      }
    }
  }
}
