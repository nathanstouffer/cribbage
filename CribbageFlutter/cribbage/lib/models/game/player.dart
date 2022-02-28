import '../ai/hand/hand_ai.dart';
import '../ai/pegger/pegger_ai.dart';

class Player {
  final HandAIEnum _handAIType;
  final PeggerAIEnum _peggerAIType;

  Player(this._handAIType, this._peggerAIType) {}
}
