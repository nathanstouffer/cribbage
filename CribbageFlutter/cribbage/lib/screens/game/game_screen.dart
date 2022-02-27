import 'package:flutter/material.dart';
import 'package:cribbage/screens/game/card_button.dart';

// TODO I think delete this import
import 'package:cribbage/models/deck/card.dart' as cb;

class GameScreen extends StatelessWidget {
  //final Game game;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.transparent,
        elevation: 0.0,
      ),
      extendBodyBehindAppBar: true,
      body: Container(
        decoration: const BoxDecoration(
          image: DecorationImage(
            image: AssetImage("assets/images/portraitTable.jpg"),
            fit: BoxFit.cover,
          ),
        ),
        child: Center(
          child: Column(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: computerCards(),
                ),
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: playerCards(),
                ),
              ]),
        ),
      ),
    );
  }

  //List<Widget> computerCards(Game game) {
  List<Widget> computerCards() {
    //game.computerCards.map((card) => )
    return [
      CardButton(cb.Card(cb.Value.ace, cb.Suit.clubs)),
      CardButton(cb.Card(cb.Value.ace, cb.Suit.clubs)),
      CardButton(cb.Card(cb.Value.ace, cb.Suit.clubs))
    ];
  }

  //List<Widget> playerCards(Game game) {
  List<Widget> playerCards() {
    return [
      CardButton(cb.Card(cb.Value.two, cb.Suit.hearts)),
      CardButton(cb.Card(cb.Value.two, cb.Suit.hearts)),
      CardButton(cb.Card(cb.Value.two, cb.Suit.hearts))
    ];
  }
}
