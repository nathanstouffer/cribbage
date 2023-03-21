import 'dart:core';

import 'package:flutter/material.dart';
import '../../models/deck/card.dart'
    as cb; // prefix to avoid name conflict with Card in material package

class CardButton extends StatelessWidget {
  static const double cCardHeight = 80.0;
  static const double cCardAspect = 0.70454545454;
  static const double cFontSize = 22.5;

  final cb.Card mCard;

  const CardButton(this.mCard, {Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: const EdgeInsets.fromLTRB(3.0, 30.0, 3.0, 30.0),
      decoration: const BoxDecoration(
        borderRadius: BorderRadius.all(Radius.circular(8)),
        image: DecorationImage(
          image: AssetImage("assets/images/whiteRectangle.png"),
          fit: BoxFit.fill,
        ),
      ),
      child: Center(
        child: SizedBox(
          height: CardButton.cCardHeight,
          width: CardButton.cCardAspect * CardButton.cCardHeight,
          child: Center(
            child: Stack(children: <Widget>[
              Text(
                mCard.toPrettyString(),
                style: TextStyle(
                    fontSize: CardButton.cFontSize,
                    foreground: Paint()
                      ..style = PaintingStyle.stroke
                      ..strokeWidth = 3
                      ..color = Colors.grey),
              ),
              Text(mCard.toPrettyString(),
                  style: TextStyle(
                      fontSize: CardButton.cFontSize, color: mCard.getColor())),
            ]),
          ),
        ),
      ),
    );
  }
}
