import 'dart:math';
import './hand_ai.dart';
import '../../deck/card.dart';

class RandomHandAI implements HandAI {
  final Random _rand = Random();

  List<Card> select(List<Card> dealt, bool isMyCrib) {
    List<Card> keep = [];

    while (keep.length < 4) {
      int i = _rand.nextInt(dealt.length);
      if (!keep.contains(dealt[i])) {
        keep.add(dealt[i]);
      }
    }

    return keep;
  }
}
