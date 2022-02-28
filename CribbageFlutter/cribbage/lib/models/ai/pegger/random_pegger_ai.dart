import 'dart:math';
import './pegger_ai.dart';
import '../../deck/card.dart';

class RandomPeggerAI implements PeggerAI {
  final Random _rand = Random();

  Card? select(List<Card> played, List<Card> avail) {
    List<Card> validCards = PeggerAI.valid(played, avail);
    if (validCards.length == 0) {
      return null;
    }

    int i = _rand.nextInt(validCards.length);
    return validCards[i];
  }
}
