# Alea jacta est

## Aufgabenstellung

Wie Cäsar bereits wusste, werden wichtige Entscheidungen per Würfel
gefällt. Aus diesem Grund soll ein Würfel mit dem ESP-Board
implementiert werden.
Grundsätzlich stehen zwei Taster und eine LED-Matrix für die
Benutzerschnittstelle zur Verfügung. Ein Druck auf den linken Taster soll
den Würfel starten, worauf die LED-Matrix “rauschen” und nach einer
Sekunde eine zufällige Zahl darstellen soll. Das Rauschen können
verschiedene Zahlen sein, die immer langsamer warden bis eine Zahl
stehenbleibt oder zufälliges Rauschen.

Für den Cheat-Mode drückt man kurz den rechten Taster. Dann startet man
normal mit linkem Taster und erhält eine 6.
Als Quelle für den Zufall soll das RNG-Peripheriemodul des ESP32-C3
verwendet werden. Auf die Tastendrucke soll per Interrupt reagiert
werden.