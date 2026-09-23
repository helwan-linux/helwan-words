# Helwan Words — Project Files Documentation

## Project Structure

```text
helwan-words/
├── src/
│   ├── main.c
│   ├── game.c
│   ├── game.h
│   ├── ui.c
│   ├── ui.h
│   ├── help.h
│   └── about.h
│
├── data/
│   ├── ar.txt
│   ├── en.txt
│   ├── es.txt
│   └── icons/
│       └── helwan-words.png
│
├── resources/
│   └── helwan-words.css
│
├── helwan-words.desktop
├── Makefile
├── PKGBUILD
├── LICENSE
└── README
```

## File Description

| File                          | Description and Function                                                                                                                                                                                                                       |
| ----------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `src/main.c`                  | **Application entry point.** Creates the GTK application using the `org.helwanlinux.words` application ID and starts the main user interface.                                                                                                  |
| `src/game.c`                  | **Core game logic.** Handles word selection, letters, attempts, win/loss conditions, scoring, and the main gameplay mechanics.                                                                                                                 |
| `src/game.h`                  | **Game engine interface.** Contains the declarations and definitions required by the user interface to communicate with the game logic.                                                                                                        |
| `src/ui.c`                    | **Main user interface.** Creates the game window, buttons, labels, language controls, and game layout. It also loads word lists, CSS, and icons, handles language direction including RTL Arabic, and connects user actions to the game logic. |
| `src/ui.h`                    | **User interface interface.** Provides the declarations required by `main.c` and other source files to create and interact with the game's UI.                                                                                                 |
| `src/help.h`                  | **Help system.** Contains the help window and information explaining how to play Helwan Words.                                                                                                                                                 |
| `src/about.h`                 | **About dialog.** Provides information about Helwan Words, its version, developer information, and the game's logo/icon.                                                                                                                       |
| `data/ar.txt`                 | **Arabic word database.** Contains the Arabic words used by the game.                                                                                                                                                                          |
| `data/en.txt`                 | **English word database.** Contains the English words used by the game.                                                                                                                                                                        |
| `data/es.txt`                 | **Spanish word database.** Contains the Spanish words used by the game.                                                                                                                                                                        |
| `data/icons/helwan-words.png` | **Main application icon.** Used for the game application, About dialog, desktop integration, and installed application icon.                                                                                                                   |
| `resources/helwan-words.css`  | **User interface styling.** Defines the application's colors, backgrounds, text appearance, buttons, button states, word display, and other GTK3 visual styling.                                                                               |
| `helwan-words.desktop`        | **Desktop integration file.** Defines the application name, descriptions, executable command, icon, categories, and other desktop-entry information so Helwan Words appears correctly in the desktop application menu.                         |
| `Makefile`                    | **Build and installation system.** Compiles the C source files, links GTK3, creates the `helwan-words` executable, and installs the executable, desktop entry, icon, CSS, and word databases into their appropriate system locations.          |
| `PKGBUILD`                    | **Arch/Helwan Linux package definition.** Defines the package name, version, dependencies, source repository, build process, and installation process for creating an Arch-compatible package.                                                 |
| `LICENSE`                     | **Project license.** Defines the legal terms under which Helwan Words can be used, modified, and distributed.                                                                                                                                  |
| `README`                      | **Project documentation.** Provides information about Helwan Words, its purpose, features, building, installation, usage, and contribution information.                                                                                        |

## Role of Each Part

The project is intentionally divided into simple components:

* **`game.c`** — The game engine and rules.
* **`ui.c`** — The graphical interface and user interaction.
* **`data/`** — Game content such as word lists and the application icon.
* **`resources/`** — Visual styling.
* **`main.c`** — Application startup.
* **`help.h`** — Player instructions.
* **`about.h`** — Application information.
* **`Makefile`** — Compilation and installation.
* **`PKGBUILD`** — Arch/Helwan Linux packaging.
* **`helwan-words.desktop`** — Desktop environment integration.
* **`LICENSE`** — Legal licensing information.
* **`README`** — Project documentation.

## Design Philosophy

Helwan Words keeps its structure deliberately simple.

The game logic, user interface, game data, visual styling, and packaging are separated into clear components so that contributors can improve one part of the project without having to understand the entire codebase.

This structure also makes it easier for the Helwan Linux community to contribute new words, languages, features, translations, visual improvements, and gameplay enhancements over time.
