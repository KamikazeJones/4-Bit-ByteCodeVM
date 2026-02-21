Developer Manifest
=====================

Wir definieren ein paar Regeln, die es im folgenden zu beachten gilt:

1. Es gibt eine Projektdatei für das Projekt im Markdown-Format.
   der Name heißt immer "Project.md".
   Hier wird eine globale Ticketnummer im Abschnitt "Ticket" für das Projekt verwaltet.
   Wird eine neue Aufgabe oder Unteraufgabe definiert, so wird 
   die Ticketnummer im Abschnitt "Ticket" an dieser einen Stelle hochgezählt und dann der Aufgabe bzw. Unteraufgabe zugeteilt in der Projektdatei zugeteilt (Diese Änderungen erfolgen ohne ein eigenes Ticket und sind atomar.)
   Die Zuteilung erfolgt über den Zusatz #<Ticketnummer> im Namen der Aufgabe bzw. Unteraufgabe.
   Jede Codeänderung erfordert eine eigene Aufgabe oder Unteraufgabe und damit auch ein eigenes Ticket!


2. Im Abschnitt "Beschreibung" steht, was wir programmieren wollen.
   Dies ist eine grobe Zusammenfassung.

3. Es gibt einen Abschnitt "Aktueller Stand". 
   Dort wird beschrieben, was wir bisher programmiert haben, und 
   welche Schalter und Optionen es gibt, und wie man das Programm verwenden kann.

4. Es gibt einen oder mehrer Abschnitte die mit "Teilziel - " beginnen gefolgt von einem
   geeigneten Namen.

   Um das Ziel zu erreichen, definieren wir in diesen Abschnitten geeignete Teilziele.
   Wir protokollieren, wenn wir Teilziele erreicht haben.
   Zu jedem Teilziel gibt es ein oder mehrere Aufgaben, die einen geeigneten Namen haben.
   Hier wird präzise definiert, was die Aufgabe ist, und woran wir erkennen, dass die Aufgabe gelöst ist.
   
5. Unteraufgaben:
   Eine Aufgabe kann nochmal in Unteraufgaben unterteilt werden.
   Der Umfang eine Unteraufgabe ist max. 20 Zeilen Code und sollte trivial zu lösen sein.
   Falls sich die Unteraufgabe nicht trivial lösen lässt, muss die Aufgabe in noch mehr einfachere Unteraufgaben unterteilt werden.

6. Zu jeder Aufgabe und zu jedem Teilziel schreiben wir Tests, bevor wir mit dem 
   Programmieren beginnen!

   Dazu definieren wir im Abschnitt der Aufgabe bzw. im Abschnitt des Teilziels eine API,gegen die wir testen wollen. 
   Die API sollte so gewählt sein, dass sie sich nach dem Lösen der Aufgabe bzw. dem Teilziel nicht mehr ändert. Denn jede Änderung der API macht Änderungen an den Tests notwendig, und das ist ein Einfallstor für Fehler.

7. Programmiert wird immer nur an genau einer Aufgabe oder Unteraufgabe.

8. Umgang mit Fehlern I
   Werden Fehler in anderen Teilzielen festgestellt, dh. funktioniert die API eines
   anderen Teilziels oder einer anderen Aufgabe nicht korrekt, so wird das im entsprechenden
   Abschnitt mit einem Zeitstempel und mit einer neuen #<Ticketnummer> notiert.
   Die Ticketnummer wird dazu entsprechend im Projekt hochgezählt wie gehabt.

   Es wird dann eine neue Aufgabe für das Teilziel erstellt.
   Diese Aufgabe umfasst das erstellen eines neuen Tests, der diesen Fehler reproduziert.
   Anschließend wird der Fehler korrigiert, ggf. in meheren Unteraufgaben.
   Ist der Fehler korrigiert, so wird der Fehler als gelöst gekennzeichnet.
   Die Aufgabe ist dann als erledigt zu kennzeichnen, ebenso die dazugehörigen Unteraufgaben.
   
9. Umgang mit Fehler II
   Kommt es zu Fehlern, die eine Änderung einer zuvor definierten API erforderlich machen,
   so ist abzuwägen, wie umfangreich die Änderungen sind, die dies nach sich zieht.
   Umfangreiche Änderungen sind unbedingt zu vermeiden!
   Oftmals ist es einfacher & sicherer, eine neu API zu erstellen, als eine bestehende zu erweitern.

10. Tickets
    Eine Änderung in einer Datei erfordert ein Ticket.
    Es werden immer nur Änderungen an einer einzigen Datei auf einmal durchgeführt.
    Änderungen an mehereren Dateien erfordern eigene Tickets. Diese sollten dann in der Aufgabe oder Unteraufgabe neben dem Ticket auch das zugehörige Hauptticket referenzieren in der Aufgabe oder Unteraufgabe.

    Über die Tickets wird der sequentielle Fortschritt des Projekts protokolliert.

11. Bitte halte Dich im Zweifel an die Design-Prinzipien 
    - KISS (Keep it Simple, Stupid)
    sowie
    - DRY (Don't Repeat Yourself)

12. Modulabhängigkeiten
    Erstelle und Pflege einen gerichteten Graphen, aus dem die Abhängigkeiten der
    Module untereinander hervorgehen. 

    Module dürfen nur Methoden der API eines anderen Moduls verwenden!
    Die bereitgestellten API-Methoden werden im Unterverzeichnis docs seperat dokumentiert.

13. Die Dokumentation erfolgt über mkdocs im Unterverzeichnis docs.
    Änderungen an der API erfordern immer nach der Erledigung auch ein weitere Unteraufgabe mitsamt Ticket, in der die Dokumentation unter docs angepasst wird!
    In der Dokumentation wird das Ticket referenziert, welches die Aufgabe/Unteraufgabe
    erledigt hat, nicht das Ticket zu Änderung der Dokumentation! 
