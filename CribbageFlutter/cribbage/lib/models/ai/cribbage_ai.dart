import 'hand/random_hand_ai.dart';
import 'pegger/random_pegger_ai.dart';
import 'hand/hand_ai.dart';
import 'pegger/pegger_ai.dart';

class CribbageAI {
  final HandAIEnum _handAIType;
  final PeggerAIEnum _peggerAIType;

  HandAI _handAI = RandomHandAI();
  PeggerAI _peggerAI = RandomPeggerAI();

  CribbageAI(this._handAIType, this._peggerAIType) {
    switch (_handAIType) {
      case HandAIEnum.Random:
        _handAI = new RandomHandAI();
        break;
      // TODO fill out all the types of ais
      default:
        _handAI = new RandomHandAI();
    }
    switch (_peggerAIType) {
      case PeggerAIEnum.Random:
        _peggerAI = new RandomPeggerAI();
        break;
      // TODO fill out all the types of ais
      default:
        _peggerAI = new RandomPeggerAI();
    }
  }
}
