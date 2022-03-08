enum Suit { clubs, diamonds, hearts, spades }
enum Value {
  ace,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  ten,
  jack,
  queen,
  king
}

class Card {
  final Value _value;
  final Suit _suit;

  Card(this._value, this._suit);

  bool operator <(Card card) {
    return _value.index < card._value.index;
  }

  int pips() {
    switch (_value) {
      case Value.ace:
        return 1;
      case Value.two:
        return 2;
      case Value.three:
        return 3;
      case Value.four:
        return 4;
      case Value.five:
        return 5;
      case Value.six:
        return 6;
      case Value.seven:
        return 7;
      case Value.eight:
        return 8;
      case Value.nine:
        return 9;
      case Value.ten:
        return 10;
      case Value.jack:
        return 10;
      case Value.queen:
        return 10;
      case Value.king:
        return 10;
    }
  }

  String valueStr() {
    switch (_value) {
      case Value.ace:
        return "ace";
      case Value.two:
        return "two";
      case Value.three:
        return "three";
      case Value.four:
        return "four";
      case Value.five:
        return "five";
      case Value.six:
        return "six";
      case Value.seven:
        return "seven";
      case Value.eight:
        return "eight";
      case Value.nine:
        return "nine";
      case Value.ten:
        return "ten";
      case Value.jack:
        return "jack";
      case Value.queen:
        return "queen";
      case Value.king:
        return "king";
    }
  }

  String suitStr() {
    switch (_suit) {
      case Suit.clubs:
        return "clubs";
      case Suit.diamonds:
        return "diamonds";
      case Suit.hearts:
        return "hearts";
      case Suit.spades:
        return "spades";
    }
  }

  String toCompactString() {
    String ret = "";
    switch (_value) {
      case Value.ace:
        ret += "A";
        break;
      case Value.jack:
        ret += "J";
        break;
      case Value.queen:
        ret += "Q";
        break;
      case Value.king:
        ret += "K";
        break;
      default:
        ret += pips().toString();
        break;
    }
    ret += " ";
    switch (_suit) {
      case Suit.clubs:
        ret += ":\u200d";
        break;
      case Suit.diamonds:
        ret += "D";
        break;
      case Suit.hearts:
        ret += "H";
        break;
      case Suit.spades:
        ret += "S";
        break;
    }
    return ret;
  }

  String toPrettyString() {
    String ret = "";
    switch (_value) {
      case Value.ace:
        ret += "A";
        break;
      case Value.jack:
        ret += "J";
        break;
      case Value.queen:
        ret += "Q";
        break;
      case Value.king:
        ret += "K";
        break;
      default:
        ret += pips().toString();
        break;
    }
    ret += " ";
    switch (_suit) {
      case Suit.clubs:
        ret += "♣";
        break;
      case Suit.diamonds:
        ret += "♦";
        break;
      case Suit.hearts:
        ret += "♥";
        break;
      case Suit.spades:
        ret += "♠";
        break;
    }
    return ret;
  }

  @override
  String toString() {
    return valueStr() + " " + suitStr();
  }

  Value getValue() {
    return _value;
  }

  Suit getSuit() {
    return _suit;
  }
}
