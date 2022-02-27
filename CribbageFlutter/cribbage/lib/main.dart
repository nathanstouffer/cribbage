// Copyright 2018 The Flutter team. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'package:flutter/material.dart';
import 'screens/game/game_screen.dart';
import 'screens/menu/menu_screen.dart';
import 'screens/settings/settings_screen.dart';
import 'screens/statistics/statistics_screen.dart';

void main() {
  runApp(const App());
}

class App extends StatelessWidget {
  const App({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      initialRoute: '/',
      routes: {
        '/': (context) => MenuScreen(),
        '/game': (context) => GameScreen(),
        '/settings': (context) => SettingsScreen(),
        '/statistics': (context) => StatisticsScreen(),
      },
      // theme: // TODO make the theme
    );
  }
}
