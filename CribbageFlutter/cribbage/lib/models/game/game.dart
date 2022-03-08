import 'package:cribbage/models/ai/cribbage_ai.dart';
import 'package:cribbage/models/ai/hand/hand_ai.dart';
import 'package:cribbage/models/ai/pegger/pegger_ai.dart';
import 'package:cribbage/models/deck/card.dart';
import 'package:cribbage/models/deck/deck.dart';

class Game {
  // TODO might be good to use a state machine in this class?

  Deck _deck = Deck();

  int _compScore = 0;
  int _humanScore = 0;

  bool _humanDealer = true; // TODO figure out how to organize dealer

  List<Card> _compCards = [];
  List<Card> _humanCards = [];

  List<Card> _humanToThrow = [];

  void deal() {
    _deck.shuffle();
    List<List<Card>> dealt = _deck.deal(); // two lists of 6 cards each
    if (_humanDealer) {
      _compCards = dealt[0];
      _humanCards = dealt[1];
    } else {
      _compCards = dealt[1];
      _humanCards = dealt[0];
    }
  }

  void markToThrow(Card card) {
    if (_humanCards.contains(card)) {
      _humanCards.remove(card);
      _humanToThrow.add(card);
    }
  }

  void markToKeep(Card card) {
    if (_humanToThrow.contains(card)) {
      _humanToThrow.remove(card);
      _humanCards.add(card);
    }
  }

  bool humanDealer() {
    return _humanDealer;
  }

  int humanScore() {
    return _humanScore;
  }

  int compScore() {
    return _compScore;
  }

  List<Card> computerCards() {
    return _compCards;
  }

  List<Card> humanCards() {
    return _humanCards;
  }

  List<Card> humanToThrow() {
    return _humanToThrow;
  }
}
