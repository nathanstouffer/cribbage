import 'dart:core';
import 'dart:ffi';

import 'package:flutter/material.dart';
import '../../models/deck/card.dart'
    as cb; // prefix to avoid name conflict with Card in material package

class CardButton extends StatelessWidget {
  static const double cardHeight = 80.0;
  static const double cardAspect = 0.70454545454;

  final cb.Card mCard;

  CardButton(this.mCard);

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: const EdgeInsets.all(3.0),
      decoration: const BoxDecoration(
        borderRadius: BorderRadius.all(Radius.circular(8)),
        image: DecorationImage(
          image: AssetImage("assets/images/whiteRectangle.png"),
          fit: BoxFit.fill,
        ),
      ),
      child: Center(
        child: Container(
          height: CardButton.cardHeight,
          width: CardButton.cardAspect * CardButton.cardHeight,
          child: Center(child: Text(mCard.toPrettyString())),
        ),
      ),
    );
  }
}
