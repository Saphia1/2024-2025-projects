# 2024-2025
# Project Index

Each folder below links to coursework or personal projects written in different languages/linking to different categories of computer science.
---

## Main Repository Folders

| Folder | Description | Tools/Languages|
|:-------|:-------------|:-------------|
| [AI](./AI) | Artificial intelligence projects and algorithms, Data Modelling, Data analysis | Python, matplotlib, numpy, pandas |
| [Architecture](./Architecture) | Computer architecture and systems design work: Created an ALU & an ARM instruction decoder| C, Hardware Description Language |
| [ARM-Assembly](./ARM-Assembly) | ARM Assembly language programs and exercises: mandelbrot generator, missing vowels program | ARM Assembly Language|
| [C](./C) | C programming coursework and experiments |
| [Databases-and-web-development](./Databases-and-web-development) | Database and web app development projects: Created a vehicle management web app with 3 different pages| HTML, CSS, JavaScript, SQL, Supasbase, Playwright|
| [Haskell](./Haskell) | Functional programming exercises in Haskell | Haskell|
| [Java](./Java) | Object-oriented programming projects in Java; Reversi game with Greedy AI | Java, Model-view-Controller, Java Standard Library (JDK) - AWT & Swing|
| [Networks](./Networks) | Created a client and server that implement both the standard and a modified QotD protocol (RFC 865) using C and the Berkeley sockets API |C, POSIX API, TCP(PIV4)|
| [Python](./Python) | Row Reducing program that shows each step | Pyhton, SymPy|

---

#  Red Wine Quality - AI Data Modelling & Analysis

This Jupyter Notebook analyses the **Red Wine Quality dataset** using data modelling and machine learning techniques covered in the **COMP1009/COMP1008 AI** module.

---

##  File
| File | Description |
|------|--------------|
| `Red-Wine-Quality-AI-data-modelling-and-analysis.ipynb` | Jupyter Notebook performing data cleaning, exploratory analysis, and supervised learning on the wine quality dataset. |

---

## Tools & Libraries
| Library | Purpose |
|----------|----------|
| **Python 3.10+** | Programming language |
| **Pandas** | Data manipulation and analysis |
| **NumPy** | Numerical operations |
| **Matplotlib / Seaborn** | Data visualisation |
| **Scikit-learn** | Machine learning models (e.g. linear regression, decision trees, random forest) |
| **Jupyter Notebook** | Interactive environment for experimentation |

---

## Project Overview
- Loads and explores the **Red Wine Quality dataset** (UCI Machine Learning Repository).  
- Performs **data cleaning** and **normalisation**.  
- Conducts **correlation analysis** and **feature importance** exploration.  
- Trains multiple models to predict **wine quality scores**.  
- Evaluates performance using accuracy and mean squared error metrics.  
- Visualises relationships between physicochemical properties and quality ratings.

---

##  Architecture

| Folder | Description |
|:--------|:-------------|
| [ALU](./Architecture/ALU) | Design and implementation of an Arithmetic Logic Unit, using logic gates and control signals to perform basic arithmetic and logical operations. |
| [Decoder](./Architecture/Decoder) | C program that can decode ARM instructions from their binary representation, generating a string containing the mneuomic you would feed an assembler |

---

##  ARM Assembly

| File / Folder | Description |
|:---------------|:-------------|
| [01-mandel.s](./ARM-Assembly/01-mandel.s) | ARM Assembly program generating a Mandelbrot using iterative arithmetic and register operations. |
| [Missing-vowels](./ARM-Assembly/Missing-vowels) | Assembly-based text processing program that removes vowels from a given string, demonstrating character manipulation and branching. |

---

# C Projects

