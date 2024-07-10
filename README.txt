In der Testing-Klasse sind für alle Klassen Tests eingebaut, die das Rechnen, Angreifen von Servern oder Senden von Nachrichten modellieren können.
Die Tests können nach Bedarf abgewandelt und unten in der Main-Funktion ein- bzw ausgeschaltet werden.

void testFp()
Testet das Rechnen im Körper Fp und alle implementierten Operationen.

void testEC()
Testet das Rechnen in der Gruppe der elliptischen Kurven, sowie die Ausgabe der Ordnung bzw. der Gruppenelemente. 
Die Ordnung wird hier nicht durch Schoof, sondern mit Eulers Kriterium berechnet, für große Primzahlen ist die Laufzeit deswegen relativ hoch.

void testAttack1()
Simuliert einen Angriff auf einen Server mit einer elliptischen Kurve über dem Körper F73.

void testAttack2()
Simuliert einen Angriff auf einen Server mit einer elliptischen Kurve über dem Körper F12347.

void testArithmetic()
Testet den Chinesischen Restsatz.

void testSending() 
Testet das verschlüsselte Senden einer Nachricht. 
Um Nachrichten von einer größeren Länge zu verschlüsseln, muss auch der "randoms"-Vektor verlängert werden.