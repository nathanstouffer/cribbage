import 'package:cribbage/models/ai/cribbage_ai.dart';
import 'package:cribbage/models/ai/hand/hand_ai.dart';
import 'package:cribbage/models/ai/pegger/pegger_ai.dart';
import 'package:cribbage/models/deck/card.dart';
import 'package:cribbage/models/deck/deck.dart';

class Game {
  Deck _deck = new Deck();

  int _compScore = 0;
  int _humanScore = 0;

  bool _humanDealer = true; // TODO figure out how to organize dealer

  List<Card> _compCards = [];
  List<Card> _humanCards = [];

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
}
