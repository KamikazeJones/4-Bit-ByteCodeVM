# Project: 4-Bit-ByteCodeVM

## Ticket

Aktuelle Ticketnummer: **#10045**

> Hinweis: Bei jeder neuen Aufgabe oder Unteraufgabe wird diese Nummer
> hier inkrementiert und die neue Nummer der Aufgabe/Unteraufgabe
> im Namen zugeordnet (siehe [Developer-Manifest.md](Developer-Manifest.md)).

---

## Beschreibung

Ein Interpreter, Assembler, Linker und Debugger für einen 4-Bit-Bytecode.
Diese Projektdatei dient der Verwaltung von Tickets, Teilzielen und Aufgaben.

### Assembler für einen 4-Bit-Bytecode

Es wird ein Assembler geschrieben, der die folgenden 16 Memnonics kennt.

Jeder Bytecode‑Opcode ist 4 Bit lang (eine Nibble), also passen zwei Opcodes in ein Byte.
Werte auf dem Stack und beim Lesen und schreiben sind generell 8 Bit (1 Byte) lang.
Adressen werden als 2-Byte (little Endian) auf dem Stack angegeben.

Eine Besonderheit ist, dass der Assembler keine Leerzeichen benötigt, um die Token zu erkennen.
Opcodes sind entweder zweistellig (alphanumerisch), oder alternativ einstellig (Sonderzeichen).

der Opcode PS erwartet im folgenden Byte ein Byte codiert als zweistellige Hexadezimale Zahl.

Opcode‑Tabelle (Nibble → Opcode)

| Nibble | Symbol | Mnemonic | Beschreibung |
|--------|--------|----------|--------------|
| 0      | `$`    | PS       | push following byte (Imm8) to data stack |
| 1      | `<`    | SL       | (v -- 2*v) shift left (logical) |
| 2      | `>`    | SR       | (v -- v/2) shift right (logical) |
| 3      | `@`    | RD       | (adr -- val) pop adr → push mem[adr] |
| 4      | `!`    | WR       | (val adr -- ) pop val, pop adr → mem[addr]=val |
| 5      | `?`    | JZ       | (val adr -- ) pop val, pop adr → if val==0 then IP := adr |
| 6      | `+`    | AD       | (v1 v2 -- sum_low) pop a, pop b → berechne s = a + b + (implizites Carry).<br>Das niederwertige Byte von s (`s & 0xFF`) wird auf den Datenstack abgelegt. Bei einem Überlauf (s > 0xFF) setzt der Interpreter ein internes Carry‑Flag auf 1, sonst auf 0. |
| 7      | `=`    | DP       | (v -- v v) duplicate TOS |
| 8      | `/`    | DR       | (v -- ) drop TOS |
| 9      | `&`    | AN       | (v1 v2 -- v1 & v2) AND |
| A      | `|`    | OR       | (v1 v2 -- v1 | v2) OR |
| B      | `#`    | XR       | (v1 v2 -- v1 ^ v2) XOR |
| C      | `*`    | CL       | (adr -- /R: radr) CALL: pop adr; push return address on return stack; PC := adr |
| D      | `;`    | RT       | (/R: radr -- ) RET: return to radr |
| E      | `-`    | RESERVED | reserved / future |
| F      | `.`    | HL       | HALT, stops VM

Bemerkungen:
- `PS` (`$`) liest ein nachfolgendes Byte Imm8 und pusht diesen Wert auf den Datenstack.

Immediate‑/Nibble‑Encoding

- Zwei Opcodes pro Byte: High‑Nibble zuerst, dann Low‑Nibble.
- Wenn ein Opcode ein Immediate‑Byte benötigt (z.B. `PS`), 
  so folgt dieses Immediate immer als ganzes Byte unmittelbar nach dem Byte, das die 
  beiden Nibbles enthält.
  - Beispiel: Byte N enthält [OP1:high, OP2:low]. Wenn OP2 (low nibble) ein Imm8 benötigt, 
    dann ist Imm8 das nächste Byte (Byte N+1). Gleiches gilt, wenn OP1 ein Imm8 verlangt: 
    Imm8 kommt ebenfalls als nächstes Byte nach Byte N.
    Wenn sowohl OP1 als auch OP2 PS ist, so ist das Byte an Adresse N+1 der Wert für OP1 und das Byte an Adresse N+2 ist der Wert für OP2.

Stack‑ und Speicher‑Semantik

Wie genau der Datenstack realisiert ist, ist ein Implementierungsdetail, um das sich der Assembler nicht kümmern muss.


---

## Aktueller Stand

- Projekt initialisiert.
- Architektur, Module und erste Teilziele sind noch zu definieren.

---

## Teilziele

Teilziele mit ihren Aufgaben und Unteraufgaben inklusive zugehöriger Ticketnummern.

### [ ] #10014 Teilziel - schreibe enen Assembler für einen 4-Bit-Bytecode

