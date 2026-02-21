# Project: 4-Bit-ByteCodeVM

## Ticket

Aktuelle Ticketnummer: **#10013**

> Hinweis: Bei jeder neuen Aufgabe oder Unteraufgabe wird diese Nummer
> hier inkrementiert und die neue Nummer der Aufgabe/Unteraufgabe
> im Namen zugeordnet (siehe [Developer-Manifest.md](Developer-Manifest.md)).

---

## Beschreibung

Ein Interpreter, Assembler, Linker und Debugger für einen 4-Bit-Bytecode.
Diese Projektdatei dient der Verwaltung von Tickets, Teilzielen und Aufgaben.

---

## Aktueller Stand

- Projekt initialisiert.
- Architektur, Module und erste Teilziele sind noch zu definieren.

---

## Teilziele

Teilziele mit ihren Aufgaben und Unteraufgaben inklusive zugehöriger Ticketnummern.

### Teilziel – Einen Test mit unity.c erstellen ✅

mit "make test" bzw. "make TARGET=test_interpreter test" wir der Test test_interpreter compiliert und dann ausgeführt.

Aufgaben:

#### [x] #10001 unity test herunterladen ✅

- [x] #10002 unity.c und Header herunterladen und nach modules/unity kopieren ✅
- [x] #10003 unity.h und unity_internals.h nach headers kopieren ✅

#### [x] #10004 einen Test kompilieren ✅
    
### [x] #10005 ein Makefile erstellen, um einen Test zu kompilieren ✅
    
- [x] #10006 In Zeile 26 gibt es einen Fehler im Makefile ✅
    - $(CC) $(CFLAGS) -o $@ $^
    - Lösung: In einem Makefile müssen alle Befehlszeilen mit einem echten TAB-Zeichen beginnen, nicht mit Leerzeichen.
    
- [x] #10007 Fehlermeldung ✅
    - make: *** No rule to make target 'modules/interpreter/unity.c', needed by 'build/unity.o'.  Stop.
    - Lösung: UNITY_SRC im Makefile geändert von modules/interpreter/unity.c nach modules/unity/unity.c
    
- [x] #10008 Fehlermeldung ✅
    - modules/unity/unity.c:8:10: fatal error: unity.h: No such file or directory
    - Lösung: Im makefile -Iheaders bei CFLAGS hinzugefügt: CFLAGS  := -std=c11 -Wall -Wextra -O2 -Iheaders

- [x] #10009 Erstelle alle benötigten Dateien für einen ersten Test ✅
    - [x] #10010 interpreter.c erstellen, das zwei zahlen addiert ✅
    - [x] #10011 interpreter.h erstellt mit add-Funktion ✅
    - [x] #10012 test_interpreter.c ruft add auf ✅

- [x] #10013 Makefile so erweitern, dass eine ausführbare Datei erstellt wird ✅
    - Lösung: Im makefile ist als TARGET test_interpreter angegeben.
    - Außerdem gibt es das Ziel test, dass das TARGET ausführt.
    - make test führt demnach test_interpreter aus.
    - Es sollte so gepflegt werden, dass make test alle Tests ausführt.