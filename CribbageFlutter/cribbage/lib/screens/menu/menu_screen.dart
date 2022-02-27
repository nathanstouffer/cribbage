import 'package:flutter/material.dart';

class MenuScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        decoration: const BoxDecoration(
          image: DecorationImage(
            image: AssetImage("assets/images/portraitTable.jpg"),
            fit: BoxFit.cover,
          ),
        ),
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              GestureDetector(
                child: const Text("New Game"),
                onTap: () => _onNewGameTap(context),
              ),
              GestureDetector(
                child: const Text("Settings"),
                onTap: () => _onSettingsTap(context),
              ),
              GestureDetector(
                child: const Text("Statistics"),
                onTap: () => _onStatisticsTap(context),
              ),
            ],
          ),
        ),
      ),
    );
  }

  _onNewGameTap(BuildContext context) {
    Navigator.pushNamed(context, '/game');
  }

  _onSettingsTap(BuildContext context) {
    Navigator.pushNamed(context, '/settings');
  }

  _onStatisticsTap(BuildContext context) {
    Navigator.pushNamed(context, '/statistics');
  }
}