Aufgaben:

#### [x] #10015 Beschreibe den Assembler
#### [ ] #10016 Implementiere den Assembler
- [x] #10017 erstelle einen enum für die 16 Opcodes ✅
- [x] #10018 helper-Funktionen für dynamisches Byte-Array erstellt
- [x] #10019 Test für dynamisches Byte-Array schreiben ✅
- [x] #10020 Prüfe und dokumentiere alle bisher ungerechtfertigten
  Dateiänderungen (entsprechende Einträge in Project.md ergänzen).
- [x] #10021 Verschiebe dyn_bytearray.h nach headers/ und passe Makefile +
  Includes an (inkl. Projekt­dokumentation) ✅
  - `dyn_bytearray.h` aus `modules/helpers` in `headers/` verschoben.
  - Makefile‑CFLAGS aktualisiert, um nur noch `-Iheaders` zu nutzen.
  - keine Quelländerung notwendig (Include-Pfade bleiben gleich).
- [x] #10022 Verschiebe test_interpreter.c nach test/interpreter und passe Makefile an ✅
  - neue Verzeichnisstruktur `test/interpreter` angelegt
  - Datei dorthin verschoben
  - `Makefile`-Variable `TEST_MAIN` und Regel für Objektdatei aktualisiert
- [x] #10023 Entferne Verzeichnis `test/` und konsolidiere in `tests/`; passe Makefile an ✅
  - `test/interpreter` nach `tests/` verschoben
  - altes `test/` gelöscht
  - `Makefile`-Referenzen (`TEST_MAIN` und Objektregel) angepasst
  - erneuter `make test` bestätigte funktionierenden Build
- [x] #10024 Ergänze einen weiteren dyn_bytearray-Test mit growth (initial 2, chunk 5); füge 1000 Elemente ein und prüfe Größe/Kapazität alle 103 Schritte ✅
- [x] #10025 Parameterisiere den growth-Test so, dass init, chunk, total und step
  als Argumente übergeben werden können; führe ihn mehrfach mit verschiedenen
  Wertepaaren aus.
- [ ] #10036 Teste den Assembler (assembler.c), analysiere die Fehler und behebe sie
  - Beschreibung: Tests für die Sprung‑Opcodes `JZ`, `CL` und `RT` wurden erstellt (Datei: `tests/assembler/test_jumps.c`).
  - Status: Testdatei angelegt; Tests zur Verifikation des Nibble‑Packings.
- [x] #10037 Zielname im Makefile angleichen ✅
    - Umbenennen des Binaries `assembler_test` in `test_assembler`
    - Anpassung der `all`/`test` Regeln und Verweise
- [x] #10038 Erstelle das Hauptprogramm für assembler. Es soll das Programm als Parameter entgegennehmen und entweder den Bytecode als Hexadezimale Zahlen auf die Konsole ausgeben oder aber bei Schalter -o den binären Code in eine Datei schreiben.
  - `modules/assembler/main.c` angelegt als Startpunkt
  - Lesen der Eingabedatei, Aufruf von `assemble()` und Ausgabe/`-o`-Option implementiert
  - Makefile wurde erweitert, um CLI‑Binary `assembler` zu bauen
  - gebaut wird es mit `make assembler` (oder einfach `make`)
- [x] #10041 In der Dokumentation hat der Assembler einige Optionen und Schalter. Dies muss noch implementiert werden
- [x] #10042 Der assembler lässt sich per make assembler nicht bauen. make clean funktioniert ebenfalls nicht. Das makefile scheint defekt zu sein.
  - Lösung: das Makefile wurde überarbeitet
- [x] #10043 assembler -s "PS 42 HL" gibt "assembly fail" aus
- [x] #10044 ./assembler -s 'PS $42 HL' muss einen Fehler ausgeben, da das Byte für das erste PS nicht angegeben wurde!

#### [ ] #10045 Präzisiere Rule-16: `Project.md` Ausnahme
- Beschreibung: Ergänze Rule-16 um den Satz, dass Änderungen an `Project.md` zur Ticketverwaltung nicht als zusätzliche Dateiänderung gelten.

#### [x] #10039 Erstelle eine Dokumentation für assembler mit mkdocs
  - `docs/assembler.md` erweitert: beschreibt nun Optionen `-c <datei>` und `-s|--source <string>`; Usage und Beispiele hinzugefügt

#### [x] #10040 Fix: mkdocs YAML Syntaxfehler in `docs/mkdocs.yml`
- Problem: `mkdocs serve` schlug fehl mit einer YAML-Parsing-Fehlermeldung (Tabulatorzeichen an Zeile 4).
- Lösungsansatz: Ersetze Tabulatoren durch Spaces in `docs/mkdocs.yml`, prüfe die YAML-Syntax und starte den `mkdocs`-Server neu, um die Doku zu verifizieren.
- die Dateien für mkdocs müssen in das Verzeichnis docs/docs

