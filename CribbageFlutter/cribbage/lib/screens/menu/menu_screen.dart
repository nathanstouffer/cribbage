import 'package:flutter/material.dart';

class MenuScreen extends StatelessWidget {
  const MenuScreen({Key? key}) : super(key: key);

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
            // TODO see if we can get these to be TextButtons
            children: <Widget>[
              GestureDetector(
                child: const Text("New Game", style: TextStyle(fontSize: 20)),
                onTap: () => _onNewGameTap(context),
              ),
              const SizedBox(height: 30),
              GestureDetector(
                child: const Text("Settings", style: TextStyle(fontSize: 20)),
                onTap: () => _onSettingsTap(context),
              ),
              const SizedBox(height: 30),
              GestureDetector(
                child: const Text("Statistics", style: TextStyle(fontSize: 20)),
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