| File / Folder | Description |
|:---------------|:-------------|
| [Cellular-automata](./C/Cellular-automata.c) | A simulation demonstrating how patterns evolve based on local rules. |
| [Drake-equation](./C/Drake-equation.c) | Implements the **Drake Equation** to estimate the number of communicative extraterrestrial civilizations. |
| [Data-structures-and-sorts](./C/Data-structures-and-sorts) | Implementations of data structures and sorting algorithms (e.g., linked lists, bubble sort, merge sort). |
| [Pascal-and-Greg](./C/Pascal-and-Greg) | Practice programs involving Pascal’s triangle and generating the Gregorian Calender date. |
| [Student-file-reading](./C/Student-file-reading) | File input/output exercises that read and process structured data such as student names, marks, or IDs. |

---

## Databases and Web Development - Vehicle Management Web App

This project implements a **Vehicle and People Management System** using **HTML**, **CSS**, **JavaScript**, and a **Supabase PostgreSQL database**.  

---

### Project Files

| File / Folder | Description |
|:---------------|:-------------|
| [addvehicle.html](./Databases-and-web-development/addvehicle.html) | Webpage allowing users to add a new vehicle, with fields for registration, make, model, colour, and owner. Includes validation and owner search functionality. |
| [vehicle.html](./Databases-and-web-development/vehicle.html) | Page to search for vehicle information by registration number, showing car and owner details, with error handling for missing or unknown data. |
| [peoplesearch.html](./Databases-and-web-development/peoplesearch.html) | Page to search for people by name or driving licence number, supporting partial and case-insensitive matches. |
| [style.css](./Databases-and-web-development/style.css) | Global stylesheet shared by all pages. Implements CSS Grid and Flexbox layouts, responsive design (width < 500px), and accessible colour contrast. |
| [addvehicle.js](./Databases-and-web-development/addvehicle.js) | JavaScript controlling form submission, Supabase integration, and owner validation when adding vehicles. |
| [vehicle.js](./Databases-and-web-development/vehicle.js) | Handles vehicle search queries, dynamically updates the DOM with search results, and provides validation feedback. |
| [peoplesearch.js](./Databases-and-web-development/peoplesearch.js) | Connects to Supabase via REST API to perform case-insensitive and partial matches on People data. Displays results dynamically. |
| [playwright.config.ts](./Databases-and-web-development/playwright.config.ts) | Playwright configuration file for running automated UI tests required by the coursework. |
| [tests/](./Databases-and-web-development/tests/) | Folder containing Playwright tests verifying input validation, search results, and database updates. |
| [1004additionalcoursework.md](./Databases-and-web-development/1004additionalcoursework.md) | Markdown report detailing additional HTML/CSS/JS/DB work, accessibility improvements, responsive layout, and test coverage. |

---


### Tools & Technologies

| Tool / Technology | Purpose |
|:------------------|:---------|
| **HTML5** | Front-end structure and semantics |
| **CSS3 (Flexbox, Grid, Media Queries)** | Styling and responsive layout |
| **JavaScript (ES6)** | Dynamic DOM updates and form logic |
| **Supabase (PostgreSQL)** | Cloud-hosted database for People and Vehicle tables |
| **Playwright** | End-to-end testing for HTML/JS features |
| **Node.js / npm** | Development environment and dependency management |

---

### Accessibility & Responsiveness

| Feature | Description |
|:----------|:-------------|
| **Accessibility (100%)** | Verified using Chrome Lighthouse; improvements include semantic HTML, labelled form inputs, and colour-contrast compliance. |
| **Responsive Design** | Page layout adapts under 500 px width: navigation becomes vertical, sidebar moves below main content. |

---

# Java
##  cw2cd Reversi Game with Greedy AI

---

##  Folder Structure

