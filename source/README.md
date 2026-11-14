# Notepad - refactorizare modulara (C++ / WinBGIm)

## Componente

- `TextDocument`: liniile de text, inserare si stergere.
- `TextCursor`: pozitia cursorului; **singurul** `setPosition` din proiect.
- `TextEditor`: operatii de editare si navigare de la tastatura; **fara** `setCursorPosition`.
- `InputManager`: citeste tastatura si mouse-ul, apeleaza `TextCursor::setPosition` pentru click-uri.
- `EditorLayout`: conversii (row, col) <-> (x, y) folosind latimea textului GDI.
- `TextRenderer`: desenare + masurare UTF-8 prin GDI/`TextOutW`.
- `MenuBar`: bara File/Edit/View si tratarea clickurilor de meniu.
- `SubMenu`: componenta vizuala reutilizabila pentru orice lista de optiuni.
- `LanguageManager`: incarca limbile din `config.txt` si retine selectia.
- `Geometry.h`, `Utf8.*`, `AppStyle.h`: tipuri si utilitare.
- `RenderWindow`: fereastra graphics.h si ordonarea desenarii.

## Cum rulezi

1. Adauga toate fisierele `.cpp` si `.h` in proiectul Visual Studio existent, pastrand configuratia WinBGIm.
2. Seteaza standardul C++17 (pentru `std::make_unique`, `std::clamp`).
3. Copiaza `config.txt` in **Working Directory** (de obicei directorul proiectului).
4. Build si Run. `Escape` inchide aplicatia.

## Implementat

- Submeniu View cu limbile din fisier, marcaj pentru limba activa, click in afara pentru inchidere.
- Meniul isi calculeaza latimile in functie de traduceri.
- Click in editor pentru mutarea cursorului, inclusiv intre caractere / final de rand.
- Randare Unicode GDI pentru interfata, folosind fontul Consolas.
- Miscare stanga/dreapta si stergere pe limite UTF-8 pentru continut deja existent.
- Fereastra redimensionabila ca in proiectul precedent.

## Limitari importante

- GDI este desenat **direct pe HDC al ferestrei WinBGIm**, nu intr-un buffer comun. Aceasta este o integrare simpla, nu un pipeline GDI robust pe `WM_PAINT`; in functie de WinBGIm pot aparea flicker / artefacte la resize sau repictare.
- Tastatura citita prin `getch()` accepta doar caractere ASCII printabile; introducerea textului cu diacritice necesita un mecanism Unicode pentru input (de exemplu `WM_CHAR`/`WM_UNICHAR`).
- File si Edit sunt deocamdata butoane vizuale fara comenzi, ca in versiunea initiala.
- Nu am putut compila in acest mediu dependintele WinBGIm/Windows; trebuie testat in Visual Studio.
