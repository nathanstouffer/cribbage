import 'package:flutter/material.dart';
import 'package:cribbage/models/game/game.dart';
import 'package:cribbage/screens/game/card_button.dart';

class GameScreen extends StatelessWidget {
  final Game _game = Game();

  GameScreen({Key? key}) : super(key: key) {
    _game.deal();
  }

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
        child: Column(
            mainAxisAlignment: MainAxisAlignment.start,
            crossAxisAlignment: CrossAxisAlignment.end,
            children: [
              Container(
                margin: const EdgeInsets.fromLTRB(0.0, 50.0, 10.0, 0.0),
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.end,
                  crossAxisAlignment: CrossAxisAlignment.end,
                  children: [
                    Text("dealer: " +
                        (_game.humanDealer() ? "you" : "computer")),
                    Text("computer score: " + _game.compScore().toString()),
                    Text("your score: " + _game.humanScore().toString())
                  ],
                ),
              ),
              Column(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        crossAxisAlignment: CrossAxisAlignment.center,
                        children: computerCards(_game)),
                    Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        crossAxisAlignment: CrossAxisAlignment.center,
                        children: humanCards(_game)),
                  ]),
            ]),
      ),
    );
  }

  List<Widget> computerCards(Game game) {
    return game.computerCards().map((card) => CardButton(card)).toList();
  }

  List<Widget> humanCards(Game game) {
    return game.humanCards().map((card) => CardButton(card)).toList();
  }
}