| File / Folder | Description |
|----------------|-------------|
| `ReversiMain.java` | Launches the game. Creates and links the model, view, and controller objects. |
| `GUIView.java` | The graphical user interface for the Reversi game. Displays two player boards with buttons for AI and restart. |
| `ReversiController.java` | The main game logic - handles valid moves, captures, player turns, and greedy AI. |
| `BoardSquareButton.java` | Custom button class that draws green squares and black/white discs, and notifies the controller when clicked. |
| `IModel.java`, `IView.java`, `IController.java` | Interface definitions for the MVC architecture - define what each component must implement. |
| `SimpleModel.java` / `SimpleTestModel.java` | Provided models that store the board state and game data. |
| `SimpleController.java` | Basic example controller (does not enforce rules). |
| `TextView.java` / `FakeTextView.java` | Text-based versions of the view for testing without GUI. |
| `TestYourController.java` / `TestYourGUIView.java` | Test harnesses for verifying your controller and GUI independently. |

---

##  Project Overview

This project implements a complete playable **Reversi (Othello)** game in **Java** using the **Model–View–Controller (MVC)** design pattern.

- **Model** stores the board state, player turns, and win conditions.  
- **View (GUIView)** displays the board graphically using `JFrame` and `JButton`.  
- **Controller (ReversiController)** enforces game rules, handles user moves, and implements a **Greedy AI** that captures the maximum possible pieces in one move.  

Two GUI windows display the board from each player's perspective (rotated 180°).

---

## Tools & Languages Used

| Tool / Library | Purpose |
|----------------|----------|
| **Java (JDK 17 or later)** | Primary programming language |
| **Swing / AWT** | GUI development (`JFrame`, `JButton`, `Graphics`, etc.) |
| **Eclipse** or **Visual Studio Code** | IDEs used for development |
| **JUnit (optional)** | Testing controller/view separately |
| **Interfaces (OOP)** | Enforce modular MVC structure |

---


#  Networks - Quotes of the Day (QotD) - TCP Clients & Servers

Implements the RFC 865 Quote of the Day protocol and a modified **Multi-Quote** variant.

---

## Folder structure

| File | Purpose |
|:-----|:--------|
| [`QuoteServer.c`](./QuoteServer.c) | **QotD server** (RFC 865 over TCP). Listens on **port 1717** (unprivileged replacement for 17). Sends one quote then closes. |
| [`QuoteClient.c`](./QuoteClient.c) | **QotD client**. Connects to server on 1717 and prints the quote. |
| [`MultiQuoteServer.c`](./MultiQuoteServer.c) | **Multi-Quote server** (modified protocol). Listens on **port 1818**; supports `ANOTHER`, `CLOSE`, invalid → `ERROR`. |
| [`MultiQuoteClient.c`](./MultiQuoteClient.c) | **Multi-Quote client**. Requests N quotes from server 1818 using `ANOTHER`, then sends `CLOSE`. |
| [`quotes`](./quotes) | Plain-text file of quotes (one per line). Passed to servers on the command line. |

---

##  Protocols

### Standard QotD (RFC 865, TCP)
- Server listens on **1717** (since 17 is privileged).
- On connection: send one quote terminated with CRLF (`\r\n`), then **close**.

### Multi-Quote (course variant)
- Server listens on **1818**.
- On connection: send first quote with CRLF, then wait for a command line:
  - `ANOTHER` → send next quote.
  - `CLOSE` → reply `BYE\r\n` and close.
  - Anything else → reply `ERROR\r\n` and continue waiting.


---

#  SymPy Row Reducer

A Python program implementing **row reduction** (Gaussian elimination) using the **SymPy** symbolic mathematics library.  

---

## File
| File | Description |
|------|--------------|
| `Rowreducer.py` | Uses SymPy to perform matrix row operations, calculate reduced row echelon form (RREF), and display intermediate steps. |

---

## Tools & Libraries
| Library | Purpose |
|----------|----------|
| **Python 3.10+** | Programming language |
| **SymPy** | Symbolic algebra, matrix manipulation, and RREF calculation |

---

## Project Overview
- Takes a user-defined matrix input.  
- Converts to SymPy `Matrix` object.  
- Applies Gaussian elimination / RREF computation.  
- Optionally displays the transformation process step-by-step.

---


