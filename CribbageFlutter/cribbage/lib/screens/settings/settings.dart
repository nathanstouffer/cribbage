import 'package:flutter/material.dart';

class Settings extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Colors.transparent,
        bottomOpacity: 0.0,
        //elevation: 0.0,
      ),
      body: Center(
        child: Text("Settings"),
      ),
    );
  }
}