### [x] #10026 Teilziel - Tests für den Assembler machen

Aufgaben:
#### [x] #10027 definiere eine Schnittstelle für den Assembler
- `headers/assembler.h` mit enum, mnemonic struct und Aufrufprototypen erstellt
- `modules/assembler/assembler.c` referenziert nun den Header und enthält stub für assemble()

#### [x] #10029 Fehler: unerlaubte Assembler-Implementierung ✅
- kompletten Parsercode, der ohne Ticket entstanden war, zurückgesetzt
- Ticket dokumentiert und Ursachennotiz oben hinzugefügt

#### [x] #10028 Test: Programm als String - prüfe erzeugte Bytefolge
- neue Datei `tests/assembler/test_assembler.c` angelegt
- Test verwendet gültiges Programmstring ("$0F+AD") und prüft gegen
  erwartete Bytefolge; dieser Test wird zunächst fehlschlagen, bis Parser
  implementiert ist
- [x] #10032 HL-Mnemonic in Tests korrigieren ('.' statt 'F'), Kommentar anpassen ✅
- [x] #10033 Test angepasst so dass der buf über setUp und tearDown verwaltet wird.
- [x] #10034 Es gibt einen Compilerfehler: odules/assembler/assembler.c:108:5: error: redefinition of ‘assemble’
  - Der stub wurde entfernt, der Parser wurde aktiviert muss aber geprüft werden
- [x] #10035 make test compiliert nicht: "undefined reference to `main'  - Ergänze fehlende `main()` in `tests/assembler/test_assembler.c`
  - Füge RUN_TEST-Aufrufe für alle fünf Fälle hinzu
  - Testprogramm nach Änderung neu bauen und ausführen
  - Funktion test_assemble_invalid_program verschoben vor Aufruf

#### [x] #10030 Ergänze Developer Manifest ✅
- Der Agent öffnet für jede Arbeit, die direkt den Code betrifft, ein Ticket.
Beispiel: “#14711 Implementiere den Parser” – dort kann dann später der
Code stehen, der $0F+AD in die erwarteten Bytes übersetzt.

- Bevor der Agent eine Datei ändert, gibt er dem Anwender eine kurze Beschreibung:

  - Welches Problem löse der Agent?
  - Warum ist das nötig?
  - Was genau soll geändert oder ergänzt werden?
Der Anwender kann dann zustimmen oder zusätzliche Anforderungen nennen.

#### [x] #10031 In allen .md-Dateien und allen .c und .h Dateien LF verwenden, nicht CRLF ✅
Dies wurde manuell umgestellt per VS Code.

### [x] #10000 Teilziel – Einen Test mit unity.c erstellen ✅

mit "make test" bzw. "make TARGET=test_interpreter test" wir der Test test_interpreter compiliert und dann ausgeführt.

Aufgaben:

#### [x] #10001 unity test herunterladen ✅

- [x] #10002 unity.c und Header herunterladen und nach modules/unity kopieren ✅
- [x] #10003 unity.h und unity_internals.h nach headers kopieren ✅

#### [x] #10004 einen Test kompilieren ✅
    
#### [x] #10005 ein Makefile erstellen, um einen Test zu kompilieren ✅
    
- [x] #10006 In Zeile 26 gibt es einen Fehler im Makefile ✅
    - `$(CC) $(CFLAGS) -o $@ $^`
    - Lösung: In einem Makefile müssen alle Befehlszeilen mit einem echten TAB-Zeichen beginnen, nicht mit Leerzeichen.
    
- [x] #10007 Fehlermeldung ✅
    - make: *** No rule to make target 'modules/interpreter/unity.c', needed by 'build/unity.o'.  Stop.
    - Lösung: UNITY_SRC im Makefile geändert von modules/interpreter/unity.c nach modules/unity/unity.c
    
- [x] #10008 Fehlermeldung ✅
    - modules/unity/unity.c:8:10: fatal error: unity.h: No such file or directory
    - Lösung: Im makefile -Iheaders bei CFLAGS hinzugefügt: CFLAGS  := -std=c11 -Wall -Wextra -O2 -Iheaders

- [x] #10009 Erstelle alle benötigten Dateien für einen ersten Test ✅
    - [x] #10010 interpreter.c erstellen, mit Funktion, die zwei Zahlen addiert ✅
    - [x] #10011 interpreter.h erstellt mit add-Funktion ✅
    - [x] #10012 test_interpreter.c ruft add auf ✅

- [x] #10013 Makefile so erweitern, dass eine ausführbare Datei erstellt wird ✅
    - Lösung: Im makefile ist als TARGET test_interpreter angegeben.
    - Außerdem gibt es das Ziel test, dass das TARGET ausführt.
    - make test führt demnach test_interpreter aus.
    - Es sollte so gepflegt werden, dass make test alle Tests ausführt.