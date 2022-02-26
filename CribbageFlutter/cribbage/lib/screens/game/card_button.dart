import 'package:flutter/material.dart';
import '../../models/deck/card.dart';

class CardButton extends StatelessWidget {
  //final Card card;

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: const BoxDecoration(
        image: DecorationImage(
          image: AssetImage("assets/images/whiteRectangle.png"),
          fit: BoxFit.fill,
        ),
      ),
      child: const Center(
        child: Text("tmp"),
      ),
    );
  }
}
