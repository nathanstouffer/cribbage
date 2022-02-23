// Copyright 2018 The Flutter team. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'package:flutter/material.dart';
import 'screens/game/game.dart';
import 'screens/menu/menu.dart';
import 'screens/settings/settings.dart';
import 'screens/statistics/statistics.dart';

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
        '/': (context) => Menu(),
        '/game': (context) => Game(),
        '/settings': (context) => Settings(),
        '/statistics': (context) => Statistics(),
      },
      // theme: // TODO make the theme
    );
  }
}
