// ignore_for_file: constant_identifier_names

import '../../deck/card.dart';
import '../../game/hand.dart';

enum PeggerAIEnum { Random, Heuristic }

abstract class PeggerAI {
  Card? select(List<Card> played, List<Card> avail);

  static List<Card> valid(List<Card> played, List<Card> avail) {
    List<Card> validCards = [];
    int sum = Hand.sum(played);
    for (int a = 0; a < avail.length; a++) {
      if (sum + avail[a].pips() <= 31) {
        validCards.add(avail[a]);
      }
    }
    return validCards;
  }

  static int points(List<Card> played, Card toPlay) {
    int size = played.length;
    int points = 0;

    if (Hand.sum(played) + toPlay.pips() == 15) // check if we are at fifteen
    {
      points += 2;
    }

    if (Hand.sum(played) + toPlay.pips() == 31) // check if we are 31
    {
      points += 2;
    }

    // check for pairs and such
    Value value = toPlay.getValue();
    if (size >= 3) {
      if (played[size - 1].getValue() == value &&
          played[size - 2].getValue() == value &&
          played[size - 3].getValue() == value) {
        points += 12;
      }
    } else if (size >= 2) {
      if (played[size - 1].getValue() == value &&
          played[size - 2].getValue() == value) {
        points += 6;
      }
    } else if (size >= 1) {
      if (played[size - 1].getValue() == value) {
        points += 2;
      }
    }

    // check for runs
    bool foundRun = false;
    for (int i = 0; i + 2 < size + 1 && !foundRun; i++) {
      List<Card> subset = [];
      for (int p = i; p < size; p++) {
        subset.add(played[p]);
      }
      subset.add(toPlay);
      if (Hand.isRun(subset)) {
        points += subset.length;
        foundRun = true;
      }
    }

    return points;
  }

  static bool fiveOr21(List<Card> played, Card toPlay) {
    int sum = Hand.sum(played) + toPlay.pips();
    return (sum == 5 || sum == 21);
  }
}
