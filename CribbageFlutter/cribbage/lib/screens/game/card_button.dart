import 'package:flutter/material.dart';
import '../../models/deck/card.dart'
    as cb; // prefix to avoid name conflict with Card in material package

class CardButton extends StatelessWidget {
  final cb.Card mCard;

  CardButton(this.mCard);

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: const BoxDecoration(
        image: DecorationImage(
          image: AssetImage("assets/images/whiteRectangle.png"),
          fit: BoxFit.fill,
        ),
      ),
      child: Center(
        child: Text(mCard.toCompactString()),
      ),
    );
  }
}
